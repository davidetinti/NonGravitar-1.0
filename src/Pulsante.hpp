#ifndef Pulsante_hpp
#define Pulsante_hpp

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Risorse.hpp"

using namespace std;
using namespace sf;

class Pulsante{
    
protected:
    
    Sprite button;
    ptr_Texture button_tx;
    Vector2f original_scale;
    
public:
    
    Pulsante();
    Pulsante(Vector2f posizione, Risorse *src, int tx_nr, float scala);
    
    bool isSelected(RenderWindow *window);
    void disegna(RenderWindow *window);
    bool gestisci(RenderWindow *window);
};

struct lista_pulsanti{
    char name[10];
    Pulsante current;
    lista_pulsanti *next;
};

typedef lista_pulsanti* ptr_lista_pulsanti;

class Finestra{
    
protected:
    
    ptr_lista_pulsanti icone;
    bool attiva;
    
public:
    
    Sprite sfondo;
    ptr_Texture sfondo_tx;
    
    Finestra();
    Finestra(Risorse *src, int tx_sfondo);
    void addButton(Vector2f posizione, Risorse *src, int tx_nr, float scala, char name[10]);
    void disegna(RenderWindow *window);
    bool getAttiva();
    void setAttiva(bool attiva);
    ptr_lista_pulsanti getIcone();
};

#endif /* Pulsante_hpp */
