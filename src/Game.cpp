#include"pch.h"
#include "Game.hpp"

using namespace std;
using namespace sf;

Game::Game(){
    
}

Game::Game(Risorse *src, Font *font){
    pausa_bk = src->caricaTexture(28);
    universe = Universo(1280, 720, src, font);
    schermata_principale = Finestra(src, 26);
    partita = Finestra(src, 2);
    crediti = Finestra(src, 2);
    pausa = Finestra(src, 2);
    char esci[] = "esci";
    char newgame[] = "newgame";
    char menu[] = "menu";
    char indietro[] = "indietro";
    char riprendi[] = "riprendi";
    char tornaalmenu[] = "backmenu";
    schermata_principale.addButton(Vector2f(640,400), src, 23, 1, newgame);
    schermata_principale.addButton(Vector2f(640,480), src, 22, 1, esci);
    partita.addButton(Vector2f(1200,30), src, 22, 0.35, menu);
    crediti.addButton(Vector2f(640,400), src, 24, 1, indietro);
    pausa.addButton(Vector2f(640,400), src, 23, 1, riprendi);
    pausa.addButton(Vector2f(640,480), src, 24, 1, tornaalmenu);
    schermata_principale.setAttiva(true);
}

void Game::gestisci(RenderWindow *window, Risorse *src, Font *font, sf::Time timePerFrame){
    if (schermata_principale.getAttiva()){
        schermata_principale.disegna(window);
        ptr_lista_pulsanti tmp = schermata_principale.getIcone();
        while (tmp != NULL){
            if (!strcmp(tmp->name,"newgame") && tmp->current.gestisci(window)){
                universe = Universo(1280, 720, src, font);
                schermata_principale.setAttiva(false);
                partita.setAttiva(true);
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
            }
            if (!strcmp(tmp->name, "esci") && tmp->current.gestisci(window)){
                window->close();
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
            }
            tmp = tmp->next;
        }
    }
    if (partita.getAttiva()){
        if (!universe.player.getIsDead()){
            
            universe.movimentiNavetta(window, src, &transizioni, timePerFrame);
            
            /// UNIVERSO
            
            if (!universe.player.getAtPlanet()) {
                window->draw(universe.universe);
                universe.disegnaPianeti(window);
                
            }
            
            /// PIANETA
            
            if (universe.player.getAtPlanet()){
                universe.getActive()->pianeti.gestione(window, &universe.player, &transizioni, timePerFrame);
                //text.setString(to_string(universe.getActive()->pianeti.getPP()->interno.getCurrent()->nr_schermata));
                if (universe.player.getAtPlanet()) {
                    universe.player.armi(window, &universe.getActive()->pianeti.getPP()->interno.getCurrent()->terrain, timePerFrame);
                    universe.player.raggiotraente(window);
                    //window.draw(text);
                    universe.checkTerrain(window);
                }
            }
            window->draw(universe.player.thrust);
            window->draw(universe.player.nave);
            universe.hud.gestisci(window, universe.player.getPunti(), universe.player.getLifebar(), universe.player.getFuelbar());
            universe.player.gestisci();
        }
        Image a;
        ptr_lista_pulsanti tmp = partita.getIcone();
        while (tmp != NULL){
            tmp->current.disegna(window);
            if (tmp->current.gestisci(window) || Keyboard::isKeyPressed(Keyboard::Escape)){
                partita.setAttiva(false);
                pausa.setAttiva(true);
				Texture tmp;
				tmp.create(window->getSize().x, window->getSize().y);
				tmp.update(*window);
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
        crediti.disegna(window);
    }
    if (pausa.getAttiva()){
        pausa.disegna(window);
        ptr_lista_pulsanti tmp = pausa.getIcone();
        while (tmp != NULL){
            if (!strcmp(tmp->name,"riprendi") && tmp->current.gestisci(window)){
                pausa.setAttiva(false);
                partita.setAttiva(true);
                if (universe.player.getAtPlanet()){
                    ptr_bunkerlist tmp = universe.getActive()->pianeti.getPP()->interno.getCurrent()->enemies.getHead();
                    while (tmp != NULL){
                        tmp->weapon.bullet_time.restart();
                        tmp = tmp->next;
                    }
                }
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
            }
            if (!strcmp(tmp->name, "backmenu") && tmp->current.gestisci(window)){
                pausa.setAttiva(false);
                schermata_principale.setAttiva(true);
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
            }
            tmp = tmp->next;
        }
    }
}
    
