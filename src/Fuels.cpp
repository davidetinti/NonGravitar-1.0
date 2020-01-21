#include "Fuels.hpp"

/// COSTRUTTORI

fuel::fuel(double x_n, double y_n, int power_n):
    x(x_n),
    y(y_n),
    power(power_n){
}

Fuels::Fuels(){
    src = nullptr;
    fuel_tx = nullptr;
    fuel_list = nullptr;
    for (int i : partial_x){
        i = 0;
    }
    
}

Fuels::Fuels(Terreno *terrain, Resources *src) {
    double x;
    int power;
    this->src = src;
    fuel_tx = src->caricaTexture(18);
    partial_x[0] = 20;
    partial_x[1] = 620;
    partial_x[2] = 1140;
    fuel_list = new list<fuel>;
    for (int i = 0; i < 3; i++){
        
        if ((rand() % 100) > 50) {
            
            if(rand() % 3 > 1) power = 25;
            else power = 10;
            
            x = partial_x[i] + rand() % 140;
            
            fuel it = fuel(x,terrain->get_Y(x),power);
            spriteSetup(&it, power);
            fuel_list->push_back(it);
        }
    }
}

/// SETTERS & GETTERS

list<fuel>::iterator Fuels::getFuelListBegin(){
    return fuel_list->begin();
}

list<fuel>::iterator Fuels::getFuelListEnd(){
    return fuel_list->end();
}

/// FUNZIONI

list<fuel>::iterator Fuels::delete_fuel(list<fuel>::iterator it){
    return fuel_list->erase(it);
}

int Fuels::getPower(list<fuel>::iterator it){
    return it->power;
}

void Fuels::gestisci(){
    list<fuel>::iterator it = fuel_list->begin();
    list<fuel>::iterator end = fuel_list->end();
    while (it != end){
        src->getWindow()->draw(it->fuel_sprite);
        it++;
    }
}

void Fuels::spriteSetup(fuel *tmp, int power){
    tmp->fuel_sprite.setTexture(*fuel_tx);
    tmp->fuel_sprite.setOrigin(fuel_tx->getSize().x/2, fuel_tx->getSize().y - 10);
    tmp->fuel_sprite.setPosition(tmp->x, tmp->y);
    tmp->fuel_sprite.setTextureRect(IntRect(0, 0, fuel_tx->getSize().x, fuel_tx->getSize().y));
    tmp->fuel_sprite.setScale(0.5, 0.5);
    
    if(power == 25){
        tmp->fuel_sprite.setColor(sf::Color::Green);
    }
}

