#pragma once
#include "Nave.hpp"

struct bunkerlist{
    int type;    // 0 = bunker spara fisso 1/2/3 colpi      1 = bunker segue il giocatore
    int damage;
    double x;
    double y;
    double life;
    double explosion_x;  //posizione del frame nell'animazione dell'esplosione
    double boss_bunker_offset;
    bool exist;
    Sprite bunker,explosion;
    Bullets *weapon;
    bunkerlist(int type_n, int tempo_n, double x_n, double y_n, double life_n,
               Bullets *weapon_n, Texture *b, Texture *e, double boss_bunker_offset = 0);
    void spriteSetup(Texture *bunker_tx,Texture *explosion_tx);
};

class Bunker{

protected:
    int const DEFAULT_TIME_BTW_SHOOT = 2000;
    int const DEFAULT_DAMAGE_SINGLE = 30;
    int const DEFAULT_DAMAGE_TRIPLE = 20;
    int const DEFAULT_SPEED = 3;
    Resources *src;
    Texture *bunker_tx,*explosion_tx,*bunker_tx2;
    double partial_x[4];        //coordinate per la griglia dei bunker
    list<bunkerlist>* bunkers;
    
public:
    
    const int DAMAGEONCOLLISION = 5;    
    Clock bunkerDamage;
    
    // COSTRUTTORI ===================================
    Bunker();
    Bunker(Resources *src, Terreno *terrain);
    
    // SETTERS E GETTERS =============================
    void setEnemies(bunkerlist *enemies);
    
    ///  FUNZIONI  //////////////////////////////////////////////////////
    void armi(bunkerlist *tmp, Terreno *terrain);
	void hitBunker(int damage, list<bunkerlist>::iterator p);
	list<bunkerlist>::iterator deleteBunker(list<bunkerlist>::iterator it);
	bool isEmpty();
    void gestisci(Nave *player, Terreno *terrain, double angle = 0);
    int checkCollisionBBullets(FloatRect obj);
    bool checkCollision(Bullets *b);
    bool checkCollision(Sprite *p);
    bool collidesWith(list<bunkerlist>::iterator p, FloatRect q);
    void drawAll();
    void restartTimers();

protected:
    void spriteSetup(bunkerlist *p);
    virtual void updatePosition(double angle);
};
