#ifndef Fuel_hpp
#define Fuel_hpp

#include "Terreno.hpp"

struct fuel{
    double x;
    double y;
    int power;
    bool exist;
    Sprite fuel_sprite;
    fuel *next;
    fuel(double x_n, double y_n, int power_n,fuel *next_n,bool exist_n);
};

class Fuel{
    
protected:
    
    Resources *src;
    Texture *fuel_tx;
    fuel *current,*head;
    double partial_x[3];
    
public:
    
    // COSTRUTTORI ===================================
    Fuel();
    Fuel(Terreno *terrain,Resources *src);
    
    // SETTERS E GETTERS =============================
    fuel *getCurrent();
    fuel *getHead();
    void setCurrent(fuel *current);
    void setHead(fuel *head);
    
    // FUNZIONI ======================================
    void delete_fuel(fuel *selected);
    void gestisci();
    
protected:
    void spriteSetup(fuel *selected, int power);

};

#endif /* Fuel_hpp */
