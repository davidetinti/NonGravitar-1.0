#pragma once
#include <chrono>
#include <random>
#include "Animation.hpp"

class Resources {
    
protected:
    
    SourceLoader *sourceLoader;
    list<Animation*> animationList;
    Event event;
    int last_input;
    
public:
    
    Resources();
    int getHeight();
    int getLength();
    int getPrimaryDamage();
    int getSecondaryDamage();
    int getLastInput();
    void setLastInput(int value);
    Event *getEvent();
    Time *getTimePerFrame();
    Time *getUtilityTime();
    Clock *getUtilityClock();
    RenderWindow *getWindow();
    SoundBuffer *caricaSuono(int n);
    Texture *caricaTexture(int n);
    Font *getFont(int n);
    list<Animation*>* getAnimationList();
    Animation* addAnimation(int x, int y, int tx_nr, int rows, int columns, float scale, double speed = 1);
    void handleAnimation();
    void handleEvents();
    int rand(int min, int max);
    bool intersecate(FloatRect object1, FloatRect object2);
    
};
