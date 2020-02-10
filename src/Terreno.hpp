#pragma once
#include <math.h>
#include "Resources.hpp"

struct soil{
    ConvexShape element;
    struct soil *next;
    soil(soil *n);
};


class Terreno{
    
protected:
    
    Resources *src;
    int schermate_nr;
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
    Terreno();
    
    /**
    Costruttore avanzato
    
    @param s puntatore all'utility class Resources
    */
    Terreno(Resources *s);
    
    /**
    Costruttore avanzato
    
    @param sx_coord coordinate sinistre
    @param dx_coord coordinate destre
    @param s puntatore all'utility class Resources
    @param tot_schermate numero di schermate di un pianeta
    */
    Terreno(int sx_coord, int dx_coord, Resources *s, int tot_schermate);
    
    int getDxCoord();
    int getSxCoord();
    void setDxCoord(int dx_coord);
    void setSxCoord(int sx_coord);

    /**
    Setta il colore del terreno
     
    @param tot_schermate numero di schermate del pianeta
    @param transparency trasparenza del terreno
    */
    Color setColor(int tot_schermate, int transparency);
    
    /**
    Disegna il terreno
    */
    void drawAll();
    
    /**
    Calcola l'altezza del terreno in un determinato punto
     
    @param x la coordinata che useremo  per trovare l'altezza
    @return l'altezza del terreno
    */
    double getTerrainY(double x);
    
    /**
    Setta la sprite del buco nella posizione corretta
     
    @param hole puntatore alla sprite del buco per il boss
    */
    void prepareForBoss(Sprite *hole);
    
    /**
    Ritorna vero se tutti i bunker sono stati eliminati
    */
    bool isBoss();
    
private:
    
    /**
    Setta le sprite
     
    @param
    */
    void spriteSetup(Vector2f p0, Vector2f p1, Vector2f p2, Vector2f p3, soil *p);
    
    /**
    Elimina più parti del terreno per far posto al buco per il boss
     
    @return la posizione di dove disegnare il buco
    */
    int prepareForHole();
};
