#ifndef Game_hpp
#define Game_hpp

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Universo.hpp"

using namespace std;
using namespace sf;

class Game{
    
protected:
    
    Finestra schermata_principale;
    Finestra crediti;
    Finestra partita;
    Finestra pausa;
    Universo universe;
    Transitions transizioni;
    ptr_Texture pausa_bk;

public:
    
    Game();
    Game(Risorse *src, Font *font);
    void gestisci(RenderWindow *window, Risorse *src, Font *font, sf::Time timePerFrame);
    
};


#endif /* Game_hpp */
