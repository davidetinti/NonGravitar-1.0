#include <ctime>
#include "Game.hpp"
//#include "Animation.hpp"

int main() {
    
    // INIZIALIZZAZIONE ==============================
    Resources src;
    Game game = Game(&src);
    //Animation prova = Animation(200, 200, 20, 1, 19, &src);
    Time timeSinceLastUpdate = Time::Zero;
    Clock deltaClock;       // This will track how much time has past since the last frame
    
    // FINESTRA ======================================
	while (src.getWindow()->isOpen()) {
		Event event1;
		while (src.getWindow()->pollEvent(event1)) {
			if (event1.type == Event::Closed)
				src.getWindow()->close();
		}
        Time deltaTime = deltaClock.restart();  // Restart returns the time since the last restart call
        timeSinceLastUpdate += deltaTime;
        if (timeSinceLastUpdate >= *src.getTimePerFrame()){
            src.getWindow()->clear(Color::Black);
            timeSinceLastUpdate -= *src.getTimePerFrame();
            game.handle();
            //prova.handle();
            src.getWindow()->display();
        }
    }
	return 0;
}
