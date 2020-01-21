#pragma once
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
    HUD hud;
    void handleStageControls();
    void updateScore();
    
public:
    
    Game();
    Game(Resources *src);
    void handle();
    
};
