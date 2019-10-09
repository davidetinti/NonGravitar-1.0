#include "pch.h"
#include "Game.hpp"

Game::Game(){
    
}

Game::Game(Resources *src){
    this->src = src;
    tmp_background = this->src->caricaTexture(33);
    universe = Universe(this->src);
    home = Stage(this->src, 25);
    game = Stage(this->src, 28);
    credits = Stage(this->src, 28);
    pause = Stage(this->src, 28);
    settings = Stage(this->src, 35);
    game_over = Stage(this->src, 28);
    home.addButton(Vector2f(330,450), 23, 0.45, (char*)"game");
    home.addButton(Vector2f(950,450), 37, 0.45, (char*)"highscore");
    home.addButton(Vector2f(170,650), 34, 0.25, (char*)"settings");
    home.addButton(Vector2f(1110,650), 21, 0.25, (char*)"credits");
    settings.addButton(Vector2f(640,650), 24, 0.25, (char*)"back");
    settings.addSlider(340, 300, 0.025, 0.1, (char*)"acceleration");
    settings.addSlider(340, 430, 3, 7, (char*)"max_speed");
    settings.addSlider(340, 560, 0, 0, (char*)"difficulty");
    game.addButton(Vector2f(1150,50), 39, 0.20, (char*)"pause");
    credits.addButton(Vector2f(640,650), 24, 0.25, (char*)"back");
    pause.addButton(Vector2f(330,450), 40, 0.45, (char*)"resume");
    pause.addButton(Vector2f(950,450), 38, 0.45, (char*)"back_to_menu");
    game_over.addButton(Vector2f(640,650), 24, 0.25, (char*)"back");
    home.setActive(true);
}

void Game::handle(){
    if (home.getActive()){
        home.draw();
        lista_pulsanti *tmp = home.getButtons();
        while (tmp != NULL){
            if (!strcmp(tmp->name,"game") && tmp->current.handle()){
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
                if (tmp->current.isSelected()){
                    home.setActive(false);
                    game.setActive(true);
                }
            } else if (!strcmp(tmp->name, "credits") && tmp->current.handle()){
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
                if (tmp->current.isSelected()){
                    home.setActive(false);
                    credits.setActive(true);
                }
            } else if (!strcmp(tmp->name, "settings") && tmp->current.handle()){
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
                if (tmp->current.isSelected()){
                    home.setActive(false);
                    settings.setActive(true);
                }
            } else if (!strcmp(tmp->name, "exit") && tmp->current.handle()){
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
                if (tmp->current.isSelected()){
                    this->src->getWindow()->close();
                }
            }
            tmp = tmp->next;
        }
    } else if (settings.getActive()){
        settings.draw();
        lista_pulsanti *tmp1 = settings.getButtons();
        sliderList *tmp2 = settings.getSliders();
        while (tmp1 != NULL){
            if (!strcmp(tmp1->name, "back") && tmp1->current.handle()){
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
                if (tmp1->current.isSelected()){
                    settings.setActive(false);
                    home.setActive(true);
                }
            }
            tmp1 = tmp1->next;
        }
        while (tmp2 != NULL){
            if (!strcmp(tmp2->name, "acceleration")){
                universe.player.setSpaceshipAcceleration(tmp2->current.getSliderValue());
            }
            if (!strcmp(tmp2->name, "max_speed")){
                universe.player.setTopSpeed(tmp2->current.getSliderValue());
            }
            tmp2 = tmp2->next;
        }
    } else if (credits.getActive()){
        credits.draw();
        lista_pulsanti *tmp = credits.getButtons();
        while (tmp != NULL){
            if (!strcmp(tmp->name, "back") && tmp->current.handle()){
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
                if (tmp->current.isSelected()){
                    credits.setActive(false);
                    home.setActive(true);
                }
            }
            tmp = tmp->next;
        }
    } else if (pause.getActive()){
        pause.draw();
        lista_pulsanti *tmp = pause.getButtons();
        while (tmp != NULL){
            if (!strcmp(tmp->name,"resume") && tmp->current.handle()){
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
                if (tmp->current.isSelected()){
                    pause.setActive(false);
                    game.setActive(true);
                    if (universe.player.getAtPlanet()){
                        bunkerlist *tmp = universe.getActive()->pianeti.getCurrent()->interno.getCurrent()->enemies.getHead();
                        while (tmp != NULL){
                            tmp->weapon->bullet_time.restart();
                            tmp = tmp->next;
                        }
                    }
                }
            }
            if (!strcmp(tmp->name, "back_to_menu") && tmp->current.handle()){
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
                if (tmp->current.isSelected()){
                    universe = Universe(this->src);
                    pause.setActive(false);
                    home.setActive(true);
                }
            }
            tmp = tmp->next;
        }
    } else if (game_over.getActive()){
        game_over.draw();
        lista_pulsanti *tmp = game_over.getButtons();
        while (tmp != NULL){
            if (!strcmp(tmp->name,"back") && tmp->current.handle()){
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
                if (tmp->current.isSelected()){
                    universe = Universe(this->src);
                    game_over.setActive(false);
                    home.setActive(true);
                }
            }
            tmp = tmp->next;
        }
    } else if (game.getActive()){
        if (!universe.player.getIsDead()){
            
            universe.handle();
            
            /// UNIVERSO
            
            if (!universe.player.getAtPlanet()) {
                this->src->getWindow()->draw(universe.background);
                universe.disegnaPianeti();
            }
            
            /// PIANETA
            
            if (universe.player.getAtPlanet()){
                universe.getActive()->pianeti.handle(&universe.player);
                if (universe.player.getAtPlanet()) {
                    universe.player.armi(&universe.getActive()->pianeti.getCurrent()->interno.getCurrent()->terrain);
                    universe.player.raggioTraente();
                    universe.checkTerrain();
                }
            }
            src->getWindow()->draw(universe.player.thrust);
            src->getWindow()->draw(universe.player.nave);
            universe.hud.gestisci(universe.player.getPunti(), universe.player.getLifebar(), universe.player.getFuelbar());
            universe.player.gestisci();
        } else {
            game_over.setActive(true);
            game.setActive(false);
        }
        Image a;
        lista_pulsanti *tmp = game.getButtons();
        while (tmp != NULL){
            tmp->current.disegna();
            if (tmp->current.handle() || Keyboard::isKeyPressed(Keyboard::Escape)){
                game.setActive(false);
                pause.setActive(true);
                Texture tmp;
                tmp.create(src->getWindow()->getSize().x, src->getWindow()->getSize().y);
                tmp.update(*src->getWindow());
                a = tmp.copyToImage();
                tmp_background->update(a);
                pause.sfondo.setTexture(*tmp_background);
                pause.sfondo.setColor(Color(128,128,128));
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
            }
            tmp = tmp->next;
        }
    }
    src->handleAnimation();
}
    
