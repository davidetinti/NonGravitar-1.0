#include "pch.h"
#include "Transitions.hpp"

using namespace sf;
using namespace std;

/// COSTRUTTORI /////////////////////////////////////////////////////

Transitions::Transitions(){
    
}

Transitions::Transitions(Risorse *src){
    this->src = src;
    this->screen.setSize(Vector2f(1280,720));
    this->screen.setPosition(0, 0);
    this->trans.setSize(Vector2f(1280,720));
    this->trans.setPosition(0, 0);
    this->tempo_transizione = 0;
}

///  SETTERS E GETTERS  /////////////////////////////////////////////



///  FUNZIONI  //////////////////////////////////////////////////////

void Transitions::inPlanet(Terreno *terrain, int tot_schermate){
    tempo_transizione = 1000;
    cl1.restart();
    t1 = cl1.getElapsedTime();
    int n = (255*t1.asMilliseconds()/tempo_transizione);
    Texture a;
    a.create
    (this->src->getWindow()->getSize().x,
     this->src->getWindow()->getSize().y);
	a.update(*this->src->getWindow());
    screen.setTexture(&a);
    trans.setFillColor(terrain->colore(tot_schermate, n));
    while (t1.asMilliseconds() < tempo_transizione){
        t1 = cl1.getElapsedTime();
        n = (255*t1.asMilliseconds())/tempo_transizione;
        trans.setFillColor(terrain->colore(tot_schermate, n));
        this->src->getWindow()->clear();
        this->src->getWindow()->draw(screen);
        this->src->getWindow()->draw(trans);
        this->src->getWindow()->display();
    }
}

void Transitions::outPlanet(){
    tempo_transizione = 1000;
    cl1.restart();
    t1 = cl1.getElapsedTime();
    int n = (255*t1.asMilliseconds()/tempo_transizione);
    Texture a;
	a.create(this->src->getWindow()->getSize().x, this->src->getWindow()->getSize().y);
	a.update(*this->src->getWindow());
    screen.setTexture(&a);
    trans.setFillColor(Color(255,255,255,n));
    while (t1.asMilliseconds() < tempo_transizione){
        t1 = cl1.getElapsedTime();
        n = (255*t1.asMilliseconds())/tempo_transizione;
        trans.setFillColor(Color(255,255,255,n));
        this->src->getWindow()->clear();
        this->src->getWindow()->draw(screen);
        this->src->getWindow()->draw(trans);
        this->src->getWindow()->display();
    }
}
