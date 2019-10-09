#include "Slider.hpp"

Slider::Slider(){
    
}

Slider::Slider(int x, int y, float min, float max, Resources *src){
    this->src = src;
    mouseWasClicked = false;
    xCord = x;
    yCord = y;
    axisHeight = 15;
    axisWidth = 600;
    sliderWidth = 25;
    sliderHeight = 50;
    axis.setPosition(x, y);
    axis.setOrigin(0, axisHeight / 2);
    axis.setSize(Vector2f(axisWidth, axisHeight));
    axis.setFillColor(Color::Red);
    slider.setPosition(x, y);
    slider.setOrigin(sliderWidth / 2, sliderHeight / 2);
    slider.setSize(Vector2f(sliderWidth, sliderHeight));
    slider.setFillColor(Color::Yellow);
    sliderValue = min;
    minValue = min;
    maxValue = max;
}

void Slider::create(float min, float max){
    sliderValue = min;
    minValue = min;
    maxValue = max;
}

void Slider::logic(){
    if ((slider.getGlobalBounds().contains(Mouse::getPosition(*src->getWindow()).x, Mouse::getPosition(*src->getWindow()).y) && Mouse::isButtonPressed(Mouse::Button::Left)) || mouseWasClicked){
        mouseWasClicked = true;
        if (Mouse::getPosition(*src->getWindow()).x >= xCord && Mouse::getPosition(*src->getWindow()).x <= xCord + axisWidth){
            slider.setPosition(Mouse::getPosition(*src->getWindow()).x, yCord);
            sliderValue = (minValue + ((slider.getPosition().x - xCord) / axisWidth * (maxValue - minValue)));
        }
        if (!Mouse::isButtonPressed(Mouse::Button::Left)){
            mouseWasClicked = false;
        }
    }
}

float Slider::getSliderValue(){
    return sliderValue;
}

void Slider::setSliderValue(float newValue){
    if (newValue >= minValue && newValue <= maxValue){
        sliderValue = newValue;
        float diff = maxValue - minValue;
        float diff2 = newValue - minValue;
        float zzz = axisWidth / diff;
        float posX = zzz*diff2;
        posX += xCord;
        slider.setPosition(posX, yCord);
    }
}

void Slider::setSliderPercentValue(float newPercentValue){
    if (newPercentValue >= 0 && newPercentValue <= 100)
    {
        sliderValue = newPercentValue / 100 * maxValue;
        slider.setPosition(xCord + (axisWidth*newPercentValue / 100), yCord);
    }
}

void Slider::draw(){
    src->getWindow()->draw(axis);
    src->getWindow()->draw(slider);
}

void Slider::handle(){
    logic();
    draw();
}
