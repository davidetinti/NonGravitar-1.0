#include "pch.h"
#include "Bunker.hpp"

using namespace sf;
using namespace std;

/// COSTRUTTORI /////////////////////////////////////////////////////
bunkerlist::bunkerlist(int type_n, int tempo_n, double x_n, double y_n, double life_n,
                bunkerlist *next_n, bool exist_n, double explosion_x_n,
                Bullets weapon_n) :
               type(type_n), x(x_n), y(y_n), life(life_n), weapon(weapon_n),
               exist(exist_n), explosion_x(explosion_x_n){

               }

Bunker::Bunker(){
    head = NULL;
    last_checked = NULL;
}
 
Bunker::Bunker(Risorse *src, Terreno *terrain){
    this->src = src;
    double x;
    explosion_tx = src->caricaTexture(20);
    partial_x[0] = 165;
    partial_x[1] = 415;
    partial_x[2] = 665;
    partial_x[3] = 915;
    bunker_tx = src->caricaTexture(3);
    x = partial_x[0] + rand() % 201;
    head = new bunkerlist(1,(rand() % 5000) + 2500,x,terrain->get_Y(x),
                          100, NULL,true, 0.0, 
                          Bullets(400, 100, 10, 14, 0, true, src));
    spriteSetup(head);

    bunkerlist *tmp = head;

    for (int i = 1; i < 4 ; i++){
        x = partial_x[i] + rand() % 201; 
        tmp->next = new bunkerlist(1,(rand() % 5000) + 2500,x, terrain->get_Y(x), 
                                   100, NULL, true, 0.0,
                                   Bullets(400, 100, 10, 14, 0, true, src));
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
    tmp->weapon.addSingleBullet(tmp->bunker, Keyboard::R, tmp->tempo);
    tmp->weapon.renderBullet(terrain, perFrame);
}

//b-->bullet, l-->laser, s-->ship
bool Bunker::checkCollisionBunker(Sprite *body, char type){
	bunkerlist *closest_bunker = head, *bunker_iterator = head;
	if (closest_bunker != NULL) {
		double min_distance_squared = pow(closest_bunker->bunker.getPosition().x - body->getPosition().x, 2) + pow(closest_bunker->bunker.getPosition().y - body->getPosition().y, 2);
		double this_distance_squared = 0;
		while (bunker_iterator != NULL) {
			this_distance_squared = (pow(bunker_iterator->bunker.getPosition().x - body->getPosition().x, 2) + pow(bunker_iterator->bunker.getPosition().y - body->getPosition().y, 2));
			if (min_distance_squared > this_distance_squared) {
				min_distance_squared = this_distance_squared;
				closest_bunker = bunker_iterator;
			}
			bunker_iterator = bunker_iterator->next;
		}
		Vector2f closest_point;
		FloatRect body_rect = body->getGlobalBounds();
		FloatRect bunker_rect = closest_bunker->bunker.getGlobalBounds();
		Vector2f center;
		center = Vector2f(bunker_rect.left + bunker_rect.width / 2, bunker_rect.top + bunker_rect.height / 2);
		closest_point = Vector2f(body_rect.top, body_rect.left);
		if (pow(closest_point.x - center.x, 2) + pow(closest_point.y - center.y, 2) < pow(body_rect.left + body_rect.width, 2) + pow(body_rect.top, 2)) closest_point = Vector2f(body_rect.left + body_rect.width, body_rect.top);
		if (pow(closest_point.x - center.x, 2) + pow(closest_point.y - center.y, 2) < pow(body_rect.left + body_rect.width, 2) + pow(body_rect.top + body_rect.height, 2)) closest_point = Vector2f(body_rect.left + body_rect.width, body_rect.top + body_rect.height);
		if (pow(closest_point.x - center.x, 2) + pow(closest_point.y - center.y, 2) < pow(body_rect.left, 2) + pow(body_rect.top + body_rect.height, 2)) closest_point = Vector2f(body_rect.left, body_rect.top + body_rect.height);

		//if(pow(closestPoint.x - centre.x, 2) + pow(closestPoint.y - centre.y, 2) < )

		if (bunker_rect.contains(closest_point)) {
			if (type == 'b' || type == 'l') last_checked = closest_bunker;
			return true;
		}
		else return false;
	}
	else return false;
}

void Bunker::hitLastChecked(int damage){
	if (last_checked != NULL) {
		last_checked->life = last_checked->life - damage;
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
        if (tmp != NULL) tmp = tmp->next;
    }
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
