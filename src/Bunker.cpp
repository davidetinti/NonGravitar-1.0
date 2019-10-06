#include "pch.h"
#include "Bunker.hpp"

using namespace sf;
using namespace std;

/// COSTRUTTORI /////////////////////////////////////////////////////
bunkerlist::bunkerlist(int type_n, int tempo_n, double x_n, double y_n, double life_n,
                bunkerlist *next_n, Bullets *weapon_n, bool exist_n, double explosion_x_n) :
               type(type_n), x(x_n), y(y_n), life(life_n), weapon(weapon_n),
               exist(exist_n), explosion_x(explosion_x_n){
                damage = 35;
               }

Bunker::Bunker(){
    head = NULL;
}
 
Bunker::Bunker(Risorse *src, Terreno *terrain){
    int p;
    this->src = src;
    double x;
    explosion_tx = src->caricaTexture(20);
    partial_x[0] = 165;
    partial_x[1] = 415;
    partial_x[2] = 665;
    partial_x[3] = 915;
    bunker_tx = src->caricaTexture(3);
    x = partial_x[0] + rand() % 201;
    p = rand() % 2;
    //TO BE MERGED WITH FOR PLS
    if(p) head = new bunkerlist(1,(rand() % 5000) + 2500,x,terrain->get_Y(x),
                          100, NULL,new SingleStraightBullets(400, 100, 10, 14, 0, true, src),true, 0.0);
    else  head = new bunkerlist(1,(rand() % 5000) + 2500,x,terrain->get_Y(x),
                          100, NULL, new TripleBullets(400, 100, 10, 14, 0, true, src), true, 0.0);
    spriteSetup(head);

    bunkerlist *tmp = head;

    for (int i = 1; i < 4 ; i++){
        p = rand() % 2;
        x = partial_x[i] + rand() % 201; 
        if(p) tmp->next = new bunkerlist(1,(rand() % 5000) + 2500,x, terrain->get_Y(x), 
                                   100, NULL, new SingleStraightBullets(400, 100, 10, 14, 0, true, src), true, 0.0);
        else  tmp->next = new bunkerlist(1,(rand() % 5000) + 2500,x, terrain->get_Y(x), 
                                   100, NULL, new TripleBullets(400, 100, 10, 14, 0, true, src), true, 0.0);
        tmp = tmp->next;
        spriteSetup(tmp);
        tmp->next = NULL;
    }
}

///  SETTERS E GETTERS  /////////////////////////////////////////////


bunkerlist *Bunker::getHead(){
    return  head;
}


///  FUNZIONI  //////////////////////////////////////////////////////

bool Bunker::isEmpty(){
    return head == NULL;
}

void Bunker::armi(bunkerlist *tmp, Terreno *terrain, Time perFrame){
    tmp->weapon->addSingleBullet(tmp->bunker, Keyboard::R, tmp->tempo);
    tmp->weapon->renderBullet(terrain, perFrame);
}


void Bunker::hitBunker(int damage, bunkerlist *p){
	if (p != NULL) {
		p->life = p->life - damage;
		/*if (last_checked->life <= 0) {
			cout << "entered if statement, life < 0";
			ptr_bunkerlist iterator = head;
			while (iterator->next != last_checked && iterator != NULL) iterator = iterator->next;
			if (iterator->next == last_checked) {
				iterator->next = last_checked->next;
				delete last_checked;
				last_checked = NULL;
			}
		}*/
		
	}
}

void Bunker::deleteBunker(bunkerlist *target){
	bunkerlist *iterator = head;
	if (iterator != NULL && target != head) {
		while (iterator->next != NULL) {
			if (iterator->next == target) {
				iterator->next = target->next;
				delete target;
			}
            if(iterator->next != NULL)  iterator = iterator->next;
		}
	}
    if (target == head) {
        head = head->next;
        delete target;
    }
}

void Bunker::esplodi(bunkerlist* target){
    target->explosion.setTextureRect(IntRect(50*(int)target->explosion_x,0,50,50));
    target->explosion_x ++;
    src->getWindow()->draw(target->explosion);
}
 
void Bunker::gestisci(Nave *player, Terreno *terrain, Time perFrame){
    bunkerlist *tmp = head;
    while (tmp != NULL){
        //cout << enemies->x << endl;
        if (tmp->exist){
            if (tmp->type == 1){
                tmp->bunker.setRotation(180 - atan((player->nave.getPosition().x-tmp->bunker.getPosition().x)/(player->nave.getPosition().y-tmp->bunker.getPosition().y))*(180/M_PI));
            }
            armi(tmp, terrain, perFrame);
            src->getWindow()->draw(tmp->bunker);
            
        }
        if (tmp->life <= 0) {
            tmp->exist = false;
            player->setPunti(player->getPunti()+100);
        }
        if (tmp->exist == false) esplodi(tmp);
        if (tmp->explosion_x >= 20){
            deleteBunker(tmp);
            tmp = NULL;
        }
        if (tmp != NULL) 
            tmp = tmp->next;
    }
}

int Bunker::checkCollisionBBullets(FloatRect obj){
    bunkerlist *bunker_iterator = head;
    int hit_counter = 0;
    while (bunker_iterator != NULL){
        hit_counter = hit_counter + bunker_iterator->weapon->checkCollision(obj);
        bunker_iterator = bunker_iterator->next;
    }
    return hit_counter;
}

bool Bunker::collidesWith(bunkerlist *p, sf::FloatRect q){
    return p->bunker.getGlobalBounds().intersects(q);
}

void Bunker::spriteSetup(bunkerlist *p){
    p->bunker.setTexture(*bunker_tx);
    p->bunker.setOrigin(bunker_tx->getSize().x/2, 15);
    p->bunker.setPosition(p->x, p->y);
    p->bunker.setRotation(180);
    p->bunker.setTextureRect(IntRect(0, 0, bunker_tx->getSize().x, bunker_tx->getSize().y));
    p->explosion.setTexture(*explosion_tx);
    p->explosion.setPosition(p->bunker.getPosition());
    p->explosion.scale(2, 2);
    p->explosion.setOrigin(25, 25);
}
