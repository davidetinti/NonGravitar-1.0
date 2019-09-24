#ifndef Universo_hpp
#define Universo_hpp

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Pianeta.hpp"
#include "HUD.hpp"

using namespace sf;
using namespace std;

struct schermata {
    schermata* dx;
    schermata* sx;
    schermata* up;
    schermata* dw;
    uPlanets pianeti;
    int x;
    int y;
};

typedef schermata* ptr_schermata;

struct lista_schermate {
    ptr_schermata it;
    int x;
    int y;
    lista_schermate* next;
};

typedef lista_schermate* ptr_lista_schermate;

class Universo {
    
protected:
    
    ptr_Texture universe_tx;
    int altezza;
    int larghezza;
    ptr_schermata active;
    ptr_lista_schermate list;
    ptr_lista_schermate head_list;
    
public:
    
    Nave player;
    Sprite universe;
    HUD hud;
    
    
    /// COSTRUTTORI /////////////////////////////////////////////////////
    Universo();
    Universo(int heigth, int lenght, Risorse *src, Font *font);
    
    ///  SETTERS E GETTERS  /////////////////////////////////////////////
    ptr_schermata getActive();
    ptr_lista_schermate getList();
    ptr_lista_schermate getHeadList();
    
    ///  FUNZIONI  //////////////////////////////////////////////////////
    ptr_schermata find(int x, int y);
    void move(int x, int y, Risorse *src);
    void disegnaPianeti(RenderWindow *window);
    void checkTerrain(RenderWindow *window);
    void movimentiNavetta(RenderWindow *window, Risorse *src, Transitions *transizioni, sf::Time timePerFrame);
};

#endif /* Universo_hpp */
