#include "SourceLoader.hpp"

using namespace std;
using namespace sf;

SourceLoader::SourceLoader(){
    length = 1280;
    height = 720;
    time_per_frame = seconds(1.0f / 120.0f); // 120 frames per second
    settings.antialiasingLevel = 8;
    window.create(VideoMode(length, height), "Non Gravitar", (Style::Titlebar | Style::Close | Style::Resize), settings);
    path = "./../resources/";
    loadTextures();
    loadSounds();
    loadFonts();
}

void SourceLoader::loadTextures(){
    for (int i = 0; i < sizeof(texture)/sizeof(texture[0]); i++){
        texture[i].loadFromFile(path + to_string(i) + ".png");
    }
}

void SourceLoader::loadSounds(){
    for (int i = 0; i < sizeof(sound)/sizeof(sound[0]); i++){
        sound[i].loadFromFile(path + to_string(i) + ".ogg");
    }
}

void SourceLoader::loadFonts(){
    for (int i = 0; i < sizeof(font)/sizeof(font[0]); i++){
        font[i].loadFromFile(path + to_string(i) + ".ttf");
    }
}

int SourceLoader::getHeight(){
    return height;
}

int SourceLoader::getLength(){
    return length;
}

SoundBuffer *SourceLoader::getSound(int n){
    return &sound[n];
}

Texture *SourceLoader::getTexture(int n){
    return &texture[n];
}

Font *SourceLoader::getFont(int n){
    return &font[n];
}

RenderWindow *SourceLoader::getWindow(){
    return &window;
}

Time *SourceLoader::getTimePerFrame(){
    return &time_per_frame;
}
