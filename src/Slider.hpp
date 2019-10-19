#ifndef Controller_hpp
#define Controller_hpp

#include "Resources.hpp"

class Slider{
    
    Resources *src;
    Sprite slider, axis;
    float minValue;
    float maxValue;
    int xCord;
    int yCord;
    int axisWidth;
    int axisHeight;
    int sliderWidth;
    int sliderHeight;
    float sliderValue;
    char name[20];
    
public:
    
    Slider();
    Slider(Vector2f position, float min, float max, char name[], Resources *src);
    void create(float min, float max);
    void logic();
    float getSliderValue();
    void setSliderValue(float newValue);
    void setSliderPercentValue(float newPercentValue);
    char *getName();
    void draw();
    void handle();
    bool mouseWasClicked;
    bool isHandled;
    
};

#endif /* Controller_hpp */
