#include "pch.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <ctime>
#include <cmath>
#include "Game.hpp"
#define _USE_MATH_DEFINES

using namespace sf;
using namespace std;

int const heigth = 720;
int const lenght = 1280;

int main() {
    
    /// INIZIALIZZAZIONE ///////////////////////////////////////
    
    srand((unsigned)time(NULL));
    Risorse src = Risorse();
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    RenderWindow window;
    window.create(VideoMode(lenght, heigth), "Non Gravitar", (Style::Titlebar | Style::Close), settings);
    Font font;
    if (!font.loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/text.ttf")) {
        if (!font.loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/text.ttf")) {
            if (!font.loadFromFile("./src/text.ttf")) {
                cout << "Errore nel caricamento del font text.ttf";
            }
        }
    }
    Text text;
    Clock utility_clock;
    Time utility_time;
    Game gioco = Game(&src, &font);
    text.setFont(font);
    text.setCharacterSize(100);
    text.setFillColor(Color::Red);
    text.setPosition(lenght/2 , heigth/2);

    sf::Time timePerFrame = sf::seconds(1.0f / 60.0f); // 60 frames per second
    sf::Clock deltaClock;  // This will track how much time has past since the last frame
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    
    /// FINESTRA
    
	while (window.isOpen()) {
		Event event1;
		while (window.pollEvent(event1)) {
			if (event1.type == Event::Closed)
				window.close();
		}
        sf::Time deltaTime = deltaClock.restart();  // Restart returns the time since the last restart call
        timeSinceLastUpdate += deltaTime;
        
        while (timeSinceLastUpdate >= timePerFrame){
            window.clear(Color::Black);
            timeSinceLastUpdate -= timePerFrame;
            gioco.gestisci(&window, &src, &font, timePerFrame);
            window.display(); // Why does this have to be inside the while?
                              // maybe SFML can't redisplay the same stuff so it stutters?
        }
            
        
    }
	return 0;
}
