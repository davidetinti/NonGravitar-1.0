#pragma once
#include "Bullets.hpp"

class SingleStraightBullets : public Bullets{
public:
    void addSingleBullet(Sprite entity, Keyboard::Key pulsante);
    void renderBullet(Time perFrame);
    SingleStraightBullets(int time_btw_shoot, int damage, int speed,
                          int tx_nr, int sd_nr, bool autoshoot, Resources *src);
    SingleStraightBullets();
    void cleanup(Terreno *terrain);
}; 

