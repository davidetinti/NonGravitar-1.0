#include "pch.h"
#include "Resources.hpp"

using namespace std;
using namespace sf;

Resources::Resources(){
    timePerFrame = seconds(1.0f / 120.0f); // 120 frames per second
    length = 1280;
    height = 720;
    settings.antialiasingLevel = 8;
    window.create(VideoMode(length, height), "Non Gravitar", (Style::Titlebar | Style::Close), settings);
    localPath[2] = "./../resources/";
    localPath[0] = "/Users/davidetinti/Desktop/NonGravitar-1.0/resources/";
    localPath[1] = "/Users/mlvp2t/Desktop/NonGravitar-1.0/resources/";
    loadSounds();
    loadTextures();
    loadFonts();
}
        
void Resources::loadTextures(){
    for (int i = 0; i < sizeof(texture)/sizeof(texture[0]); i++){
        for (String userPath: localPath){
            texture[i].loadFromFile(userPath + to_string(i) + ".png");
        }
    }
}
        
void Resources::loadSounds(){
    for (int i = 0; i < sizeof(sound)/sizeof(sound[0]); i++){
        for (String userPath: localPath){
            sound[i].loadFromFile(userPath + to_string(i) + ".ogg");
        }
    }
}

void Resources::loadFonts(){
    for (int i = 0; i < sizeof(font)/sizeof(font[0]); i++){
        for (String userPath: localPath){
            font[i].loadFromFile(userPath + to_string(i) + ".ttf");
        }
    }
}

SoundBuffer Resources::caricaSuono(int n){
    return sound[n];
}

Texture *Resources::caricaTexture(int n){
    return &texture[n];
}

RenderWindow *Resources::getWindow(){
    return &window;
}

int Resources::getHeight(){
    return height;
}

int Resources::getLength(){
    return length;
}

Font Resources::getFont(int n){
    return font[n];
}

Time *Resources::getTimePerFrame(){
    return &timePerFrame;
}
