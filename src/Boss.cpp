#include "Boss.hpp"

// COSTRUTTORI =======================================

Boss::Boss() {
    this->hp_total = 1;
    this->hp_left = 1;
    this->turret_total = 1;
    this->turret_left = turret_total;
    this->angle = 0;
    this->boss_tx = NULL;
    this->alive = true;
    this->radius = 200;
}

Boss::Boss(int life, int turrets, Resources *src, double angolo, int vel, bool notdead){
    this->src = src;
	this->hp_total = life;
	this->hp_left = hp_total;
	this->turret_total = turrets;
	this->turret_left = turret_total;
	this->boss_tx = src->caricaTexture(14);
	this->alive = notdead;
	this->angle = angolo;
	this->radius = 200;
	this->notBoss.setRadius(radius);
	this->notBoss.setPointCount(40);
	this->notBoss.setOrigin(Vector2f(radius, radius));
	this->notBoss.setPosition(400, 400);
	this->centre.x = notBoss.getOrigin().x + notBoss.getPosition().x - radius;
	this->centre.y = notBoss.getOrigin().y + notBoss.getPosition().y - radius;
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

// FUNZIONI ==========================================

bool Boss::checkCollisionBoss(Sprite *body){
	Vector2f closestPoint;
	FloatRect bodyRect = body->getGlobalBounds();
	double distanceSquared = 0; 
	closestPoint = Vector2f(bodyRect.top, bodyRect.left);
	if (pow(closestPoint.x - centre.x, 2) + pow(closestPoint.y - centre.y, 2) < pow(bodyRect.left + bodyRect.width, 2) + pow(bodyRect.top, 2)) closestPoint = Vector2f(bodyRect.left + bodyRect.width, bodyRect.top);
	if (pow(closestPoint.x - centre.x, 2) + pow(closestPoint.y - centre.y, 2) < pow(bodyRect.left + bodyRect.width, 2) + pow(bodyRect.top + bodyRect.height, 2)) closestPoint = Vector2f(bodyRect.left + bodyRect.width, bodyRect.top + bodyRect.height);
	if (pow(closestPoint.x - centre.x, 2) + pow(closestPoint.y - centre.y, 2) < pow(bodyRect.left, 2) + pow(bodyRect.top + bodyRect.height, 2)) closestPoint = Vector2f(bodyRect.left, bodyRect.top + bodyRect.height);

	distanceSquared = pow(closestPoint.x-centre.x, 2) + pow(closestPoint.y-centre.y, 2);
	if(distanceSquared < pow(radius, 2))	return false;
	else {
		getHit(1);
		return true;
	}
}

void Boss::getHit(int shot){
	hp_total = hp_total - shot;
}

void Boss::draw(){
	src->getWindow()->draw(notBoss);
}

