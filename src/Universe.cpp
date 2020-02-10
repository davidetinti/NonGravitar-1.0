#include "Universe.hpp"


uni_screen::uni_screen(int x_n, int y_n, Resources *src, uni_screen *d, uni_screen *s, 
        uni_screen *u, uni_screen *down, uni_screen *nxt) :
    dx(d),
    sx(s),
    up(u),
    dw(down),
    x(x_n),
    y(y_n),
    next(nxt)
    {
        pianeti = Pianeti(src);
    }


Universe::Universe(){
    
} 


Universe::Universe(Resources *src){
    this->src = src;
    this->player = Nave(this->src);
    this->active = new uni_screen(0, 0, this->src);
    this->head_list = active;
    this->tail = head_list;
}


uni_screen *Universe::getActive(){
    return  this->active;
}


uni_screen *Universe::getTail(){
    return  this->tail;
}


uni_screen *Universe::getHeadList(){
    return  this->head_list;
}


uni_screen *Universe::find(int x, int y){
    uni_screen *b = head_list;
    bool found = false;
    while (b != nullptr && !found) {
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
        if (active->dx == nullptr) {
            active->dx = new uni_screen(active->x + x,active->y + y,src);
            addToList(active->dx);
        }
        active = active->dx;
    }
    if (x == 0 && y == 1) {
        if (active->up == nullptr) {
            active->up = new uni_screen(active->x + x, active->y + y,src);
            addToList(active->up);
        }
        active = active->up;
    }
    if (x == -1 && y == 0) {
        if (active->sx == nullptr) {
            active->sx = new uni_screen(active->x+x,active->y+y,src);
            addToList(active->sx);
        }
        active = active->sx;
    }
    if (x == 0 && y == -1) {
        if (active->dw == nullptr) {
            active->dw = new uni_screen(active->x+x,active->y+y,src);
            addToList(active->dw);
        }
        active = active->dw;
    }
    active->dx = find((active->x + 1), active->y);
    active->sx = find((active->x - 1), active->y);
    active->up = find(active->x, (active->y + 1));
    active->dw = find(active->x, (active->y - 1));
}


void Universe::handle(){

    //TODO: throughout code, keep logic and drawing separate, maybe. i think it would look cleaner
    player.handle();
    player.handleThrust();
    

    //TODO: collapse these if's somehow. useless lines of code.
    if (!player.getAtPlanet()){
        //src->getWindow()->draw(background);
        active->pianeti.draw();

        //verify if out of bounds
        if (player.spaceship.getPosition().x >= src->getLength()) {
            player.spaceship.setPosition(0, player.spaceship.getPosition().y);
            move(1, 0);
        }
        if (player.spaceship.getPosition().y >= src->getHeight()) {
            player.spaceship.setPosition(player.spaceship.getPosition().x, 0);
            move(0, 1);
        }
        if (player.spaceship.getPosition().x < 0) {
            player.spaceship.setPosition(src->getLength(), player.spaceship.getPosition().y);
            move(-1, 0);
        }
        if (player.spaceship.getPosition().y < 0) {
            player.spaceship.setPosition(player.spaceship.getPosition().x, src->getHeight());
            move(0, -1);
        }
        
        list<SinglePlanet>::iterator it = active->pianeti.planetlist.begin();
        list<SinglePlanet>::iterator end = active->pianeti.planetlist.end();
        while (it != end && !player.getAtPlanet()){
            if (contactPlanet(player.spaceship.getPosition(),&*it)){
                active->pianeti.setCurrent(&*it);
                it->interno.initialize(it->tot_schermate, src);
                player.setAtPlanet(true);
                
                player.braceForEntry(it->planet.getPosition());
            }
            it++;
        }
    }
    if (player.getAtPlanet()){
        getActive()->pianeti.handle(&player);

        if (player.spaceship.getPosition().y < 0) {
            exitPlanet();
        }

        if(active->pianeti.getCurrent()->interno.getCompleted()){
            exitPlanet();
            src->addAnimation(active->pianeti.getCurrent()->planet.getPosition().x,
                              active->pianeti.getCurrent()->planet.getPosition().y,
                              20, 1, 20, 3, 0.5);
            active->pianeti.deletePlanet(active->pianeti.getCurrent());
            active->pianeti.setCurrent(nullptr);
            player.resetStats();
        }
    }
    src->getWindow()->draw(player.thrust);
    src->getWindow()->draw(player.spaceship);
}


bool Universe::contactPlanet(Vector2f pos, SinglePlanet* p){
    return abs(pos.x - (p->relative_x + p->grid_x)) < p->diameter &&
            abs(pos.y - (p->relative_y + p->grid_y)) < p->diameter &&
             p->exist ;
}


void Universe::addToList(uni_screen *p){
    if(p != nullptr){
        tail->next = p;
        tail = tail->next;
    }
}


void Universe::exitPlanet(){
    player.spaceship.setPosition(player.getX_planet(), player.getY_planet());
    player.spaceship.setRotation(player.getAnglePlanet());
    player.setDxDy(0, 0.1);
    player.setAtPlanet(false);
}
