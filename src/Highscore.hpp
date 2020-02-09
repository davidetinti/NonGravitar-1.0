#pragma once
#include "Resources.hpp"

struct ScoreRow {
    Text rank,name,score;
};

class Highscore {
protected:
    Resources *src;
    list<ScoreRow*> scores;
    fstream file;
    string player_name;;
    Text* player;
    Text* score;
    Clock insertion_clock;
public:
    
    /**
     Costruttore semplice
     */
    Highscore();
    
    /**
     Costruttore avanzato

     @param src puntatore alla classe risorse di gioco
    */
    Highscore(Resources *src);
    
    /**
     Imposta il nome del giocatore

     @param text stringa da sostituire
    */
    void setTextPlayer(Text* text);
    
    /**
     Imposta il punteggio del giocatore

     @param text stringa da sostituire
    */
    void setTextScore(Text* text);
    
    /**
     Visualizza la griglia dei 3 migliori punteggi,
    */
    void draw();
    
    /**
     Gestisce l'inserimento di testo nella schermata Game Over e verifica se il nuovo punteggio va inserito tra i migliori

     @return true se viene premuto il tasto Invio (Keyboard::Key::Enter), false altrimenti
    */
    bool insert();
    
    /**
     Verify if the score is a new highscore, and if it's true insert it in the Highscore File
     and in the Highscore Tab in Highscore Scene.

     @param player string containing inserted player name.
     @param score string containing score reached.
    */
    void checkNewScore(Text* player, Text* score);
    
};
