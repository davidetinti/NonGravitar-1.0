#include "Universe.hpp"

// COSTRUTTORI =======================================

lista_schermate::lista_schermate(int x_n, int y_n, Resources *src, lista_schermate *d, lista_schermate *s, 
        lista_schermate *u, lista_schermate *down, lista_schermate *nxt) : dx(d), sx(s), up(u),
        dw(down), x(x_n), y(y_n), next(nxt){
            pianeti = uPlanets(src);
        }

Universe::Universe(){
    
} 

Universe::Universe(Resources *src){
    this->src = src;
    this->hud = HUD(this->src);
    this->player = Nave(this->src);
    this->active = new lista_schermate(0, 0, this->src);
    this->head_list = active;
    this->tail = head_list;
}

// SETTERS E GETTERS =================================

lista_schermate *Universe::getActive(){
    return  this->active;
}

lista_schermate *Universe::getTail(){
    return  this->tail;
}

lista_schermate *Universe::getHeadList(){
    return  this->head_list;
}

// FUNZIONI ==========================================

lista_schermate *Universe::find(int x, int y){
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

void Universe::move(int x, int y){
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

void Universe::disegnaPianeti(){
    Pianeta *planetIterator = active->pianeti.getHead();
    while (planetIterator != NULL) {
        if (planetIterator->exist) src->getWindow()->draw(planetIterator->planet);
        planetIterator = planetIterator->next;
    }
}

void Universe::handle(){

    //TODO: throughout code, keep logic and drawing separate, maybe. i think it would look cleaner
    player.gestisci();
    player.handleThrust();
    

    //TODO: collapse these if's somehow. useless lines of code.
    if (!player.getAtPlanet()){
        //src->getWindow()->draw(background);
        disegnaPianeti();

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
        getActive()->pianeti.handle(&player);

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
        //only able to go down far enough after boss is unlocked
        if (player.nave.getPosition().y > src->getHeight()){
            active->pianeti.getCurrent()->interno.enterBoss(&player);
        }
    }
    src->getWindow()->draw(player.thrust);
    src->getWindow()->draw(player.nave);
}


bool Universe::contactPlanet(Vector2f pos, Pianeta* p){
    return abs(pos.x - (p->relative_x + p->grid_x)) < p->diameter &&
            abs(pos.y - (p->relative_y + p->grid_y)) < p->diameter &&
             p->exist ;
}

void Universe::addToList(lista_schermate *p){
    if(p != NULL){
        tail->next = p;
        tail = tail->next;
    }
}
