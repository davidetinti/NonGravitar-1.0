#ifndef Pianeta_hpp
#define Pianeta_hpp

#include "GPlanet.hpp"

using namespace sf;
using namespace std;

struct Pianeta {
    int relative_x, relative_y, grid_x, grid_y, tot_schermate;
    double diameter;
    bool exist;
    Sprite planet;
    GPlanet interno;
    Texture *planet_tx;
    Pianeta* next;
    Pianeta(bool ex, int rel_x, int rel_y, int gr_x, int gr_y, int screens, 
            Pianeta *next);
};


class uPlanets {
    
protected:
    
    int str_l[8];
    int str_h[8];
    Pianeta* head, *current;
    Sprite explosion;
    Texture* explosion_tx;
    Risorse *src;
    
public:
    
    /// COSTRUTTORI /////////////////////////////////////////////////////
    uPlanets();
    uPlanets(Risorse *src);
    
    ///  SETTERS E GETTERS  /////////////////////////////////////////////
    Pianeta* getHead();
    void setHead(Pianeta* h);
    Pianeta* getCurrent();
    void setCurrent(Pianeta* h);
    
    ///  FUNZIONI  //////////////////////////////////////////////////////
    void gestione(Nave *player, Transitions *transizioni, Time perFrame);
private:
    void spriteSetup(Pianeta* p);
    void deletePlanet(Pianeta* p);
    //questa funzione è O(n) per la cancellazione: le altre due possibilità erano rendere la lista
    //bidirezionale e inserire l'eliminazione, impropriamente, nella funzione di disegno in universo.
    //poiché questa funzione è al più chiamata una volta ogni qualche minuto, credo l'efficienza debba
    //lasciare spazio sia alla pulizia del codice sia all'uso di memoria dei puntatori.
}; 

#endif /* Pianeta_hpp */
