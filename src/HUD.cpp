#include "HUD.hpp"

HUD::HUD(){
}

HUD::HUD(Resources *src){
    this->src = src;
    bars_tx = this->src->getTexture(16);
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
    life = Text("LIFE", *src->getFont(1));
    life.setFillColor(Color::Red);
    life.setOutlineColor(Color::White);
    life.setCharacterSize(20);
    life.setOutlineThickness(1);
    life.setPosition(this->src->getLength()/2 - 210 - life.getLocalBounds().width, 16);
    fuel = Text("FUEL", *src->getFont(1));
    fuel.setFillColor(Color::Blue);
    fuel.setOutlineColor(Color::White);
    fuel.setCharacterSize(20);
    fuel.setOutlineThickness(1);
    fuel.setPosition(this->src->getLength()/2 + 210, 16);
    score = Text("SCORE: 0", *src->getFont(1));
    score.setFillColor(Color::Black);
    score.setOutlineColor(Color::White);
    score.setCharacterSize(20);
    score.setOutlineThickness(1);
    score.setPosition((this->src->getLength() - score.getLocalBounds().width)/2, 40);
}

void HUD::gestisci(int point_f, float life_f, float fuel_f){
    if (life_f>0 && life_f<=100) lifebar_active.setTextureRect(IntRect(0, 31, 400*life_f/100, 32));
    if (fuel_f>0 && fuel_f<=100) fuelbar_active.setTextureRect(IntRect(0, 62, 400*fuel_f/100, 32));
    if (life_f<=0) lifebar_active.setTextureRect(IntRect(0, 31, 0, 32));
    if (fuel_f<=0) fuelbar_active.setTextureRect(IntRect(0, 62, 0, 32));
    score.setString("SCORE: " + to_string(point_f));
    src->getWindow()->draw(life);
    src->getWindow()->draw(fuel);
    src->getWindow()->draw(score);
    src->getWindow()->draw(lifebar_back);
    src->getWindow()->draw(lifebar_active);
    src->getWindow()->draw(fuelbar_back);
    src->getWindow()->draw(fuelbar_active);
}
