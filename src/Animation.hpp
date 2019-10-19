#ifndef Animation_hpp
#define Animation_hpp

#include "SourceLoader.hpp"

class Animation {
    
protected:
    
    SourceLoader *src;
    Sprite sprite;
    int frameWidth, frameHeight, maxX, maxY;
    double currentX, currentY, speed;
    
public:
    
    Animation();
    Animation(int x, int y, int tx_nr, int rows, int columns, float scale, SourceLoader *src, double imagespeed = 1);
    bool handle();
    
};

#endif /* Animation_hpp */
