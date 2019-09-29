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

struct lista_schermate {
    lista_schermate* dx;
    lista_schermate* sx;
    lista_schermate* up;
    lista_schermate* dw;
    int x;
    int y;
    uPlanets pianeti;
    lista_schermate* next;
    lista_schermate(int x_n, int y_n, Risorse *src, lista_schermate *d=NULL, lista_schermate *s=NULL, 
        lista_schermate *u=NULL, lista_schermate *down=NULL, lista_schermate *nxt=NULL);
};


class Universo {
    
protected:
    
    ptr_Texture universe_tx;
    int altezza;
    int larghezza;
    lista_schermate *active;
    lista_schermate *tail;
    lista_schermate *head_list;
    Risorse *src;
    
public:
    
    Nave player;
    Sprite universe;
    HUD hud;
    
    
    /// COSTRUTTORI /////////////////////////////////////////////////////
    Universo();
    Universo(int heigth, int lenght, Risorse *src, Font *font, Time *time);
    
    ///  SETTERS E GETTERS  /////////////////////////////////////////////
    lista_schermate *getActive();
    lista_schermate *getTail();
    lista_schermate *getHeadList();
    
    ///  FUNZIONI  //////////////////////////////////////////////////////
    lista_schermate *find(int x, int y);
    void move(int x, int y, Risorse *src);
    void disegnaPianeti(RenderWindow *window);
    void checkTerrain(RenderWindow *window);
    void movimentiNavetta(RenderWindow *window, Risorse *src, Transitions *transizioni, sf::Time timePerFrame);
private:
    bool contactPlanet(Vector2f pos, Pianeta* p);
    void addToList(lista_schermate *p);
};

#endif /* Universo_hpp */
