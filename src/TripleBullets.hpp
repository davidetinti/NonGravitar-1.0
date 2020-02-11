#pragma once
#include "SingleStraightBullets.hpp"

/**
Classe astratta che estende la classe Bullets.
Composta da una lista di proiettili, gestiti controllandone la posizione,
spostamento e collisioni con altre entità.
*/
class TripleBullets: public Bullets{
    
    SingleStraightBullets left, centre, right;
    
    /**
     Elimina i proiettili in collisione o fuori dal campo visivo
    
     @param terrain terreno della schermata corrente, se presente
    */
    void cleanup(Terrain *terrain);
    
public:
    
    /**
     Costruttore base
    */
    TripleBullets();
    
    /**
     Costruttore avanzato
    
     @param time_btw_shoot intervallo tra due colpi
     @param damage danno dei poroiettili
     @param speed velocità di movimento dei proiettili
     @param tx_nr indice di posizione della texture
     @param autoshoot possibilità di fuoco automatico
     @param src puntatore all'utility class Resources
    */
    TripleBullets(int time_btw_shoot, int damage, int speed,
                  int tx_nr, bool autoshoot, Resources *src);
    
    /**
     Inserice un proiettile nella lista bulletList
    
     @param entity sprite del "padre" del proiettile
     @param pulsante pulsante associato al fuoco
    */
    void addSingleBullet(Sprite entity, Keyboard::Key pulsante);
    
    /**
     Gestisce, visualizza ed elimina i proiettili nella lista
    */
    void renderBullet();
    
    /**
     Verifica le collisioni tra tutti i proiettili e l'oggetto p
    */
    int checkCollision(FloatRect p);
};

