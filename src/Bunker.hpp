#ifndef Bunker_hpp
#define Bunker_hpp

#include "Nave.hpp"

using namespace sf;
using namespace std;

struct bunkerlist{
    int type;    // 0 = bunker spara fisso 1/2/3 colpi      1 = bunker segue il giocatore
    int tempo;
    int damage;
    double x;
    double y;
    double life;
    double explosion_x;  //posizione del frame nell'animazione dell'esplosione
    bool exist;
    Sprite bunker,explosion;
    Bullets *weapon;
    bunkerlist *next;
    bunkerlist(int type_n, int tempo_n, double x_n, double y_n, double life_n,
               bunkerlist *next_n, Bullets *weapon_n, bool exist_n = true, double explosion_x_n = 0);
};

class Bunker{

protected:
    
    Risorse *src;
    Texture *bunker_tx,*explosion_tx;
	bunkerlist *head;
    double partial_x[4];        //coordinate per la griglia dei bunker
    
public:
    
    Clock bunkerDamage;
    
    /// COSTRUTTORI /////////////////////////////////////////////////////
    Bunker();
    Bunker(Risorse *src, Terreno *terrain);
    
    ///  SETTERS E GETTERS  /////////////////////////////////////////////
    bunkerlist *getHead();
    void setEnemies(bunkerlist *enemies);
    
    ///  FUNZIONI  //////////////////////////////////////////////////////
    void armi(bunkerlist *tmp, Terreno *terrain, Time perFrame);
	void hitBunker(int damage, bunkerlist *p);
	void deleteBunker(bunkerlist *target);
    void esplodi(bunkerlist *target);
	bool isEmpty();
    void gestisci(Nave *player, Terreno *terrain, Time perFrame);
    int checkCollisionBBullets(FloatRect obj);
    bool collidesWith(bunkerlist *p, FloatRect q);

protected:
    void spriteSetup(bunkerlist *p);
};

#endif /* Bunker_hpp */
