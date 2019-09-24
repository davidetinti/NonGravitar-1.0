#include "pch.h"
#include "Terreno.hpp"

using namespace std;
using namespace sf;

/// COSTRUTTORI /////////////////////////////////////////////////////

Terreno::Terreno(){
    
}

Terreno::Terreno(int sx_coord, int dx_coord, Risorse *src, int tot_schermate){
    terrain_tx = src->caricaTexture(29);
    terrain_tx->setRepeated(true);
    background_tx = src->caricaTexture(13);
    background.setTexture(*background_tx);
    background.setPosition(0, 0);
    background.setColor(colore(tot_schermate,128));
    this->dx_coord = dx_coord;
    this->sx_coord = sx_coord;
    int nr = 4 + rand() % 20;   //elementi di soil
    float px = 1280/nr;         //partial x
    int tmp = 700 - rand() % 100;   //altezza del terreno temporanea
    current = new soil;
    current->next = NULL;
    current->soil.setPointCount(4);
    current->soil.setPoint(0, Vector2f(px*0, 720));
    current->soil.setPoint(1, Vector2f(px*0, sx_coord));
    current->soil.setPoint(2, Vector2f(px*1, tmp));
    current->soil.setPoint(3, Vector2f(px*1, 720));
    current->soil.setTexture(terrain_tx);
    current->soil.setFillColor(colore(tot_schermate,255));
    head = current;
    for (int i = 2; i < nr ; i++){
        current->next = new soil;
        current->next->next = NULL;
        current->next->soil.setPointCount(4);
        current->next->soil.setPoint(0, Vector2f(px*(i-1), 720));
        current->next->soil.setPoint(1, Vector2f(px*(i-1), tmp));
        tmp = 700 - rand() % 100;
        current->next->soil.setPoint(2, Vector2f(px*i, tmp));
        current->next->soil.setPoint(3, Vector2f(px*i, 720));
        current->next->soil.setTexture(terrain_tx);
        current->next->soil.setFillColor(colore(tot_schermate,255));
        current = current->next;
    }
    current->next = new soil;
    current->next->next = NULL;
    current->next->soil.setPointCount(4);
    current->next->soil.setPoint(0, Vector2f(px*(nr-1), 720));
    current->next->soil.setPoint(1, Vector2f(px*(nr-1), tmp));
    current->next->soil.setPoint(2, Vector2f(1280, dx_coord));
    current->next->soil.setPoint(3, Vector2f(1280, 720));
    current->next->soil.setTexture(terrain_tx);
    current->next->soil.setFillColor(colore(tot_schermate,255));
    current = head;
    
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

void Terreno::gestisci(RenderWindow *window){
    window->draw(background);
    current = head;
    while (current != NULL){
        window->draw(current->soil);
        current = current->next;
    };
    current = head;
}

double Terreno::get_Y(double x){
    current = head;
	if (current != NULL) {
		while (current->soil.getPoint(2).x <= x && current->next != NULL) {//current->soil.getPoint(2).x < DxCoord){
			current = current->next;
		}
		double x1 = current->soil.getPoint(1).x;
		double x2 = current->soil.getPoint(2).x;
		double y1 = current->soil.getPoint(1).y;
		double y2 = current->soil.getPoint(2).y;
		double m = (y1 - y2) / (x1 - x2);
		double q = (x1 * y2 - x2 * y1) / (x1 - x2);
		current = head;
		return (m * x + q);
	}
	else return 0;
}
