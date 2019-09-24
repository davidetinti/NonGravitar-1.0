#include "pch.h"
#include "Transitions.hpp"

using namespace sf;
using namespace std;

/// COSTRUTTORI /////////////////////////////////////////////////////

Transitions::Transitions(){
    screen.setSize(Vector2f(1280,720));
    screen.setPosition(0, 0);
    trans.setSize(Vector2f(1280,720));
    trans.setPosition(0, 0);
    tempo_transizione = 0;
}

///  SETTERS E GETTERS  /////////////////////////////////////////////



///  FUNZIONI  //////////////////////////////////////////////////////

void Transitions::inPlanet(RenderWindow *window, Terreno *terrain, int tot_schermate){
    tempo_transizione = 1000;
    cl1.restart();
    t1 = cl1.getElapsedTime();
    int n = (255*t1.asMilliseconds()/tempo_transizione);
    Texture a;
    a.create(window->getSize().x, window->getSize().y);
	a.update(*window);
    screen.setTexture(&a);
    trans.setFillColor(terrain->colore(tot_schermate, n));
    while (t1.asMilliseconds() < tempo_transizione){
        t1 = cl1.getElapsedTime();
        n = (255*t1.asMilliseconds())/tempo_transizione;
        trans.setFillColor(terrain->colore(tot_schermate, n));
        window->clear();
        window->draw(screen);
        window->draw(trans);
        window->display();
    }
}

void Transitions::outPlanet(RenderWindow *window){
    tempo_transizione = 1000;
    cl1.restart();
    t1 = cl1.getElapsedTime();
    int n = (255*t1.asMilliseconds()/tempo_transizione);
    Texture a;
	a.create(window->getSize().x, window->getSize().y);
	a.update(*window);
    screen.setTexture(&a);
    trans.setFillColor(Color(255,255,255,n));
    while (t1.asMilliseconds() < tempo_transizione){
        t1 = cl1.getElapsedTime();
        n = (255*t1.asMilliseconds())/tempo_transizione;
        trans.setFillColor(Color(255,255,255,n));
        window->clear();
        window->draw(screen);
        window->draw(trans);
        window->display();
    }
}
