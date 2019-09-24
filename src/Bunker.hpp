#ifndef Bunker_hpp
#define Bunker_hpp

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Nave.hpp"

using namespace sf;
using namespace std;

struct bunkerlist{
    int type;    // 0 = bunker spara fisso 1/2/3 colpi      1 = bunker segue il giocatore
    int tempo;
    double x;
    double y;
    double life;
    double explosion_x;  //posizione del frame nell'animazione dell'esplosione
    bool exist;
    Sprite bunker,explosion;
    Bullets weapon;
    bunkerlist *next;
    bunkerlist(int type_n, int tempo_n, double x_n, double y_n, double life_n,
               bunkerlist *next_n, bool exist_n = true, double explosion_x_n = 0,
               Bullets weapon_n = Bullets());
};

typedef bunkerlist* ptr_bunkerlist;

class Bunker{

protected:
    
    ptr_Texture bunker_tx,explosion_tx;
	ptr_bunkerlist head,last_checked;
    double partial_x[4];        //coordinate per la griglia dei bunker
    
public:
    
    Clock bunkerDamage;
    
    /// COSTRUTTORI /////////////////////////////////////////////////////
    Bunker();
    Bunker(Risorse *src, Terreno *terrain);
    
    ///  SETTERS E GETTERS  /////////////////////////////////////////////
    ptr_bunkerlist getHead();
    void setEnemies(ptr_bunkerlist enemies);
    
    ///  FUNZIONI  //////////////////////////////////////////////////////
    void armi(bunkerlist *tmp, RenderWindow *window, Terreno *terrain, Time perFrame);
	bool checkCollisionBunker(Sprite *body, char type);
	void hitLastChecked(int damage);
	void deleteBunker(ptr_bunkerlist target);
    void esplodi(RenderWindow *window, ptr_bunkerlist target);
	bool isEmpty();
    void gestisci(RenderWindow *window, Nave *player, Terreno *terrain, Time perFrame);

protected:
    void spriteSetup(bunkerlist *p);
};

#endif /* Bunker_hpp */
