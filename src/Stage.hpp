#ifndef Stage_hpp
#define Stage_hpp

#include "Pulsante.hpp"
#include "Slider.hpp"

class Stage{
    
protected:
    
    Resources *src;
    lista_pulsanti *icone;
    sliderList *slider;
    bool attiva;
    
public:
    
    Sprite sfondo;
    Texture *sfondo_tx;
    
    Stage();
    Stage(Resources *src, int tx_sfondo);
    void addButton(Vector2f posizione, int tx_nr, float scala, char name[10]);
    void addSlider(int x, int y, float min, float max, char name[10]);
    void draw();
    bool getActive();
    void setActive(bool attiva);
    lista_pulsanti *getButtons();
    sliderList *getSliders();
};

#endif /* Stage_hpp */
