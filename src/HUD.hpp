#ifndef HUD_hpp
#define HUD_hpp

#include "Pulsante.hpp"

using namespace std;
using namespace sf;

class HUD{
    
protected:
    
    Risorse *src;
    Sprite lifebar_active, lifebar_back, fuelbar_active, fuelbar_back;
    Texture* bars_tx;
    Text life, fuel, score;
    //Pulsante pausa;
    
public:
    
    HUD();
    HUD(Risorse *src);
    void gestisci(int point, float life, float fuel);
};

#endif /* HUD_hpp */
