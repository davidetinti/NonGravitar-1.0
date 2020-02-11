#include "Bunkers.hpp"


bunker::bunker(int type_n, double x_n, double y_n, double life_n,
                       Bullets *weapon_n, Texture *b, Texture *e, double boss_bunker_offset) :
    type(type_n),
    x(x_n),
    y(y_n),
    life(life_n),
    weapon(weapon_n),
    boss_bunker_offset(boss_bunker_offset)
    {
        exist = true;
        explosion_x = 0;
        damage = 35;
        spriteSetup(b,e);
    }


void bunker::spriteSetup(Texture *bunker_tx, Texture *explosion_tx){
    bunker_sprite.setTexture(*bunker_tx);
    bunker_sprite.setOrigin(bunker_tx->getSize().x/2, 15);
    bunker_sprite.setPosition(this->x, this->y);
    bunker_sprite.setRotation(180);
    bunker_sprite.setTextureRect(IntRect(0, 0, bunker_tx->getSize().x, bunker_tx->getSize().y));
    this->explosion.setTexture(*explosion_tx);
    this->explosion.setPosition(bunker_sprite.getPosition());
    this->explosion.scale(2, 2);
    this->explosion.setOrigin(25, 25);
}


Bunkers::Bunkers(){
    bunkers = nullptr;
}

 
Bunkers::Bunkers(Resources *src, Terrain *terrain){
    int p;
    int p2;
    this->src = src;
    explosion_tx = src->getTexture(20);
    partial_x[0] = 165;
    partial_x[1] = 415;
    partial_x[2] = 665;
    partial_x[3] = 915;
    bunker_tx = src->getTexture(3);
    bunker_tx2 = src->getTexture(42);
    int x;
    
    bunkers = new list<bunker>;
    int nr_bunkers = src->rand(1,4);
    for(int i = 0; i < nr_bunkers; i++){
        x = partial_x[i] + src->rand(0,201);
        //one or triple bullets
        p=src->rand(0,11);
        //rotation or not
        p2=src->rand(0,1);
        
        if(p>4) bunkers->push_front(bunker(p2,x,terrain->getTerrainY(x),
                                               100, new SingleStraightBullets(DEFAULT_TIME_BTW_SHOOT,
                                               DEFAULT_DAMAGE_SINGLE, DEFAULT_SPEED, 14, true, src),
                                               bunker_tx2, explosion_tx));
        else bunkers->push_front(bunker(p2,x,terrain->getTerrainY(x),
                                            100, new TripleBullets(DEFAULT_TIME_BTW_SHOOT,
                                            DEFAULT_DAMAGE_TRIPLE, DEFAULT_SPEED, 14,
                                            true, src),bunker_tx,explosion_tx));
    }
}


bool Bunkers::isEmpty(){
    return bunkers->empty();
}


void Bunkers::handleWeapons(bunker *tmp, Terrain *terrain){
    tmp->weapon->addSingleBullet(tmp->bunker_sprite, Keyboard::R);
    tmp->weapon->handle(terrain);
}


void Bunkers::hitBunker(int damage, list<bunker>::iterator p){
    if (!p->is_red){
        p->life = p->life - damage;
        p->is_red = true;
        p->bunker_sprite.setColor(Color::Red);
        p->last_hit.restart();
    }
}


list<bunker>::iterator Bunkers::deleteBunker(list<bunker>::iterator it){
    src->addAnimation(it->bunker_sprite.getPosition().x, it->bunker_sprite.getPosition().y, 20, 1, 20, 3, 0.5);
	return(bunkers->erase(it));
}
 

void Bunkers::handle(Nave *player, Terrain *terrain){
    list<bunker>::iterator it = bunkers->begin();
    list<bunker>::iterator end = bunkers->end();
    while (it != end){
        if (it->exist){
            if(it->is_red && it->last_hit.getElapsedTime().asMilliseconds() > HIT_TIMER_MS){
                it->is_red = false;
                it->bunker_sprite.setColor(Color::White);
            }
            if (it->type == 1){
                it->bunker_sprite.setRotation(270 + atan2((player->spaceship.getPosition().y-it->bunker_sprite.getPosition().y),
                                        (player->spaceship.getPosition().x-it->bunker_sprite.getPosition().x)) * 180/M_PI);
            }
            handleWeapons(&*it, terrain);
        }
        if (it->life <= 0) {
            it = deleteBunker(it);
            player->incrasePoints(100);
        }
        if (it->exist == false){
        }
        if (it != end)
            it++;
    }
    drawAll();
}


//returns only the damage by the last detected bunker. see
//comment on Bullets::checkCollision for reasoning
//it still verifies no other bullets are hitting the player
int Bunkers::checkCollisionBBullets(FloatRect obj){
    list<bunker>::iterator it = bunkers->begin();
    list<bunker>::iterator end = bunkers->end();
    int hit = 0;
    int tmp_damage = 0;
    while (it != end){
        tmp_damage = it->weapon->checkCollision(obj);
        if(tmp_damage > hit) 
            hit = tmp_damage;
        it++;
    }
    return hit;
}


bool Bunkers::checkCollision(Bullets *b){
    list<proiettile>::iterator itB = b->bulletList->begin();
    list<proiettile>::iterator endB = b->bulletList->end();
    list<bunker>::iterator it = bunkers->begin();
    list<bunker>::iterator end = bunkers->end();
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


bool Bunkers::checkCollision(Sprite *p){
    list<bunker>::iterator it = bunkers->begin();
    list<bunker>::iterator end = bunkers->end();
    bool hit = false;

    while (it != end){
        if(collidesWith(it,p->getGlobalBounds()))
            hit = true;
        it++;
    }
    return hit;
}


bool Bunkers::collidesWith(list<bunker>::iterator p, sf::FloatRect q){
    return p->bunker_sprite.getGlobalBounds().intersects(q);
}


void Bunkers::drawAll(){
    list<bunker>::iterator it = bunkers->begin();
    list<bunker>::iterator end = bunkers->end();
    while (it != end){
        if(it->exist)
            src->getWindow()->draw(it->bunker_sprite);
        it++;
    } 
}


void Bunkers::restartTimers(){
    list<bunker>::iterator it = bunkers->begin();
    list<bunker>::iterator end = bunkers->end();
    while (it != end){
        it->weapon->bullet_time.restart();
        it++;
    } 
}
