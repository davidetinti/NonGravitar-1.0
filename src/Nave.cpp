#include "Nave.hpp"


Nave::Nave(){
    
}


Nave::Nave(Resources* src){
    this->src = src;
    ray_x = 0;
    ray_y = 0;
    ray_tx = this->src->getTexture(17);
    ray.setScale(0.30, 0.80);
    ray.setTexture(*ray_tx);
    ray.setColor(Color(255,255,255,160));
    points = 0;
    planet_x = this->src->getLength()/2;
    planet_y = this->src->getHeight()/2;
    life_left = TOTAL_LIFE;
    fuel_left = TOTAL_FUEL;
    top_speed = 5;
	current_speed = 0;
	direction_x = 0; direction_y = 0;
    acceleration = 0.1;
    at_planet = false;
    is_dead = false;
    is_red = false;
    spaceship_tx = this->src->getTexture(4);
    spaceship.setOrigin(Vector2f(spaceship_tx->getSize().x/2, spaceship_tx->getSize().y/2));
    spaceship.setPosition(Vector2f(this->src->getLength() / 2, this->src->getHeight() / 2));
    spaceship.setTexture(*spaceship_tx);
    spaceship.scale(Vector2f(0.2, 0.2));
    spaceship.setRotation(0);
    spaceship.setTextureRect(IntRect(0, 0, spaceship_tx->getSize().x, spaceship_tx->getSize().y));
    SingleShot = new SingleStraightBullets(100, 50, 10, 0, 0, false, src);
    Laser = new SingleStraightBullets(5000, 200, 10, 1, 0, false, src);
	time_btw_hit_S = 0.75;
	time_btw_pushes_MS = 500;
	thrust_tx = src->getTexture(30);
	thrust.setTexture(*thrust_tx);
	thrust.setScale(0.04, 0.04);
	thrust_int = 0;
	thrust.setOrigin(Vector2f(thrust_tx->getSize().x/2, thrust_tx->getSize().y));
    in_boss = false;
}


bool Nave::getIsDead(){
    return this->is_dead;
}


bool Nave::getAtPlanet(){
    return this->at_planet;
}


void Nave::setAtPlanet(bool atplanet){
    this->at_planet = atplanet;
}


double Nave::getLifebar(){
    return this->life_left;
}


double Nave::getFuelbar(){
    return this->fuel_left;
}


void Nave::increaseFuel(double fuelbar){
    if (fuel_left + fuelbar >= 100){
        fuel_left = 100;
    } else {
        fuel_left = fuel_left + fuelbar;
    }
}


void Nave::setTopSpeed(double speed){
    this->top_speed = speed;
}


void Nave::setSpaceshipAcceleration(float acceleration){
    this->acceleration = acceleration;
}


double Nave::getX_planet(){
    return this->planet_x;
}


double Nave::getY_planet(){
    return this->planet_y;
}


int Nave::getPoints(){
    return this->points;
}


void Nave::incrasePoints(int new_points){
    this->points = this->points + new_points * src->getDifficulty();
}


void Nave::setDxDy(double newDx, double newDy){
	direction_x = newDx; direction_y = newDy;
}


void Nave::addToDxDy(double offsetDx, double offsetDy){
	direction_x = direction_x + offsetDx;
	direction_y = direction_y + offsetDy;
}


double Nave::getAnglePlanet(){
	return angle_entering_planet;
}


void Nave::decayThrustInt(){
	if (thrust_int > 0) thrust_int=thrust_int - 10;
	if (thrust_int < 0) thrust_int = 0;
}


void Nave::armi(Terreno *terrain){
    SingleShot->addSingleBullet(spaceship, Keyboard::Key::S);
    Laser->addSingleBullet(spaceship, Keyboard::Key::L);
    SingleShot->handle(terrain);
    Laser->handle(terrain);
}


bool Nave::raggioTraente(){
    if (Keyboard::isKeyPressed(Keyboard::F)){
        if (ray_x > 8){
            ray_y++;
            ray_x = 0;
        }
        if (ray_y > 8){
            ray_x = 0;
            ray_y = 0;
        }
        ray.setTextureRect(IntRect(500*(int)ray_x,500*(int)ray_y,500,500));
        ray.setPosition(spaceship.getPosition());
        ray.setOrigin(250, 0);
        ray_x = ray_x+0.2;
        src->getWindow()->draw(ray);
        return true;
    } else {
        return false;
    }
} 

//call with 1 to ignore clock
void Nave::getHit(int damage, int hit_type){
    if ((!is_red || hit_type == 1) && damage > 0){
        is_red = true;
        spaceship.setColor(Color::Red);
        last_hit.restart();
        life_left = life_left - (src->getDifficulty() * damage);
    } else if (last_hit.getElapsedTime().asMilliseconds() > HIT_TIMER_MS){
        spaceship.setColor(Color::White);
        is_red = false;
    }
}

void Nave::push_back(int distance, int dir){
	Time elapsed = push_clock.getElapsedTime();
    static Vector2f centre = Vector2f(src->getLength()/2,src->getHeight()/2);
	if (elapsed.asMilliseconds() > time_btw_pushes_MS) {
        switch (dir){
            case 0: 
                spaceship.setRotation(180);
		        direction_y = -10 * distance;
                break;
            case 1:
                spaceship.setRotation(270 + atan2(centre.y-spaceship.getPosition().y, 
                                        centre.x-spaceship.getPosition().x) * (180/M_PI));
                direction_x = cos((spaceship.getRotation()-270) * M_PI / 180) * distance;
                direction_y = sin((spaceship.getRotation()-270) * M_PI / 180) * distance;
                
                break;
        }
		
		push_clock.restart();
	}
}

void Nave::gestisci(){
    movements();
    if (life_left <= 0 || fuel_left <= 0) is_dead = true;
}

void Nave::handleThrust(){
    thrust.setRotation(spaceship.getRotation());
	thrust.setPosition(spaceship.getPosition());
	thrust.setColor(Color(255, 255, 255, thrust_int));
}

void Nave::movements(){
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        spaceship.setRotation(spaceship.getRotation() - 3);
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        spaceship.setRotation(spaceship.getRotation() + 3);
    }
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
		addToDxDy(cos((spaceship.getRotation()-270) * M_PI / 180) * acceleration, 
                  sin((spaceship.getRotation()-270) * M_PI / 180) * acceleration);
		thrust_int = 255;
		if (fuel_left > 0 && !in_boss)
            fuel_left = fuel_left - src->getDifficulty() * acceleration/2;
    } else {
		decayThrustInt();
		if(at_planet)
			setDxDy(direction_x*0.98, direction_y*0.98);
    }
	current_speed = sqrt(direction_x * direction_x + direction_y * direction_y);
	if (current_speed > top_speed) {
		setDxDy(direction_x * top_speed / current_speed, direction_y * top_speed / current_speed);
	}

	spaceship.move(direction_x * src->getTimePerFrame()->asMilliseconds() * 0.1,direction_y * src->getTimePerFrame()->asMilliseconds() * 0.1);
}

void Nave::braceForEntry(Vector2f planetPos){
    spaceship.setPosition(src->getLength()/2, 0);
    angle_entering_planet = 0;
    planet_x = planetPos.x;
    planet_y = planetPos.y + 35;
    spaceship.setRotation(0);
    setDxDy(0, 0.8);
    current_speed = sqrt(direction_x * direction_x + direction_y * direction_y);
}

void Nave::resetStats(){
    life_left = TOTAL_LIFE;
    fuel_left = TOTAL_FUEL;
    in_boss = false;
}

