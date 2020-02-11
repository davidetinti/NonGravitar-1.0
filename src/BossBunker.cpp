#include "BossBunker.hpp"


BossBunker::BossBunker(){
}


BossBunker::BossBunker(Resources *s, double r){
    src = s;
    explosion_tx = src->getTexture(20);
    bunker_tx = src->getTexture(43);
    double angle = 0;
    double offset = 360 / BUNKER_NR;
    Vector2f newPos;
    radius = r + 50;
    centre = Vector2f(src->getLength()/2, src->getHeight()/2);
    bunkers = new list<bunker>;
    newPos = Vector2f(centre.x+radius,centre.y);
    for(int i = 0; i < BUNKER_NR; i++){
        bunkers->push_front(bunker(0,newPos.x, newPos.y,10,
                          new SingleStraightBullets(1500, 100, 2, 14, true, src),bunker_tx,explosion_tx,angle));
        angle = angle + offset;
        newPos = newPosition(angle);
    }
}


Vector2f BossBunker::newPosition(double angle){
    Vector2f *start = new Vector2f(radius, 0);
    angle = angle *M_PI/180;
    double finalx = (start->x) * cos(angle) - start->y * sin(angle);
    double finaly = (start->x) * sin(angle) + start->y * cos(angle);
    Vector2f *result = new Vector2f(finalx + centre.x,finaly + centre.y);
    return *result;
}


void BossBunker::updatePosition(double angle){
    list<bunker>::iterator it = bunkers->begin();
    list<bunker>::iterator end = bunkers->end();
    double newAng = 0;
    int i = 0;
    Vector2f newPos;
    while (it != end){
        newAng = angle + it->boss_bunker_offset;
        newPos = newPosition(newAng);
        it->x = newPos.x;
        it->y = newPos.y;
        it->bunker_sprite.setPosition(it->x, it->y);
        it++;
        i++;
    }
    updateRotation();
}


void BossBunker::updateRotation(){
    list<bunker>::iterator iterator = bunkers->begin();
    list<bunker>::iterator end = bunkers->end();
    while(iterator != end){
        iterator->bunker_sprite.setRotation(270 + atan2(centre.y-iterator->bunker_sprite.getPosition().y, 
                                        centre.x-iterator->bunker_sprite.getPosition().x) * (180/M_PI));
        iterator++;
    }
}
