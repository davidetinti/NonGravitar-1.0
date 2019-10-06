#include "pch.h"
#include "Risorse.hpp"

using namespace std;
using namespace sf;

Risorse::Risorse(){
    length = 1280;
    height = 720;
    settings.antialiasingLevel = 8;
    window.create(VideoMode(length, height), "Non Gravitar", (Style::Titlebar | Style::Close), settings);
    localPath[0] = "./../resources/";
    localPath[1] = "/Users/davidetinti/Desktop/NonGravitar-1.0/resources/";
    localPath[2] = "/Users/mlvp2t/Desktop/NonGravitar-1.0/resources/";
    loadSounds();
    loadTextures();
    if (!font.loadFromFile("/Users/davidetinti/Desktop/nongravitar/nongravitar/nongravitar/src/text.ttf")) {
        if (!font.loadFromFile("/Users/mlvp2t/Desktop/nongravitar/nongravitar/nongravitar/src/text.ttf")) {
            if (!font.loadFromFile("./src/text.ttf")) {
            }
        }
    }
    primaryDamage = 35;
    secondaryDamage = 100;
}
        
void Risorse::loadTextures(){
    for (int i = 0; i < sizeof(texture)/sizeof(texture[0]); i++){
        for (String userPath: localPath){
            texture[i].loadFromFile(userPath + to_string(i) + ".png");
        }
    }
}
        
void Risorse::loadSounds(){
    for (int i = 0; i < sizeof(sound)/sizeof(sound[0]); i++){
        for (String userPath: localPath){
            sound[i].loadFromFile(userPath + to_string(i) + ".ogg");
        }
    }
}

SoundBuffer Risorse::caricaSuono(int n){
    return sound[n];
}

Texture *Risorse::caricaTexture(int n){
    return &texture[n];
}

RenderWindow *Risorse::getWindow(){
    return &window;
}

int Risorse::getHeight(){
    return height;
}

int Risorse::getLength(){
    return length;
}

Font *Risorse::getFont(){
    return &font;
}

int Risorse::getPrimaryDamage(){
    return primaryDamage;
}

int Risorse::getSecondaryDamage(){
    return secondaryDamage;
}
