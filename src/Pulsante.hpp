#ifndef Pulsante_hpp
#define Pulsante_hpp

#include "Resources.hpp"

class Pulsante{
    
protected:
    
    Resources *src;
    Sprite button;
    Texture *button_tx;
    Vector2f original_scale;
    
public:
    
    Pulsante();
    Pulsante(Vector2f posizione, Resources *src, int tx_nr, float scala);
    
    bool isSelected();
    void disegna();
    bool handle();
};

struct lista_pulsanti{
    char name[10];
    Pulsante current;
    lista_pulsanti *next;
};

#endif /* Pulsante_hpp */
