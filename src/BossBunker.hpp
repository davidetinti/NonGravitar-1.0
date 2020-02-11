#pragma once
#include "Bunkers.hpp"

/**
 Bunker posizionati sul Boss.
 Differenziano della classe Bunker il movimento, mentre mantengono inalterate le altre funzionalità.
 */
class BossBunker: public Bunkers{
    
protected:
    
    const int DAMAGE = 10;
    const int SPEED = 10;
    const int BUNKER_NR = 3;
    
    double radius;
    Vector2f centre;
    /**
     Ruota la sprite dei bunker seguendo la rotazione della sprite del Boss
     */
    void updateRotation();
    
public:
    
    /**
     Costruttore base
     */
    BossBunker();
    
    /**
     Costruttore avanzato
     
     @param s puntatore all'utility class Resources
     @param r raggio del Boss, usato per offset di costruzione
     */
    BossBunker(Resources *s, double r);
    
    /**
     Genera le coordinate della nuova posizione del bunker basandosi sull'angolo fornito come dato in ingresso
     
     @param angle angolo di rotazione della sprite del Boss
     
     @return vettore con le coordinate generate
     */
    Vector2f newPosition(double angle);
    
    /**
     Aggiorna la posizione e rotazione del bunker basandosi sull'angolo fornito come dato in ingresso
     
     @param angle angolo di rotazione per il calcolo degli offset
     */
    void updatePosition(double angle);
};
