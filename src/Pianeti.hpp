#pragma once
#include "GPlanet.hpp"

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
    
    Pianeti();
    Pianeti(Resources *src);
    
    SinglePlanet* getHead();
    void setHead(SinglePlanet* h);
    SinglePlanet* getCurrent();
    void setCurrent(SinglePlanet* h);
    
    void handle(Nave *player);
    void deletePlanet(SinglePlanet* p);
    void draw();
private:
    void spriteSetup(SinglePlanet* p);
};
