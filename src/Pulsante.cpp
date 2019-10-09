#include "Pulsante.hpp"

Pulsante::Pulsante(){
    
}

Pulsante::Pulsante(Vector2f posizione, Resources *src, int tx_nr, float scala){
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

bool Pulsante::handle(){
    disegna();
    if (isSelected() && Mouse::isButtonPressed(Mouse::Left)){
        return true;
    } else {
        return false;
    }
}
