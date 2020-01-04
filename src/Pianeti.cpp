#include "Pianeti.hpp"

// COSTRUTTORI =======================================

SinglePlanet::SinglePlanet(bool ex, int rel_x, int rel_y, int gr_x, int gr_y, int screens, Resources *s)
                : exist(ex), relative_x(rel_x), relative_y(rel_y), grid_x(gr_x), grid_y(gr_y),
                  tot_schermate(screens){
                      interno = GPlanet();
                      diameter = 32;
                      spriteSetup(s);
                  }

void SinglePlanet::spriteSetup(Resources *src){
    this->planet_tx = src->caricaTexture(this->tot_schermate + 2);
    this->planet.setTexture(*planet_tx);
    this->planet.setOrigin(Vector2f(planet_tx->getSize().x/2, planet_tx->getSize().y/2));
    this->planet.setPosition(relative_x + grid_x, relative_y + grid_y);
    this->planet.setTextureRect(IntRect(0, 0, planet_tx->getSize().x, planet_tx->getSize().y));
    this->planet.scale(0.2, 0.2);
}

Pianeti::Pianeti(){
    
}

Pianeti::Pianeti(Resources *s){
    int str_l[] = {50,50,360,360,670,670,980,980};
    int str_h[] = {60,410,60,410,60,410,60,410};

    src = s;
    planetlist = list<SinglePlanet>();
    bool exists = false;
    for (int i = 0; i < 8; i++) {
        exists = src->rand(0,2) > 0;
        if(exists){
            planetlist.push_back(SinglePlanet(true, src->rand(0,250), src->rand(0,250), str_l[i], 
            str_h[i], src->rand(3,10),s));
        }
    }
    explosion_tx = src->caricaTexture(19);
    explosion.setTexture(*explosion_tx);
}

// SETTERS E GETTERS =================================

SinglePlanet* Pianeti::getHead(){
    return head;
}

void Pianeti::setHead(SinglePlanet* h){
    head = h;
}

SinglePlanet* Pianeti::getCurrent(){
    return current;
}

void Pianeti::setCurrent(SinglePlanet* h){
    current = h;
}

// FUNZIONI ==========================================

void Pianeti::handle(Nave *player){
    lista_schermate_pianeta *iterator = current->interno.getHead();
    bool no_bunkers = true;
    current->interno.handle(player);
    /*
    for (int i = 0; i < current->tot_schermate; i++){
        if (iterator->enemies.getHead() == nullptr){
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


void Pianeti::deletePlanet(SinglePlanet* p){
    list<SinglePlanet>::iterator it = planetlist.begin();
    bool deleted = false;
    while(it != planetlist.end() && !deleted){
        if(&*it == p) {
            it = planetlist.erase(it);
            deleted = true;
        }
        it++;
    }
}

void Pianeti::draw(){
    list<SinglePlanet>::iterator it = planetlist.begin();
    list<SinglePlanet>::iterator end = planetlist.end();
    while (it != end) {
        src->getWindow()->draw(it->planet);
        it++;
    }
}