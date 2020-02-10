#pragma once
#include "Resources.hpp"

class Pulsante{
    
protected:
    
    Resources *src;
    Sprite button;
    Texture *button_tx;
    Vector2f original_scale;
    char name[20];
    
public:
    
    /**
     Costruttore base.
     */
    Pulsante();
    
    /**
     Costruttore avanzato.
     Imposta i valori per la corretta visualizzazione del pulsante
     
     @param position coordinate di posizionamento
     @param tx_nr numero della texture
     @param scale fattore di scala
     @param name_a stringa del nome associato all'oggetto
     @param s puntatore alla classe risorse di gioco
     */
    Pulsante(Vector2f position, int tx_nr, float scale, char name_a[], Resources *s);
    
    /**
     Ritorna il nome del pulsante
     
     @return stringa contenente il nome salvato in name
     */
    char* getName();
    
    /**
     Verifica la selezione del pulsante
     
     @return true se il cursore è posizionato sopra di esso, false altrimenti
     */
    bool isSelected();
    
    /**
     Mostra il pulsante a schermo.
     Se selezionato viene mostrato ingrandito, di dimensioni normali altrimenti
     */
    void draw();
    
    /**
     Mostra il pulsante e ne verifica la selezione
     
     @return true se selazionato, false altrimenti
     */
    bool handle();
};
