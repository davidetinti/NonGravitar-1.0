#include "Pianeta.hpp"

// COSTRUTTORI =======================================

Pianeta::Pianeta(bool ex, int rel_x, int rel_y, int gr_x, int gr_y, int screens, Pianeta *n)
                : exist(ex), relative_x(rel_x), relative_y(rel_y), grid_x(gr_x), grid_y(gr_y),
                  tot_schermate(screens), next(n){
                      interno = GPlanet();
                      diameter = 32;
                  }

uPlanets::uPlanets(){
    
}

uPlanets::uPlanets(Resources *s){
    int str_l[] = {50,50,360,360,670,670,980,980};
    int str_h[] = {60,410,60,410,60,410,60,410};

    src = s;
    head = new Pianeta(true, rand() % 251, rand() % 251, str_l[0], str_h[0], 3 + rand() % 8, NULL);
    head->interno = GPlanet();
    spriteSetup(head);
    current = head;
    Pianeta *pp = head;
    bool exists = false;
    for (int i = 1; i < 8; i++) {
        exists = rand() % 6 > 2;
        if(exists){
            pp->next = new Pianeta(true, rand() % 251, rand() % 251, str_l[i], str_h[i], 3 + rand() % 8, NULL);
            pp = pp->next;
            spriteSetup(pp);
        }
    }
    explosion_tx = src->caricaTexture(19);
    explosion.setTexture(*explosion_tx);
    //explosion.setOrigin(<#float x#>, <#float y#>)
}

// SETTERS E GETTERS =================================

Pianeta* uPlanets::getHead(){
    return head;
}

void uPlanets::setHead(Pianeta* h){
    head = h;
}

Pianeta* uPlanets::getCurrent(){
    return current;
}

void uPlanets::setCurrent(Pianeta* h){
    current = h;
}

// FUNZIONI ==========================================

void uPlanets::handle(Nave *player){
    lista_schermate_pianeta *iterator = current->interno.getHead();
    bool no_bunkers = true;
    current->interno.handle(player);
    /*
    for (int i = 0; i < current->tot_schermate; i++){
        if (iterator->enemies.getHead() == NULL){
            iterator = iterator->next;
        } else {
            no_bunkers = false;
        }
    }
    if (no_bunkers) {
        player->nave.setPosition(player->getX_planet(), player->getY_planet());
        player->nave.setRotation(player->getAnglePlanet() + 180);
        player->setAtPlanet(false);
        current->exist = false;
        deletePlanet(current);
    }
    */
}

void uPlanets::spriteSetup(Pianeta* p){
    p->planet_tx = src->caricaTexture(p->tot_schermate + 2);
    p->planet.setTexture(*p->planet_tx);
    p->planet.setOrigin(Vector2f(p->planet_tx->getSize().x/2, p->planet_tx->getSize().y/2));
    p->planet.setPosition(p->relative_x + p->grid_x, p->relative_y + p->grid_y);
    p->planet.setTextureRect(IntRect(0, 0, p->planet_tx->getSize().x, p->planet_tx->getSize().y));
    p->planet.scale(0.2, 0.2);
}

void uPlanets::deletePlanet(Pianeta* p){
    if(p!=NULL){
        Pianeta *tmp = getHead();
        while(tmp != NULL){
            if(tmp->next == p && !p->exist) {
                tmp->next = p->next;
                delete p;
            }
            if(tmp!=NULL) tmp = tmp->next;
        }
    }
}
