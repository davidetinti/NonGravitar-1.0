#pragma once
#include "Terreno.hpp"

struct proiettile{
    bool exist;
    Sprite bullet;
    Sound bullet_sound;
    Clock invuln_clock;
    proiettile(double x, double y, double rotation, Texture *bullet_tx);
};


class Bullets{
    
protected:
    
    Resources *src;
    Texture *bullet_tx;
    int time_btw_shoot; //tempo tra i colpi
    int damage;
    int speed;
    double invuln_time; //tempo di invulnerabilità
    bool autoshoot;
    
public:
    list<proiettile> *bulletList;
    SoundBuffer bullet_sb;
    Clock bullet_time;
    
    Bullets();
    Bullets(int time_btw_shoot, int damage, int speed, int tx_nr, int sd_nr, bool autoshoot, Resources *src);
    
    int getDamage();
    
    virtual void addSingleBullet(Sprite entity, Keyboard::Key pulsante) = 0;
    virtual void renderBullet(Time perFrame) = 0;
    virtual int checkCollision(FloatRect p);
    void handle(Time perFrame, Terreno *terrain = nullptr);
    virtual void cleanup(Terreno *terrain) = 0;

protected:

    bool collidesWith(list<proiettile>::iterator p, FloatRect obj);
    bool outsideBounds(list<proiettile>::iterator p, Terreno *terrain);
    bool outsideBounds(list<proiettile>::iterator p);
};
