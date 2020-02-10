#include "Boss.hpp"


Boss::Boss(){
    
}


Boss::Boss(int life, int turrets_n, Resources *src_a){
    hp_left = life;
    turrets_left = turrets_n;
    radius = boss_tx->getSize().x/2 - 350;
    red = false;
	alive = true;
    dying = false;
    src = src_a;
    centre = boss_sprite.getPosition();
	boss_tx = src->getTexture(32);
	boss_sprite.setTexture(*boss_tx);
	boss_sprite.setOrigin(Vector2f(boss_tx->getSize().x/2, boss_tx->getSize().y/2));
	boss_sprite.setPosition(src->getLength()/2, src->getHeight()/2);
	turrets = nullptr;
	collision_boundary = CircleShape(radius, 30);
	collision_boundary.setOrigin(Vector2f(radius, radius));
	collision_boundary.setPosition(centre);
	collision_boundary.setOutlineColor(Color::Cyan);
	collision_boundary.setOutlineThickness(2);
	collision_boundary.setFillColor(Color(0, 0, 0, 0));
    EXPL_NR = src->rand(3,10);
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


void Boss::setEnemies(BossBunker *boss_bunker_list){
	turrets = boss_bunker_list;
}


bool Boss::checkCollisionBoss(Bullets *weapon){
	list<proiettile>::iterator it = weapon->bulletList->begin();
	list<proiettile>::iterator end = weapon->bulletList->end();
	bool hit = false;
	while (it != end && !hit){
		if(checkCollisionBoss(&it->bullet)){
			hit = true;
			getHit(weapon->getDamage());
			it = weapon->bulletList->erase(it);
		}
		else it++;
	}
	return hit;
}


bool Boss::checkCollisionBoss(Sprite *body){
	if (pow(body->getPosition().x - centre.x, 2) + pow(body->getPosition().y - centre.y, 2) >= pow(radius, 2)) {
		getHit(DAMAGE_ON_COLLISION);
		return true;
	}
	else return false;
}


void Boss::getHit(int damage){
	if (!dying){
		last_hit.restart();
		if (turrets->isEmpty()){
			hp_left = hp_left - damage;
			boss_sprite.setColor(Color::Red);
			red = true;
		}
		else src->getWindow()->draw(collision_boundary);
	}
}


void Boss::draw(){
	if (alive) {
		src->getWindow()->draw(boss_sprite);
		turrets->drawAll();
        
		if (!turrets->isEmpty() && last_hit.getElapsedTime().asMilliseconds() < HIT_TIMER_MS){
			src->getWindow()->draw(collision_boundary);
		}
	}
}


void Boss::handle(){
	if(red && last_hit.getElapsedTime().asMilliseconds() > HIT_TIMER_MS){
		red = false;
		boss_sprite.setColor(Color::White);
	}

	if (rotation.getElapsedTime().asMilliseconds() > 20 && !(dying  || !alive)) {
        boss_sprite.setRotation(boss_sprite.getRotation() + Boss::ROTATION_STEP);
		turrets->updatePosition(boss_sprite.getRotation() + Boss::ROTATION_STEP);
		rotation.restart();
	}
	if (hp_left <= 0 && !dying) {
		dying = true;
		explode();
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
 
