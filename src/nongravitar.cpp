#include <ctime>
#include "Game.hpp"
#include <unistd.h>
#include <stdio.h>

int main() {
    
    // INIZIALIZZAZIONE ==============================
    Resources src;
    Game game = Game(&src);
    Time timeSinceLastUpdate = Time::Zero;
    Clock deltaClock;       // This will track how much time has passed since the last frame
    
    // FINESTRA ======================================
	while (src.getWindow()->isOpen()) {
        Time deltaTime = deltaClock.restart();  // Restart returns the time since the last restart call
        timeSinceLastUpdate += deltaTime;
        if (timeSinceLastUpdate >= *src.getTimePerFrame()){
            src.handleEvents();
            src.getWindow()->clear(Color::Black);
            timeSinceLastUpdate -= *src.getTimePerFrame();
            game.handle();
            src.getWindow()->display();
        }
    }
	return 0;
}
