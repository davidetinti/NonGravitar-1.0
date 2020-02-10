#pragma once
#include "Resources.hpp"

class Slider{
    
    Resources *src;
    Sprite slider, axis;
    float min_value;
    float max_value;
    int x_coord;
    int y_coord;
    int axis_width;
    int axis_height;
    int slider_width;
    int slider_height;
    float slider_value;
    char name[20];
    bool mouse_was_clicked;
    
public:
    
    /**
     Costruttore base.
     */
    Slider();
    
    /**
     Costruttore avanzato.
     Imposta i valori per la corretta visualizzazione dello slider.
     
     @param position coordinate di posizionamento
     @param min valore minimo che può assumere
     @param max valore massino che può assumere
     @param name stringa del nome associato all'oggetto
     @param src puntatore alla classe risorse di gioco
     */
    Slider(Vector2f position, float min, float max, char name[], Resources *src);
    
    /**
     Modifica il valore percentuale dello slider.
     
     @param newPercentValue nuovo valore percentuale
     */
    void setSliderPercentValue(float newPercentValue);
    
    /**
     Ritorna il valore rappresentato dallo slider
     
     @return valore attuale dello slider
     */
    float getSliderValue();
    
    /**
     Ritorna il nome dello slider
     
     @return stringa contenente il nome salvato in name
     */
    char* getName();
    
    /**
     Verifica se è presenta un'interazione con lo slider.
     In caso positivo ne modifica il valore seguendo il moviento del cursore.
     
     @return true se il cursore è cliccato in corrispondenza dello slider o se era già stato cliccato in precedenza, false se il cursore viene rilasciato o non stave interagendo precedentemente con lo slider
     */
    bool logic();
    
    /**
     Mostra lo slider
     */
    void draw();

};
