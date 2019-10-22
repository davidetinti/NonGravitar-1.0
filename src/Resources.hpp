#ifndef Resources_hpp
#define Resources_hpp

#include <chrono>
#include <random>
#include "Animation.hpp"
#include "SourceLoader.hpp"

class Resources {
    
protected:
    
    SourceLoader *sourceLoader;
    list<Animation*> animationList;
    
public:
    
    Resources();
    int getHeight();
    int getLength();
    int getPrimaryDamage();
    int getSecondaryDamage();
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
    int rand(int max, int min);
    bool intersecate(FloatRect object1, FloatRect object2);
    
};

#endif /* Risorse_hpp */
