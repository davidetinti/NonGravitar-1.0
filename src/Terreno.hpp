#ifndef Terreno_hpp
#define Terreno_hpp

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "cmath"
#include "Risorse.hpp"

using namespace sf;
using namespace std;

struct soil{
    ConvexShape soil;
    struct soil *next;
};

typedef soil* ptr_soil;

class Terreno{
    
protected:
    
    int dx_coord,sx_coord;
    ptr_Texture terrain_tx;
    ptr_Texture background_tx;
    ptr_soil head,current;
    
public:
    
    Sprite background;
    
    /// COSTRUTTORI /////////////////////////////////////////////////////
    Terreno();
    Terreno(int sx_coord, int dx_coord, Risorse *src, int tot_schermate);
    
    ///  SETTERS E GETTERS  /////////////////////////////////////////////
    int getDxCoord();
    int getSxCoord();
    void setDxCoord(int dx_coord);
    void setSxCoord(int sx_coord);
    
    ///  FUNZIONI  //////////////////////////////////////////////////////
    Color colore(int tot_schermate, int transparency);
    void gestisci(RenderWindow *window);
    double get_Y(double x);
};

#endif /* Terreno_hpp */
