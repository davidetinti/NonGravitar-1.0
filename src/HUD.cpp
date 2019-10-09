#include "HUD.hpp"

HUD::HUD(){
}

HUD::HUD(Resources *src){
    this->src = src;
    /*
    font.loadFromFile("/Users/davidetinti/Desktop/NonGravitar-1.0/resources/0.ttf");
    life.setFont(font);
    life.setString("LIFE");
    life.setFillColor(Color::Red);
    life.setOutlineColor(Color::White);
    life.setCharacterSize(30);
    life.setOutlineThickness(1);
    life.setPosition(100,100);
    fuel.setFont(font);
    fuel.setString("FUEL");
    fuel.setFillColor(Color::Blue);
    fuel.setOutlineColor(Color::White);
    fuel.setCharacterSize(18);
    fuel.setOutlineThickness(1);
    fuel.setPosition(this->src->getLength()/2+205, 16);
    score.setFont(this->src->getFont(0));
    score.setString("SCORE: 0");
    score.setFillColor(Color::Black);
    score.setOutlineColor(Color::White);
    score.setCharacterSize(18);
    score.setOutlineThickness(1);
    score.setPosition(this->src->getLength()/2-35, 40);
     */
    bars_tx = this->src->caricaTexture(16);
    lifebar_active.setTexture(*bars_tx);
    lifebar_active.setTextureRect(IntRect(0, 31, 400, 32));
    lifebar_active.setOrigin(400,0);
    lifebar_active.setPosition(this->src->getLength()/2-200, 20);
    lifebar_active.setScale(-0.5, 0.5);
    lifebar_back.setTexture(*bars_tx);
    lifebar_back.setTextureRect(IntRect(0, 0, 400, 32));
    lifebar_back.setOrigin(400,0);
    lifebar_back.setPosition(this->src->getLength()/2, 20);
    lifebar_back.setScale(0.5, 0.5);
    fuelbar_active.setTexture(*bars_tx);
    fuelbar_active.setTextureRect(IntRect(0, 62, 400, 32));
    fuelbar_active.setOrigin(0,0);
    fuelbar_active.setPosition(this->src->getLength()/2, 20);
    fuelbar_active.setScale(0.5, 0.5);
    fuelbar_back.setTexture(*bars_tx);
    fuelbar_back.setTextureRect(IntRect(0, 0, 400, 32));
    fuelbar_back.setOrigin(0,0);
    fuelbar_back.setPosition(this->src->getLength()/2, 20);
    fuelbar_back.setScale(0.5, 0.5);
}

void HUD::gestisci(int point_f, float life_f, float fuel_f){
    if (life_f>0 && life_f<=100) lifebar_active.setTextureRect(IntRect(0, 31, 400*life_f/100, 32));
    if (fuel_f>0 && fuel_f<=100) fuelbar_active.setTextureRect(IntRect(0, 62, 400*fuel_f/100, 32));
    if (life_f<=0) lifebar_active.setTextureRect(IntRect(0, 31, 0, 32));
    if (fuel_f<=0) fuelbar_active.setTextureRect(IntRect(0, 62, 0, 32));
    src->getWindow()->draw(lifebar_back);
    src->getWindow()->draw(lifebar_active);
    src->getWindow()->draw(fuelbar_back);
    src->getWindow()->draw(fuelbar_active);
}
