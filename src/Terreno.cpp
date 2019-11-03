#include "Terreno.hpp"

// COSTRUTTORI =======================================

soil::soil(soil *n):
        next(n){
            element = ConvexShape(4);
        }

Terreno::Terreno(Resources *s){
    //TODO use this for boss background
    background_tx = s->caricaTexture(33);
    background.setTexture(*background_tx);
    background.setColor(Color::Yellow);
}

Terreno::Terreno(int sx_coord, int dx_coord, Resources *src, int tot_schermate){
    this->src = src;
    nr_schermate = tot_schermate;
    terrain_tx = src->caricaTexture(29);
    terrain_tx->setRepeated(true);
    background_tx = src->caricaTexture(13);
    background.setTexture(*background_tx);
    background.setPosition(0, 0);
    background.setColor(colore(tot_schermate,128));
    this->dx_coord = dx_coord;
    this->sx_coord = sx_coord;
    int nr = src->rand(4,23);   //elementi di soil
    float px = src->getLength()/nr;         //partial x
    int firstHeight = src->getHeight() - src->rand(0,99);   //altezza del terreno temporanea
    head = new soil(NULL);
    soil *tmp = head;
    spriteSetup(Vector2f(0,src->getHeight()),Vector2f(0,sx_coord),
                Vector2f(px,firstHeight),Vector2f(px,src->getHeight()),tmp);
    int heightLeft = firstHeight;
    int heightRight = src->getHeight() - src->rand(0,99);
    for (int i = 2; i < nr ; i++){
        tmp->next = new soil(NULL);
        spriteSetup(Vector2f(px*(i-1), src->getHeight()),Vector2f(px*(i-1), heightLeft),
                    Vector2f(px*i, heightRight),Vector2f(px*i, src->getHeight()),tmp->next);
        heightLeft = heightRight;
        heightRight = src->getHeight() - src->rand(0,99);
        tmp = tmp->next;
    }
    tmp->next = new soil(NULL);
    tmp = tmp->next;
    spriteSetup(Vector2f(px*(nr-1), src->getHeight()),Vector2f(px*(nr-1), heightLeft),
                Vector2f(src->getLength(), dx_coord),Vector2f(src->getLength(), src->getHeight()),tmp);

    minSizeHole = 400;
    minSizeSoil = 30;
}

// SETTERS E GETTERS =================================

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

// FUNZIONI ==========================================
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

void Terreno::drawAll(){
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

void Terreno::spriteSetup(Vector2f p0, Vector2f p1, Vector2f p2, Vector2f p3, soil *p){
    p->element.setPoint(0,p0);
    p->element.setPoint(1,p1);
    p->element.setPoint(2,p2);
    p->element.setPoint(3,p3);
    p->element.setTexture(terrain_tx);
    p->element.setFillColor(colore(nr_schermate,255));
}

int Terreno::prepareForHole(){
	soil *tmp = head->next;
    Vector2f topRight = tmp->element.getPoint(3);  
    while ((topRight.x - head->element.getPoint(3).x) < minSizeHole + 2 * minSizeSoil){ //delete all necessary soils until
        tmp = tmp->next;              //hole can fit
        delete head->next;
        head->next = tmp;
        topRight = tmp->element.getPoint(3);
    }

    head->next = new soil(tmp);    //create first soil after hole
    double last_x = tmp->element.getPoint(0).x - minSizeSoil;
    spriteSetup(Vector2f(last_x,src->getHeight()),Vector2f(last_x,src->getHeight()),
                tmp->element.getPoint(1),tmp->element.getPoint(0),
                head->next);
    tmp = head->next;
    head->next = new soil(tmp);     //create first soil before hole
    last_x = tmp->element.getPoint(1).x - minSizeHole;
    spriteSetup(head->element.getPoint(3),head->element.getPoint(2),
                Vector2f(last_x,src->getHeight()),Vector2f(last_x,src->getHeight()),
                head->next);

    return head->next->element.getPoint(2).x;    
}

void Terreno::prepareForBoss(Sprite *hole){
    hole->setPosition(prepareForHole() + minSizeHole / 2, 700);
}
