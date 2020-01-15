#include "Boss.hpp"

/// COSTRUTTORI /////////////////////////////////////////////////////

Boss::Boss(){
    
}


Boss::Boss(int life, int turrets_n, Resources *src, double angolo, int vel, bool notdead){
    this->src = src;
	hp_total = life;
	hp_left = hp_total;
	turret_total = turrets_n;
	turret_left = turret_total;
	alive = notdead;
	angle = angolo;
	boss_tx = src->caricaTexture(32);
	radius = boss_tx->getSize().x/2;
	notBoss.setTexture(*boss_tx);
	notBoss.setScale(3.5, 3.5);
	notBoss.setOrigin(Vector2f(boss_tx->getSize().x/2, boss_tx->getSize().y/2));
	notBoss.setPosition(src->getLength()/2, src->getHeight()/2);
	//notBoss.setColor(Color(255, 0, 0, 255));
    centre = notBoss.getPosition();
	speed = 1;
	turrets = nullptr;
	red = false;
	dying = false;
	EXPL_NR = src->rand(3,10);

	CollisionBoundary = CircleShape(radius, 30);
	VirtualCenter = CircleShape(2, 30);
	CollisionBoundary.setOrigin(Vector2f(radius, radius));
	CollisionBoundary.setPosition(centre);
	CollisionBoundary.setOutlineColor(Color::Cyan);
	CollisionBoundary.setOutlineThickness(2);
	CollisionBoundary.setFillColor(Color(0, 0, 0, 0));
	VirtualCenter.setOrigin(1, 1);
	VirtualCenter.setPosition(centre);
	VirtualCenter.setOutlineColor(Color(255, 0, 0, 255));
	VirtualCenter.setOutlineThickness(4);
	VirtualCenter.setFillColor(Color(0, 0, 0, 0));
	bossSpriteBoundary = RectangleShape(Vector2f(notBoss.getGlobalBounds().width, notBoss.getGlobalBounds().height));
	bossSpriteBoundary.setOrigin(bossSpriteBoundary.getGlobalBounds().width / 2, bossSpriteBoundary.getGlobalBounds().height / 2);
	bossSpriteBoundary.setPosition(notBoss.getPosition());
	bossSpriteBoundary.setFillColor(Color(0, 0, 0, 0));
	bossSpriteBoundary.setOutlineColor(Color(255, 0, 0, 255));
	bossSpriteBoundary.setOutlineThickness(4);
}

/// SETTERS E GETTERS ================================

int Boss::getHp(){
	return this->hp_left;
}

void Boss::setHp(int h_total, int h_left){
	this->hp_total = h_total;
	this->hp_left = h_left;
}

void Boss::setHp(int h_left){
	this->hp_left = h_left;
}

double Boss::getAngle(){
	return this->notBoss.getRotation();
}

void Boss::setAngle(double a){
	this->notBoss.setRotation(a);
}

bool Boss::isDead(){
	return !alive;
}

Vector2f Boss::getCenter(){
	return centre;
}

double Boss::getRadius(){
	return radius;
}

void Boss::setEnemies(BossBunker *p){
	turrets = p;
}


///  FUNZIONI  //////////////////////////////////////////////////////

bool Boss::checkCollisionBoss(Bullets *b){
	list<proiettile>::iterator it = b->bulletList->begin();
	list<proiettile>::iterator end = b->bulletList->end();
	bool hit = false;
	while (it != end){
		if(checkCollisionBoss(&it->bullet)){
			hit = true;
			getHit(b->getDamage());
			it = b->bulletList->erase(it);
		}
		else it++;
	}
	return hit;
}

bool Boss::checkCollisionBoss(Sprite *body){
	if (pow(body->getPosition().x - centre.x, 2) + pow(body->getPosition().y - centre.y, 2) >= pow(radius, 2)) {
		getHit(1);
		return true;
	}
	else return false;
}


void Boss::getHit(int shot){
	if (!dying){
		last_hit.restart();
		if (turrets->isEmpty()){
			hp_left = hp_left - shot;
			notBoss.setColor(Color::Red);
			red = true;
		}
		else src->getWindow()->draw(CollisionBoundary);
	}
}

void Boss::draw(int type){
	if (alive) {
		src->getWindow()->draw(notBoss);
		turrets->drawAll();

		if (!turrets->isEmpty() && last_hit.getElapsedTime().asMilliseconds() < HIT_TIMER_MS){
			src->getWindow()->draw(CollisionBoundary);
		}

		if (type == 1) {
			src->getWindow()->draw(VirtualCenter);
			src->getWindow()->draw(CollisionBoundary);
			bossSpriteBoundary.setRotation(notBoss.getRotation());
			src->getWindow()->draw(bossSpriteBoundary);
		}
	}
}

void Boss::gestisci(){
	if(red && last_hit.getElapsedTime().asMilliseconds() > HIT_TIMER_MS){
		red = false;
		notBoss.setColor(Color::White);
	}

	if (rotation.getElapsedTime().asMilliseconds() > 20 && !(dying  || !alive)) {
		notBoss.setRotation(notBoss.getRotation() + Boss::ROTATION_STEP);	//make it dependent from timePerFrame
		turrets->updatePosition(notBoss.getRotation() + Boss::ROTATION_STEP);
		rotation.restart();
	}
	if (hp_left <= 0 && !dying) {
		dying = true;
		explode();
	}
	else if (dying && last_hit.getElapsedTime().asMilliseconds() < DEATH_TIMER_MS){
		//if we want to add more explosions, this is where.
	}
	else if(dying && last_hit.getElapsedTime().asMilliseconds() > DEATH_TIMER_MS){
		alive = false;
	}
}

void Boss::explode(){
	int offset = 360/EXPL_NR;
	Vector2f newPos = turrets->newPosition(0);
	for (int i = 0; i < EXPL_NR; i++){
		src->addAnimation(newPos.x, newPos.y, 20, 1, 20, 6, 0.3);
		newPos = turrets->newPosition(offset * i);
	}	
}
 
