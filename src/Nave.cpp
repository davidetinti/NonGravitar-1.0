#include "Nave.hpp"

// COSTRUTTORI =======================================

Nave::Nave(){
    
}

Nave::Nave(Resources* src){
    this->src = src;
    raggiox = 0;
    raggioy = 0;
    raggio_tx = this->src->caricaTexture(17);
    raggio.setTexture(*raggio_tx);
    raggio.setScale(0.2,0.4);
    raggio.setColor(Color(255,255,255,160));
    punti = 0;
    X_planet = this->src->getLength()/2;
    Y_planet = this->src->getHeight()/2;
    Lifebar = 100;
    Fuelbar = 100;
    TopSpeed = 5;
	CurrentSpeed = 0;
	dx = 0; dy = 0;
    SpaceshipAcceleration = 0.1;
    AtPlanet = false;
    IsDead = false;
    Nave_tx = this->src->caricaTexture(4);
    nave.setOrigin(Vector2f(Nave_tx->getSize().x/2, Nave_tx->getSize().y/2));
    nave.setPosition(Vector2f(this->src->getLength() / 2, this->src->getHeight() / 2));
    nave.setTexture(*Nave_tx);
    nave.scale(Vector2f(0.15, 0.15));
    nave.setRotation(0);
    nave.setTextureRect(IntRect(0, 0, Nave_tx->getSize().x, Nave_tx->getSize().y));
    SingleShot = new SingleStraightBullets(100, 100, 10, 0, 0, false, src);
    Laser = new SingleStraightBullets(5000, 200, 10, 1, 0, false, src);
	Time_btw_hitS = 0.75;
	Time_btw_pushesMS = 500;
	thrust_tx = src->caricaTexture(30);
	thrust.setTexture(*thrust_tx);
	thrust.setScale(0.04, 0.04);
	thrust_int = 0;
	thrust.setOrigin(Vector2f(thrust_tx->getSize().x/2, thrust_tx->getSize().y));
}

// SETTERS E GETTERS =================================

bool Nave::getIsDead(){
    return this->IsDead;
}

void Nave::setIsDead(bool isdead){
    this->IsDead = isdead;
}

bool Nave::getAtPlanet(){
    return this->AtPlanet;
}

void Nave::setAtPlanet(bool atplanet){
    this->AtPlanet = atplanet;
}

double Nave::getLifebar(){
    return this->Lifebar;
}

void Nave::setLifebar(double lifebar){
    this->Lifebar = lifebar;
}

double Nave::getFuelbar(){
    return this->Fuelbar;
}

void Nave::setFuelbar(double fuelbar){
    if (fuelbar >= 100){
        this->Fuelbar = 100;
    } else {
        this->Fuelbar = fuelbar;
    }
}

double Nave::getTopSpeed(){
    return this->TopSpeed;
}

void Nave::setTopSpeed(double speed){
    this->TopSpeed = speed;
}

float Nave::getSpaceshipAcceleration(){
    return this->SpaceshipAcceleration;
}

void Nave::setSpaceshipAcceleration(float acceleration){
    this->SpaceshipAcceleration = acceleration;
}

double Nave::getX_planet(){
    return this->X_planet;
}

void Nave::setX_planet(double x){
    this->X_planet = x;
}

double Nave::getY_planet(){
    return this->Y_planet;
}

void Nave::setY_planet(double y){
    this->Y_planet = y;
}


int Nave::getPunti(){
    return this->punti;
}

void Nave::setPunti(int punti){
    this->punti = punti;
}

void Nave::setDxDy(double newDx, double newDy){
	dx = newDx; dy = newDy;
}

void Nave::addToDxDy(double offsetDx, double offsetDy){
	dx = dx + offsetDx;
	dy = dy + offsetDy;
}

double Nave::getDx(){
	return dx;
}

double Nave::getDy(){
	return dy;
}

double Nave::getCurrentSpeed(){
	return CurrentSpeed;
}

void Nave::setCurrentSpeed(double speed){
	CurrentSpeed = speed;
}

void Nave::setAnglePlanet(double angle){
	angle_entering_planet = angle;
}

double Nave::getAnglePlanet(){
	return angle_entering_planet;
}

void Nave::setThrustInt(int boost){
	thrust_int = boost;
}

int Nave::getThrustInt(){
	return thrust_int;
}

void Nave::decayThrustInt(){
	if (thrust_int > 0) thrust_int=thrust_int - 10;
	if (thrust_int < 0) thrust_int = 0;
}

// FUNZIONI ==========================================

void Nave::armi(Terreno *terrain){
    SingleShot->addSingleBullet(nave, Keyboard::Key::S, 0);
    Laser->addSingleBullet(nave, Keyboard::Key::L, 0);
    SingleShot->renderBullet(terrain, *src->getTimePerFrame());
    Laser->renderBullet(terrain, *src->getTimePerFrame());
}

bool Nave::raggioTraente(){
    if (Keyboard::isKeyPressed(Keyboard::F)){
        raggio.setTextureRect(IntRect(256*raggiox,256*raggioy,256,256));
        raggiox++;
        if (raggiox >= 5){
            raggioy++;
            raggiox = 0;
        }
        if (raggioy >= 4){
            raggiox = 0;
            raggioy = 0;
        }
        raggio.setPosition(nave.getPosition());
        raggio.setOrigin(128, 0);
        src->getWindow()->draw(raggio);
        return true;
    } else {
        return false;
    }
} 

//call with 1 to ignore clock
void Nave::getHit(int damage, int hitType){
	Time elapsed = DamageClock.getElapsedTime();
	if (elapsed.asSeconds() > Time_btw_hitS || hitType == 1) {
		Lifebar = Lifebar - damage;
		DamageClock.restart();
	}
}

void Nave::push_back(int distance){
	Time elapsed = PushClock.getElapsedTime();
	if (elapsed.asMilliseconds() > Time_btw_pushesMS) {
		nave.setRotation(180);
		dy = 10 * distance;
		PushClock.restart();
	}
}

void Nave::gestisci(){
    movements();
    //if (Lifebar <= 0 || Fuelbar <= 0) IsDead = true;
}

void Nave::handleThrust(){
    thrust.setRotation(nave.getRotation());
	thrust.setPosition(nave.getPosition());
	thrust.setColor(Color(255, 255, 255, getThrustInt()));
}

void Nave::movements(){
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        nave.setRotation(nave.getRotation() - 3);
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        nave.setRotation(nave.getRotation() + 3);
    }
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
		addToDxDy(cos((nave.getRotation()-270) * M_PI / 180) * getSpaceshipAcceleration(), sin((nave.getRotation()-270) * M_PI / 180) * getSpaceshipAcceleration());
		setThrustInt(255);
		if (getFuelbar() > 0)
            setFuelbar(getFuelbar() - getSpaceshipAcceleration()/2);
    } else {
		decayThrustInt();
		if(getAtPlanet())
			setDxDy(getDx()*0.98, getDy()*0.98);
    }
	setCurrentSpeed(sqrt(getDx() * getDx() + getDy() * getDy()));
	if (getCurrentSpeed() > getTopSpeed()) {
		setDxDy(getDx() * getTopSpeed() / getCurrentSpeed(), getDy() * getTopSpeed() / getCurrentSpeed());
	}

	nave.move(getDx() * src->getTimePerFrame()->asMilliseconds() * 0.1,getDy() * src->getTimePerFrame()->asMilliseconds() * 0.1);
}

void Nave::braceForEntry(Vector2f planetPos, int larghezza){
    nave.setPosition(larghezza/2, 0);
    setAnglePlanet(0);
    setX_planet(planetPos.x);
    setY_planet(planetPos.y + 35);
    nave.setRotation(0);
    setDxDy(0, 0.8);
    setCurrentSpeed(sqrt(getDx() * getDx() + getDy() * getDy()));
}
