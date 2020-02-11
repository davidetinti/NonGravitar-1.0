#pragma once
#include "Nave.hpp"

struct bunker{
    int type;
    int damage;
    double x;
    double y;
    double life;
    double explosion_x;  //posizione del frame nell'animazione dell'esplosione
    double boss_bunker_offset;
    bool exist;
    bool is_red;
    Sprite bunker_sprite;
    Sprite explosion;
    Bullets *weapon;
    Clock last_hit;
    
    /**
     Costruttore della lista di bunker per la schermata corrrente.
     
     @param type_n tipo d bunker, 0 = bunker con rotazione bloccata, 1 = bunker con rotazione attivata, segue il giocatore
     @param x_n coordinata x della posizione
     @param y_n coordinta y della posizione
     @param life_n punti vita del bunker
     @param weapon_n puntatore all'arma da assegnare al bunker
     @param b texture del bunker
     @param e texture dell'esplosione
     @param boss_bunker_offset offset per il posizionamento sul boss
     */
    bunker(int type_n, double x_n, double y_n, double life_n,
               Bullets *weapon_n, Texture *b, Texture *e, double boss_bunker_offset = 0);
    
    /**
     Inizializza le sprite del bunker e della rispettiva esplosione.
     
     @param bunker_tx texture del bunker
     @param explosion_tx texture dell'esplosione
     */
    void spriteSetup(Texture *bunker_tx,Texture *explosion_tx);
};

class Bunkers{

protected:
    
    int const DEFAULT_TIME_BTW_SHOOT = 2000;
    int const DEFAULT_DAMAGE_SINGLE = 30;
    int const DEFAULT_DAMAGE_TRIPLE = 20;
    int const DEFAULT_SPEED = 3;
    int const HIT_TIMER_MS = 100;
    
    double partial_x[4]; // coordinate per la griglia dei bunker
    Resources *src;
    Texture *bunker_tx;
    Texture *explosion_tx;
    Texture *bunker_tx2;
    list<bunker>* bunkers;
    
public:
    
    Clock bunkerDamage; //tempo passato dall'ultimo colpo subito
    
    /**
     Costruttore base.
     */
    Bunkers();
    
    /**
     Costruttore avanzato.
     Genera i bunker da associare alla schermata corrente.
     
     @param src puntatore all'utility class Resources
     @param terrain puntatore al terreno della schermata corrente
     */
    Bunkers(Resources *src, Terrain *terrain);
      
    /**
     @return true se la lista di bunker è vuota, false altrimenti
     */
    bool isEmpty();
    
    /**
     Gestisce i proiettili del bunker passato come argomenti, creandone di nuovi, muovendoli ed eliminandoli se necessario.
     
     @param tmp bunker del quale gestire le armi
     @param terrain terreno della schermata corrente
     */
    void handleWeapons(bunker *tmp, Terrain *terrain);
	
    /**
     Infligge danno al bunker passato come argomento.
     
     @param damage quantità danno inflitto
     @param p bunker al quale infliggere danno
     */
    void hitBunker(int damage, list<bunker>::iterator p);
	
    /**
     Elimina il bunker dalla lista e genera un animazione al suo posto.
     
     @param it bunker da eliminare
     
     @return bunker successivo a quello eliminato nella lista
     */
    list<bunker>::iterator deleteBunker(list<bunker>::iterator it);
	
    /**
     Gestione globale della lista di bunker, ne vengono gestiti i movimenti, punti salute e proiettili.
     
     @param player puntatore al giocatore
     @param terrain puntatore al terreno della schermata
     */
    void handle(Nave *player, Terrain *terrain);
    
    int checkCollisionBBullets(FloatRect obj);
    
    /**
     Verifica le collisioni tra i bunker della lista e i proiettili della classe passata come argomento.
     
     @param b classe contenente i proiettili da verificare
     
     @return true se almeno un proiettile collide, false altrimenti
     */
    bool checkCollision(Bullets *b);
    
    /**
     Verifica le collisioni tra i bunker della lista e la sprite passata come argomento.
     
     @param p sprite della quale verificare la collisione
     
     @return true se collide, false altrimenti
     */
    bool checkCollision(Sprite *p);
    
    /**
     Verifica la collisione tra le due entità passate come argomento.
     
     @param p bunker del quale verificare la collisione
     @param q seconda entità della quale verificare la collisione
     
     @return true se collidono, false altrimenti
     */
    bool collidesWith(list<bunker>::iterator p, FloatRect q);
    
    /**
     Mostra i bunker a schermo.
     */
    void drawAll();
    
    /**
     Restarta i timer relativi ai proiettile dei bunker, usata principalmente nei cambi di schermata.
     */
    void restartTimers();

};
