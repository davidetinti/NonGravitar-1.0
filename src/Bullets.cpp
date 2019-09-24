#include "pch.h"
#include "Bullets.hpp"

using namespace sf;
using namespace std;

///  COSTRUTTORI  /////////////////////////////////////////////////////

proiettile::proiettile(proiettile *next_n, proiettile *prev_n)
                : next(next_n), prev(prev_n) {
                    exist = true;
                    if(next != NULL) 
                        next->prev = this;
                    if(prev != NULL)
                        prev->next = this;
                }

Bullets::Bullets(){
    
}

Bullets::Bullets(int time_btw_shoot,int damage, int speed, int tx_nr, int sd_nr, bool autoshoot, Risorse *src){
    this->autoshoot = autoshoot;
    this->head = NULL;
    this->time_btw_shoot = time_btw_shoot;
    this->damage = damage;
    this->speed = speed;
    this->bullet_tx = src->caricaTexture(tx_nr);
    this->bullet_sb = src->caricaSuono(sd_nr);
	this->invuln_time = 500;
}

///  SETTERS E GETTERS  /////////////////////////////////////////////


proiettile* Bullets::getHead(){
    return this->head;
}

void Bullets::setHead(proiettile *head){
    this->head = head;
}

///  FUNZIONI  //////////////////////////////////////////////////////

void Bullets::addSingleBullet(Sprite entity, Keyboard::Key pulsante, int tempo){
    double x = entity.getPosition().x;
    double y = entity.getPosition().y;
    double rotation = entity.getRotation();
    if ((!autoshoot && Keyboard::isKeyPressed(pulsante) && bullet_time.getElapsedTime().asMilliseconds()>time_btw_shoot) || (autoshoot && bullet_time.getElapsedTime().asMilliseconds()>(time_btw_shoot + tempo))) {
        proiettile *tmp = head;
        head = new proiettile(tmp);
        spriteSetup(head,x,y,rotation);
        bullet_time.restart();
    }
}

void Bullets::renderBullet(RenderWindow *window, Terreno *terrain, Time perFrame){
    proiettile *pointer = head;
    Time elapsed;
    while (pointer != NULL){
		elapsed = pointer->invuln_clock.getElapsedTime();
		if ((elapsed.asMilliseconds() > invuln_time || !autoshoot) &&
			outsideBounds(pointer, terrain)){
            proiettile *tmp = pointer;
            pointer = pointer->next;
            deleteBullet(tmp);
        } else {
            double angle = M_PI * pointer->bullet.getRotation() / 180;
            pointer->bullet.move(-sin(angle)*speed*perFrame.asSeconds()*100,
                             cos(angle)*speed*perFrame.asSeconds()*100);
            window->draw(pointer->bullet);
            pointer = pointer->next;
        }
    }
}

void Bullets::deleteBullet(proiettile *bullet){
	proiettile *iterator = head;
    if(bullet->prev == NULL && bullet->next == NULL){
        delete bullet;
        head = NULL;
    } else if(bullet->prev == NULL) {
        head = bullet->next;
        head->prev = NULL;
        delete bullet;
    } else if(bullet->next == NULL) {
        bullet->prev->next = NULL;
        delete bullet;
    }
}

void Bullets::spriteSetup(proiettile *p, double x, double y, double rotation){
    p->bullet.setTexture(*bullet_tx);
    p->bullet.setOrigin(bullet_tx->getSize().x/2, bullet_tx->getSize().y/2);
    p->bullet.setPosition(x, y);
    p->bullet.setRotation(rotation);
    p->bullet.setTextureRect(IntRect(0, 0, bullet_tx->getSize().x, bullet_tx->getSize().y));
    p->bullet.scale(1,1);
    p->bullet_sound.setBuffer(bullet_sb);
}

bool Bullets::outsideBounds(proiettile *pointer, Terreno *terrain){
    return pointer->bullet.getPosition().x < 0 ||
     pointer->bullet.getPosition().x > 1280 ||
      pointer->bullet.getPosition().y < 0 ||
       pointer->bullet.getPosition().y >= terrain->get_Y(pointer->bullet.getPosition().x - 15);

}