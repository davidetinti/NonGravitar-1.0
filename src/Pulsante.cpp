#include"pch.h"
#include "Pulsante.hpp"

using namespace sf;
using namespace std;

Pulsante::Pulsante(){
    
}

Pulsante::Pulsante(Vector2f posizione, Risorse *src, int tx_nr, float scala){
    original_scale = Vector2f(scala,scala);
    button_tx = src->caricaTexture(tx_nr);
    button.setTexture(*button_tx);
    button.setTextureRect(IntRect(0,0,button_tx->getSize().x,button_tx->getSize().y));
    button.setOrigin(button_tx->getSize().x/2,button_tx->getSize().y/2);
    button.setPosition(posizione);
    button.setScale(original_scale);
}

bool Pulsante::isSelected(RenderWindow *window){
    if (Mouse::getPosition(*window).x >= button.getPosition().x - original_scale.x*button_tx->getSize().x/2 && Mouse::getPosition(*window).x <= button.getPosition().x + original_scale.x*button_tx->getSize().x/2 &&
        Mouse::getPosition(*window).y >= button.getPosition().y - original_scale.x*button_tx->getSize().y/2 && Mouse::getPosition(*window).y <= button.getPosition().y + original_scale.x*button_tx->getSize().y/2){
        return true;
    } else {
        return false;
    }
}

void Pulsante::disegna(RenderWindow *window){
    if (isSelected(window)){
        button.setScale(original_scale.x*1.2,original_scale.y*1.2);
        window->draw(button);
    } else {
        button.setScale(original_scale);
        window->draw(button);
    }
}

bool Pulsante::gestisci(RenderWindow *window){
    disegna(window);
    if (isSelected(window) && Mouse::isButtonPressed(Mouse::Left)){
        return true;
    } else {
        return false;
    }
}

Finestra::Finestra(){
    
}

Finestra::Finestra(Risorse *src, int tx_sfondo){
    sfondo_tx = src->caricaTexture(tx_sfondo);
    sfondo.setTexture(*sfondo_tx);
    sfondo.setTextureRect(IntRect(0,0,sfondo_tx->getSize().x,sfondo_tx->getSize().y));
    icone = NULL;
    attiva = false;
}

void Finestra::addButton(Vector2f posizione, Risorse *src, int tx_nr, float scala, char name[10]){
    ptr_lista_pulsanti tmp = new lista_pulsanti;
    tmp->current = Pulsante(posizione, src, tx_nr, scala);
    strcpy(tmp->name, name);
    tmp->next = icone;
    icone = tmp;
}

void Finestra::disegna(RenderWindow *window){
    window->draw(sfondo);
    ptr_lista_pulsanti tmp = icone;
    while (tmp != NULL){
        tmp->current.gestisci(window);
        tmp = tmp->next;
    }
}

bool Finestra::getAttiva(){
    return this->attiva;
}

void Finestra::setAttiva(bool attiva){
    this->attiva = attiva;
}

ptr_lista_pulsanti Finestra::getIcone(){
    return this->icone;
}
