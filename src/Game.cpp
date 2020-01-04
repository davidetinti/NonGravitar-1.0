#include "Game.hpp"

Game::Game(){
    
}

Game::Game(Resources *src){
    this->src = src;
    this->hud = HUD(src);
    highscore_st = Highscore(src);
    tmp_background = src->caricaTexture(36);
    universe = new Universe(src);
    home = new Stage(src, 25);
    settings = new Stage(src, 35);
    credits = new Stage(src, 26);
    highscore = new Stage(src, 27);
    game = new Stage(src, 28);
    pause = new Stage(src, 36);
    game_over = new Stage(src, 41);
    home->addButton(Vector2f(330,450), 23, 0.45, (char*)"1_game");
    home->addButton(Vector2f(950,450), 37, 0.45, (char*)"4_highscore");
    home->addButton(Vector2f(170,650), 34, 0.25, (char*)"3_settings");
    home->addButton(Vector2f(1110,650), 21, 0.25, (char*)"2_credits");
    settings->addButton(Vector2f(640,650), 24, 0.25, (char*)"5_back");
    settings->addSlider(Vector2f(364, 290), 0.025, 0.1, (char*)"A_acceleration");
    settings->addSlider(Vector2f(364, 421), 3, 7, (char*)"B_max_speed");
    settings->addSlider(Vector2f(363, 552), 0, 0, (char*)"C_difficulty");
    String str_credits = String("DEVELOPED BY:\n\n- DAVIDE TINTI\n- PAOLO MARZOLO\n- MATTEO FEROLI");
    credits->addText(Vector2f(430,250), str_credits, Color::Black, Color::White, 40, 1);
    credits->addButton(Vector2f(640,650), 24, 0.25, (char*)"5_back");
    highscore->addButton(Vector2f(640,650), 24, 0.25, (char*)"5_back");
    game->addButton(Vector2f(1150,50), 39, 0.20, (char*)"7_pause");
    pause->addButton(Vector2f(330,450), 40, 0.45, (char*)"1_resume");
    pause->addButton(Vector2f(950,450), 38, 0.45, (char*)"6_back_to_menu");
    pause->getBackground()->setColor(Color(128,128,128));
    points = game_over->addText(Vector2f(260, 360), to_string(10000),
                                Color::White, Color::Black, 60, 1);
    highscore_st.setTextScore(points);
    highscore_st.setTextPlayer(game_over->addText(Vector2f(880, 360), to_string(10000),
                                                  Color::White, Color::Black, 60, 1));
    active = home;
}

void Game::handleStageControls(){
    for (Pulsante* button : *active->getButtonsList()){
        if (button->isSelected() && Mouse::isButtonPressed(Mouse::Left)) {
            while (Mouse::isButtonPressed(Mouse::Left)){
                
            }
            if (button->isSelected()){
                switch (*button->getName()) {
                    default:
                        break;
                    case '1':
                        active = game;
                        break;
                    case '2':
                        active = credits;
                        break;
                    case '3':
                        active = settings;
                        break;
                    case '4':
                        active = highscore;
                        break;
                    case '5':
                        active = home;
                        break;
                    case '6':
                        universe = new Universe(this->src);
                        active = home;
                        break;
                    case '7':
                        active = pause;
                        break;
                }
            }
        }
    }
    for (Slider* slider : *active->getSliderList()){
        slider->logic();
        switch (*slider->getName()) {
                // SETTINGS - A_acceleration
            case 'A':
                universe->player.setSpaceshipAcceleration(slider->getSliderValue());
                break;
                // SETTINGS - B_max_speed
            case 'B':
                universe->player.setTopSpeed(slider->getSliderValue());
                break;
                // SETTINGS - C_difficulty
            case 'C':
                //... TODO
                break;
            default:
                break;
        }
    }
}

void Game::updateScore(){
    points->setString(to_string(universe->player.getPunti()));
    points->setPosition(370 - points->getLocalBounds().width/2, 360);
}

void Game::handle(){
    active->drawBackground();
    handleStageControls();
    if (active == game){
        if (!universe->player.getIsDead()){
            universe->handle();
            hud.gestisci(universe->player.getPunti(),
                         universe->player.getLifebar(),
                         universe->player.getFuelbar());
        } else {
            updateScore();
            active = game_over;
        }
    }
    if (active == highscore){
        highscore_st.draw();
    }
    if (active == game_over){
        if (highscore_st.insert()){
            active = home;
            universe = new Universe(this->src);
        }
    }
    src->handleAnimation();
    active->drawObjects();
}
