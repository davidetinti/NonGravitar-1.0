#ifndef Game_hpp
#define Game_hpp

#include "Universo.hpp"

using namespace std;
using namespace sf;

class Game{
    
protected:
    
    Risorse *src;
    Finestra schermata_principale;
    Finestra crediti;
    Finestra partita;
    Finestra pausa;
    Universo universe;
    Transitions transizioni;
    Texture *pausa_bk;

public:
    
    Game();
    Game(Risorse *src, Time *time);
    void handle(sf::Time timePerFrame);
    
};


#endif /* Game_hpp */
