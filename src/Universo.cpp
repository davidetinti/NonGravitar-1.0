#include "pch.h"
#include "Universo.hpp"

using namespace sf;
using namespace std;

/// COSTRUTTORI /////////////////////////////////////////////////////

Universo::Universo(){
    
}

Universo::Universo(int lenght, int heigth, Risorse *src, Font *font){
    hud = HUD(lenght, heigth, src, font);
    player = Nave(lenght, heigth, src);
    universe_tx = src->caricaTexture(2);
    universe.setPosition(0, 0);
    universe.setTexture(*universe_tx);
    altezza = heigth;
    larghezza = lenght;
    active = new schermata;
    active->dx = NULL;
    active->sx = NULL;
    active->up = NULL;
    active->dw = NULL;
    active->pianeti = uPlanets(src);
    active->x = 0;
    active->y = 0;
    list = new lista_schermate;
    list->x = active->x;
    list->y = active->y;
    list->it = active;
    list->next = NULL;
    head_list = list;
}

///  SETTERS E GETTERS  /////////////////////////////////////////////

ptr_schermata Universo::getActive(){
    return  this->active;
}

ptr_lista_schermate Universo::getList(){
    return  this->list;
}

ptr_lista_schermate Universo::getHeadList(){
    return  this->head_list;
}

///  FUNZIONI  //////////////////////////////////////////////////////

ptr_schermata Universo::find(int x, int y){
    ptr_lista_schermate b = head_list;
    ptr_schermata tmp = NULL;
    while (b != NULL) {
        if (x == b->x && y == b->y) {
            tmp = b->it;
        }
        b = b->next;
    }
    return tmp;
}

void Universo::move(int x, int y, Risorse *src){
    if (x == 1 && y == 0) {
        if (active->dx == NULL) {
            active->dx = new schermata;
            active->dx->x = active->x + x;
            active->dx->y = active->y + y;
            active->dx->pianeti = uPlanets(src);
            list->next = new lista_schermate;
            list = list->next;
            list->x = active->dx->x;
            list->y = active->dx->y;
            list->it = active->dx;
            list->next = NULL;
        };
        active = active->dx;
        active->dx = find((active->x + 1), active->y);
        active->sx = find((active->x - 1), active->y);
        active->up = find(active->x, (active->y + 1));
        active->dw = find(active->x, (active->y - 1));
    };
    if (x == 0 && y == 1) {
        if (active->up == NULL) {
            active->up = new schermata;
            active->up->x = active->x + x;
            active->up->y = active->y + y;
            active->up->pianeti = uPlanets(src);
            list->next = new lista_schermate;
            list = list->next;
            list->x = active->up->x;
            list->y = active->up->y;
            list->it = active->up;
            list->next = NULL;
        };
        active = active->up;
        active->dx = find((active->x + 1), active->y);
        active->sx = find((active->x - 1), active->y);
        active->up = find(active->x, (active->y + 1));
        active->dw = find(active->x, (active->y - 1));
    };
    if (x == -1 && y == 0) {
        if (active->sx == NULL) {
            active->sx = new schermata;
            active->sx->x = active->x + x;
            active->sx->y = active->y + y;
            active->sx->pianeti = uPlanets(src);
            list->next = new lista_schermate;
            list = list->next;
            list->x = active->sx->x;
            list->y = active->sx->y;
            list->it = active->sx;
            list->next = NULL;
        };
        active = active->sx;
        active->dx = find((active->x + 1), active->y);
        active->sx = find((active->x - 1), active->y);
        active->up = find(active->x, (active->y + 1));
        active->dw = find(active->x, (active->y - 1));
    };
    if (x == 0 && y == -1) {
        if (active->dw == NULL) {
            active->dw = new schermata;
            active->dw->x = active->x + x;
            active->dw->y = active->y + y;
            active->dw->pianeti = uPlanets(src);
            list->next = new lista_schermate;
            list = list->next;
            list->x = active->dw->x;
            list->y = active->dw->y;
            list->it = active->dw;
            list->next = NULL;
        };
        active = active->dw;
        active->dx = find((active->x + 1), active->y);
        active->sx = find((active->x - 1), active->y);
        active->up = find(active->x, (active->y + 1));
        active->dw = find(active->x, (active->y - 1));
    }
}

void Universo::disegnaPianeti(RenderWindow *window){
    Pianeta *planetIterator = active->pianeti.getHead();
    while (planetIterator != NULL) {
        if (planetIterator->exist) window->draw(planetIterator->planet);
        planetIterator = planetIterator->next;
    }
}

void Universo::movimentiNavetta(RenderWindow *window, Risorse *src, Transitions *transizioni, sf::Time timePerFrame){
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        player.nave.setRotation(player.nave.getRotation() - 3);
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        player.nave.setRotation(player.nave.getRotation() + 3);
    }
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
		player.addToDxDy(cos((player.nave.getRotation()-270) * M_PI / 180) * player.getSpaceshipAcceleration(), sin((player.nave.getRotation()-270) * M_PI / 180) * player.getSpaceshipAcceleration());
		player.setThrustInt(255);
		if (player.getFuelbar() > 0)
            player.setFuelbar(player.getFuelbar() - player.getSpaceshipAcceleration()/800);
    } else {
		player.decayThrustInt();
		if(player.getAtPlanet())
			player.setDxDy(player.getDx()*0.98, player.getDy()*0.98);
    }
	player.setCurrentSpeed(sqrt(player.getDx() * player.getDx() + player.getDy() * player.getDy()));
	if (player.getCurrentSpeed() > player.getTopSpeed()) {
		player.setDxDy(player.getDx() * player.getTopSpeed() / player.getCurrentSpeed(), player.getDy() * player.getTopSpeed() / player.getCurrentSpeed());
	}

	player.nave.move(player.getDx() * timePerFrame.asMilliseconds() * 0.1,player.getDy() * timePerFrame.asMilliseconds() * 0.1);
	player.thrust.setRotation(player.nave.getRotation());
	player.thrust.setPosition(player.nave.getPosition());
	player.thrust.setColor(Color(255, 255, 255, player.getThrustInt()));

    if (!player.getAtPlanet()){
        if (player.nave.getPosition().x >= larghezza) {
            player.nave.setPosition(0, player.nave.getPosition().y);
            move(1, 0, src);
        }
        if (player.nave.getPosition().y >= altezza) {
            player.nave.setPosition(player.nave.getPosition().x, 0);
            move(0, 1, src);
        }
        if (player.nave.getPosition().x < 0) {
            player.nave.setPosition(larghezza, player.nave.getPosition().y);
            move(-1, 0, src);
        }
        if (player.nave.getPosition().y < 0) {
            player.nave.setPosition(player.nave.getPosition().x, altezza);
            move(0, -1, src);
        }
    }
    if (!player.getAtPlanet()){
        Pianeta *planetIterator = active->pianeti.getHead();
        while (planetIterator != NULL && !player.getAtPlanet()){
            if (contactPlanet(player.nave.getPosition(),planetIterator)){
                active->pianeti.setCurrent(planetIterator);
                planetIterator->interno.inizializza(planetIterator->tot_schermate, src);
                transizioni->inPlanet(window,&planetIterator->interno.getHead()->terrain,planetIterator->tot_schermate);
                player.setAtPlanet(true);
                
                bunkerlist *tmp = planetIterator->interno.getCurrent()->enemies.getHead();
                while (tmp != NULL){
                    tmp->weapon.bullet_time.restart();
                    tmp = tmp->next;
                }
                player.nave.setPosition(larghezza/2, 0);
				
				player.setX_planet((double)player.nave.getPosition().x - 2*(player.nave.getPosition().x - planetIterator->planet.getPosition().x));
				player.setY_planet((double)player.nave.getPosition().y - 2*(player.nave.getPosition().y - planetIterator->planet.getPosition().y));
				player.setAnglePlanet(player.nave.getRotation());
				player.nave.setRotation(0);
				player.setDxDy(0, 0);
            }
            //Ovviamente planetIterator non può mai essere NULL. Al più sarà l'ultimo della lista
            planetIterator = planetIterator->next;
        }
    }
    if (player.getAtPlanet()){
        if (player.nave.getPosition().x >= larghezza) {
			player.nave.setPosition(0, player.nave.getPosition().y);
			active->pianeti.getCurrent()->interno.cambia_schermata(1);
        }
        if (player.nave.getPosition().x < 0) {
			player.nave.setPosition(larghezza, player.nave.getPosition().y);
			active->pianeti.getCurrent()->interno.cambia_schermata(-1);
        }
        if (player.nave.getPosition().y < 0) {
            player.nave.setPosition(player.getX_planet(), player.getY_planet());
            player.nave.setRotation(player.getAnglePlanet() + 180);
			player.setDxDy(0.1, 0.1);
            player.setAtPlanet(false);
        }
    }
}

void Universo::checkTerrain(RenderWindow *window){
    if (player.nave.getPosition().y + 22 >= active->pianeti.getCurrent()->interno.getCurrent()->terrain.get_Y(player.nave.getPosition().x))
        player.setIsDead(true);
}

bool Universo::contactPlanet(Vector2f pos, Pianeta* p){
    return abs(pos.x - (p->relative_x + p->grid_x)) < p->diameter &&
            abs(pos.y - (p->relative_y + p->grid_y)) < p->diameter &&
             p->exist ;
}