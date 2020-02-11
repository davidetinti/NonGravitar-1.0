#pragma once
#include "GPlanet.hpp"

/**
Singolo pianeta
*/
struct SinglePlanet {
    int relative_x, relative_y, grid_x, grid_y, tot_schermate;
    double diameter;
    bool exist;
    Sprite planet;
    GPlanet interno;
    Texture *planet_tx;
    SinglePlanet(bool ex, int rel_x, int rel_y, int gr_x, int gr_y, int screens, Resources *s);
    void spriteSetup(Resources *src);
};


class Pianeti {
    
protected:
    
    int str_l[8];
    int str_h[8];
    SinglePlanet* head, *current;
    Sprite explosion;
    Texture* explosion_tx;
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
     Ritorna la testa della lista dei pianeti
    */
    SinglePlanet* getHead();
    
    /**
     Setta la testa della lista dei pianeti
     
     @param h puntatore ad un pianeta
    */
    void setHead(SinglePlanet* h);
    
    /**
     Ritorna il pianeta corrente
    */
    SinglePlanet* getCurrent();
    
    /**
     Seleziona il pianeta corrente
     
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
    
private:
    
    /**
     Setta la sprite al pianeta in base al numero di schermate di cui esso è composto.
       
     @param p puntatore ad un pianeta
     */
    void spriteSetup(SinglePlanet* p);
};
