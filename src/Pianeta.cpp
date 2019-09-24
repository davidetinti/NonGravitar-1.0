#include "pch.h"
#include "Pianeta.hpp"

using namespace sf;
using namespace std;

/// COSTRUTTORI /////////////////////////////////////////////////////

uPlanets::uPlanets(){
    
}

uPlanets::uPlanets(Risorse *src){
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
    pp = new Pianeta;
    pp->tot_schermate = 3 + rand() % 8;
    pp->exist = (rand() % 6 > 2);
    pp->relative_x = rand() % 251;
    pp->relative_y = rand() % 251;
    pp->grid_x = str_l[0];
    pp->grid_y = str_h[0];
    pp->interno = GPlanet();
    pp->next = NULL;
    pp->planet_tx = src->caricaTexture(pp->tot_schermate + 2);
    pp->planet.setTexture(*pp->planet_tx);
    pp->planet.setOrigin(Vector2f(pp->planet_tx->getSize().x/2, pp->planet_tx->getSize().y/2));
    pp->planet.setPosition(pp->relative_x + pp->grid_x, pp->relative_y + pp->grid_y);
    pp->planet.setTextureRect(IntRect(0, 0, pp->planet_tx->getSize().x, pp->planet_tx->getSize().y));
    pp->planet.scale(0.2, 0.2);
    hp = pp;
    for (int i = 1; i < 8; i++) {
        pp->next = new Pianeta;
        pp = pp->next;
        pp->interno = GPlanet();
        pp->tot_schermate = 3 + rand() % 8;
        pp->exist = (rand() % 6 > 2);
        pp->relative_x = rand() % 251;
        pp->relative_y = rand() % 251;
        pp->grid_x = str_l[i];
        pp->grid_y = str_h[i];
        pp->next = NULL;
        pp->planet_tx = src->caricaTexture(pp->tot_schermate + 2);
        pp->planet.setTexture(*pp->planet_tx);
        pp->planet.setOrigin(Vector2f(pp->planet_tx->getSize().x/2, pp->planet_tx->getSize().y/2));
        pp->planet.setPosition(pp->relative_x + pp->grid_x, pp->relative_y + pp->grid_y);
        pp->planet.setTextureRect(IntRect(0, 0, pp->planet_tx->getSize().x, pp->planet_tx->getSize().y));
        pp->planet.scale(0.2, 0.2);
    }
    pp = hp;
    explosion_tx = src->caricaTexture(19);
    explosion.setTexture(*explosion_tx);
    //explosion.setOrigin(<#float x#>, <#float y#>)
}

///  SETTERS E GETTERS  /////////////////////////////////////////////

ptr_Pianeta uPlanets::getPP(){
    return this->pp;
}

ptr_Pianeta uPlanets::getHP(){
    return this->hp;
}

void uPlanets::setPP(ptr_Pianeta pp){
    this->pp = pp;
}

void uPlanets::setHP(ptr_Pianeta hp){
    this->hp = hp;
}

///  FUNZIONI  //////////////////////////////////////////////////////

void uPlanets::gestione(RenderWindow *window, Nave *player, Transitions *transizioni, Time perFrame){
    ptr_lista_schermate_pianeta iterator = pp->interno.getHead();
    bool no_bunkers = true;
    pp->interno.gestione(window, player, perFrame);
    for (int i = 0; i < pp->tot_schermate; i++){
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
        pp->exist = false;
        transizioni->outPlanet(window);
    }
}
