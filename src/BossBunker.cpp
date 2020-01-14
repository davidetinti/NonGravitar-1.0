#include "BossBunker.hpp"

BossBunker::BossBunker(){
}

BossBunker::BossBunker(Resources *s, double r, Vector2f c){
    src = s;
    explosion_tx = src->caricaTexture(20);
    bunker_tx = src->caricaTexture(3);
    double angle = 0;
    double offset = 360 / N_BUNKER;
    Vector2f newPos;
    bunkerlist *tmp;
    radius = r + bunker_tx->getSize().y;
    centre = Vector2f(src->getLength()/2, src->getHeight()/2);
    bunkers = new list<bunkerlist>;
    int nr_bunkers = src->rand(1,4);
    newPos = Vector2f(centre.x+radius,centre.y);
    for(int i = 0; i < N_BUNKER; i++){
        bunkers->push_front(bunkerlist(0,100,newPos.x, newPos.y,10,
                          new SingleStraightBullets(400, 100, 2, 14, 0, true, src),bunker_tx,explosion_tx));
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
    list<bunkerlist>::iterator it = bunkers->begin();
    list<bunkerlist>::iterator end = bunkers->end();
    double newAng = 0;
    double offset = 360 / N_BUNKER;
    int i = 0;
    Vector2f newPos;
    while (it != end){
        newAng = angle + offset * i;
        newPos = newPosition(newAng);
        it->x = newPos.x;
        it->y = newPos.y;
        it->bunker.setPosition(it->x, it->y);
        it++;
        i++;
    }
    updateRotation();
}

void BossBunker::updateRotation(){
    list<bunkerlist>::iterator iterator = bunkers->begin();
    list<bunkerlist>::iterator end = bunkers->end();
    while(iterator != end){
        iterator->bunker.setRotation(270 + atan2(centre.y-iterator->bunker.getPosition().y, 
                                        centre.x-iterator->bunker.getPosition().x) * (180/M_PI));
        iterator++;
    }
}
