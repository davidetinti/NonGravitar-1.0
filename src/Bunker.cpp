#include "Bunker.hpp"

// COSTRUTTORI =======================================
bunkerlist::bunkerlist(int type_n, int tempo_n, double x_n, double y_n, double life_n,
                       Bullets *weapon_n, Texture *b, Texture *e, double boss_bunker_offset) :
type(type_n),
x(x_n), y(y_n),
life(life_n),
weapon(weapon_n),
boss_bunker_offset(boss_bunker_offset)
{
    exist = true;
    explosion_x = 0;
    damage = 35;
    spriteSetup(b,e);
}

void bunkerlist::spriteSetup(Texture *bunker_tx, Texture *explosion_tx){
    this->bunker.setTexture(*bunker_tx);
    this->bunker.setOrigin(bunker_tx->getSize().x/2, 15);
    this->bunker.setPosition(this->x, this->y);
    this->bunker.setRotation(180);
    this->bunker.setTextureRect(IntRect(0, 0, bunker_tx->getSize().x, bunker_tx->getSize().y));
    this->explosion.setTexture(*explosion_tx);
    this->explosion.setPosition(this->bunker.getPosition());
    this->explosion.scale(2, 2);
    this->explosion.setOrigin(25, 25);
}

Bunker::Bunker(){
    bunkers = nullptr;
}
 
Bunker::Bunker(Resources *src, Terreno *terrain){
    int p;
    int p2;
    this->src = src;
    explosion_tx = src->caricaTexture(20);
    partial_x[0] = 165;
    partial_x[1] = 415;
    partial_x[2] = 665;
    partial_x[3] = 915;
    bunker_tx = src->caricaTexture(3);
    int x;
    
    bunkers = new list<bunkerlist>;
    int nr_bunkers = src->rand(1,4);
    for(int i = 0; i < nr_bunkers; i++){
        x = partial_x[i] + src->rand(0,201);
        p=src->rand(0,11);
        p2=src->rand(0,1);
        
        if(p>4) bunkers->push_front(bunkerlist(p2,(src->rand(2500,7500)),x,terrain->get_Y(x),
                          100, new SingleStraightBullets(DEFAULT_TIME_BTW_SHOOT, DEFAULT_DAMAGE_SINGLE,
                                 DEFAULT_SPEED, 14, 0, true, src),bunker_tx,explosion_tx));
        else bunkers->push_front(bunkerlist(p2,(src->rand(2500,7500)),x,terrain->get_Y(x),
                          100, new TripleBullets(DEFAULT_TIME_BTW_SHOOT, DEFAULT_DAMAGE_TRIPLE,
                                 DEFAULT_SPEED, 14, 0, true, src),bunker_tx,explosion_tx));
    }
}

// SETTERS E GETTERS =================================




// FUNZIONI ==========================================

bool Bunker::isEmpty(){
    return bunkers->empty();
}

void Bunker::armi(bunkerlist *tmp, Terreno *terrain, Time perFrame){//perFrame should be in Resources
    tmp->weapon->addSingleBullet(tmp->bunker, Keyboard::R);
    tmp->weapon->handle(perFrame, terrain);
}


void Bunker::hitBunker(int damage, list<bunkerlist>::iterator p){
	p->life = p->life - damage;
}

list<bunkerlist>::iterator Bunker::deleteBunker(list<bunkerlist>::iterator it){
    src->addAnimation(it->bunker.getPosition().x, it->bunker.getPosition().y, 20, 1, 20, 3, 0.5);
	return(bunkers->erase(it));
}
 
void Bunker::gestisci(Nave *player, Terreno *terrain, double angle){
    list<bunkerlist>::iterator it = bunkers->begin();
    //updatePosition(angle);
    while (it != bunkers->end()){
        if (it->exist){
            if (it->type == 1){
                it->bunker.setRotation(270 + atan2((player->nave.getPosition().y-it->bunker.getPosition().y), 
                                        (player->nave.getPosition().x-it->bunker.getPosition().x)) * 180/M_PI);
            }
            armi(&*it, terrain, *src->getTimePerFrame());
        }
        if (it->life <= 0) {
            it->exist = false;
            player->setPunti(player->getPunti()+100);
        }
        if (it->exist == false){
            it = deleteBunker(it);
        }
        if (it != bunkers->end()) 
            it++;
    }
    drawAll();
}

int Bunker::checkCollisionBBullets(FloatRect obj){
    list<bunkerlist>::iterator it = bunkers->begin();
    int hit_counter = 0;
    while (it != bunkers->end()){
        hit_counter = hit_counter + it->weapon->checkCollision(obj);
        it++;
    }
    return hit_counter;
}

bool Bunker::checkCollision(Bullets *b){
    list<proiettile>::iterator itB = b->bulletList->begin();
    list<proiettile>::iterator endB = b->bulletList->end();
    list<bunkerlist>::iterator it = bunkers->begin();
    list<bunkerlist>::iterator end = bunkers->end();
    bool deleted = false;
    bool hit = false;
    while (itB != endB){
        deleted = false;
        it = bunkers->begin();
        while (it != end && !deleted){
            if (collidesWith(it,itB->bullet.getGlobalBounds())){
                hitBunker(b->getDamage(),it);
                itB = b->bulletList->erase(itB);
                deleted = true;
                hit = true;
            }
            it++;
        }
        if(!deleted) itB++;
    }
    return hit;
}

bool Bunker::checkCollision(Sprite *p){
    list<bunkerlist>::iterator it = bunkers->begin();
    list<bunkerlist>::iterator end = bunkers->end();
    bool hit = false;

    while (it != end){
        if(collidesWith(it,p->getGlobalBounds()))
            hit = true;
        it++;
    }
    return hit;
}

bool Bunker::collidesWith(list<bunkerlist>::iterator p, sf::FloatRect q){
    return p->bunker.getGlobalBounds().intersects(q);
}


void Bunker::drawAll(){
    list<bunkerlist>::iterator it = bunkers->begin();
    while (it != bunkers->end()){
        if(it->exist)
            src->getWindow()->draw(it->bunker);
        it++;
    } 
}

void Bunker::restartTimers(){
    list<bunkerlist>::iterator it = bunkers->begin();
    while (it != bunkers->end()){
        it->weapon->bullet_time.restart();
        it++;
    } 
}

void Bunker::updatePosition(double angle){
    //left it for completeness, if we want to implement moving bunkers. 
    //makes it much cleaner in BossBunker :)
}
