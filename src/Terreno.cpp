#include "pch.h"
#include "Terreno.hpp"

using namespace std;
using namespace sf;

/// COSTRUTTORI /////////////////////////////////////////////////////

soil::soil(soil *n):
        next(n){
            element = ConvexShape(4);
        }

Terreno::Terreno(){
    
}

Terreno::Terreno(int sx_coord, int dx_coord, Risorse *src, int tot_schermate){
    this->src = src;
    terrain_tx = src->caricaTexture(29);
    terrain_tx->setRepeated(true);
    background_tx = src->caricaTexture(13);
    background.setTexture(*background_tx);
    background.setPosition(0, 0);
    background.setColor(colore(tot_schermate,128));
    this->dx_coord = dx_coord;
    this->sx_coord = sx_coord;
    int nr = 4 + rand() % 20;   //elementi di soil
    float px = src->getLength()/nr;         //partial x
    int firstHeight = src->getHeight() - rand() % 100;   //altezza del terreno temporanea
    head = new soil(NULL);
    soil *tmp = head;
    spriteSetup(tot_schermate,Vector2f(0,src->getHeight()),Vector2f(0,sx_coord),
                Vector2f(px,firstHeight),Vector2f(px,src->getHeight()),tmp);
    int heightLeft = firstHeight;
    int heightRight = src->getHeight() - rand() % 100;
    for (int i = 2; i < nr ; i++){
        tmp->next = new soil(NULL);
        spriteSetup(tot_schermate,Vector2f(px*(i-1), src->getHeight()),Vector2f(px*(i-1), heightLeft),
                    Vector2f(px*i, heightRight),Vector2f(px*i, src->getHeight()),tmp->next);
        heightLeft = heightRight;
        heightRight = src->getHeight() - rand() % 100;
        tmp = tmp->next;
    }
    tmp->next = new soil(NULL);
    tmp = tmp->next;
    spriteSetup(tot_schermate,Vector2f(px*(nr-1), src->getHeight()),Vector2f(px*(nr-1), heightLeft),
                Vector2f(src->getLength(), dx_coord),Vector2f(src->getLength(), src->getHeight()),tmp);
}

///  SETTERS E GETTERS  /////////////////////////////////////////////

int Terreno::getDxCoord(){
    return this->dx_coord;
}

int Terreno::getSxCoord(){
    return this->sx_coord;
}

void Terreno::setDxCoord(int dx_coord){
    this->dx_coord = dx_coord;
}

void Terreno::setSxCoord(int sx_coord){
    this->sx_coord = sx_coord;
}

///  FUNZIONI  //////////////////////////////////////////////////////

Color Terreno::colore(int tot_schermate, int transparency){
    switch (tot_schermate) {
        case 3:
            return Color::White;
        case 4:
            return Color(255,162,0,transparency);
        case 5:
            return Color(179,0,255,transparency);
        case 6:
            return Color(0,213,255,transparency);
        case 7:
            return Color(0,77,255,transparency);
        case 8:
            return Color(176,0,0,transparency);
        case 9:
            return Color(255,230,0,transparency);
        case 10:
            return Color(0,168,17,transparency);
        default:
            return Color(255,255,255,transparency);
    }
}

void Terreno::gestisci(){
    src->getWindow()->draw(background);
    soil *tmp = head;
    while (tmp != NULL){
            src->getWindow()->draw(tmp->element);
        tmp = tmp->next;
    };
}

double Terreno::get_Y(double x){
    soil *tmp = head;
	if (tmp != NULL) {
		while (tmp->element.getPoint(2).x <= x && tmp->next != NULL) {//tmp->soil.getPoint(2).x < DxCoord){
			tmp = tmp->next;
		}
		double x1 = tmp->element.getPoint(1).x;
		double x2 = tmp->element.getPoint(2).x;
		double y1 = tmp->element.getPoint(1).y;
		double y2 = tmp->element.getPoint(2).y;
		double m = (y1 - y2) / (x1 - x2);
		double q = (x1 * y2 - x2 * y1) / (x1 - x2);
		return (m * x + q);
	}
	else return 0;
}

void Terreno::spriteSetup(int tot_sch, Vector2f p0, Vector2f p1, Vector2f p2, Vector2f p3, soil *p){
    p->element.setPoint(0,p0);
    p->element.setPoint(1,p1);
    p->element.setPoint(2,p2);
    p->element.setPoint(3,p3);
    p->element.setTexture(terrain_tx);
    p->element.setFillColor(colore(tot_sch,255));
}
