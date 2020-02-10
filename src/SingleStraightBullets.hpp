#pragma once
#include "Bullets.hpp"

class SingleStraightBullets : public Bullets{
    
public:
    
    /**
    Costruttore base
    */
    SingleStraightBullets();
    
    /**
    Costruttore avanzato
     
     @param time_btw_shot tempo che c'è fra uno sparo e l'altro
     @param damage danno dei proiettili
     @param speed velocità dei proiettili
     @param tx_nr texture dei proiettili
     @param autoshoot colpi automatici (es bunker)
     @param src puntatore all'utility class SourceLoader
    */
    SingleStraightBullets(int time_btw_shoot, int damage, int speed,
                          int tx_nr, bool autoshoot, Resources *src);
    
    /**
    Inserice un proiettile nella lista dei proiettili
    
    @param entity sprite del "padre" del proiettile
    @param pulsante pulsante associato al fuoco
    */
    void addSingleBullet(Sprite entity, Keyboard::Key pulsante);
   
    /**
    Gestisce, visualizza ed elimina i proiettili nella lista
    */
    void renderBullet();
    
    /**
    Elimina i proiettili in collisione o fuori dal campo visivo
    
    @param terrain terreno della schermata corrente, se presente
    */
    void cleanup(Terreno *terrain);
}; 

