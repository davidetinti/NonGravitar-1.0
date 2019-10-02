#include "pch.h"
#include "Boss.hpp"


/// COSTRUTTORI /////////////////////////////////////////////////////

Boss::Boss(int life, int turrets, Risorse *src, double angolo, int vel, bool notdead){
    this->src = src;
	hp_total = life;
	hp_left = hp_total;
	turret_total = turrets;
	turret_left = turret_total;
	boss_tx = src->caricaTexture(14);
	alive = notdead;
	angle = angolo;
	radius = 200;
	notBoss.setRadius(radius);
	notBoss.setPointCount(40);
	notBoss.setOrigin(Vector2f(radius, radius));
	notBoss.setPosition(400, 400);
	centre.x = notBoss.getOrigin().x + notBoss.getPosition().x - radius;
	centre.y = notBoss.getOrigin().y + notBoss.getPosition().y - radius;
}

Boss::Boss() {
	hp_total = 1;
	hp_left = 1;
	turret_total = 1;
	turret_left = turret_total;
	angle = 0;
	boss_tx = NULL;
	alive = true;
	radius = 200;
}

///  SETTERS E GETTERS  /////////////////////////////////////////////

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

///  FUNZIONI  //////////////////////////////////////////////////////

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

