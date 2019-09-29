#include "pch.h"
#include "GPlanet.hpp"

using namespace sf;
using namespace std;

/// COSTRUTTORI /////////////////////////////////////////////////////

lista_schermate_pianeta::lista_schermate_pianeta(Terreno terrain_n, int n,
                        int totale_schermate, Risorse *src,
                        lista_schermate_pianeta *next_n,
                        lista_schermate_pianeta *prev_n):
                            next(next_n),prev(prev_n),terrain(terrain_n),
                            nr_schermata(n){
                                enemies = Bunker(src,&terrain);
                                carb = Fuel(&terrain,src);
                            }

GPlanet::GPlanet(){
    current = NULL;
    head = NULL;
	boss = Boss();
	boss_unlocked = false;
}

///  SETTERS E GETTERS  /////////////////////////////////////////////

bool GPlanet::getBoss_unlocked(){
    return this->boss_unlocked;
}

ptr_lista_schermate_pianeta GPlanet::getCurrent(){
    return  this->current;
}

ptr_lista_schermate_pianeta GPlanet::getHead(){
    return  this->head;
}

void GPlanet::setBoss_unlocked(bool boss_unlocked){
    this->boss_unlocked = boss_unlocked;
}

void GPlanet::setCurrent(ptr_lista_schermate_pianeta current){
    this->current = current;
}

void GPlanet::setHead(ptr_lista_schermate_pianeta head){
    this->head = head;
}

///  FUNZIONI  //////////////////////////////////////////////////////

ptr_lista_schermate_pianeta GPlanet::find(int n){
    ptr_lista_schermate_pianeta tmp = head;
    ptr_lista_schermate_pianeta a = NULL;
    while (tmp != NULL && a == NULL){
        if (tmp->nr_schermata == n) a = tmp;
        tmp = tmp->next;
    }
    return a;
}


int GPlanet::checkCollisionBunkBullets(FloatRect obj){
    int hit_counter = 0;
    if (current != NULL) {
        ptr_bunkerlist bunker_iterator = current->enemies.getHead();
        while (bunker_iterator != NULL) {
            proiettile* bullet_iterator = bunker_iterator->weapon.getHead();
            while (bullet_iterator != NULL) {
                if (bullet_iterator->bullet.getGlobalBounds().intersects(obj)) {
                    hit_counter++;
                    bunker_iterator->weapon.deleteBullet(bullet_iterator);
                }
                if(bullet_iterator != NULL) bullet_iterator = bullet_iterator->next;
            }
            bunker_iterator = bunker_iterator->next;
        }
    }
    return hit_counter;
}

void GPlanet::inizializza(int tot_schermate, Risorse *src){
    lista_schermate_pianeta *tmp, *pre_tmp;
    if(head == NULL){
        head = new lista_schermate_pianeta(
            Terreno(random_height(), random_height(), src, tot_schermate),
            0, tot_schermate, src);
        pre_tmp = head;
        for (int i = 1; i < tot_schermate; i++){
            tmp = new lista_schermate_pianeta(
                Terreno(random_height(), pre_tmp->terrain.getSxCoord(),src,tot_schermate),
                i, tot_schermate, src, NULL, pre_tmp);
            pre_tmp->next = tmp;
            pre_tmp = tmp;
        }
        tmp->next = head;
        head->prev = tmp;
        boss = Boss(100, 3, src);
        current = head;
    } else {
        bunkerlist *tmp = getCurrent()->enemies.getHead();
        while (tmp != NULL){
            tmp->weapon.bullet_time.restart();
            tmp = tmp->next;
        }
    }
}

void GPlanet::cambia_schermata(int n){
    if (n == 1){
        current = current->next;
    } else {
        current = current->prev;
    }
    bunkerlist *tmp = current->enemies.getHead();
    while (tmp != NULL){
        tmp->weapon.bullet_time.restart();
        tmp = tmp->next;
    }
}

void GPlanet::checkCollision(RenderWindow *window, Nave *player) {
    proiettile *bullet_ptr = player->SingleShot.getHead(), *laser_ptr = player->Laser.getHead();
    while (bullet_ptr != NULL) {
        if (bullet_ptr->exist) {
            if (current->enemies.checkCollisionBunker(&bullet_ptr->bullet,'b')) {
                //delete bullet;
                player->SingleShot.deleteBullet(bullet_ptr);
                bullet_ptr = NULL;
                cout << "HIT";
                current->enemies.hitLastChecked(35);
            }
        }
        if(bullet_ptr != NULL)  bullet_ptr = bullet_ptr->next;
    }
    while (laser_ptr != NULL) {
        if (laser_ptr->exist) {
            if (current->enemies.checkCollisionBunker(&laser_ptr->bullet, 'l')) {
                //delete bullet;
                player->SingleShot.deleteBullet(laser_ptr);
                laser_ptr = NULL;
                current->enemies.hitLastChecked(100);
            }
        }
        if(laser_ptr != NULL) laser_ptr = laser_ptr->next;
    }
    if (current->enemies.checkCollisionBunker(&player->nave,'s')) {
        player->getHit(30);
        //cout << "collision with bunker";
        player->push_back(5);
    }
    int hit_n = checkCollisionBunkBullets(player->nave.getGlobalBounds());
    //getHit called with 1 so that it ignores clock
    player->getHit(30 * hit_n, 1);
    /*if (universe_ptr->active->pianeti.pp->interno.boss.checkCollisionBoss(&ship_ptr->nave)) {
     ship_ptr->getHit(5);
     ship_ptr->push_back(4);
     }*/
}

void GPlanet::gestione(RenderWindow *window, Nave *player, Time perFrame){
    checkCollision(window, player);
    current->terrain.gestisci(window);
    current->carb.gestisci(window);
    current->enemies.gestisci(window,player, &current->terrain, perFrame);
    //boss.draw(window);
}

int GPlanet::random_height(){
    return 720 - rand() % 100;
}
