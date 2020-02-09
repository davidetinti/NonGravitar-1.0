#pragma once
#include "SourceLoader.hpp"

class Animation {
    
protected:
    
    SourceLoader *src;
    Sprite sprite;
    int frame_width, frame_height, max_x, max_y;
    double current_x, current_y, speed;
    
public:
    
    /**
     Costruttore semplice
     */
    Animation();
    
    /**
     Costruttore avanzato
     
     @param x coordinata x dell'animazione da generare
     @param y coordinata y dell'animazione da generare
     @param tx_nr indice texture aminazione
     @param rows righe dello spritesheet dell'animazione
     @param columns colonne dello spritesheet dell'animazione
     @param scale fattore di scala
     @param src puntatore all'utility class SourceLoader
     @param image_speed velocità ripoduzione animazione
     */
    Animation(int x, int y, int tx_nr, int rows, int columns, float scale, SourceLoader *src, double image_speed = 1);
    
    /**
     Ritorna la sprite dell'animazione corrente
     */
    Sprite* getSprite();
    
    /**
     True se l'animazione è terminata
     */
    bool isEnded();
    
    /**
     Gestisce l'aggiornamento del frame dell'animazione
     */
    void handle();
    
};
