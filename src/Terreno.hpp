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
    
    Terreno();
    Terreno(Resources *s);
    Terreno(int sx_coord, int dx_coord, Resources *s, int tot_schermate);
    
    int getDxCoord();
    int getSxCoord();
    void setDxCoord(int dx_coord);
    void setSxCoord(int sx_coord);
    Color setColor(int tot_schermate, int transparency);
    
    void drawAll();
    double getTerrainY(double x);
    void prepareForBoss(Sprite *hole);
    bool isBoss();
    
private:
    
    void spriteSetup(Vector2f p0, Vector2f p1, Vector2f p2, Vector2f p3, soil *p);
    int prepareForHole();
};
