#pragma once
#include "Terreno.hpp"

struct fuel{
    double x;
    double y;
    int power;
    Sprite fuel_sprite;
    fuel(double x_n, double y_n, int power_n);
};

class Fuels{
    
protected:
    
    Resources *src;
    Texture *fuel_tx;
    list<fuel> *fuel_list;
    double partial_x[3];
    
public:
    
    Fuels();
    Fuels(Terreno *terrain,Resources *src);
    
    list<fuel>::iterator getFuelListBegin();
    list<fuel>::iterator getFuelListEnd();
    
    list<fuel>::iterator delete_fuel(list<fuel>::iterator it);
    int getPower(list<fuel>::iterator it);
    void gestisci();
    
protected:
    
    void spriteSetup(fuel *selected, int power);

};
