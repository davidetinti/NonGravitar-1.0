#include "Slider.hpp"

Slider::Slider(){
    
}

Slider::Slider(Vector2f position, float min, float max, char nome[], Resources *src){
    this->src = src;
    Texture *slider_tx, *axis_tx;
    slider_tx = src->getTexture(2);
    slider.setTexture(*slider_tx);
    sliderWidth = slider_tx->getSize().x;
    sliderHeight = slider_tx->getSize().y;
    slider.setPosition(position);
    slider.setOrigin(sliderWidth / 2, sliderHeight / 2);
    axis_tx = src->getTexture(22);
    axis.setTexture(*axis_tx);
    axisWidth = axis_tx->getSize().x;
    axisHeight = axis_tx->getSize().y ;
    axis.setPosition(position);
    axis.setOrigin(0, axisHeight / 2);
    xCord = position.x;
    yCord = position.y;
    sliderValue = min;
    minValue = min;
    maxValue = max;
    strncpy(name, nome, 20);
    mouseWasClicked = false;
    isHandled = false;
    this->setSliderPercentValue(50);
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

char *Slider::getName(){
    return name;
}

void Slider::draw(){
    src->getWindow()->draw(axis);
    src->getWindow()->draw(slider);
}

void Slider::handle(){
    logic();
    draw();
}
