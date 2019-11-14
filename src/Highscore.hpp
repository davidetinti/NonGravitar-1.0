#ifndef Highscore_hpp
#define Highscore_hpp

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
    
private:
    
    
    
public:
    
    Highscore();
    Highscore(Resources *src);
    void load();
    void draw();
    bool insert();
    void setTextPlayer(Text* text);
    void setTextScore(Text* text);
    void checkNewScore(Text* player, Text* score);
    
};

#endif /* Highscore_hpp */
