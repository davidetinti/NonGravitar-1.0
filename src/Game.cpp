#include"pch.h"
#include "Game.hpp"

using namespace std;
using namespace sf;

Game::Game(){
    
}

Game::Game(Risorse *src, Time *time){
    this->src = src;
    pausa_bk = this->src->caricaTexture(28);
    universe = Universo(this->src, time);
    schermata_principale = Finestra(this->src, 26);
    partita = Finestra(this->src, 2);
    crediti = Finestra(this->src, 2);
    pausa = Finestra(this->src, 2);
    schermata_principale.addButton(Vector2f(640,400), 23, 1, (char*)"newgame");
    schermata_principale.addButton(Vector2f(640,480),22, 1, (char*)"esci");
    partita.addButton(Vector2f(1200,30), 22, 0.35, (char*)"menu");
    crediti.addButton(Vector2f(640,400), 24, 1, (char*)"indietro");
    pausa.addButton(Vector2f(640,400), 23, 1, (char*)"riprendi");
    pausa.addButton(Vector2f(640,480), 24, 1, (char*)"tornaalmenu");
    schermata_principale.setAttiva(true);
}

void Game::handle(Time timePerFrame){
    if (schermata_principale.getAttiva()){
        schermata_principale.disegna();
        lista_pulsanti *tmp = schermata_principale.getIcone();
        while (tmp != NULL){
            if (!strcmp(tmp->name,"newgame") && tmp->current.gestisci()){
                universe = Universo(this->src, &timePerFrame);
                schermata_principale.setAttiva(false);
                partita.setAttiva(true);
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
            }
            if (!strcmp(tmp->name, "esci") && tmp->current.gestisci()){
                this->src->getWindow()->close();
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
            }
            tmp = tmp->next;
        }
    }
    if (partita.getAttiva()){
        if (!universe.player.getIsDead()){
            
            universe.handle(&transizioni, timePerFrame);
            
            /// UNIVERSO
            
            if (!universe.player.getAtPlanet()) {
                this->src->getWindow()->draw(universe.background);
                universe.disegnaPianeti();
                
            }
            
            /// PIANETA
            
            if (universe.player.getAtPlanet()){
                universe.getActive()->pianeti.gestione(&universe.player, &transizioni, timePerFrame);
                //text.setString(to_string(universe.getActive()->pianeti.getPP()->interno.getCurrent()->nr_schermata));
                if (universe.player.getAtPlanet()) {
                    universe.player.armi(&universe.getActive()->pianeti.getCurrent()->interno.getCurrent()->terrain, timePerFrame);
                    universe.player.raggioTraente();
                    //window.draw(text);
                    universe.checkTerrain();
                }
            }
            src->getWindow()->draw(universe.player.thrust);
            src->getWindow()->draw(universe.player.nave);
            universe.hud.gestisci(universe.player.getPunti(), universe.player.getLifebar(), universe.player.getFuelbar());
            universe.player.gestisci();
        }
        Image a;
        lista_pulsanti *tmp = partita.getIcone();
        while (tmp != NULL){
            tmp->current.disegna();
            if (tmp->current.gestisci() || Keyboard::isKeyPressed(Keyboard::Escape)){
                partita.setAttiva(false);
                pausa.setAttiva(true);
				Texture tmp;
				tmp.create(src->getWindow()->getSize().x, src->getWindow()->getSize().y);
				tmp.update(*src->getWindow());
                a = tmp.copyToImage();
                pausa_bk->update(a);
                pausa.sfondo.setTexture(*pausa_bk);
                pausa.sfondo.setColor(Color(128,128,128));
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
            }
            tmp = tmp->next;
        }
    }
    if (crediti.getAttiva()){
        crediti.disegna();
    }
    if (pausa.getAttiva()){
        pausa.disegna();
        lista_pulsanti *tmp = pausa.getIcone();
        while (tmp != NULL){
            if (!strcmp(tmp->name,"riprendi") && tmp->current.gestisci()){
                pausa.setAttiva(false);
                partita.setAttiva(true);
                if (universe.player.getAtPlanet()){
                    bunkerlist *tmp = universe.getActive()->pianeti.getCurrent()->interno.getCurrent()->enemies.getHead();
                    while (tmp != NULL){
                        tmp->weapon.bullet_time.restart();
                        tmp = tmp->next;
                    }
                }
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
            }
            if (!strcmp(tmp->name, "backmenu") && tmp->current.gestisci()){
                pausa.setAttiva(false);
                schermata_principale.setAttiva(true);
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
            }
            tmp = tmp->next;
        }
    }
}
    
