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
    int getLastInput();
    void setLastInput(int value);
    Time *getTimePerFrame();
    RenderWindow *getWindow();
    SoundBuffer *getSound(int n);
    Texture *getTexture(int n);
    Font *getFont(int n);
    
    Animation* addAnimation(int x, int y, int tx_nr, int rows, int columns, float scale, double speed = 1);
    void handleAnimation();
    void handleEvents();
    int rand(int min, int max);
};
