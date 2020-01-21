#pragma once
#include "BossBunker.hpp"

class Boss {
    
private:
    
    static constexpr double ROTATION_STEP = 0.3;
    static const int HIT_TIMER_MS = 100;
    static const int DEATH_TIMER_MS = 800;
    static const int DAMAGE_ON_COLLISION = 5;
    int EXPL_NR;
     
protected:
    
    int hp_left;
    int turrets_left;
    double radius;
    bool red;
	bool alive;
    bool dying;
    Resources *src;
    Clock last_hit;
    Clock rotation;
	Vector2f centre;
    Texture *boss_tx;
    Texture *hole_tx;
    Sprite boss_sprite;
    BossBunker *turrets;
    CircleShape collision_boundary;
    
public: 
    
    Boss();
    Boss(int life, int turrets, Resources *src_a);
    
    bool isDead();
    Vector2f getCenter();
    double getRadius();
    void setEnemies(BossBunker *boss_bunker_list);
    
    bool checkCollisionBoss(Bullets *weapon);
	bool checkCollisionBoss(Sprite *body);
	void getHit(int damage);
	void draw();
    void handle();
    void explode();
};

 
