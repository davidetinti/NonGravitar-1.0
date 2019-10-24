#include "BossBunker.hpp"

BossBunker::BossBunker(){
    //chissà perché serve il costruttore di default. qualcuno mi illumina?
}

BossBunker::BossBunker(Resources *s, double r, Vector2f c){
    explosion_tx = src->caricaTexture(20);
    bunker_tx = src->caricaTexture(3);
    double angle = 0;
    double offset = 360 / N_BUNKER;
    Vector2f newPos;
    bunkerlist *tmp;
    src = s;
    radius = r;
    centre = Vector2f(src->getLength()/2, src->getHeight()/2);
    head = new bunkerlist(0,100,centre.x + radius, centre.y,10,NULL,
                          new SingleStraightBullets(400, 100, 10, 14, 0, true, src),true);
    spriteSetup(head);
    cout << "head is at  " << head->x << "\t" << head->y << '\n';
    tmp = head;
    for(int i = 0; i < N_BUNKER - 1; i++){
        angle = angle + offset;
        newPos = newPosition(angle);
        tmp->next = new bunkerlist(0,100,newPos.x, newPos.y,10,NULL,
                          new SingleStraightBullets(400, 100, 10, 14, 0, true, src),true);
        tmp = tmp->next;
        spriteSetup(tmp);
        cout << "number "<< i+1 << " is at  " << tmp->x << "\t" << tmp->y << '\n';
        tmp->next = NULL;
    }
}

Vector2f BossBunker::newPosition(double angle){
    double x = (centre.x + radius) * cos(angle) - centre.y * sin(angle);
    double y = (centre.x + radius) * sin(angle) + centre.y * cos(angle);
    return Vector2f(x,y);
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
        iterator = iterator->next;
        i++;
    }
}