#include "Animation.hpp"


Animation::Animation(){
    
}


Animation::Animation(int x, int y, int tx_nr, int rows, int columns,
                     float scale, SourceLoader *src_a, double image_speed){
    src = src_a;
    sprite.setTexture(*src->getTexture(tx_nr));
    frame_width = sprite.getTexture()->getSize().x/columns;
    frame_height = sprite.getTexture()->getSize().y/rows;
    current_x = 0.0;
    current_y = 0.0;
    speed = image_speed;
    max_x = columns;
    max_y = rows;
    sprite.setPosition(x, y);
    sprite.setScale(scale, scale);
    sprite.setOrigin(frame_width/2, frame_height/2);
}


Sprite* Animation::getSprite(){
    return &sprite;
}


bool Animation::isEnded(){
    if (current_y >= max_y){
        return true;
    }
    return false;
}


void Animation::handle(){
    if (current_x >= max_x){
        current_y++;
        current_x = 0;
    }
    int base_x = frame_width * (int)current_x;
    int base_y = frame_height * (int)current_y;
    sprite.setTextureRect(IntRect(base_x, base_y, frame_width, frame_height));
    src->getWindow()->draw(sprite);
    current_x = current_x + (1 * speed);
}
