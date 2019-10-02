#include "pch.h"
#include "Universo.hpp"

using namespace sf;
using namespace std;

/// COSTRUTTORI /////////////////////////////////////////////////////

lista_schermate::lista_schermate(int x_n, int y_n, Risorse *src, lista_schermate *d, lista_schermate *s, 
        lista_schermate *u, lista_schermate *down, lista_schermate *nxt) : dx(d), sx(s), up(u),
        dw(down), x(x_n), y(y_n), next(nxt){
            pianeti = uPlanets(src);
        }

Universo::Universo(){
    
} 

Universo::Universo(Risorse *src, Time *time){
    this->src = src;
    hud = HUD(src);
    player = Nave(src, time);
    universe_tx = src->caricaTexture(2);
    background.setPosition(0, 0);
    background.setTexture(*universe_tx);
    active = new lista_schermate(0,0,src);
    head_list = active;
    tail = head_list;
}

///  SETTERS E GETTERS  /////////////////////////////////////////////

lista_schermate *Universo::getActive(){
    return  active;
}

lista_schermate *Universo::getTail(){
    return  tail;
}

lista_schermate *Universo::getHeadList(){
    return  head_list;
}

///  FUNZIONI  //////////////////////////////////////////////////////

lista_schermate *Universo::find(int x, int y){
    lista_schermate *b = head_list;
    bool found = false;
    while (b != NULL && !found) {
        if (x == b->x && y == b->y) {
            found = true;
        } else {
            b = b->next;
            }
    }
    return b;
}

void Universo::move(int x, int y){
    if (x == 1 && y == 0) {
        if (active->dx == NULL) {
            active->dx = new lista_schermate(active->x + x,active->y + y,src);
            addToList(active->dx);
        }
        active = active->dx;
    }
    if (x == 0 && y == 1) {
        if (active->up == NULL) {
            active->up = new lista_schermate(active->x + x, active->y + y,src);
            addToList(active->up);
        }
        active = active->up;
    }
    if (x == -1 && y == 0) {
        if (active->sx == NULL) {
            active->sx = new lista_schermate(active->x+x,active->y+y,src);
            addToList(active->sx);
        }
        active = active->sx;
    }
    if (x == 0 && y == -1) {
        if (active->dw == NULL) {
            active->dw = new lista_schermate(active->x+x,active->y+y,src);
            addToList(active->dw);
        }
        active = active->dw;
    }
    active->dx = find((active->x + 1), active->y);
    active->sx = find((active->x - 1), active->y);
    active->up = find(active->x, (active->y + 1));
    active->dw = find(active->x, (active->y - 1));
}

void Universo::disegnaPianeti(){
    Pianeta *planetIterator = active->pianeti.getHead();
    while (planetIterator != NULL) {
        if (planetIterator->exist) src->getWindow()->draw(planetIterator->planet);
        planetIterator = planetIterator->next;
    }
}

void Universo::handle(Transitions *transizioni, sf::Time timePerFrame){
    player.movements();
    player.handleThrust();

    if (!player.getAtPlanet()){
        //verify if out of bounds
        if (player.nave.getPosition().x >= src->getLength()) {
            player.nave.setPosition(0, player.nave.getPosition().y);
            move(1, 0);
        }
        if (player.nave.getPosition().y >= src->getHeight()) {
            player.nave.setPosition(player.nave.getPosition().x, 0);
            move(0, 1);
        }
        if (player.nave.getPosition().x < 0) {
            player.nave.setPosition(src->getLength(), player.nave.getPosition().y);
            move(-1, 0);
        }
        if (player.nave.getPosition().y < 0) {
            player.nave.setPosition(player.nave.getPosition().x, src->getHeight());
            move(0, -1);
        }
        Pianeta *planetIterator = active->pianeti.getHead();
        while (planetIterator != NULL && !player.getAtPlanet()){
            if (contactPlanet(player.nave.getPosition(),planetIterator)){
                active->pianeti.setCurrent(planetIterator);
                planetIterator->interno.inizializza(planetIterator->tot_schermate, src);
                //transizioni->inPlanet(&planetIterator->interno.getHead()->terrain, planetIterator->tot_schermate);
                player.setAtPlanet(true);
                
                player.braceForEntry(planetIterator->planet.getPosition(), src->getLength());
            }
            //Ovviamente planetIterator non può mai essere NULL. Al più sarà l'ultimo della lista
            planetIterator = planetIterator->next;
        }
    }
    if (player.getAtPlanet()){
        if (player.nave.getPosition().x >= src->getLength()) {
			player.nave.setPosition(0, player.nave.getPosition().y);
			active->pianeti.getCurrent()->interno.cambia_schermata(1);
        }
        if (player.nave.getPosition().x < 0) {
			player.nave.setPosition(src->getLength(), player.nave.getPosition().y);
			active->pianeti.getCurrent()->interno.cambia_schermata(-1);
        }
        if (player.nave.getPosition().y < 0) {
            player.nave.setPosition(player.getX_planet(), player.getY_planet());
            player.nave.setRotation(player.getAnglePlanet());
			player.setDxDy(0, 0.1);
            player.setAtPlanet(false);
            active->pianeti.setCurrent(NULL);
        }
    }
}

void Universo::checkTerrain(){
    if (player.nave.getPosition().y + 22 >= active->pianeti.getCurrent()->interno.getCurrent()->terrain.get_Y(player.nave.getPosition().x))
        player.setIsDead(true);
}

bool Universo::contactPlanet(Vector2f pos, Pianeta* p){
    return abs(pos.x - (p->relative_x + p->grid_x)) < p->diameter &&
            abs(pos.y - (p->relative_y + p->grid_y)) < p->diameter &&
             p->exist ;
}

void Universo::addToList(lista_schermate *p){
    if(p != NULL){
        tail->next = p;
        tail = p;
    }
}
