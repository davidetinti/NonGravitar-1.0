#pragma once
#include "SingleStraightBullets.hpp"

class TripleBullets: public Bullets{
    
    SingleStraightBullets left, centre, right;
    
    void cleanup(Terreno *terrain);
    
public:
    
    TripleBullets();
    TripleBullets(int time_btw_shoot, int damage, int speed,
                  int tx_nr, int sd_nr, bool autoshoot, Resources *src);
    
    void addSingleBullet(Sprite entity, Keyboard::Key pulsante);
    void renderBullet();
    int checkCollision(FloatRect p);
};

