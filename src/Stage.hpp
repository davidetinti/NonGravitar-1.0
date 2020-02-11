#pragma once
#include "Pulsante.hpp"
#include "Slider.hpp"

class Stage{
    
protected:
    
    Resources *src;
    Sprite background;
    list<Pulsante*> buttonList;
    list<Slider*> sliderList;
    list<Text*> textList;
    bool sliderSelected;
    
public:
    
    /**
     Costruttore base
    */
    Stage();
    
    /**
     Costruttore avanzato
    
     @param src puntatore all'utility class Resources
     @param tx_sfondo texture dello sfondo
    */
    Stage(Resources *src, int tx_sfondo);
    
    /**
     Ritorna lo sfondo dello stage
    */
    Sprite* getBackground();
    
    /**
     Ritorna la lista dei bottoni
    */
    list<Pulsante*> *getButtonsList();
    
    /**
     Ritorna la lista degli slider
    */
    list<Slider*> *getSliderList();
    
    /**
     Ritorna la lista di testi
    */
    list<Text*> *getTextList();
    
    /**
     Aggiunge un bottone allo stage corrente
        
     @param position  posizione del bottone
     @param tx_nr  numero della texture
     @param scale  grandezza del bottone
     @param name nome del bottone
    */
    void addButton(Vector2f position, int tx_nr, float scale, char name[]);
    
    /**
     Aggiunge uno slider allo stage corrente
        
     @param position  posizione dello slider
     @param min valore minimo dello slider
     @param max valore massimo dello slider
     @param name nome dello slider
    */
    void addSlider(Vector2f position, float min, float max, char name[]);
    
    /**
     Aggiunge un testo allo stage corrente
        
     @param position  posizione dello slider
     @param text testo da visualizzare
     @param fillColor colore del testo
     @param outlineColor colore del bordo del testo
     @param size grandezza del testo
     @param border spessore del testo
    */
    Text* addText(Vector2f position, String text, Color fillColor, Color outlineColor, int size, float border);
    
    /**
     Disegna lo sfondo dello stage corrente
    */
    void drawBackground();
    
    /**
     Disegna tutti i pulsanti, testi e slider
    */
    void drawObjects();
};

