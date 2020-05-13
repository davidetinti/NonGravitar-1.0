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
    Pianeti planets;
    uni_screen *next;

    /**
        Costruttore della lista di schermate.

        @param x_n coordinata x della posizione
        @param y_n coordinta y della posizione
        @param src puntatore all'utility class Resources
        @param d puntatore alla schermata graficamente sotto la corrente
        @param s puntatore alla schermata graficamente a sinistra della corrente
        @param u puntatore alla schermata graficamente sopra la corrente
        @param down puntatore alla schermata graficamente a destra della corrente
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
    
    /**
    Costruttore base.
    */
    Universe();

    /**
    Costruttore avanzato.
    Inizializza il giocatore, e la prima schermata di pianeti

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
    Controlla se il giocatore è in entrata su di un pianeta

    @param pos posizione del giocatore
    @param p puntatore al pianeta del quale verificare il contatto
    */
    bool contactPlanet(Vector2f pos, SinglePlanet* p);

    /**
    Aggiunge una nuova schermata dell'universo alla lista di schermate

    @param p puntatore alla lista di schermate
    */
    void addToList(uni_screen *p);

    /**
    Setta la posizione della navicella quando il giocatore esce dal pianeta
    */
    void exitPlanet();
};
