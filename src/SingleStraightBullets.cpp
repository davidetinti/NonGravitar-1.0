#include "SingleStraightBullets.hpp"

using namespace sf;
//tx_nr dovrebbe essere deciso qui invece che dal caller
SingleStraightBullets::SingleStraightBullets(int time_btw_shoot, int damage, int speed, 
                                int tx_nr, int sd_nr, bool autoshoot, Resources *src):
                                Bullets(time_btw_shoot,damage,speed,tx_nr,sd_nr,autoshoot,src){}

void SingleStraightBullets::addSingleBullet(Sprite entity, Keyboard::Key pulsante, int tempo){
    double x = entity.getPosition().x;
    double y = entity.getPosition().y;
    double rotation = entity.getRotation();
    Time elapsed = bullet_time.getElapsedTime();
    if ((!autoshoot && Keyboard::isKeyPressed(pulsante) && elapsed.asMilliseconds()>time_btw_shoot) || 
        (autoshoot && elapsed.asMilliseconds() > (time_btw_shoot + tempo))) { //perché tempo? a cosa dovrebbe servire
        bulletList->push_front(proiettile(x,y,rotation,bullet_tx));
        bullet_time.restart();
    }
}

void SingleStraightBullets::renderBullet(Time perFrame){ //perFrame should be in Resources
    list<proiettile>::iterator it = bulletList->begin();
    list<proiettile>::iterator end = bulletList->end();
    while (it != end){
        double angle = M_PI * it->bullet.getRotation() / 180;
        it->bullet.move(-sin(angle)*speed*perFrame.asSeconds()*100,
                        cos(angle)*speed*perFrame.asSeconds()*100);
        src->getWindow()->draw(it->bullet);
        it++;
    }
}

SingleStraightBullets::SingleStraightBullets(){}

int SingleStraightBullets::checkCollision(FloatRect p){
    list<proiettile>::iterator it = bulletList->begin();
    list<proiettile>::iterator end = bulletList->end();
    int hit_counter = 0;
    while (it != end){
        if (collidesWith(it,p)){
            hit_counter++;
            it = bulletList->erase(it);
        } else {
            it++;
        }
    }
    return hit_counter;
}

void SingleStraightBullets::cleanup(Terreno *terrain){
    list<proiettile>::iterator iterator = bulletList->begin();
    list<proiettile>::iterator end = bulletList->end();
    Time elapsed;
    while (iterator != end){
            elapsed = iterator->invuln_clock.getElapsedTime();
            if ((elapsed.asMilliseconds() > invuln_time) &&
                (terrain == nullptr ?  outsideBounds(iterator) : outsideBounds(iterator, terrain))){
                iterator = bulletList->erase(iterator);
            } else {
                iterator++;
            }
    }
}