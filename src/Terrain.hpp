#pragma once
#include <math.h>
#include "Resources.hpp"

/**
 Wrapper class per una componente del terreno rappresentata con una ConvexShape
 */
struct soil{
    ConvexShape element;
    struct soil *next;
    soil(soil *n);
};


class Terrain{
    
protected:
    
    Resources *src;
    int screens_nr;
    int dx_coord,sx_coord;
    Texture* terrain_tx;
    Texture* background_tx;
    soil* head;
    double min_size_hole; //minimum space needed for initial soil + bosshole
    double min_size_soil; //minimum size of soils to right and left
    
public:
    
    Sprite background;
    
    /**
     Costruttore base
    */
    Terrain();
    
    /**
     Costruttore avanzato
    
     @param s puntatore all'utility class Resources
    */
    Terrain(Resources *s);
    
    /**
     Costruttore avanzato
    
     @param sx_coord coordinata y sinistra del primo elemento soil
     @param dx_coord coordinata y destra dell'ultimo elemento soil
     @param s puntatore all'utility class Resources
     @param tot_screens numero di schermate di un pianeta
    */
    Terrain(int sx_coord, int dx_coord, Resources *s, int tot_screens);
    
    int getDxCoord();
    int getSxCoord();
    void setDxCoord(int dx_coord);
    void setSxCoord(int sx_coord);

    /**
     Setta il colore del terreno
     
     @param tot_screens numero di schermate del pianeta
     @param transparency trasparenza di colorazione
    */
    Color setColor(int tot_screens, int transparency);
    
    /**
     Disegna il terreno
    */
    void drawAll();
    
    /**
     Calcola l'altezza del terreno in un determinato punto
     
     @param x la coordinata x della quale trovare la rispettiva y
     
     @return l'altezza del terreno
    */
    double getTerrainY(double x);
    
    /**
     Setta la sprite del buco nella posizione corretta
     
     @param hole puntatore alla sprite del buco per il boss
     */
    void prepareForBoss(Sprite *hole);
    
    /**
     Ritorna se tutti i bunker sono stati eliminati.
     
     @return true se tutti bunker sono eliminati, false altrimenti
     */
    bool isBoss();
    
private:
    
    /**
     Setta le sprite
     
     @param p0 coordinate primo vertice della convex shape
     @param p1 coordinate secondo vertice della convex shape
     @param p2 coordinate terzo vertice della convex shape
     @param p3 coordinate quarto vertice della convex shape
     @param p porzione di terreno alla quale impostare la Sprite
    */
    void spriteSetup(Vector2f p0, Vector2f p1, Vector2f p2, Vector2f p3, soil *p);
    
    /**
     Elimina più parti del terreno per far posto al buco per il boss
     
     @return la posizione di dove disegnare il buco
    */
    int prepareForHole();
};
