#ifndef GPlanet_hpp
#define GPlanet_hpp

#include "pch.h"
#include "Bunker.hpp"
#include "Fuel.hpp"
#include "Boss.hpp"
#include "Transitions.hpp"

using namespace sf;
using namespace std;

struct lista_schermate_pianeta {
    lista_schermate_pianeta* next;
    lista_schermate_pianeta* prev;
    Bunker enemies;
    Terreno terrain;
    Fuel carb;
    int nr_schermata;
    lista_schermate_pianeta(Terreno terrain_n, int n,
                        int totale_schermate, Risorse *src,
                        lista_schermate_pianeta *next_n = NULL,
                        lista_schermate_pianeta *prev_n = NULL);
    lista_schermate_pianeta(Risorse *src);
};

class GPlanet {
    
protected:
    
    Risorse *src;
    bool boss_unlocked,in_boss;
    lista_schermate_pianeta *current, *head, *boss_screen;
    Texture *hole_tx;
    Sprite hole;
    
public:
    
    Boss boss;
    
    /// COSTRUTTORI /////////////////////////////////////////////////////
    GPlanet();

    ///  SETTERS E GETTERS  /////////////////////////////////////////////
    bool getBoss_unlocked();
    lista_schermate_pianeta *getCurrent();
    lista_schermate_pianeta *getHead();
    void setBoss_unlocked(bool boss_unlocked);
    void setCurrent(lista_schermate_pianeta *current);
    void setHead(lista_schermate_pianeta *head);
    
    ///  FUNZIONI  //////////////////////////////////////////////////////
    lista_schermate_pianeta *find(int n);
    int checkCollisionBunkBullets(FloatRect obj);
    void inizializza(int tot_schermate, Risorse *src);
    void cambia_schermata(int n);
    void checkCollision(Nave *player);
    void gestione(Nave *player, Time perFrame);
protected:
    int random_height();
};

#endif /* GPlanet_hpp */
