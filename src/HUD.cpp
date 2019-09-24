#include "pch.h"
#include "HUD.hpp"

using namespace std;
using namespace sf;

HUD::HUD(){
    
}

HUD::HUD(int lenght, int heigth, Risorse *src, Font *font){
    life.setFont(*font);
    life.setString("LIFE");
    life.setFillColor(Color::Red);
    life.setOutlineColor(Color::White);
    life.setCharacterSize(18);
    life.setOutlineThickness(1);
    life.setPosition(lenght/2-245, 16);
    fuel.setFont(*font);
    fuel.setString("FUEL");
    fuel.setFillColor(Color::Blue);
    fuel.setOutlineColor(Color::White);
    fuel.setCharacterSize(18);
    fuel.setOutlineThickness(1);
    fuel.setPosition(lenght/2+205, 16);
    score.setFont(*font);
    score.setString("SCORE: 0");
    score.setFillColor(Color::Black);
    score.setOutlineColor(Color::White);
    score.setCharacterSize(18);
    score.setOutlineThickness(1);
    score.setPosition(lenght/2-35, 40);
    bars_tx = src->caricaTexture(16);
    lifebar_active.setTexture(*bars_tx);
    lifebar_active.setTextureRect(IntRect(0, 31, 400, 32));
    lifebar_active.setOrigin(400,0);
    lifebar_active.setPosition(lenght/2-200, 20);
    lifebar_active.setScale(-0.5, 0.5);
    lifebar_back.setTexture(*bars_tx);
    lifebar_back.setTextureRect(IntRect(0, 0, 400, 32));
    lifebar_back.setOrigin(400,0);
    lifebar_back.setPosition(lenght/2, 20);
    lifebar_back.setScale(0.5, 0.5);
    fuelbar_active.setTexture(*bars_tx);
    fuelbar_active.setTextureRect(IntRect(0, 62, 400, 32));
    fuelbar_active.setOrigin(0,0);
    fuelbar_active.setPosition(lenght/2, 20);
    fuelbar_active.setScale(0.5, 0.5);
    fuelbar_back.setTexture(*bars_tx);
    fuelbar_back.setTextureRect(IntRect(0, 0, 400, 32));
    fuelbar_back.setOrigin(0,0);
    fuelbar_back.setPosition(lenght/2, 20);
    fuelbar_back.setScale(0.5, 0.5);
    //pausa = Pulsante(Vector2f(1200,30), src, 21, 0.35);
}

void HUD::gestisci(RenderWindow *window, int point, float life, float fuel){
    if (life>0 && life<=100) lifebar_active.setTextureRect(IntRect(0, 31, 400*life/100, 32));
    if (fuel>0 && fuel<=100) fuelbar_active.setTextureRect(IntRect(0, 62, 400*fuel/100, 32));
    if (life<=0) lifebar_active.setTextureRect(IntRect(0, 31, 0, 32));
    if (fuel<=0) fuelbar_active.setTextureRect(IntRect(0, 62, 0, 32));
    window->draw(lifebar_back);
    window->draw(lifebar_active);
    window->draw(fuelbar_back);
    window->draw(fuelbar_active);
    window->draw(this->life);
    window->draw(this->fuel);
    score.setString("SCORE: " + to_string(point));
    window->draw(score);
    //pausa.gestisci(window);
}
