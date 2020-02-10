#pragma once
#include "BossBunker.hpp"

/**
 Entità raggiunta dal giocatore nella fase finale di completamento del pianeta.
 La classe è composta da una sprite circolare, il boss, sulla quale sono posizionati diversi bunker indipendenti da esso.
 */

class Boss {
    
private:
    
    static constexpr double ROTATION_STEP = 0.3;
    static const int HIT_TIMER_MS = 100;
    static const int DEATH_TIMER_MS = 800;
    static const int DAMAGE_ON_COLLISION = 5;
    int EXPL_NR;
     
protected:
    
    int hp_left;
    int turrets_left;
    double radius;
    bool red;
	bool alive;
    bool dying;
    Resources *src;
    Clock last_hit;
    Clock rotation;
	Vector2f centre;
    Texture *boss_tx;
    Sprite boss_sprite;
    BossBunker *turrets;
    CircleShape collision_boundary; //confine interno
    
public: 
    
    /**
     Costruttore base
     */
    Boss();
    
    /**
     Costruttore avanzato
     
     @param life vita dell'entità
     @param turrets numero di BossBunker
     @param src_a puntatore all'utility class Resources
     */
    Boss(int life, int turrets, Resources *src_a);
    
    /**
     @return true se non alive, false altrimenti
     */
    bool isDead();
    
    /**
     Ritorna la coordinate del centro dell'entità.
     
     @return Vector2f con coordinate del centro
     */
    Vector2f getCenter();
    
    /**
     Ritorna il raggio dell'entità,
     
     @return raggio dell'entità
     */
    double getRadius();
    
    /**
     Assegna la lista dei bunker del boss.
     
     @param boss_bunker_list lista contenente i bunker del boss
     */
    void setEnemies(BossBunker *boss_bunker_list);
    
    /**
     Verifica le collisioni dei proiettili appartenenti alla classe weapon con i confini interni del boss
     
     @param weapon classe padre dei proiettili dei quali verificare le collisioni
     
     @return true se almeno un proiettile collide, false altrimenti
     */
    bool checkCollisionBoss(Bullets *weapon);
    
    /**
     Verifica la collisione della sprite body con i confini interni del boss
     
     @param body entità della quale verificare la collisione
     
     @return true se collide, false altrimenti
     */
	bool checkCollisionBoss(Sprite *body);
    
    /**
     Gestisce i colpi subiti dal boss.
     In caso di colpo, se sono presenti bunker lo evita e accende i limiti interni, altrimenti subisce.
     
     @param damage valore di danno del colpo subito
     */
	void getHit(int damage);
    
    /**
     Mostra gli oggetti della classe.
     */
	void draw();
    
    /**
     Gestisce il funzionamento del boss.
     Viene effettuata la rotazione della sprite del boss e  dei bunker, la gestione della colorazione in caso di colpo subito e la distruzione in caso di vita terminata.
     */
    void handle();
    
    /**
     Genera un numero random di esplosioni.
     */
    void explode();
};

 
