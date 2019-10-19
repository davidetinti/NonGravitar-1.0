#include "Animation.hpp"

Animation::Animation(){
    
}

Animation::Animation(int x, int y, int tx_nr, int rows, int columns, float scale, SourceLoader *src, double imagespeed){
    this->src = src;
    sprite.setTexture(*src->getTexture(tx_nr));
    frameWidth = sprite.getTexture()->getSize().x/columns;
    frameHeight = sprite.getTexture()->getSize().y/rows;
    currentX = 0.0;
    currentY = 0.0;
    speed = imagespeed;
    maxX = columns;
    maxY = rows;
    sprite.setPosition(x, y);
    sprite.setScale(Vector2f(scale,scale));
    sprite.setOrigin(frameWidth/2, frameHeight/2);
    
}

bool Animation::handle(){
    if (currentX >= maxX){
        currentY++;
        currentX = 0;
    }
    if (currentY >= maxY){
        return false;
    }
    sprite.setTextureRect(IntRect(frameWidth*(int)currentX, frameHeight*(int)currentY, frameWidth, frameHeight));
    src->getWindow()->draw(sprite);
    currentX = currentX + 1*speed;
    return true;
}
