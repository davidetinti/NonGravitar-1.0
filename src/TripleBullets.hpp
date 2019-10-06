#include "Terreno.hpp"
#include "SingleStraightBullets.hpp"

using namespace sf;
using namespace std;


class TripleBullets: public Bullets{
    SingleStraightBullets left, centre, right;
public:
    void addSingleBullet(Sprite entity, Keyboard::Key pulsante, int tempo);
    TripleBullets(int time_btw_shoot, int damage, int speed, int tx_nr, int sd_nr, bool autoshoot, Risorse *src);
    TripleBullets();
    void renderBullet(Terreno *terrain, Time perFrame);
    int checkCollision(FloatRect p);
};

