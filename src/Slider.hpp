#pragma once
#include "Resources.hpp"

class Slider{
    
    Resources *src;
    Sprite slider, axis;
    float min_value;
    float max_value;
    int x_coord;
    int y_coord;
    int axis_width;
    int axis_height;
    int slider_width;
    int slider_height;
    float slider_value;
    char name[20];
    bool mouse_was_clicked;
    
public:
    
    Slider();
    Slider(Vector2f position, float min, float max, char name[], Resources *src);
    
    void setSliderPercentValue(float newPercentValue);
    float getSliderValue();
    char* getName();
    
    bool logic();
    void draw();

};
