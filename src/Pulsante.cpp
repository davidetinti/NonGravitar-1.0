#include "Pulsante.hpp"

Pulsante::Pulsante(){
    
}

Pulsante::Pulsante(Vector2f posizione, int tx_nr, float scala, char nome[], Resources *src){
    this->src = src;
    original_scale = Vector2f(scala,scala);
    button_tx = src->caricaTexture(tx_nr);
    button.setTexture(*button_tx);
    button.setTextureRect(IntRect(0,0,button_tx->getSize().x,button_tx->getSize().y));
    button.setOrigin(button_tx->getSize().x/2,button_tx->getSize().y/2);
    button.setPosition(posizione);
    button.setScale(original_scale);
    strncpy(name, nome, 20);
}

char* Pulsante::getName(){
    return name;
}

bool Pulsante::isSelected(){
    if (button.getGlobalBounds().contains(Mouse::getPosition(*src->getWindow()).x, Mouse::getPosition(*src->getWindow()).y)){
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

bool Pulsante::handle(){
    disegna();
    if (isSelected()){
        return true;
    } else {
        return false;
    }
}
