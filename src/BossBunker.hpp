#pragma once
#include "Bunker.hpp"

class BossBunker: public Bunker{
    
protected:
    
    const int DAMAGE = 10;
    const int SPEED = 10;
    const int N_BUNKER = 3;
    double radius;
    Vector2f centre;
    void updateRotation();
    
public:
    
    Vector2f newPosition(double angle);
    BossBunker();
    BossBunker(Resources *src, double radius, Vector2f centre = Vector2f());
    void updatePosition(double angle);
};
