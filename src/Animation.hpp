#pragma once
#include "SourceLoader.hpp"

class Animation {
    
protected:
    
    SourceLoader *src;
    Sprite sprite;
    int frame_width, frame_height, max_x, max_y;
    double current_x, current_y, speed;
    
public:
    
    Animation();
    Animation(int x, int y, int tx_nr, int rows, int columns, float scale, SourceLoader *src, double image_speed = 1);
    Sprite* getSprite();
    bool isEnded();
    void handle();
    
};
