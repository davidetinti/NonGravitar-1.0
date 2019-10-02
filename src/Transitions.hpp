#ifndef Transitions_hpp
#define Transitions_hpp

#include "Terreno.hpp"

using namespace sf;
using namespace std;

class Transitions{
    
protected:
    
    Risorse *src;
    int tempo_transizione;
    
public:
    
    Time t1,t2,t3;
    Clock cl1,cl2,c3;
    RectangleShape screen,trans;
    
    /// COSTRUTTORI /////////////////////////////////////////////////////
    Transitions();
    Transitions(Risorse *src);
    
    ///  SETTERS E GETTERS  /////////////////////////////////////////////
    
    
    ///  FUNZIONI  //////////////////////////////////////////////////////
    void inPlanet(Terreno *terrain, int tot_schermate);
    void outPlanet();
};

#endif /* Transitions_hpp */
