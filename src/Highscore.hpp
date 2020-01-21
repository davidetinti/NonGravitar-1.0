#pragma once
#include "Resources.hpp"

struct ScoreRow {
    Text rank,name,score;
};

class Highscore {
protected:
    Resources *src;
    list<ScoreRow*> scores;
    fstream file;
    string player_name;;
    Text* player;
    Text* score;
    Clock insertion_clock;
public:
    
    /**
     Default constructor.
    */
    Highscore();
    
    /**
     Main constructor.

     @param src pointer to main game's Resources class.
    */
    Highscore(Resources *src);
    
    /**
     Set the player text string.

     @param text string to replace.
    */
    void setTextPlayer(Text* text);
    
    /**
     Set the score text string.

     @param text string to replace.
    */
    void setTextScore(Text* text);
    
    /**
     Draw the highscore grid in the highscore scene.
    */
    void draw();
    
    /**
     Handle the player text insertion, verify if the new score is an highscore.

     @return true if Key::Enter is pressed, else false.
    */
    bool insert();
    
    /**
     Verify if the score is a new highscore, and if it's true insert it in the Highscore File
     and in the Highscore Tab in Highscore Scene.

     @param player string containing inserted player name.
     @param score string containing score reached.
    */
    void checkNewScore(Text* player, Text* score);
    
};
