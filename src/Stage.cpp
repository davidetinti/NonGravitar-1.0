#include "Stage.hpp"

Stage::Stage(){
    
}

Stage::Stage(Resources *src, int tx_sfondo){
    this->src = src;
    Texture* sfondo_tx = src->caricaTexture(tx_sfondo);
    background.setTexture(*sfondo_tx);
    background.setTextureRect(IntRect(0,0,sfondo_tx->getSize().x,sfondo_tx->getSize().y));
    sliderSelected = false;
}

Sprite* Stage::getBackground(){
    return &background;
}

list<Slider*> *Stage::getSliderList(){
    return &sliderList;
}

list<Pulsante*> *Stage::getButtonsList(){
    return &buttonList;
}

list<Text*> *Stage::getTextList(){
    return &textList;
}

void Stage::addSlider(Vector2f position, float min ,float max, char name[]){
    Slider* tmp = new Slider(position, min, max, name, src);
    sliderList.push_back(tmp);
}

void Stage::addButton(Vector2f position, int tx_nr, float scala, char name[]){
    Pulsante* tmp = new Pulsante(position, tx_nr, scala, name, src);
    buttonList.push_back(tmp);
}

Text* Stage::addText(Vector2f position, String text, Color fillColor, Color outlineColor, int size, float border){
    Text* tmp = new Text(text, *src->getFont(1));
    tmp->setPosition(position);
    tmp->setFillColor(fillColor);
    tmp->setOutlineColor(outlineColor);
    tmp->setCharacterSize(size);
    tmp->setOutlineThickness(border);
    textList.push_back(tmp);
    return tmp;
}

void Stage::drawBackground(){
    src->getWindow()->draw(background);
}

void Stage::drawObjects(){
    for (Pulsante* button : buttonList){
        button->disegna();
    }
    for (Slider* slider : sliderList){
        slider->draw();
    }
    for (Text* text : textList){
        src->getWindow()->draw(*text);
    }
}
