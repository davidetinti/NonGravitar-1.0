#ifndef Pulsante_hpp
#define Pulsante_hpp

#include "Risorse.hpp"

using namespace std;
using namespace sf;

class Pulsante{
    
protected:
    
    Risorse *src;
    Sprite button;
    Texture *button_tx;
    Vector2f original_scale;
    
public:
    
    Pulsante();
    Pulsante(Vector2f posizione, Risorse *src, int tx_nr, float scala);
    
    bool isSelected();
    void disegna();
    bool gestisci();
};

struct lista_pulsanti{
    char name[10];
    Pulsante current;
    lista_pulsanti *next;
};

class Finestra{
    
protected:
    
    Risorse *src;
    lista_pulsanti *icone;
    bool attiva;
    
public:
    
    Sprite sfondo;
    Texture *sfondo_tx;
    
    Finestra();
    Finestra(Risorse *src, int tx_sfondo);
    void addButton(Vector2f posizione, int tx_nr, float scala, char name[10]);
    void disegna();
    bool getAttiva();
    void setAttiva(bool attiva);
    lista_pulsanti *getIcone();
};

#endif /* Pulsante_hpp */
