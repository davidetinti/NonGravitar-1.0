#ifndef Game_hpp
#define Game_hpp

#include "Universe.hpp"
#include "Stage.hpp"

class Game{
    
protected:
    
    Resources *src;
    Stage *home, *credits, *game, *pause, *settings, *game_over, *highscore, *active;
    Universe *universe;
    Texture *tmp_background;
    void handleStageControls();
    
public:
    
    Game();
    Game(Resources *src);
    void handle();
    
};

#endif /* Game_hpp */
