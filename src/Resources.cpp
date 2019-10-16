#include "Resources.hpp"

Resources::Resources(){
    sourceLoader = new SourceLoader();
    animatonList = new AnimationList;
    animatonList->current = NULL;
    animatonList->prev = animatonList;
    animatonList->next = animatonList;
}

int Resources::getHeight(){
    return sourceLoader->getHeight();
}

int Resources::getLength(){
    return sourceLoader->getLength();
}

int Resources::getPrimaryDamage(){
    return sourceLoader->getPrimaryDamage();
}

int Resources::getSecondaryDamage(){
    return sourceLoader->getSecondaryDamage();
}

Time *Resources::getTimePerFrame(){
    return sourceLoader->getTimePerFrame();
}

Time *Resources::getUtilityTime(){
    return sourceLoader->getUtilityTime();
}

Clock *Resources::getUtilityClock(){
    return sourceLoader->getUtilityClock();
}

RenderWindow *Resources::getWindow(){
    return sourceLoader->getWindow();
}

SoundBuffer *Resources::caricaSuono(int n){
    return sourceLoader->getSound(n);
}

Texture *Resources::caricaTexture(int n){
    return sourceLoader->getTexture(n);
}

Font *Resources::getFont(int n){
    return sourceLoader->getFont(n);
}

AnimationList *Resources::getAnimationList(){
    return animatonList;
}

void Resources::addAnimation(int x, int y, int tx_nr, int rows, int columns, float scale){
    AnimationList *tmp = new AnimationList;
    tmp->current = new Animation(x, y, tx_nr, rows, columns, scale, sourceLoader);
    tmp->next = animatonList;
    tmp->prev = animatonList->prev;
    animatonList->prev->next = tmp;
    animatonList->prev = tmp;
}

void Resources::handleAnimation(){
    AnimationList *tmp = animatonList->next;
    while (tmp != animatonList){
        if (tmp->current->handle()){
            tmp = tmp->next;
        } else {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            AnimationList *tmp1 = tmp;
            tmp = tmp->next;
            delete tmp1;
        }
    }
}

int Resources::rand(int min, int max){
    static default_random_engine dre(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> uid (min,max);
    return uid(dre);
}

bool Resources::intersecate(FloatRect object1, FloatRect object2){
    if (object1.intersects(object2)){
        return true;
    } else {
        return false;
    }
}
