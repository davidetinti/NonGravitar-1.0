#ifndef Bullets_hpp
#define Bullets_hpp

#include "Terreno.hpp"

struct proiettile{
    bool exist;
    Sprite bullet;
    Sound bullet_sound;
    Clock invuln_clock;
    proiettile *next;
    proiettile *prev;
    proiettile(proiettile *next_n, proiettile *prev_n = NULL);
};


class Bullets{
    
protected:
    
    Resources *src;
    Texture *bullet_tx;
    proiettile *head;
    int time_btw_shoot; //tempo tra i colpi
    int damage;
    int speed;
    double invuln_time; //tempo di invulnerabilità
    bool autoshoot;
    
public:
    
    SoundBuffer bullet_sb;
    Clock bullet_time;
    
    // COSTRUTTORI ===================================
    Bullets();
    Bullets(int time_btw_shoot, int damage, int speed, int tx_nr, int sd_nr, bool autoshoot, Resources *src);
    
    // SETTERS E GETTERS =============================
    proiettile* getHead();
    void setHead(proiettile *head);

    ///  FUNZIONI  //////////////////////////////////////////////////////
    virtual void addSingleBullet(Sprite entity, Keyboard::Key pulsante, int tempo) = 0;
    virtual void renderBullet(Terreno *terrain,Time perFrame) = 0;
	void deleteBullet(proiettile *p);
    virtual int checkCollision(FloatRect p);

protected:

    bool collidesWith(proiettile *p, FloatRect obj);
    void spriteSetup(proiettile *p, double x, double y, double rotation);
    bool outsideBounds(proiettile *p, Terreno *terrain);
};

#endif /* Bullets_hpp */
