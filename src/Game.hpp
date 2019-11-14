#ifndef Game_hpp
#define Game_hpp

#include "Universe.hpp"
#include "Stage.hpp"
#include "Highscore.hpp"

class Game{
    
protected:
    
    Resources *src;
    Stage *home, *credits, *game, *pause, *settings, *game_over, *highscore, *active;
    Universe *universe;
    Texture *tmp_background;
    Text* points;
    Highscore highscore_st;
    void handleStageControls();
    void updateScore();
    
public:
    
    Game();
    Game(Resources *src);
    void handle();
    
};

#endif /* Game_hpp */
