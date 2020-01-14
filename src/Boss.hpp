#pragma once
#include "BossBunker.hpp"
#include "Bullets.hpp"

class Boss {
private:
    static constexpr double ROTATION_STEP = 0.6;
    static const int HIT_TIMER_MS = 100;
    static const int DEATH_TIMER_MS = 800;
    int EXPL_NR;
     
protected:
    bool dying;
    bool red;
    Clock last_hit;
    Resources *src;
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
    BossBunker *turrets;
	Clock rotation;
	Texture *hole_tx;
     
public: 
    
    Sprite notBoss;
	RectangleShape bossSpriteBoundary;
	CircleShape CollisionBoundary;
	CircleShape VirtualCenter;
    
    // COSTRUTTORI ===================================
	Boss(int life, int turrets, Resources *src, double angolo = 0, int vel = 1, bool notdead = true);
	Boss();
    
    // SETTERS E GETTERS =============================
    int getHp();
    void setHp(int h_total, int h_left);
    void setHp(int h_left);
    double getAngle();
    void setAngle(double a);
    bool isDead();
    Vector2f getCenter();
    double getRadius();
    void setEnemies(BossBunker *p);
    
    // FUNZIONI ======================================
    bool checkCollisionBoss(Bullets *b);
	bool checkCollisionBoss(Sprite *body);
	void getHit(int shot);
	void draw(int type = 0);
    void gestisci(Nave *player);
    void explode();
};

 
