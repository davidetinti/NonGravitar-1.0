#ifndef Animation_hpp
#define Animation_hpp

#include "SourceLoader.hpp"

class Animation {
    
protected:
    
    SourceLoader *src;
    Sprite sprite;
    int frameWidth, frameHeight, currentX, currentY, maxX, maxY;
    
public:
    
    Animation();
    Animation(int x, int y, int tx_nr, int rows, int columns, float scale, SourceLoader *src);
    bool handle();
    
};

struct AnimationList{
    Animation *current;
    AnimationList *next;
    AnimationList *prev;
};

#endif /* Animation_hpp */
