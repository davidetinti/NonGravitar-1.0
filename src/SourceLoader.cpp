#include "SourceLoader.hpp"

using namespace std;
using namespace sf;

SourceLoader::SourceLoader(){
    length = 1280;
    height = 720;
    primaryDamage = 100;
    secondaryDamage = 100;
    timePerFrame = seconds(1.0f / 120.0f); // 120 frames per second
    settings.antialiasingLevel = 8;
    window.create(VideoMode(length, height), "Non Gravitar", (Style::Titlebar | Style::Close | Style::Resize), settings);
    path[0] = "./../resources/";
    //localPath[2] = "/Users/mlvp2t/Desktop/NonGravitar-1.0/resources/";
    loadTextures();
    loadSounds();
    loadFonts();
}

void SourceLoader::loadTextures(){
    for (int i = 0; i < sizeof(texture)/sizeof(texture[0]); i++){
        for (String userPath: path){
            texture[i].loadFromFile(userPath + to_string(i) + ".png");
        }
    }
}

void SourceLoader::loadSounds(){
    for (int i = 0; i < sizeof(sound)/sizeof(sound[0]); i++){
        for (String userPath: path){
            sound[i].loadFromFile(userPath + to_string(i) + ".ogg");
        }
    }
}

void SourceLoader::loadFonts(){
    for (int i = 0; i < sizeof(font)/sizeof(font[0]); i++){
        if (!font[i].loadFromFile("./../resources/" + to_string(i) + ".ttf")){
            if (!font[i].loadFromFile("/Users/mlvp2t/Desktop/NonGravitar-1.0/resources/" + to_string(i) + ".ttf")){
                    cout << "ERROR";
            }
        }
    }
}

int SourceLoader::getHeight(){
    return height;
}

int SourceLoader::getLength(){
    return length;
}

int SourceLoader::getPrimaryDamage(){
    return primaryDamage;
}

int SourceLoader::getSecondaryDamage(){
    return secondaryDamage;
}

String *SourceLoader::getLocalPath(int n){
    return &path[n];
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
    return &timePerFrame;
}

Time *SourceLoader::getUtilityTime(){
    return &utilityTime;
}

Clock *SourceLoader::getUtilityClock(){
    return &utilityClock;
}
