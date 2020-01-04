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
	notBoss.setPosition(620, 360);
	//notBoss.setColor(Color(255, 0, 0, 255));
	centre.x = notBoss.getPosition().x;
	centre.y = notBoss.getPosition().y;
	speed = 1;
	turrets = nullptr;
	

	CollisionBoundary = CircleShape(radius, 30);
	VirtualCenter = CircleShape(2, 30);
	CollisionBoundary.setOrigin(Vector2f(radius, radius));
	CollisionBoundary.setPosition(centre.x, centre.y);
	CollisionBoundary.setOutlineColor(Color(255, 0, 0, 255));
	CollisionBoundary.setOutlineThickness(2);
	CollisionBoundary.setFillColor(Color(0, 0, 0, 0));
	VirtualCenter.setOrigin(1, 1);
	VirtualCenter.setPosition(centre.x, centre.y);
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
	return turrets->isEmpty(); // || hp_left > 0;
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
	hp_total = hp_total - shot;
}

void Boss::draw(int type){
	if (alive) {
		src->getWindow()->draw(notBoss);
		turrets->drawAll();

		if (type == 1) {
			src->getWindow()->draw(VirtualCenter);
			src->getWindow()->draw(CollisionBoundary);
			bossSpriteBoundary.setRotation(notBoss.getRotation());
			src->getWindow()->draw(bossSpriteBoundary);
		}
	}
}

void Boss::gestisci(Nave *player){
	if (rotation.getElapsedTime().asMilliseconds() > 20) {
		notBoss.setRotation(notBoss.getRotation() + Boss::ROTATION_STEP);	//make it dependent from timePerFrame
		turrets->updatePosition(notBoss.getRotation() + Boss::ROTATION_STEP);
		rotation.restart();
	}
	if (hp_left <= 0) {
		alive = false;
	}
}

 
