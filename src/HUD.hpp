#ifndef HUD_hpp
#define HUD_hpp

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Pulsante.hpp"
#include "cstring"

using namespace std;
using namespace sf;

class HUD{
    
protected:
    Sprite lifebar_active, lifebar_back, fuelbar_active, fuelbar_back;
    ptr_Texture bars_tx;
    Text life, fuel, score;
    //Pulsante pausa;
    
public:
    
    HUD();
    HUD(int lenght, int heigth, Risorse *src, Font *font);
    void gestisci(RenderWindow *window, int point, float life, float fuel);
};

#endif /* HUD_hpp */
