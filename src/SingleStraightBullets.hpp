#include "Terreno.hpp"
#include "Bullets.hpp"

using namespace sf;
using namespace std;


class SingleStraightBullets: public Bullets{
public:
    void addSingleBullet(Sprite entity, Keyboard::Key pulsante, int tempo);
    void renderBullet(Time perFrame);
    int checkCollision(FloatRect p);
    SingleStraightBullets(int time_btw_shoot, int damage, int speed, int tx_nr, int sd_nr, bool autoshoot, Resources *src);
    SingleStraightBullets();
    void cleanup(Terreno *terrain);
}; 

