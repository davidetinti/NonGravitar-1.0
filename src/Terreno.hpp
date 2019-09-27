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
    ConvexShape element;
    struct soil *next;
    soil(soil *n);
};

class Terreno{
    
protected:
    
    int dx_coord,sx_coord;
    ptr_Texture terrain_tx;
    ptr_Texture background_tx;
    soil * head, *current;
    
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
private:
    void spriteSetup(int tot_sch, Vector2f p0, Vector2f p1, Vector2f p2, Vector2f p3, soil *p);
};

#endif /* Terreno_hpp */
