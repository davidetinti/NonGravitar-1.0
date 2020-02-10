#pragma once
#include "Terreno.hpp"


struct proiettile{
    bool exist;
    Sprite bullet;
    Clock invuln_clock;
    proiettile(double x, double y, double rotation, Texture *bullet_tx);
};

/**
 Classe astratta rappresentante le armi utilizzate dalle entità.
 Composta da una lista di proiettili, gestiti controllandone la posizione,
 spostamento e collisioni con altre entità.
 */
class Bullets{
    
protected:
    
    Resources *src;
    Texture *bullet_tx;
    int time_btw_shoot; //intervallo tra i colpi
    int damage;
    int speed;
    double invuln_time; //intervallo di invulnerabilità
    bool autoshoot;
    
public:
    
    list<proiettile> *bulletList;
    Clock bullet_time; //tempo passato tra i colpi
    
    /**
     Costruttore base
     */
    Bullets();
    
    /**
     Costruttore avanzato
     
     @param time_btw_shoot intervallo tra due colpi
     @param damage danno dei poroiettili
     @param speed velocità di movimento dei proiettili
     @param tx_nr indice di posizione della texture
     @param autoshoot possibilità di fuoco automatico
     @param src puntatore all'utility class Resources
     */
    Bullets(int time_btw_shoot, int damage, int speed, int tx_nr, bool autoshoot, Resources *src);
    
    /**
     Ritorna il danno dei proiettili
     
     @return danno inflitto dai proiettili
     */
    int getDamage();
    
    /**
     Inserice un proiettile nella lista bulletList
     
     @param entity sprite del "padre" del proiettile
     @param pulsante pulsante associato al fuoco
     */
    virtual void addSingleBullet(Sprite entity, Keyboard::Key pulsante) = 0;
    
    /**
     Gestisce, visualizza ed elimina i proiettili nella lista
     */
    virtual void renderBullet() = 0;
    
    /**
     Verifica le collisioni tra tutti i proiettili e l'oggetto p
     */
    virtual int checkCollision(FloatRect p);
    
    /**
     Funzione generale di gestione della classe
     
     @param terrain terreno della schermata corrente, se presente
     */
    void handle(Terreno *terrain = nullptr);
    
    /**
     Elimina i proiettili in collisione o fuori dal campo visivo
     
     @param terrain terreno della schermata corrente, se presente
     */
    virtual void cleanup(Terreno *terrain) = 0;

protected:

    bool collidesWith(list<proiettile>::iterator p, FloatRect obj);
    bool outsideBounds(list<proiettile>::iterator p, Terreno *terrain);
    bool outsideBounds(list<proiettile>::iterator p);
};
