#pragma once
#include "Pianeti.hpp"
#include "HUD.hpp"

struct uni_screen {
    uni_screen* dx;
    uni_screen* sx;
    uni_screen* up;
    uni_screen* dw;
    int x;
    int y;
    Pianeti pianeti;
    uni_screen *next;
    uni_screen(int x_n, int y_n, Resources *src, uni_screen *d = nullptr,
                    uni_screen *s = nullptr, uni_screen *u = nullptr,
                    uni_screen *down = nullptr, uni_screen *nxt = nullptr);
};


class Universe {
    
protected:
    
    uni_screen *active;
    uni_screen *tail;
    uni_screen *head_list;
    Resources *src;
    
public:
    
    Nave player;
    HUD hud;
    
    Universe();
    Universe(Resources *src);
    
    uni_screen *getActive();
    uni_screen *getTail();
    uni_screen *getHeadList();
    
    uni_screen *find(int x, int y);
    void move(int x, int y);
    void checkTerrain();
    void handle();
    
private:
    
    bool contactPlanet(Vector2f pos, SinglePlanet* p);
    void addToList(uni_screen *p);
    void exitPlanet();
};
