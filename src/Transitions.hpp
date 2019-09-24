#ifndef Transitions_hpp
#define Transitions_hpp

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Terreno.hpp"

using namespace sf;
using namespace std;

class Transitions{
    
protected:
    
    int tempo_transizione;
    
public:
    
    Time t1,t2,t3;
    Clock cl1,cl2,c3;
    RectangleShape screen,trans;
    
    /// COSTRUTTORI /////////////////////////////////////////////////////
    Transitions();
    
    ///  SETTERS E GETTERS  /////////////////////////////////////////////
    
    
    ///  FUNZIONI  //////////////////////////////////////////////////////
    void inPlanet(RenderWindow *window, Terreno *terrain, int tot_schermate);
    void outPlanet(RenderWindow *window);
};

#endif /* Transitions_hpp */
