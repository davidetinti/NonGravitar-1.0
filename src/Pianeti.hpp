#pragma once
#include "GPlanet.hpp"

/**
Singolo pianeta
*/
struct SinglePlanet {
    int relative_x, relative_y, grid_x, grid_y, tot_screen;
    double diameter;
    bool exist;
    Sprite planet;
    GPlanet inside;
    Texture *planet_tx;
    SinglePlanet(bool ex, int rel_x, int rel_y, int gr_x, int gr_y, int screens, Resources *s);
    void spriteSetup(Resources *src);
};


class Pianeti {

protected:

    int str_l[8]; //offset in x per la griglia del posizionamento dei pianeti
    int str_h[8]; //offset in y per la griglia del posizionamento dei pianeti
    SinglePlanet *current;
    Sprite explosion;
    Texture *explosion_tx;
    Resources *src;

public:

    list<SinglePlanet> planetlist;

    /**
     Costruttore base
    */
    Pianeti();

    /**
     Costruttore avanzato

     @param src puntatore all'utility class Resources
    */
    Pianeti(Resources *src);

    /**
     Ritorna il pianeta corrente
    */
    SinglePlanet* getCurrent();

    /**
     Imposta il pianeta corrente

     @param h puntatore ad un pianeta
    */
    void setCurrent(SinglePlanet* h);

    /**
     Trasmette l'azione di gestione al suo interno

     @param player puntatore alla classe del giocatore
     */
    void handle(Nave *player);

    /**
     Elimina il pianeta dalla lista di pianeti.

     @param p pianeta da eliminare
    */
    void deletePlanet(SinglePlanet* p);

    /**
     Disegna i pianeti nello schermo.
    */
    void draw();
};
