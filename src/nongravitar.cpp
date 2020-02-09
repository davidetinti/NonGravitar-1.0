#include <ctime>
#include "Game.hpp"
#include <unistd.h>
#include <stdio.h>

int main() {
    
    /// INIZIALIZZAZIONE
    Resources src;
    Game game = Game(&src);
    Time timeSinceLastUpdate = Time::Zero;
    Clock deltaClock;       // Conta il tempo passato dall'ultimo frame visualizzato
    
    /// FINESTRA
	while (src.getWindow()->isOpen()) {
        Time deltaTime = deltaClock.restart();
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
