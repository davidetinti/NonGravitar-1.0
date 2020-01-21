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
    int nr_schermate;
    int dx_coord,sx_coord;
    Texture* terrain_tx;
    Texture* background_tx;
    soil* head;
    double minSizeHole;//minimum space needed for initial soil + bosshole
    double minSizeSoil;//minimum size of soils to right and left
    
public:
    
    Sprite background;
    
    Terreno();
    Terreno(Resources *src);
    Terreno(int sx_coord, int dx_coord, Resources *src, int tot_schermate);
    
    int getDxCoord();
    int getSxCoord();
    void setDxCoord(int dx_coord);
    void setSxCoord(int sx_coord);
    
    Color colore(int tot_schermate, int transparency);
    void drawAll();
    double get_Y(double x);
    void prepareForBoss(Sprite *hole);
    bool isBoss();
private:
    void spriteSetup(Vector2f p0, Vector2f p1, Vector2f p2, Vector2f p3, soil *p);
    int prepareForHole();
};
