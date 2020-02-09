#pragma once
#include "Pulsante.hpp"

class HUD{
    
protected:
    
    Resources *src;
    Sprite lifebar_active, lifebar_back, fuelbar_active, fuelbar_back;
    Texture *bars_tx;
    Text life,fuel,score;
    
public:
    
    HUD();
    HUD(Resources *src);
    
    void gestisci(int point, float life, float fuel);
    
};
