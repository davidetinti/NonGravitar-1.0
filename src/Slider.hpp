#ifndef Controller_hpp
#define Controller_hpp

#include "Resources.hpp"

class Slider{
    
    Resources *src;
    RectangleShape slider;
    RectangleShape axis;
    float minValue;
    float maxValue;
    int xCord;
    int yCord;
    int axisWidth;
    int axisHeight;
    int sliderWidth;
    int sliderHeight;
    float sliderValue;
    
public:
    
    Slider();
    Slider(int x, int y, float min, float max, Resources *src);
    void create(float min, float max);
    void logic();
    float getSliderValue();
    void setSliderValue(float newValue);
    void setSliderPercentValue(float newPercentValue);
    void draw();
    void handle();
    bool mouseWasClicked;
    
};

struct sliderList{
    char name[10];
    Slider current;
    sliderList *next;
};

#endif /* Controller_hpp */
