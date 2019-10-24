#include "Bullets.hpp"

// COSTRUTTORI =======================================

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

Bullets::Bullets(int time_btw_shoot,int damage, int speed, int tx_nr, int sd_nr, bool autoshoot, Resources *src){
    this->src = src;
    this->autoshoot = autoshoot;
    this->head = NULL;
    this->time_btw_shoot = time_btw_shoot;
    this->damage = damage;
    this->speed = speed;
    this->bullet_tx = src->caricaTexture(tx_nr);
    //this->bullet_sb = *src->caricaSuono(tx_nr);
	this->invuln_time = 500;
}

// SETTERS E GETTERS =================================


proiettile* Bullets::getHead(){
    return this->head;
}

void Bullets::setHead(proiettile *head){
    this->head = head;
}

// FUNZIONI ==========================================


void Bullets::deleteBullet(proiettile *p){
    if(p->prev == NULL && p->next == NULL){
        delete p;
        head = NULL;
    } else if(p->prev == NULL) {
        head = p->next;
        head->prev = NULL;
        delete p;
    } else if(p->next == NULL) {
        p->prev->next = NULL;
        delete p;
    }
}

int Bullets::checkCollision(FloatRect p){
    proiettile *tmp = head;
    int hit_counter = 0;
    while (tmp != NULL){
        if (collidesWith(tmp,p)){
            hit_counter++;
            proiettile *target = tmp;
            tmp = tmp->next;
            deleteBullet(target);
        } else {
            tmp = tmp->next;
        }
    }
    return hit_counter;
}

bool Bullets::collidesWith(proiettile *p, FloatRect obj){
    return p->bullet.getGlobalBounds().intersects(obj);
}

void Bullets::spriteSetup(proiettile *p, double x, double y, double rotation){
    p->bullet.setTexture(*bullet_tx);
    p->bullet.setOrigin(bullet_tx->getSize().x/2, bullet_tx->getSize().y/2);
    p->bullet.setPosition(x, y);
    p->bullet.setRotation(rotation);
    p->bullet.setTextureRect(IntRect(0, 0, bullet_tx->getSize().x, bullet_tx->getSize().y));
    p->bullet.scale(1,1);
    //p->bullet_sound.setBuffer(bullet_sb);
}

bool Bullets::outsideBounds(proiettile *p, Terreno *terrain){
    return p->bullet.getPosition().x < 0 ||
     p->bullet.getPosition().x > src->getLength() ||
      p->bullet.getPosition().y < 0 ||
       p->bullet.getPosition().y >= terrain->get_Y(p->bullet.getPosition().x - 15);

}
