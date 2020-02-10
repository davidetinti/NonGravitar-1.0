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
    
    /**
        Costruttore della lista di schermate.
        
        @param x_n coordinata x della posizione
        @param y_n coordinta y della posizione
        @param src puntatore all'utility class Resources
        @param d puntatore alla schermata sotto a quella corrente
        @param s puntatore alla schermata sinistra rispetto a quella corrente
        @param u puntatore alla schermata sopra a quella corrente
        @param d puntatore alla schermata destra ripsetto a quella corrente
        @param nxt puntatore alla schermata successiva
        */
     
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
    
    /**
    Costruttore base.
    */
    Universe();
    
    /**
    Costruttore avanzato.
    Genera la schermata dell'universo giusta.
    
    @param src puntatore all'utility class Resources
    */
    Universe(Resources *src);
    
    /**
    Ritorna la schermata attiva
    */
    uni_screen *getActive();
    
    /**
    Ritorna la coda della lista delle schermate
    */
    uni_screen *getTail();
    
    /**
    Ritorna la testa della lista delle schermate
    */
    uni_screen *getHeadList();
    
    /**
    Trova la schermata da caricare
    
    @param x fattore di spostamento lungo l'asse  x
    @param y fattore di spostamento lungo l'asse  y
    */
    uni_screen *find(int x, int y);
    
    /**
    Gestisce le schermate in base alla direzione della navicella
    
    @param x fattore di spostamento lungo l'asse  x
    @param y fattore di spostamento lungo l'asse  y
    */
    void move(int x, int y);
    
    /**
    Gestione globale dell'universo (animazioni, raffigurazione ed eliminazione dei pianeti ecc)
    */
    void handle();
    
private:
    
    /**
    Controlla se il giocatore si scontra con un pianeta
    
    @param pos posizione del giocatore
    @param p puntatore ad un pianeta
    */
    bool contactPlanet(Vector2f pos, SinglePlanet* p);
    
    /**
    Aggiunge una nuova schermata di dell'universo alla lista di schermate
    
    @param p puntatore alla lista di schermate
    */
    void addToList(uni_screen *p);
    
    /**
    Setta la posizione della navicella quando il giocatore esce dal pianeta
    */
    void exitPlanet();
};
