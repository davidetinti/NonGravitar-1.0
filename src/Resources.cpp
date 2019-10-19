#include "Resources.hpp"

Resources::Resources(){
    sourceLoader = new SourceLoader();
    animationList = new list<Animation*>;
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

Time* Resources::getTimePerFrame(){
    return sourceLoader->getTimePerFrame();
}

Time* Resources::getUtilityTime(){
    return sourceLoader->getUtilityTime();
}

Clock* Resources::getUtilityClock(){
    return sourceLoader->getUtilityClock();
}

RenderWindow* Resources::getWindow(){
    return sourceLoader->getWindow();
}

SoundBuffer* Resources::caricaSuono(int n){
    return sourceLoader->getSound(n);
}

Texture* Resources::caricaTexture(int n){
    return sourceLoader->getTexture(n);
}

Font* Resources::getFont(int n){
    return sourceLoader->getFont(n);
}

list<Animation*>* Resources::getAnimationList(){
    return animationList;
}

void Resources::addAnimation(int x, int y, int tx_nr, int rows, int columns, float scale, double speed){
    Animation* tmp = new Animation(x, y, tx_nr, rows, columns, scale, sourceLoader, speed);
    animationList->push_back(tmp);
}

void Resources::handleAnimation(){
    for (Animation* animation : *animationList){
        if (!animation->handle()){
            animationList->clear();
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
