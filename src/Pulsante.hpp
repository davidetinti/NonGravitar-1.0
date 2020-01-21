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
    
    Pulsante();
    Pulsante(Vector2f position, int tx_nr, float scala, char nome[], Resources *s);
    
    char* getName();
    bool isSelected();
    
    void draw();
    bool handle();
};
