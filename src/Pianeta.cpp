#include "pch.h"
#include "Pianeta.hpp"

using namespace sf;
using namespace std;

/// COSTRUTTORI /////////////////////////////////////////////////////

Pianeta::Pianeta(bool ex, int rel_x, int rel_y, int gr_x, int gr_y, int screens, Pianeta *n)
                : exist(ex), relative_x(rel_x), relative_y(rel_y), grid_x(gr_x), grid_y(gr_y),
                  tot_schermate(screens), next(n){
                      interno = GPlanet();
                      diameter = 32;
                  }

uPlanets::uPlanets(){
    
}

uPlanets::uPlanets(Risorse *s){
    str_l[0] = 50;
    str_l[1] = 50;
    str_l[2] = 360;
    str_l[3] = 360;
    str_l[4] = 670;
    str_l[5] = 670;
    str_l[6] = 980;
    str_l[7] = 980;
    str_h[0] = 60;
    str_h[1] = 410;
    str_h[2] = 60;
    str_h[3] = 410;
    str_h[4] = 60;
    str_h[5] = 410;
    str_h[6] = 60;
    str_h[7] = 410;
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

///  SETTERS E GETTERS  /////////////////////////////////////////////

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

///  FUNZIONI  //////////////////////////////////////////////////////

void uPlanets::gestione(RenderWindow *window, Nave *player, Transitions *transizioni, Time perFrame){
    ptr_lista_schermate_pianeta iterator = current->interno.getHead();
    bool no_bunkers = true;
    current->interno.gestione(window, player, perFrame);
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
        player->setSpaceshipAcceleration(0);
        player->setAtPlanet(false);
        current->exist = false;
        deletePlanet(current);
        transizioni->outPlanet(window);
    }
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
