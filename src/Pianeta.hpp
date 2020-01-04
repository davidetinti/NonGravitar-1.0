#ifndef Pianeta_hpp
#define Pianeta_hpp

#include "GPlanet.hpp"

struct Pianeta {
    int relative_x, relative_y, grid_x, grid_y, tot_schermate;
    double diameter;
    bool exist;
    Sprite planet;
    GPlanet interno;
    Texture *planet_tx;
    Pianeta* next;
    Pianeta(bool ex, int rel_x, int rel_y, int gr_x, int gr_y, int screens, 
            Pianeta *next);
};


class uPlanets {
    
protected:
    
    int str_l[8];
    int str_h[8];
    Pianeta* head, *current;
    Sprite explosion;
    Texture* explosion_tx;
    Resources *src;
    
public:
    
    // COSTRUTTORI ===================================
    uPlanets();
    uPlanets(Resources *src);
    
    // SETTERS E GETTERS =============================
    Pianeta* getHead();
    void setHead(Pianeta* h);
    Pianeta* getCurrent();
    void setCurrent(Pianeta* h);
    
    // FUNZIONI ======================================
    void handle(Nave *player);
    void deletePlanet(Pianeta* p);
private:
    void spriteSetup(Pianeta* p);
}; 

#endif /* Pianeta_hpp */
