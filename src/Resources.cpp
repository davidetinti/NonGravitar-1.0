#include "Resources.hpp"


Resources::Resources(){
    sourceLoader = new SourceLoader();
    animationList = list<Animation*>();
    last_input = NULL;
    difficulty = 1;
}


int Resources::getHeight(){
    return sourceLoader->getHeight();
}


int Resources::getLength(){
    return sourceLoader->getLength();
}


int Resources::getLastInput(){
    return last_input;
}


void Resources::setLastInput(int value){
    last_input = value;
}


float Resources::getDifficulty(){
    return difficulty;
}


void Resources::setDifficulty(float value){
    difficulty = value;
}


Time* Resources::getTimePerFrame(){
    return sourceLoader->getTimePerFrame();
}


RenderWindow* Resources::getWindow(){
    return sourceLoader->getWindow();
}


SoundBuffer* Resources::getSound(int n){
    return sourceLoader->getSound(n);
}


Texture* Resources::getTexture(int n){
    return sourceLoader->getTexture(n);
}


Font* Resources::getFont(int n){
    return sourceLoader->getFont(n);
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
        if (item->isEnded()){
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


int Resources::rand(int min, int max){
    static default_random_engine dre(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> uid (min,max);
    return uid(dre);
}
