#include "BossBunker.hpp"

BossBunker::BossBunker(){
    //chissà perché serve il costruttore di default. qualcuno mi illumina?
}

BossBunker::BossBunker(Resources *s, double r, Vector2f c){
    src = s;
    explosion_tx = src->caricaTexture(20);
    bunker_tx = src->caricaTexture(3);
    double angle = 0;
    double offset = 360 / N_BUNKER;
    Vector2f newPos;
    bunkerlist *tmp;
    radius = r;
    centre = Vector2f(src->getLength()/2, src->getHeight()/2);
    head = new bunkerlist(0,100,centre.x + radius, centre.y,10,NULL,
                          new SingleStraightBullets(400, 100, 10, 14, 0, true, src),true);
    spriteSetup(head);
    tmp = head;
    for(int i = 0; i < N_BUNKER - 1; i++){
        angle = angle + offset;
        newPos = newPosition(angle);
        tmp->next = new bunkerlist(0,100,newPos.x, newPos.y,10,NULL,
                          new SingleStraightBullets(400, 100, 10, 14, 0, true, src),true);
        tmp = tmp->next;
        spriteSetup(tmp);
        tmp->next = NULL;
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
    bunkerlist *iterator = head;
    double newAng = 0;
    double offset = 360 / N_BUNKER;
    int i = 0;
    Vector2f newPos;
    while (iterator != NULL){
        newAng = angle + offset * i;
        newPos = newPosition(newAng);
        iterator->x = newPos.x;
        iterator->y = newPos.y;
        iterator->bunker.setPosition(iterator->x, iterator->y);
        iterator = iterator->next;
        i++;
    }
    updateRotation();
}

void BossBunker::updateRotation(){
    bunkerlist *iterator = head;
    while(iterator != NULL){
        iterator->bunker.setRotation(270 + atan2(centre.y-iterator->bunker.getPosition().y, 
                                        centre.x-iterator->bunker.getPosition().x) * (180/M_PI));
        iterator = iterator->next;
    }
}
