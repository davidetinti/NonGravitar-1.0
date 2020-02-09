#include "Pulsante.hpp"


Pulsante::Pulsante(){
    
}


Pulsante::Pulsante(Vector2f position, int tx_nr, float scale, char name_a[], Resources *s){
    src = s;
    original_scale = Vector2f(scale,scale);
    button_tx = src->getTexture(tx_nr);
    button.setTexture(*button_tx);
    button.setTextureRect(IntRect(0,0,button_tx->getSize().x,button_tx->getSize().y));
    button.setOrigin(button_tx->getSize().x/2,button_tx->getSize().y/2);
    button.setPosition(position);
    button.setScale(original_scale);
    strncpy(name, name_a, 20);
}


char* Pulsante::getName(){
    return name;
}


bool Pulsante::isSelected(){
    if (button.getGlobalBounds().contains(Mouse::getPosition(*src->getWindow()).x,
                                          Mouse::getPosition(*src->getWindow()).y)){
        return true;
    } else {
        return false;
    }
}


void Pulsante::draw(){
    if (isSelected()){
        button.setScale(original_scale.x * 1.2, original_scale.y * 1.2);
        src->getWindow()->draw(button);
    } else {
        button.setScale(original_scale);
        src->getWindow()->draw(button);
    }
}


bool Pulsante::handle(){
    draw();
    if (isSelected()){
        return true;
    } else {
        return false;
    }
}
