#include "GPlanet.hpp"


planet_screen::planet_screen(Terreno *terrain_n, int n, Resources *src,
                             planet_screen *next_n, planet_screen *prev_n):
    next(next_n),
    prev(prev_n),
    terrain(terrain_n),
    screen_nr(n)
    {
        enemies = new Bunker(src,terrain);
        carb = new Fuels(terrain,src);
    }


planet_screen::planet_screen(Resources *s) :
    next(nullptr),
    prev(nullptr),
    terrain(nullptr),
    screen_nr(BOSS_SCREEN){
        // TODO: complete this
        //carb = BossFuel(...);
    }


GPlanet::GPlanet(){
    current = nullptr;
    head = nullptr;
	boss = Boss();
	boss_unlocked = false;
    in_boss = false;
    completed = false;
    
}


bool GPlanet::getBoss_unlocked(){
    return this->boss_unlocked;
}


planet_screen *GPlanet::getCurrent(){
    return  this->current;
}


planet_screen *GPlanet::getHead(){
    return  this->head;
}


void GPlanet::setBoss_unlocked(bool boss_unlocked){
    this->boss_unlocked = boss_unlocked;
}


void GPlanet::setCurrent(planet_screen *current){
    this->current = current;
}


void GPlanet::setHead(planet_screen *head){
    this->head = head;
}


bool GPlanet::getIn_boss(){
    return in_boss;
}


void GPlanet::inizializza(int tot_schermate, Resources *src){
    planet_screen *tmp = nullptr;
    planet_screen *pre_tmp = nullptr;

    if(head == nullptr){
        hole_tx = src->getTexture(31);
        hole.setTexture(*hole_tx);
        hole.setOrigin(hole_tx->getSize().x / 2, hole_tx->getSize().y / 2);
        this->src = src;
        nr_schermate = tot_schermate;

        head = new planet_screen(
            new Terreno(random_height(), random_height(), src, tot_schermate), 0, src);
        pre_tmp = head;
        for (int i = 1; i < tot_schermate; i++){
            tmp = new planet_screen(
                new Terreno(random_height(), pre_tmp->terrain->getSxCoord(),src,tot_schermate),
                                              i, src, nullptr, pre_tmp);
            pre_tmp->next = tmp;
            pre_tmp = tmp;
        }
        tmp->next = head;
        head->prev = tmp;
        boss_screen = new planet_screen(src);
        boss = Boss(1000, 3, src);
        boss_screen->enemies = new BossBunker(src,boss.getRadius(),boss.getCenter());
        boss_screen->terrain = new Terreno(src);
        boss.setEnemies((BossBunker *)boss_screen->enemies);
        boss_unlocked = false;
        in_boss = false;
        current = head;
    } else {
        current->enemies->restartTimers();
    }
}


void GPlanet::cambia_schermata(int n){
    if (n != BOSS_SCREEN){
        if (n == 1){
            current = current->next;
        } else {
            current = current->prev;
        }
        current->enemies->restartTimers();
    } else {
        current = boss_screen;
    }
}


void GPlanet::checkCollision(Nave *player) {
    current->enemies->checkCollision(player->SingleShot);
    current->enemies->checkCollision(player->Laser);
    if (current->enemies->checkCollision(&player->spaceship) > 0){
        if (current->screen_nr == BOSS_SCREEN){
            player->push_back(5, current->screen_nr == BOSS_SCREEN);
        } else {
            player->push_back(5, current->screen_nr == BOSS_SCREEN);
        }
        player->getHit(COLLISION_DAMAGE);
    }
    if (in_boss){
        boss.checkCollisionBoss(player->SingleShot);
        boss.checkCollisionBoss(player->Laser);
    }
    
    int damage = current->enemies->checkCollisionBBullets(player->spaceship.getGlobalBounds());
    player->getHit(damage, 0);
}
 

void GPlanet::handle(Nave *player){
    if (!boss_unlocked) updateBossLock();
    checkCollision(player);
    checkTerrain(player);
    checkScreen(player);
    current->terrain->drawAll();
    if (!in_boss) {
        current->carb->draw();
        raggiotraente(player);
	}
	if (boss_unlocked && current == head) src->getWindow()->draw(hole);
	if (in_boss){
        boss.handle();
		boss.draw();
    }
	current->enemies->handle(player, current->terrain);
    player->armi(current->terrain);
    
    if(boss.isDead()){
        completed = true;
        player->incrasePoints(STANDARD_PLANET_POINTS + 100 * nr_schermate);
    }
}


bool GPlanet::inHole(Sprite *body){
    if(boss_unlocked)
        return hole.getGlobalBounds().contains(body->getPosition());
    else return false;
}


void GPlanet::enterBoss(Nave *player){
    in_boss = true;
    cambia_schermata(BOSS_SCREEN);
    player->spaceship.setPosition(src->getLength()/2, src->getHeight()/2);
    player->in_boss = true;
}


void GPlanet::checkTerrain(Nave *player){
    if (!in_boss){
        if(inHole(&player->spaceship))
            enterBoss(player);
        else if (player->spaceship.getPosition().y + 22 >= getCurrent()->terrain->getTerrainY(player->spaceship.getPosition().x)){
            player->getHit(COLLISION_DAMAGE);
            player->push_back(5, current->screen_nr == BOSS_SCREEN);
        }
                
        
    } else {
        if(boss.checkCollisionBoss(&player->spaceship)) {
            player->getHit(COLLISION_DAMAGE);
            player->push_back(2,1);
        }
    }
}


int GPlanet::random_height(){
    return src->getHeight() - src->rand(0,99);
}


void GPlanet::updateBossLock(){
    bool no_bunkers = true;
    int i = 0;
    planet_screen *iterator = head;
    while (iterator != nullptr && no_bunkers && i < nr_schermate) {
        no_bunkers = no_bunkers && (iterator->enemies->isEmpty());
        iterator = iterator->next;
        i++;
    }
    if (no_bunkers) {
        boss_unlocked = true;
        head->terrain->prepareForBoss(&hole);
    }
}


bool GPlanet::getCompleted(){
    return completed;
}


void GPlanet::raggiotraente(Nave *player){
    list<fuel>::iterator it = current->carb->getFuelListBegin();
    list<fuel>::iterator end = current->carb->getFuelListEnd();
    if (player->raggioTraente()){
        while(it != end){
            if(player->ray.getGlobalBounds().intersects(it->fuel_sprite.getGlobalBounds())){
                double temp_x = player->spaceship.getPosition().x - it->fuel_sprite.getPosition().x;
                double temp_y = player->spaceship.getPosition().y - it->fuel_sprite.getPosition().y;
                double angle = atan(temp_x/temp_y);
                it->x = it->x - 1 * sin(angle);
                it->y = min(it->y - 1 * cos(angle), current->terrain->getTerrainY(it->x));
                it->fuel_sprite.setPosition(it->x, it->y);
            } else {
                it->y = min(current->terrain->getTerrainY(it->x), it->y + 1);
                it->fuel_sprite.setPosition(it->x, it->y);
            }
            if(player->spaceship.getGlobalBounds().intersects(it->fuel_sprite.getGlobalBounds())){
                player->increaseFuel((2 - src->getDifficulty()) * it->power);
                it = current->carb->delete_fuel(it);
            } else {
                it++;
            }
        }
    } else {
        while (it != end){
            it->y = min(current->terrain->getTerrainY(it->x), it->y + 1);
            it->fuel_sprite.setPosition(it->x, it->y);
            it++;
        }
    }
}


void GPlanet::checkScreen(Nave *player){
    if (player->spaceship.getPosition().x >= src->getLength()) {
        player->spaceship.setPosition(0, player->spaceship.getPosition().y);
        cambia_schermata(1);
    }
    if (player->spaceship.getPosition().x < 0) {
        player->spaceship.setPosition(src->getLength(), player->spaceship.getPosition().y);
        cambia_schermata(-1);
    }
    if (player->spaceship.getPosition().y > src->getHeight()){
        enterBoss(player);
    }
}
