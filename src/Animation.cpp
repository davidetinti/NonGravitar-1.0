#include "Animation.hpp"

Animation::Animation(){
    
}

Animation::Animation(int x, int y, int tx_nr, int rows, int columns, Resources *src){
    this->src = src;
    sprite.setTexture(*src->caricaTexture(tx_nr));
    frameWidth = sprite.getTexture()->getSize().x/columns;
    frameHeight = sprite.getTexture()->getSize().y/rows;
    currentX = 0;
    currentY = 0;
    maxX = columns;
    maxY = rows;
    sprite.setPosition(x, y);
    sprite.setOrigin(frameWidth/2, frameHeight/2);
}

void Animation::handle(){
    sprite.setTextureRect(IntRect(frameWidth*currentX, frameHeight*currentY, frameWidth, frameHeight));
    currentX++;
    if (currentX >= maxX){
        currentY++;
        currentX = 0;
    }
    if (currentY >= maxY){
        currentY = 0;
        currentX = 0;
    }
    src->getWindow()->draw(sprite);
}
