#pragma once
#include <iostream>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstring>
#include <fstream>

using namespace std;
using namespace sf;

class SourceLoader{
    
private:
    
    static const int TEXTURE_NR = 44;
    static const int FONT_NR = 2;
    
protected:
    
    int height;
    int length;
    String path;
    Texture texture[TEXTURE_NR];
    Font font[FONT_NR];
    ContextSettings settings;
    RenderWindow window;
    Time time_per_frame;      // Stabilisce gli FPS
    
    void loadTextures();
    void loadFonts();
    String *getPath();
    
public:
    
    SourceLoader();
    
    int getHeight();
    int getLength();
    Texture *getTexture(int n);
    Font *getFont(int n);
    RenderWindow *getWindow();
    Time *getTimePerFrame();
};

/*

 FONTS:
 0.ttf - Text
 1.ttf - Demonized
 
 TEXTURES:
 0.png - player bullet
 1.png - player laser
 2.png - slider
 3.png - bunker triple bullet
 4.png - spaceship
 5.png - planet type 1
 6.png - planet type 2
 7.png - planet type 3
 8.png - planet type 4
 9.png - planet type 5
 10.png - planet type 6
 11.png - planet type 7
 12.png - planet type 8
 13.png - inside planet background
 14.png - enemies bullet type 1
 15.png - enemies bullet type 2
 16.png - life/fuel bar
 17.png - tractor beam //raggio traente
 18.png - fuel tank
 19.png - explosion type 1
 20.png - explosion type 2
 21.png - credits button
 22.png - slider axis
 23.png - new game button
 24.png - back button
 25.png - main menu background
 26.png - credits background
 27.png - highscore background
 28.png - universe background
 29.png - planet soil
 30.png - thrust
 31.png - hole
 32.png - boss
 33.jpg - boss background
 34.png - settings button
 35.png - settings background
 36.png - pause background (need to be overwritten)
 37.png - highscore button
 38.png - main menu button
 39.png - pause button
 40.png - resume button
 41.png - game over background
 42.png - bunker one bullet
 43.png - boss bunker

 */
