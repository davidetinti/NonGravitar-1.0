#include "pch.h"
#include "Game.hpp"

Game::Game(){
    
}

Game::Game(Resources *src){
    this->src = src;
    tmp_background = this->src->caricaTexture(36);
    universe = new Universe(this->src);
    home = new Stage(this->src, 25);
    settings = new Stage(this->src, 35);
    credits = new Stage(this->src, 26);
    highscore = new Stage(this->src, 27);
    game = new Stage(this->src, 28);
    pause = new Stage(this->src, 36);
    game_over = new Stage(this->src, 41);
    home->addButton(Vector2f(330,450), 23, 0.45, (char*)"game");
    home->addButton(Vector2f(950,450), 37, 0.45, (char*)"highscore");
    home->addButton(Vector2f(170,650), 34, 0.25, (char*)"settings");
    home->addButton(Vector2f(1110,650), 21, 0.25, (char*)"credits");
    settings->addButton(Vector2f(640,650), 24, 0.25, (char*)"back");
    settings->addSlider(Vector2f(364, 290), 0.025, 0.1, (char*)"acceleration");
    settings->addSlider(Vector2f(364, 421), 3, 7, (char*)"max_speed");
    settings->addSlider(Vector2f(363, 552), 0, 0, (char*)"difficulty");
    credits->addButton(Vector2f(640,650), 24, 0.25, (char*)"back");
    credits->addText(Vector2f(430,250), "DEVELOPED BY:\n\n- DAVIDE TINTI\n- PAOLO MARZOLO\n- MATTEO FEROLI", Color::Black, Color::White, 40, 1);
    highscore->addButton(Vector2f(640,650), 24, 0.25, (char*)"back");
    game->addButton(Vector2f(1150,50), 39, 0.20, (char*)"pause");
    pause->addButton(Vector2f(330,450), 40, 0.45, (char*)"resume");
    pause->addButton(Vector2f(950,450), 38, 0.45, (char*)"back_to_menu");
    game_over->addButton(Vector2f(640,650), 24, 0.25, (char*)"back");
    game_over->addText(Vector2f(300, 250), "YOUR SCORE IS: ", Color::Red, Color::Black, 60, 1);
    home->setActive(true);
}

void Game::handle(){
    if (home->getActive()){
        home->draw();
        for (Pulsante* button : *home->getButtonsList()){
            if (button->isSelected() && Mouse::isButtonPressed(Mouse::Left)) {
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
                if (button->isSelected()){
                    switch (*button->getName()) {
                            // game
                        case 'g':
                            home->setActive(false);
                            game->setActive(true);
                            break;
                            // credits
                        case 'c':
                            home->setActive(false);
                            credits->setActive(true);
                            break;
                            // settings
                        case 's':
                            home->setActive(false);
                            settings->setActive(true);
                            break;
                            // highscore
                        case 'h':
                            home->setActive(false);
                            highscore->setActive(true);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    } else if (settings->getActive()){
        settings->draw();
        for (Pulsante* button : *settings->getButtonsList()){
            if (button->isSelected() && Mouse::isButtonPressed(Mouse::Left)) {
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
                if (button->isSelected()){
                    switch (*button->getName()) {
                            // back
                        case 'b':
                            settings->setActive(false);
                            home->setActive(true);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        for (Slider* slider : *settings->getSliderList()){
            slider->logic();
            switch (*slider->getName()) {
                    // acceleration
                case 'a':
                    universe->player.setSpaceshipAcceleration(slider->getSliderValue());
                    break;
                    // max_speed
                case 'm':
                    universe->player.setTopSpeed(slider->getSliderValue());
                    break;
                default:
                    break;
            }
        }
    } else if (credits->getActive()){
        credits->draw();
        for (Pulsante* button : *credits->getButtonsList()){
            if (button->isSelected() && Mouse::isButtonPressed(Mouse::Left)) {
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
                if (button->isSelected()){
                    switch (*button->getName()) {
                            // back
                        case 'b':
                            credits->setActive(false);
                            home->setActive(true);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    } else if (highscore->getActive()){
        highscore->draw();
        for (Pulsante* button : *highscore->getButtonsList()){
            if (button->isSelected() && Mouse::isButtonPressed(Mouse::Left)) {
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
                if (button->isSelected()){
                    switch (*button->getName()) {
                            // back
                        case 'b':
                            highscore->setActive(false);
                            home->setActive(true);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    } else if (game->getActive()){
        game->draw();
        if (!universe->player.getIsDead()){
            
            universe->handle();

            //TODO: move hud to game. why would it be in universe???
            universe->hud.gestisci(universe->player.getPunti(), universe->player.getLifebar(), universe->player.getFuelbar());
            

        } else {
            game_over->setActive(true);
            game->setActive(false);
        }
        for (Pulsante* button : *game->getButtonsList()){
            if ((button->isSelected() && Mouse::isButtonPressed(Mouse::Left))) {
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
                if (button->isSelected()){
                    cout << *button->getName();
                    switch (*button->getName()) {
                            // pause
                        case 'p':
                            game->setActive(false);
                            pause->setActive(true);
                            Texture tmp;
                            tmp.create(src->getWindow()->getSize().x, src->getWindow()->getSize().y);
                            tmp.update(*src->getWindow());
                            //TODO creare un posto nella lista texture da dedicare a quella della pausa
                            //in quanto va sempre sovrascritta od ogni chiamata e non puo essere usata
                            //texture dedica a qualcosaltro
                            Image a = tmp.copyToImage();
                            tmp_background->update(a);
                            pause->getBackground()->setTexture(*tmp_background);
                            pause->getBackground()->setColor(Color(128,128,128));
                            break;
                    }
                }
            }
        }
    } else if (pause->getActive()){
        pause->draw();
        for (Pulsante* button : *pause->getButtonsList()){
            if (button->isSelected() && Mouse::isButtonPressed(Mouse::Left)) {
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
                if (button->isSelected()){
                    switch (*button->getName()) {
                            // back
                        case 'b':
                            universe = new Universe(this->src);
                            pause->setActive(false);
                            home->setActive(true);
                            break;
                            // resume
                        case 'r':
                            pause->setActive(false);
                            game->setActive(true);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    } else if (game_over->getActive()){
        game_over->draw();
        for (Pulsante* button : *game_over->getButtonsList()){
            if (button->isSelected() && Mouse::isButtonPressed(Mouse::Left)) {
                while (Mouse::isButtonPressed(Mouse::Left)){
                    
                }
                if (button->isSelected()){
                    switch (*button->getName()) {
                            // back_to_menu
                        case 'b':
                            universe = new Universe(this->src);
                            game_over->setActive(false);
                            home->setActive(true);
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
    src->handleAnimation();
}
    
