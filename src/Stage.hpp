#ifndef Stage_hpp
#define Stage_hpp

#include "Pulsante.hpp"
#include "Slider.hpp"

class Stage{
    
protected:
    
    Resources *src;
    Sprite background;
    list<Pulsante*> buttonList;
    list<Slider*> sliderList;
    list<Text*> textList;
    bool attiva;
    bool sliderSelected;
    
public:
    
    //CONSTRUCTORS
    Stage();
    Stage(Resources *src, int tx_sfondo);
    
    //GETTERS AND SETTERS
    Sprite* getBackground();
    list<Pulsante*> *getButtonsList();
    list<Slider*> *getSliderList();
    list<Text*> *getTextList();
    bool getActive();
    void setActive(bool attiva);
    
    //FUNCTIONS
    void addButton(Vector2f position, int tx_nr, float scale, char name[]);
    void addSlider(Vector2f position, float min, float max, char name[]);
    void addText(Vector2f position, char* text, Color fillColor, Color outlineColor, int size, float border);
    void draw();
};

#endif /* Stage_hpp */
