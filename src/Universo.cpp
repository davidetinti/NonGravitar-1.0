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

Universo::Universo(int lenght, int heigth, Risorse *s, Font *font){
    src = s;
    hud = HUD(lenght, heigth, src, font);
    player = Nave(lenght, heigth, src);
    universe_tx = src->caricaTexture(2);
    universe.setPosition(0, 0);
    universe.setTexture(*universe_tx);
    altezza = heigth;
    larghezza = lenght;
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

void Universo::move(int x, int y, Risorse *src){
    if (x == 1 && y == 0) {
        if (active->dx == NULL) {
            active->dx = new lista_schermate(active->x + x,active->y + y,src);
            addToList(active->dx);
        };
        active = active->dx;
    };
    if (x == 0 && y == 1) {
        if (active->up == NULL) {
            active->up = new lista_schermate(active->x + x, active->y + y,src);
            addToList(active->up);
        };
        active = active->up;
    };
    if (x == -1 && y == 0) {
        if (active->sx == NULL) {
            active->sx = new lista_schermate(active->x+x,active->y+y,src);
            addToList(active->sx);
        };
        active = active->sx;
    };
    if (x == 0 && y == -1) {
        if (active->dw == NULL) {
            active->dw = new lista_schermate(active->x+x,active->y+y,src);
            addToList(active->dw);
        };
        active = active->dw;
    }
    active->dx = find((active->x + 1), active->y);
    active->sx = find((active->x - 1), active->y);
    active->up = find(active->x, (active->y + 1));
    active->dw = find(active->x, (active->y - 1));
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

void Universo::addToList(lista_schermate *p){
    if(p != NULL){
        tail->next = p;
        tail = p;
    }
}