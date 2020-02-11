#include "SingleStraightBullets.hpp"


SingleStraightBullets::SingleStraightBullets(){
    
}


SingleStraightBullets::SingleStraightBullets(int time_btw_shoot, int damage, int speed,
                                int tx_nr, bool autoshoot, Resources *src):
Bullets(time_btw_shoot,damage,speed,tx_nr,autoshoot,src){
    
}


void SingleStraightBullets::addSingleBullet(Sprite entity, Keyboard::Key pulsante){
    double x = entity.getPosition().x;
    double y = entity.getPosition().y;
    double rotation = entity.getRotation();
    Time elapsed = bullet_time.getElapsedTime();
    if ((!autoshoot && Keyboard::isKeyPressed(pulsante) && elapsed.asMilliseconds()>time_btw_shoot) || 
        (autoshoot && elapsed.asMilliseconds() > (time_btw_shoot))) { //perché tempo? a cosa dovrebbe servire
        bulletList->push_front(proiettile(x,y,rotation,bullet_tx));
        bullet_time.restart();
    }
}


void SingleStraightBullets::renderBullet(){
    list<proiettile>::iterator it = bulletList->begin();
    list<proiettile>::iterator end = bulletList->end();
    while (it != end){
        double angle = M_PI * it->bullet.getRotation() / 180;
        it->bullet.move(-sin(angle) * speed * src->getTimePerFrame()->asSeconds() * 100,
                        cos(angle) * speed * src->getTimePerFrame()->asSeconds() * 100);
        src->getWindow()->draw(it->bullet);
        it++;
    }
}


void SingleStraightBullets::cleanup(Terrain *terrain){
    list<proiettile>::iterator iterator = bulletList->begin();
    list<proiettile>::iterator end = bulletList->end();
    Time elapsed;
    while (iterator != end){
            elapsed = iterator->invuln_clock.getElapsedTime();
            if ((elapsed.asMilliseconds() > invuln_time) &&
                (terrain->isBoss() ?  outsideBounds(iterator) : outsideBounds(iterator, terrain))){
                iterator = bulletList->erase(iterator);
            } else {
                iterator++;
            }
    }
}
