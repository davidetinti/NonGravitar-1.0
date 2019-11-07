#include "Fuel.hpp"

// COSTRUTTORI =======================================

fuel::fuel(double x_n, double y_n, int power_n,fuel *next_n, bool exist_n) :
x(x_n),y(y_n),power(power_n),exist(exist_n){
    
}

Fuel::Fuel(){
    head=nullptr;
}

Fuel::Fuel(Terreno *terrain, Resources *src) {
    this->src = src;
    double x;
    bool exist;
    int power;
    fuel_tx = src->caricaTexture(18);
    partial_x[0] = 20;
    partial_x[1] = 620;
    partial_x[2] = 1140;
    x = partial_x[0] + rand() % 140;
    exist=((rand() % 100)>50);
    
    
    if(rand() % 3 >1){
        power = 25;
    }
    else {
        power=10;
    }
    
    head = new fuel (x,terrain->get_Y(x),power,nullptr,exist);
    current = head;
    head->next = nullptr;
    spriteSetup(current,power);
    
    if(!exist){
        delete_fuel(current);
        current=head;
    }
    
    for (int i = 1; i < 3; i++){
        
        if(rand() % 3 > 1){
            power = 25;
        }else {
            power = 10;
        }
        
        exist = ((rand() % 100) > 50);
        x = partial_x[i] + rand() % 140;
        
        if(current==nullptr){
            current = new fuel(x,terrain->get_Y(x),power,nullptr,exist);
            head=current;
            spriteSetup(current,power);
        }else{
            current->next = new fuel(x,terrain->get_Y(x),power,nullptr,exist);
            current = current->next;
            spriteSetup(current,power);
        }
        current->next = nullptr;
        if(!exist){
            delete_fuel(current);
            current = head;
        }
    }
    current = head;
}
///  SETTERS E GETTERS  /////////////////////////////////////////////

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

int Fuel::getPower(fuel *current){
    return(this->current->power);
    
}

///  FUNZIONI  //////////////////////////////////////////////////////

/*
 delete the fuel during the initializing and when the ship catches the fuel
 
 @param A pointer at the fuel that mast be deleted
 */
void Fuel::delete_fuel(fuel *selected){
    fuel *tmp=head;
    if(selected==head){
        head = head->next;
        delete selected;
    }else{
        while(tmp!=nullptr){
            if(tmp->next==selected){
                tmp->next=tmp->next->next;
                delete selected;
                current=head;
            }
            tmp=tmp->next;
        }
        
    }
}


void Fuel::gestisci(){
    current = head;
    while (current != nullptr){
        src->getWindow()->draw(current->fuel_sprite);
        current = current->next;
    }
    current = head;
}

/*
 Set the texture at the sprite
 
 @param the list of fuel and the power to change the color
 */
void Fuel::spriteSetup(fuel *tmp, int power){
    tmp->fuel_sprite.setTexture(*fuel_tx);
    tmp->fuel_sprite.setOrigin(fuel_tx->getSize().x/2, fuel_tx->getSize().y-10);
    tmp->fuel_sprite.setPosition(tmp->x, tmp->y);
    tmp->fuel_sprite.setTextureRect(IntRect(0,0,fuel_tx->getSize().x,fuel_tx->getSize().y));
    tmp->fuel_sprite.setScale(0.5, 0.5);
    if(power==25){
        tmp->fuel_sprite.setColor(sf::Color::Green);
    }
}

