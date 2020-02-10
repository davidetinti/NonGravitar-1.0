#pragma once
#include "Universe.hpp"
#include "Stage.hpp"
#include "Highscore.hpp"

class Game{
    
protected:
    
    Resources *src;
    Stage *home;
    Stage *credits;
    Stage *game;
    Stage *pause;
    Stage *settings;
    Stage *game_over;
    Stage *highscore;
    Stage *active;
    Universe *universe;
    Texture *tmp_background;
    Text* points;
    Highscore highscore_st;
    HUD hud;
    Slider* current_handled;
    
    /**
     Switchando tra gli oggetti di controllo (slider e button) della schermata corrente, ne gestisce gli input.
     */
    void handleStageControls();
    
    /**
     Aggiorna il punteggio della partita corrente, mostrandolo a schermo.
     */
    void updateScore();
    
public:
    
    /**
     Costruttore base.
     */
    Game();
    
    /**
     Costruttore avanzato.
     Inizializza i campi della classe, assegnando ad ognuno le rispettive funzionalità (slider, button, text, ecc...)
     
     @param src puntatore all'utility class Resources
     */
    Game(Resources *src);
    
    /**
     Mostra lo sfondo, riceve gli input dagli oggetti di controllo (slider e button) e passa la gestione agli oggetti interni alla schermata attiva.
     */
    void handle();
    
};
