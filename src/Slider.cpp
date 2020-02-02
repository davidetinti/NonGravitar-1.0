#include "Slider.hpp"

Slider::Slider(){
    
}

Slider::Slider(Vector2f position, float min, float max, char nome[], Resources *src){
    this->src = src;
    Texture *slider_tx, *axis_tx;
    slider_tx = src->getTexture(2);
    slider.setTexture(*slider_tx);
    slider_width = slider_tx->getSize().x;
    slider_height = slider_tx->getSize().y;
    slider.setPosition(position);
    slider.setOrigin(slider_width / 2, slider_height / 2);
    axis_tx = src->getTexture(22);
    axis.setTexture(*axis_tx);
    axis_width = axis_tx->getSize().x;
    axis_height = axis_tx->getSize().y ;
    axis.setPosition(position);
    axis.setOrigin(0, axis_height / 2);
    x_coord = position.x;
    y_coord = position.y;
    slider_value = min;
    min_value = min;
    max_value = max;
    strncpy(name, nome, 20);
    this->setSliderPercentValue(50);
}

void Slider::setSliderPercentValue(float newPercentValue){
    if (newPercentValue >= 0 && newPercentValue <= 100)
    {
        slider_value = newPercentValue / 100 * max_value;
        slider.setPosition(x_coord + (axis_width*newPercentValue / 100), y_coord);
    }
}

float Slider::getSliderValue(){
    return slider_value;
}

char* Slider::getName(){
    return name;
}

bool Slider::logic(){
    if ((slider.getGlobalBounds().contains(Mouse::getPosition(*src->getWindow()).x, Mouse::getPosition(*src->getWindow()).y) && Mouse::isButtonPressed(Mouse::Button::Left)) || mouse_was_clicked){
        mouse_was_clicked = true;
        if (Mouse::getPosition(*src->getWindow()).x >= x_coord && Mouse::getPosition(*src->getWindow()).x <= x_coord + axis_width){
            slider.setPosition(Mouse::getPosition(*src->getWindow()).x, y_coord);
            slider_value = (min_value + ((slider.getPosition().x - x_coord) / axis_width * (max_value - min_value)));
        }
        if (!Mouse::isButtonPressed(Mouse::Button::Left)) mouse_was_clicked = false;
    }
    return mouse_was_clicked;
}

void Slider::draw(){
    src->getWindow()->draw(axis);
    src->getWindow()->draw(slider);
}
