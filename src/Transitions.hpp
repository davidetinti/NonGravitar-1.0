#pragma once
#include "Terreno.hpp"

class Transitions{
    
protected:
    
    Resources *src;
    int tempo_transizione;
    
public:
    
    Time t1,t2,t3;
    Clock cl1,cl2,c3;
    RectangleShape screen,trans;
    
    Transitions();
    Transitions(Resources *src);
    void inPlanet(Terreno *terrain, int tot_schermate);
    void outPlanet();
};
