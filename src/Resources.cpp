#include "Resources.hpp"

Resources::Resources(){
    sourceLoader = new SourceLoader();
    animationList = list<Animation*>();
    last_input = NULL;
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

int Resources::getLastInput(){
    return last_input;
}

void Resources::setLastInput(int value){
    last_input = value;
}

Event* Resources::getEvent(){
    return &event;
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
    return &animationList;
}

Animation* Resources::addAnimation(int x, int y, int tx_nr, int rows, int columns, float scale, double speed){
    Animation* tmp = new Animation(x, y, tx_nr, rows, columns, scale, sourceLoader, speed);
    animationList.push_front(tmp);
    return tmp;
}

void Resources::handleAnimation(){
    list<Animation*>::iterator it = animationList.begin();
    list<Animation*>::iterator end = animationList.end();
    while (it != end){
        Animation *item = *it;
        if (item->isTerminated()){
            delete item;
            it = animationList.erase(it);
        } else {
            item->handle();
            it++;
        }
    }
}

void Resources::handleEvents(){
    while (getWindow()->pollEvent(event)) {
        switch (event.type) {
            case Event::TextEntered:
                last_input = event.text.unicode;
                break;
            case Event::Closed:
                getWindow()->close();
            default:
                break;
        }
    }
}
//DESCRIPTION NEEDED
int Resources::rand(int min, int max){
    //need to include checks on input
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
