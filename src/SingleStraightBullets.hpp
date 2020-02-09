#pragma once
#include "Bullets.hpp"

class SingleStraightBullets : public Bullets{
    
public:
    
    SingleStraightBullets();
    SingleStraightBullets(int time_btw_shoot, int damage, int speed,
                          int tx_nr, int sd_nr, bool autoshoot, Resources *src);
    
    void addSingleBullet(Sprite entity, Keyboard::Key pulsante);
    void renderBullet();
    void cleanup(Terreno *terrain);
}; 

