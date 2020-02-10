#pragma once
#include "Resources.hpp"

/**
 Riga nella tabella di visualizzazione dei punteggi.
 Mostra 3 campi:
 - rank: posizione in classifica
 - name: nome dell'autore del punteggio
 - score: valore del punteggio
 */

struct ScoreRow {
    Text rank;
    Text name;
    Text score;
};

class Highscore {
    
protected:
    
    Resources *src;
    list<ScoreRow*> scores;
    fstream file;
    string player_name;;
    Text* player;
    Text* score;
    
public:
    
    /**
     Costruttore semplice
     */
    Highscore();
    
    /**
     Costruttore avanzato.
     Verifica la presenza del file contente i punteggi (altrimenti ne crea uno nuovo) e registra i valori letti come elementi di scores.

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
     Visualizza la tabella dei 3 migliori punteggi.
    */
    void draw();
    
    /**
     Gestisce l'inserimento del nome del giocatore nella schermata Game Over.
     Alla pressione del tasto Invio verifica se il nuovo punteggio va inserito tra i migliori.

     @return true se viene premuto il tasto Invio, false altrimenti
    */
    bool insert();
    
    /**
     Verifica se il dati passati come argomento devono essere inseriti tra i migliori 3 punteggi.
     In caso positivo aggiorna le voci della lista scores e nel file contenente i punteggi.

     @param player stringa contenente il nome del giocatore
     @param score stringa contenente il punteggio ottenuto
    */
    void checkNewScore(Text* player, Text* score);
    
};
