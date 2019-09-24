#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Bullets.hpp"

using namespace sf;

class Boss{
    
protected:
    
	int hp_total;
	int hp_left;
	int turret_total;
	int turret_left;
    int speed;
    double angle;
    double radius;
	bool alive;
	Vector2f centre;
    ptr_Texture boss_tx;
    
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
	void draw(RenderWindow *window);
};

