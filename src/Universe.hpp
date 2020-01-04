#ifndef Universe_hpp
#define Universe_hpp

#include "Pianeti.hpp"
#include "HUD.hpp"

struct lista_schermate {
    lista_schermate* dx;
    lista_schermate* sx;
    lista_schermate* up;
    lista_schermate* dw;
    int x;
    int y;
    Pianeti pianeti;
    lista_schermate *next;
    lista_schermate(int x_n, int y_n, Resources *src, lista_schermate *d=nullptr, lista_schermate *s=nullptr, 
        lista_schermate *u=nullptr, lista_schermate *down=nullptr, lista_schermate *nxt=nullptr);
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
    void checkTerrain();
    void handle();
    
private:
    
    bool contactPlanet(Vector2f pos, SinglePlanet* p);
    void addToList(lista_schermate *p);
    void exitPlanet();
};

#endif /* Universo_hpp */
