#pragma once
#include "Fuels.hpp"
#include "Boss.hpp"

struct lista_schermate_pianeta {
    lista_schermate_pianeta* next;
    lista_schermate_pianeta* prev;
    Bunker *enemies;
    Terreno *terrain;
    Fuels *carb;
    int nr_schermata;
    lista_schermate_pianeta(Terreno *terrain_n, int n,
                        int totale_schermate, Resources *src,
                        lista_schermate_pianeta *next_n = nullptr,
                        lista_schermate_pianeta *prev_n = nullptr);
    lista_schermate_pianeta(Resources *src);
};

class GPlanet {
    
protected:
    
    static const int BOSS_POINTS = 1000;
    Resources *src;
    bool boss_unlocked,in_boss;
    lista_schermate_pianeta *current, *head, *boss_screen;
    Texture *hole_tx;
    Sprite hole;
    int nr_schermate;
    bool completed;
    
public:
    
    Boss boss;
    
    GPlanet();

    bool getBoss_unlocked();
    lista_schermate_pianeta *getCurrent();
    lista_schermate_pianeta *getHead();
    void setBoss_unlocked(bool boss_unlocked);
    void setCurrent(lista_schermate_pianeta *current);
    void setHead(lista_schermate_pianeta *head);
    bool getIn_boss();
    
    lista_schermate_pianeta *find(int n);
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
