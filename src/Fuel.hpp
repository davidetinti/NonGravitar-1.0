#ifndef Fuel_hpp
#define Fuel_hpp

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Terreno.hpp"

using namespace sf;
using namespace std;

struct fuel{
    double x;
    double y;
    int power;
    bool exist;
    Sprite fuel_sprite;
    fuel* next;
};

typedef fuel* ptr_fuel;

class Fuel{
    
protected:
    
    ptr_Texture fuel_tx;
    ptr_fuel current,head;
    double partial_x[3];
    
public:
    
    /// COSTRUTTORI /////////////////////////////////////////////////////
    Fuel();
    Fuel(Terreno *terrain,Risorse *src);
    
    ///  SETTERS E GETTERS  /////////////////////////////////////////////
    ptr_fuel getCurrent();
    ptr_fuel getHead();
    void setCurrent(ptr_fuel current);
    void setHead(ptr_fuel head);
    
    ///  FUNZIONI  //////////////////////////////////////////////////////
    void delete_fuel(ptr_fuel selected);
    void gestisci(RenderWindow *window);
};

#endif /* Fuel_hpp */
