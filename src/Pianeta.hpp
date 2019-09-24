#ifndef Pianeta_hpp
#define Pianeta_hpp

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "GPlanet.hpp"

using namespace sf;
using namespace std;

struct Pianeta {
    int relative_x, relative_y, grid_x, grid_y, tot_schermate;
    bool exist;
    Sprite planet;
    GPlanet interno;
    Pianeta* next;
    ptr_Texture planet_tx;
};

typedef Pianeta* ptr_Pianeta;

class uPlanets {
    
protected:
    
    int str_l[8];
    int str_h[8];
    ptr_Pianeta pp, hp;
    Sprite explosion;
    ptr_Texture explosion_tx;
    
public:
    
    /// COSTRUTTORI /////////////////////////////////////////////////////
    uPlanets();
    uPlanets(Risorse *src);
    
    ///  SETTERS E GETTERS  /////////////////////////////////////////////
    ptr_Pianeta getPP();
    ptr_Pianeta getHP();
    void setPP(ptr_Pianeta pp);
    void setHP(ptr_Pianeta hp);
    
    ///  FUNZIONI  //////////////////////////////////////////////////////
    void gestione(RenderWindow *window, Nave *player, Transitions *transizioni, Time perFrame);
};

#endif /* Pianeta_hpp */
