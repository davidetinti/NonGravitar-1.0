#pragma once
#include "Fuels.hpp"
#include "Boss.hpp"

#define BOSS_SCREEN 666
#define STANDARD_PLANET_POINTS 500
#define COLLISION_DAMAGE 10

struct planet_screen {
    
    int screen_nr;
    Fuels *carb;
    Bunker *enemies;
    Terreno *terrain;
    planet_screen* next;
    planet_screen* prev;
    planet_screen(Terreno *terrain_n, int n, Resources *src,
                  planet_screen *next_n = nullptr, planet_screen *prev_n = nullptr);
    planet_screen(Resources *src);
};

class GPlanet {
    
protected:
    
    Resources *src;
    bool boss_unlocked,in_boss;
    planet_screen *current, *head, *boss_screen;
    Texture *hole_tx;
    Sprite hole;
    int nr_schermate;
    bool completed;
    
public:
    
    Boss boss;
    
    GPlanet();

    bool getBoss_unlocked();
    planet_screen *getCurrent();
    planet_screen *getHead();
    void setBoss_unlocked(bool boss_unlocked);
    void setCurrent(planet_screen *current);
    void setHead(planet_screen *head);
    bool getIn_boss();
    
    void inizializza(int tot_schermate, Resources *src);
    void cambia_schermata(int n);
    void checkCollision(Nave *player);
    void handle(Nave *player);
    bool inHole(Sprite *body);
    void enterBoss(Nave *player);
    void checkTerrain(Nave *player);
    void raggiotraente(Nave *player);
    bool getCompleted();
    void checkScreen(Nave *player);
    
protected:
    
    int random_height();
    void updateBossLock();
};
