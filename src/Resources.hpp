#ifndef Resources_hpp
#define Resources_hpp

#include "Animation.hpp"
#include "SourceLoader.hpp"

class Resources {
    
protected:
    
    SourceLoader *sourceLoader;
    AnimationList *animatonList;
    
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
    AnimationList *getAnimationList();
    void addAnimation(int x, int y, int tx_nr, int rows, int columns, float scale);
    void handleAnimation();
    
};

#endif /* Risorse_hpp */
