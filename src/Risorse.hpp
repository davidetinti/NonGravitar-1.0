#ifndef Risorse_hpp
#define Risorse_hpp

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <cstring>

using namespace std;
using namespace sf;

typedef Texture *ptr_Texture;

class Risorse{
    
protected:
    
    SoundBuffer sound[1];
    Texture texture[31];
    
public:
    
    Risorse();
    SoundBuffer caricaSuono(int n);
    ptr_Texture caricaTexture(int n);
    
};

/*
 SUONI:
 0.player_bullet.ogg

 TEXTURE:
 0.player_bullet_tx.png
 1.player_laser_tx.png
 2.universe_tx.jpg
 3.bunker_tx.png
 4.nave_tx.png
 5.planet3.png
 6.planet4.png
 7.planet5.png
 8.planet6.png
 9.planet7.png
 10.planet8.png
 11.planet9.png
 12.planet10.png
 13.inside.png
 14.bullet1_tx.png
 15.bullet2_tx.png
 16.bar.png
 17.raggio.png
 18.fuel_tank.png
 19.explosion1.png
 20.explosion2.png
 21.credits.png
 22.esci.png
 23.gioca.png
 24.indietro.png
 25.1.png
 26.2.png
 27.3.png
 28.nongravitar.png     // sfondo pausa
 29.terra.png
 */

#endif /* Risorse_hpp */
