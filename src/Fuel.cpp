#include "Fuel.hpp"

// COSTRUTTORI =======================================

Fuel::Fuel(){
    
}

Fuel::Fuel(Terreno *terrain, Resources *src) {
    this->src = src;
    fuel_tx = src->caricaTexture(18);
    partial_x[0] = 20;
    partial_x[1] = 620;
    partial_x[2] = 1140;
    current = new fuel;
    current->exist = ((rand() % 100)>70);
    current->next = NULL;
    head = current;
    for (int i = 1; i<3; i++){
        current->next = new fuel;
        current->next->exist = ((rand() % 100)>70);
        current->next->next = NULL;
        current = current->next;
    }
    current = head;
    for (int i = 0; i<3; i++){
        if (current->exist){
            current->x = partial_x[i] + (rand() % 140);
            current->y = terrain->get_Y(current->x);
            current->power = 10;  ////////////////////////// DA CAMBIARE
            current->fuel_sprite.setTexture(*fuel_tx);
            current->fuel_sprite.setOrigin(fuel_tx->getSize().x/2, fuel_tx->getSize().y-10);
            current->fuel_sprite.setPosition(current->x, current->y);
            current->fuel_sprite.setTextureRect(IntRect(0,0,fuel_tx->getSize().x,fuel_tx->getSize().y));
            current->fuel_sprite.setScale(0.5, 0.5);
            current = current->next;
        } else {
            delete_fuel(current);
            current = current->next;
        }
    }
}

// SETTERS E GETTERS =================================

fuel *Fuel::getCurrent(){
    return this->current;
}

fuel *Fuel::getHead(){
    return this->head;
}

void Fuel::setCurrent(fuel *current){
    this->current = current;
}

void Fuel::setHead(fuel *head){
    this->head = head;
}

// FUNZIONI ==========================================

void Fuel::delete_fuel(fuel *selected){
    
}

void Fuel::gestisci(){
    current = head;
    while (current != NULL){
        src->getWindow()->draw(current->fuel_sprite);
        current = current->next;
    }
    current = head;
}


