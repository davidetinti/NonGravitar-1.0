#include "Terreno.hpp"


soil::soil(soil *n):
    next(n)
    {
        element = ConvexShape(4);
    }


Terreno::Terreno(Resources *s){
    src = s;
    schermate_nr = 1;
    dx_coord = 0;
    sx_coord = 0;
    terrain_tx = nullptr;
    background_tx = s->getTexture(33);
    background.setTexture(*background_tx);
    head = nullptr;
    min_size_hole = 0;
    min_size_soil = 0;
    
}


Terreno::Terreno(int sx_coord, int dx_coord, Resources *s, int tot_schermate){
    src = s;
    schermate_nr = tot_schermate;
    terrain_tx = src->getTexture(29);
    terrain_tx->setRepeated(true);
    background_tx = src->getTexture(13);
    background.setTexture(*background_tx);
    background.setPosition(0, 0);
    background.setColor(setColor(tot_schermate,128));
    this->dx_coord = dx_coord;
    this->sx_coord = sx_coord;
    int nr = src->rand(4,23);   //poligoni del terreno
    float px = src->getLength()/nr;         //partial x
    int firstHeight = src->getHeight() - src->rand(0,99);   //altezza del terreno temporanea
    head = new soil(nullptr);
    soil *tmp = head;
    spriteSetup(Vector2f(0,src->getHeight()),Vector2f(0,sx_coord),
                Vector2f(px,firstHeight),Vector2f(px,src->getHeight()),tmp);
    int heightLeft = firstHeight;
    int heightRight = src->getHeight() - src->rand(0,99);
    for (int i = 2; i < nr ; i++){
        tmp->next = new soil(nullptr);
        spriteSetup(Vector2f(px*(i-1), src->getHeight()),Vector2f(px*(i-1), heightLeft),
                    Vector2f(px*i, heightRight),Vector2f(px*i, src->getHeight()),tmp->next);
        heightLeft = heightRight;
        heightRight = src->getHeight() - src->rand(0,99);
        tmp = tmp->next;
    }
    tmp->next = new soil(nullptr);
    tmp = tmp->next;
    spriteSetup(Vector2f(px*(nr-1), src->getHeight()),Vector2f(px*(nr-1), heightLeft),
                Vector2f(src->getLength(), dx_coord),Vector2f(src->getLength(), src->getHeight()),tmp);

    min_size_hole = 400;
    min_size_soil = 30;
}


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


Color Terreno::setColor(int tot_schermate, int transparency){
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
    while (tmp != nullptr){
        src->getWindow()->draw(tmp->element);
        tmp = tmp->next;
    };
}


double Terreno::getTerrainY(double x){
    soil *tmp = head;
	if (tmp != nullptr) {
		while (tmp->element.getPoint(2).x <= x && tmp->next != nullptr) {//tmp->soil.getPoint(2).x < DxCoord){
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
    p->element.setFillColor(setColor(schermate_nr,255));
}


int Terreno::prepareForHole(){
	soil *tmp = head->next;
    Vector2f topRight = tmp->element.getPoint(3);  
    while ((topRight.x - head->element.getPoint(3).x) < min_size_hole + 2 * min_size_soil){ //delete all necessary soils until
        tmp = tmp->next;              //hole can fit
        delete head->next;
        head->next = tmp;
        topRight = tmp->element.getPoint(3);
    }

    head->next = new soil(tmp);    //create first soil after hole
    double last_x = tmp->element.getPoint(0).x - min_size_soil;
    spriteSetup(Vector2f(last_x,src->getHeight()),Vector2f(last_x,src->getHeight()),
                tmp->element.getPoint(1),tmp->element.getPoint(0),
                head->next);
    tmp = head->next;
    head->next = new soil(tmp);     //create first soil before hole
    last_x = tmp->element.getPoint(1).x - min_size_hole;
    spriteSetup(head->element.getPoint(3),head->element.getPoint(2),
                Vector2f(last_x,src->getHeight()),Vector2f(last_x,src->getHeight()),
                head->next);

    return head->next->element.getPoint(2).x;    
}


void Terreno::prepareForBoss(Sprite *hole){
    hole->setPosition(prepareForHole() + min_size_hole / 2, 700);
}


bool Terreno::isBoss(){
    return head == nullptr
    && terrain_tx == nullptr;
}
