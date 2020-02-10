#pragma once
#include "Terreno.hpp"

/**
 Singola tanica di carburante
 */
struct fuel{
    double x;
    double y;
    int power;
    Sprite fuel_sprite;
    fuel(double x_n, double y_n, int power_n);
};


class Fuels{
    
protected:
    
    Resources *src;
    Texture *fuel_tx;
    list<fuel> *fuel_list;
    double partial_x[3];
    
public:
    
    /**
     Costruttore base
     */
    Fuels();
    
    /**
     Costruttore avanzato.
     In modo randomico sceglie posizione, potenza e numero del carburante disponible sulla superficie del pianeta
     
     @param terrain puntatore al terreno della schermata corrente
     @param src puntatore all'utility class Resources
     */
    Fuels(Terreno *terrain,Resources *src);
    
    /**
     Ritorna l'inizio della lista contentente il carburante
     
     @return primo elemento della lista di carburante
     */
    list<fuel>::iterator getFuelListBegin();
    
    /**
    Ritorna la coda della lista contentente il carburante
    
    @return utlimo elemento della lista di carburante
    */
    list<fuel>::iterator getFuelListEnd();
    
    /**
    Elimina l'elemento passato come argomento dalla lista di carburante
    
    @return elemento successivo all'eliminato
    */
    list<fuel>::iterator delete_fuel(list<fuel>::iterator it);
    
    /**
     Ritorna la potenza del carburante passato come argomento
     
     @param it elemento del quale ottenere la potenza
     
     @return potenza dell'elemento
     */
    int getPower(list<fuel>::iterator it);
    
    /**
     Mostra il carburante nel gioco.
     */
    void draw();
    
protected:
    
    /**
    Inizializza le sprite del carburante in base alla potenza.
    
    @param f carburante del quale settare la sprite
    @param power valore di potenza del carburante
    */
    void spriteSetup(fuel *f, int power);

};
