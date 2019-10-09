#include "Stage.hpp"

Stage::Stage(){
    
}

Stage::Stage(Resources *src, int tx_sfondo){
    this->src = src;
    sfondo_tx = src->caricaTexture(tx_sfondo);
    sfondo.setTexture(*sfondo_tx);
    sfondo.setTextureRect(IntRect(0,0,sfondo_tx->getSize().x,sfondo_tx->getSize().y));
    icone = NULL;
    slider = NULL;
    attiva = false;
}

void Stage::addSlider(int x, int y, float min ,float max, char name[10]){
    sliderList *tmp = new sliderList;
    tmp->current = Slider(x,y,min,max,src);
    tmp->current.setSliderPercentValue(50);
    strcpy(tmp->name, name);
    tmp->next = slider;
    slider = tmp;
}

void Stage::addButton(Vector2f posizione, int tx_nr, float scala, char name[10]){
    lista_pulsanti *tmp = new lista_pulsanti;
    tmp->current = Pulsante(posizione, src, tx_nr, scala);
    strcpy(tmp->name, name);
    tmp->next = icone;
    icone = tmp;
}

void Stage::draw(){
    src->getWindow()->draw(sfondo);
    lista_pulsanti *tmp1 = icone;
    while (tmp1 != NULL){
        tmp1->current.handle();
        tmp1 = tmp1->next;
    }
    sliderList *tmp2 = slider;
    while (tmp2 != NULL){
        tmp2->current.handle();
        tmp2 = tmp2->next;
    }
}

bool Stage::getActive(){
    return this->attiva;
}

void Stage::setActive(bool attiva){
    this->attiva = attiva;
}

lista_pulsanti *Stage::getButtons(){
    return this->icone;
}

sliderList *Stage::getSliders(){
    return this->slider;
}
