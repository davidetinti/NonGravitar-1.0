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

lista_schermate_pianeta *GPlanet::getCurrent(){
    return  this->current;
}

lista_schermate_pianeta *GPlanet::getHead(){
    return  this->head;
}

void GPlanet::setBoss_unlocked(bool boss_unlocked){
    this->boss_unlocked = boss_unlocked;
}

void GPlanet::setCurrent(lista_schermate_pianeta *current){
    this->current = current;
}

void GPlanet::setHead(lista_schermate_pianeta *head){
    this->head = head;
}

///  FUNZIONI  //////////////////////////////////////////////////////

lista_schermate_pianeta *GPlanet::find(int n){
    lista_schermate_pianeta *tmp = head;
    lista_schermate_pianeta *a = NULL;
    while (tmp != NULL && a == NULL){
        if (tmp->nr_schermata == n) a = tmp;
        tmp = tmp->next;
    }
    return a;
}
 

int GPlanet::checkCollisionBunkBullets(FloatRect obj){
    return current->enemies.checkCollisionBBullets(obj);
}

void GPlanet::inizializza(int tot_schermate, Risorse *src){
    this->src = src;
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
            tmp->weapon->bullet_time.restart();
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
        tmp->weapon->bullet_time.restart();
        tmp = tmp->next;
    }
}

void GPlanet::checkCollision(Nave *player) { //should this be moved into Bunker?
    int primary = src->getPrimaryDamage(), secondary = src->getSecondaryDamage();
    bunkerlist *bunk_iterator = current->enemies.getHead();
    while (bunk_iterator != NULL){
        if (player->SingleShot->checkCollision(bunk_iterator->bunker.getGlobalBounds()) > 0)
            current->enemies.hitBunker(primary, bunk_iterator);
        if(player->Laser->checkCollision(bunk_iterator->bunker.getGlobalBounds()) > 0)
            current->enemies.hitBunker(secondary, bunk_iterator);
        if(current->enemies.collidesWith(bunk_iterator, player->nave.getGlobalBounds())){
            player->getHit(bunk_iterator->damage);
            player->push_back(5);
        }
        bunk_iterator = bunk_iterator->next;
    }
    int hit_n = checkCollisionBunkBullets(player->nave.getGlobalBounds());
    //getHit called with 1 so that it ignores clock
    player->getHit(30 * hit_n, 1);
    /*if (universe_ptr->active->pianeti.pp->interno.boss.checkCollisionBoss(&ship_ptr->nave)) {
     ship_ptr->getHit(5);
     ship_ptr->push_back(4);
     }*/
}

void GPlanet::gestione(Nave *player, Time perFrame){
    checkCollision(player);
    current->terrain.gestisci();
    current->carb.gestisci();
    current->enemies.gestisci(player, &current->terrain, perFrame);
    //boss.draw(window);
}

int GPlanet::random_height(){
    return src->getHeight() - rand() % 100;
}
