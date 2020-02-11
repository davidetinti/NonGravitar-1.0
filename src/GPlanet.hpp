#pragma once
#include "Fuels.hpp"
#include "Boss.hpp"

#define BOSS_SCREEN 666
#define STANDARD_PLANET_POINTS 500
#define COLLISION_DAMAGE 10

/**
 Struttura rappresentate una singola schermata dell'interno di un pianeta, con rispettivi bunker, fuel e terreno.
 */
struct planet_screen {
    
    int screen_nr;
    Fuels *carb;
    Bunkers *enemies;
    Terrain *terrain;
    planet_screen* next;
    planet_screen* prev;
    planet_screen(Terrain *terrain_n, int n, Resources *src,
                  planet_screen *next_n = nullptr, planet_screen *prev_n = nullptr);
    planet_screen(Resources *src);
};

/**
 Struttura interna del pianeta, divisa in schermate visitabili, ognuna delle quali autonomamente gestita, più una schermata aggiuntiva sbloccabile al completamento delle precedetni, contenente il boss.
 */

class GPlanet {
    
protected:
    
    int screen_nr;
    bool completed;
    bool boss_unlocked;
    bool in_boss;
    planet_screen *current;
    planet_screen *head;
    planet_screen *boss_screen;
    Texture *hole_tx;
    Sprite hole;
    Resources *src;
    
public:
    
    Boss boss;
    
    /**
     Costruttore base.
     */
    GPlanet();

    /**
     Ritorna il valore di boss_unlocked.
     
     @return true se boss_unlocked è vero, false altrimenti
     */
    bool getBoss_unlocked();
    
    /**
     Ritorna la schermata corrente.
     
     @return schermata corrente
     */
    planet_screen *getCurrent();
    
    /**
     Ritorna la schermata in testa alla lista.
    
     @return prima schermata della lista
    */
    planet_screen *getHead();
    
    /**
     Imposta il valore di boss_unlocked
    
     @param boss_unlocked definisce se sbloccare la schermata boss
    */
    void setBoss_unlocked(bool boss_unlocked);
    
    /**
     Imposta il valore della schermata corrente.
    
     @param current schermata attualmente visualizzata
    */
    void setCurrent(planet_screen *current);
    
    /**
     Imposta il valore della schermata in testa alla lista.
    
     @param head prima schermata della lista
    */
    void setHead(planet_screen *head);
    
    /**
     Ritorna il valore di in_boss.
    
     @return true se in_boss è vero, false altrimenti
    */
    bool getIn_boss();
    
    /**
     Inizializza il pianete, costruendone gli elementi interni alle schermate.
    
     @param tot_screen numero di schermate del pianete
     @param src puntatore all'utility class Resources
    */
    void initialize(int tot_screen, Resources *src);
    
    /**
     Aggiorna il valore della schermata corrente
     
     @param n indice di spostamento della schermata
     */
    void cambia_schermata(int n);
    
    /**
     Gestisce le collisioni tra:
     - il giocatore e il terreno;
     - il giocatore e i bunker;
     - i proiettili nemici e il giocatore;
     - i proiettili del giocatore e i nemici
     
     @param player puntatore alla classe del giocatore
     */
    void checkCollision(Nave *player);
    
    /**
     Gestione globale della classe:
     - generazione proiettili;
     - moviementi entità schermata;
     - visualizzazione oggetti;
     - controllo collisioni;
     
     @param player puntatore alla classe del giocatore
     */
    void handle(Nave *player);
    
    /**
     Verifica la collisione tra il giocatore e la sprite dell'entrata nella schermata boss
     
     @param body sprite del giocatore
     
     @return true se collidono, false altrimenti
     */
    bool inHole(Sprite *body);
    
    /**
     Cambia la schermata attuale con quella del boss, riposiziona il giocatore.
     
     @param player puntatore alla classe del giocatore
     */
    void enterBoss(Nave *player);
    
    /**
     Gestisce la collisione tra il giocatore e il terreno (contorno del boss se dentro ad esso)
     In caso di collisione, il giocatore viene respinto nel verso opposto.
     
     @param player puntatore alla classe del giocatore
     */
    void checkTerrain(Nave *player);
    
    /**
     Gestisce il comportamento del raggio traente.
     Quando a contatto con uno dei carburanti della schermata, quest'ultimo è attratto al giocatore, fino a "guadagnarlo" raggiunta una certa vicinanza.
     Mentre il raggio non è utilizzato, i carburanti non toccati tornano al livello del terreno.
     
     @param player puntatore alla classe del giocatore
     */
    void raggiotraente(Nave *player);
    
    /**
     Verifica lo stato i completamento del pianeta
     
     @return true se completato (tutti i nemici sconfitti), false atriementi
     */
    bool getCompleted();
    
    /**
     Gestisce l'interazione tra la posizione del giocatore nella schermata e il cambiamento di quest'ultima.
     
     @param player puntatore alla classe del giocatore
     */
    void checkScreen(Nave *player);
    
protected:
    
    /**
     Genera un intero casuale.
     Usato per la generazione delle altezze della ConvexShape del terreno
     
     @return intero randomico
     */
    int random_height();
    
    /**
     Gestisce l'attivazione della schermata boss.
     Quando tutti i bunker sulla superfice del pianeta sono eliminati rende accessibile la schermata boss, rendendone visibile l'entrata.
     */
    void updateBossLock();
};
