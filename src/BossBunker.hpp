#pragma once
#include "Bunker.hpp"

class BossBunker: public Bunker{
    
protected:
    
    const int DAMAGE = 10;
    const int SPEED = 10;
    const int BUNKER_NR = 3;
    double radius;
    Vector2f centre;
    void updateRotation();
    
public:
    
    BossBunker();
    BossBunker(Resources *src, double radius, Vector2f centre = Vector2f());
    
    Vector2f newPosition(double angle);
    void updatePosition(double angle);
};
