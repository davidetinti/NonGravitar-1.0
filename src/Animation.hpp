#pragma once
#include "SourceLoader.hpp"

/**
 Animazione realizzata tramite una Sprite dinamica, la quale viene aggiornata in base
 al contenuto della Texture associata, preventivamente predisposta a questo utilizzo.
 Al momento della creazione, la Texture scelta è divisa in una tabella di frame in base
 ai valori di rows e columns.
 Ad ogni ciclo di gioco il frame visualizzato si aggiorna passando al successivo scorrendo
 in orizzontale la propria texture, fino al raggiungimento dell'ultimo, terminando.
 */

class Animation {
    
protected:
    
    SourceLoader *src;
    Sprite sprite;
    int frame_width, frame_height, max_x, max_y;
    double current_x, current_y, speed;
    
public:
    
    /**
     Costruttore base
     */
    Animation();
    
    /**
     Costruttore avanzato
     
     @param x coordinata x dell'animazione da generare
     @param y coordinata y dell'animazione da generare
     @param tx_nr indice della texture dell'animazione
     @param rows righe dello spritesheet dell'animazione
     @param columns colonne dello spritesheet dell'animazione
     @param scale fattore di scala
     @param src puntatore all'utility class SourceLoader
     @param image_speed velocità ripoduzione animazione
     */
    Animation(int x, int y, int tx_nr, int rows, int columns, float scale, SourceLoader *src, double image_speed = 1);
    
    /**
     @return sprite dell'animazione corrente
     */
    Sprite* getSprite();
    
    /**
     @return true se l'animazione è terminata, false altrimenti
     */
    bool isEnded();
    
    /**
     Gestisce l'aggiornamento del frame dell'animazione
     */
    void handle();
    
};
