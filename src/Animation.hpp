#ifndef Animation_hpp
#define Animation_hpp

#include "Resources.hpp"

class Animation {
    
protected:
    
    Resources *src;
    Sprite sprite;
    int frameWidth, frameHeight, currentX, currentY, maxX, maxY;
    
public:
    
    Animation();
    Animation(int x, int y, int tx_nr, int rows, int columns, Resources *src);
    void handle();
    
};

struct AnimationList{
    Animation current;
    AnimationList *next;
};

#endif /* Animation_hpp */
