#include "pch.h"
#include "Pulsante.hpp"

using namespace sf;
using namespace std;

Pulsante::Pulsante(){
    
}

Pulsante::Pulsante(Vector2f posizione, Risorse *src, int tx_nr, float scala){
    this->src = src;
    original_scale = Vector2f(scala,scala);
    button_tx = src->caricaTexture(tx_nr);
    button.setTexture(*button_tx);
    button.setTextureRect(IntRect(0,0,button_tx->getSize().x,button_tx->getSize().y));
    button.setOrigin(button_tx->getSize().x/2,button_tx->getSize().y/2);
    button.setPosition(posizione);
    button.setScale(original_scale);
}

bool Pulsante::isSelected(){
    if (Mouse::getPosition(*src->getWindow()).x >= button.getPosition().x - original_scale.x*button_tx->getSize().x/2 && Mouse::getPosition(*src->getWindow()).x <= button.getPosition().x + original_scale.x*button_tx->getSize().x/2 &&
        Mouse::getPosition(*src->getWindow()).y >= button.getPosition().y - original_scale.x*button_tx->getSize().y/2 && Mouse::getPosition(*src->getWindow()).y <= button.getPosition().y + original_scale.x*button_tx->getSize().y/2){
        return true;
    } else {
        return false;
    }
}

void Pulsante::disegna(){
    if (isSelected()){
        button.setScale(original_scale.x*1.2,original_scale.y*1.2);
        src->getWindow()->draw(button);
    } else {
        button.setScale(original_scale);
        src->getWindow()->draw(button);
    }
}

bool Pulsante::gestisci(){
    disegna();
    if (isSelected() && Mouse::isButtonPressed(Mouse::Left)){
        return true;
    } else {
        return false;
    }
}

Finestra::Finestra(){
    
}

Finestra::Finestra(Risorse *src, int tx_sfondo){
    this->src = src;
    sfondo_tx = src->caricaTexture(tx_sfondo);
    sfondo.setTexture(*sfondo_tx);
    sfondo.setTextureRect(IntRect(0,0,sfondo_tx->getSize().x,sfondo_tx->getSize().y));
    icone = NULL;
    attiva = false;
}

void Finestra::addButton(Vector2f posizione, int tx_nr, float scala, char name[10]){
    lista_pulsanti *tmp = new lista_pulsanti;
    tmp->current = Pulsante(posizione, src, tx_nr, scala);
    strcpy(tmp->name, name);
    tmp->next = icone;
    icone = tmp;
}

void Finestra::disegna(){
    src->getWindow()->draw(sfondo);
    lista_pulsanti *tmp = icone;
    while (tmp != NULL){
        tmp->current.gestisci();
        tmp = tmp->next;
    }
}

bool Finestra::getAttiva(){
    return this->attiva;
}

void Finestra::setAttiva(bool attiva){
    this->attiva = attiva;
}

lista_pulsanti *Finestra::getIcone(){
    return this->icone;
}
