#include "pch.h"
#include <ctime>
#include "Game.hpp"

using namespace sf;
using namespace std;

int main() {
    
    
    /// INIZIALIZZAZIONE ///////////////////////////////////////
    
    srand((unsigned)time(NULL));
    Risorse src;
    Time timePerFrame = seconds(1.0f / 60.0f); // 60 frames per second
    Clock deltaClock;  // This will track how much time has past since the last frame
    Time timeSinceLastUpdate = Time::Zero;
    Clock utility_clock;
    Time utility_time;
    Game game = Game(&src, &timePerFrame);
    Text text;
    
    /// FINESTRA
    
	while (src.getWindow()->isOpen()) {
		Event event1;
		while (src.getWindow()->pollEvent(event1)) {
			if (event1.type == Event::Closed)
				src.getWindow()->close();
		}
        Time deltaTime = deltaClock.restart();  // Restart returns the time since the last restart call
        timeSinceLastUpdate += deltaTime;
        
        while (timeSinceLastUpdate >= timePerFrame){
            src.getWindow()->clear(Color::Black);
            timeSinceLastUpdate -= timePerFrame;
            game.handle(timePerFrame);
            src.getWindow()->display(); // Why does this have to be inside the while?
                              // maybe SFML can't redisplay the same stuff so it stutters?
        }
            
        
    }
	return 0;
}
