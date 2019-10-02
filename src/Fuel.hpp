#ifndef Fuel_hpp
#define Fuel_hpp

#include "Terreno.hpp"

using namespace sf;
using namespace std;

struct fuel{
    double x;
    double y;
    int power;
    bool exist;
    Sprite fuel_sprite;
    fuel *next;
};

class Fuel{
    
protected:
    
    Risorse *src;
    Texture *fuel_tx;
    fuel *current,*head;
    double partial_x[3];
    
public:
    
    /// COSTRUTTORI /////////////////////////////////////////////////////
    Fuel();
    Fuel(Terreno *terrain,Risorse *src);
    
    ///  SETTERS E GETTERS  /////////////////////////////////////////////
    fuel *getCurrent();
    fuel *getHead();
    void setCurrent(fuel *current);
    void setHead(fuel *head);
    
    ///  FUNZIONI  //////////////////////////////////////////////////////
    void delete_fuel(fuel *selected);
    void gestisci();
};

#endif /* Fuel_hpp */
