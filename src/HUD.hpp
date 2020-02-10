#pragma once
#include "Pulsante.hpp"

class HUD{
    
protected:
    
    Resources *src;
    Sprite lifebar_active;
    Sprite lifebar_back;
    Sprite fuelbar_active;
    Sprite fuelbar_back;
    Texture *bars_tx;
    Text life;
    Text fuel;
    Text score;
    
public:
    
    /**
     Costruttore base.
     */
    HUD();
    
    /**
     Costruttore avanzato.
     Inizializza le sprite delle status bar e del punteggio da visualizzare durante la partita, impostandone il corretto posizionamento.
     
     @param src puntatore alla classe risorse di gioco
     */
    HUD(Resources *src);
    
    /**
     Modifica le status bar e il punteggio rapportandosi ai valori forniti in argomento.
     Ridimensione le sprite "active" e modifica la stringa del punteggio.
     
     @param point valore attuale dei punti guadagnati
     @param life valore attuale della salute rimasta
     @param fuel valore attuale del carburante rimasto
     */
    void gestisci(int point, float life, float fuel);
    
};
