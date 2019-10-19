#ifndef Universe_hpp
#define Universe_hpp

#include "Pianeta.hpp"
#include "HUD.hpp"

struct lista_schermate {
    lista_schermate* dx;
    lista_schermate* sx;
    lista_schermate* up;
    lista_schermate* dw;
    int x;
    int y;
    uPlanets pianeti;
    lista_schermate *next;
    lista_schermate(int x_n, int y_n, Resources *src, lista_schermate *d=NULL, lista_schermate *s=NULL, 
        lista_schermate *u=NULL, lista_schermate *down=NULL, lista_schermate *nxt=NULL);
};


class Universe {
    
protected:
    
    lista_schermate *active;
    lista_schermate *tail;
    lista_schermate *head_list;
    Resources *src;
    
public:
    
    Nave player;
    HUD hud;
    
    
    // COSTRUTTORI ===================================
    Universe();
    Universe(Resources *src);
    
    // SETTERS E GETTERS =============================
    lista_schermate *getActive();
    lista_schermate *getTail();
    lista_schermate *getHeadList();
    
    // FUNZIONI ======================================
    lista_schermate *find(int x, int y);
    void move(int x, int y);
    void disegnaPianeti();
    void checkTerrain();
    void handle();
    
private:
    
    bool contactPlanet(Vector2f pos, Pianeta* p);
    void addToList(lista_schermate *p);
};

#endif /* Universo_hpp */
