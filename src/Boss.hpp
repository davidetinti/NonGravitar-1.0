#pragma once
#include "Bullets.hpp"

using namespace sf;

class Boss{
    
protected:
    
    Risorse *src;
	int hp_total;
	int hp_left;
	int turret_total;
	int turret_left;
    int speed;
    double angle;
    double radius;
	bool alive;
	Vector2f centre;
    Texture *boss_tx;
    
public:
    
    CircleShape notBoss;
    
    /// COSTRUTTORI /////////////////////////////////////////////////////
	Boss(int life, int turrets, Risorse *src, double angolo = 0, int vel = 1, bool notdead = true);
	Boss();
    
    ///  SETTERS E GETTERS  /////////////////////////////////////////////
    int getHp();
    void setHp(int h_total, int h_left);
    void setHp(int h_left);
    double getAngle();
    void setAngle(double a);
    
    ///  FUNZIONI  //////////////////////////////////////////////////////
	bool checkCollisionBoss(Sprite *body);
	void getHit(int shot);
	void draw();
};

