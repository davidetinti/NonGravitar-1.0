#ifndef Pulsante_hpp
#define Pulsante_hpp

#include "Resources.hpp"

class Pulsante{
    
protected:
    
    Resources *src;
    Sprite button;
    Texture *button_tx;
    Vector2f original_scale;
    char name[20];
    
public:
    
    Pulsante();
    Pulsante(Vector2f posizione, int tx_nr, float scala, char nome[], Resources *src);
    
    char* getName();
    bool isSelected();
    void disegna();
    bool handle();
};

#endif /* Pulsante_hpp */
