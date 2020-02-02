#include "Highscore.hpp"

Highscore::Highscore(){
    
}

Highscore::Highscore(Resources *src){
    this->src = src;
    int i = 0;
    string line;
    file.open("./../resources/highscore", fstream::in | fstream::out);
    if (!file.is_open()){
        ofstream newfile {"./../resources/highscore"};
        newfile << "#1" << endl << "---" << endl << 0 << endl
                << "#2" << endl << "---" << endl << 0 << endl
                << "#3" << endl << "---" << endl << 0 << endl;
        newfile.close();
        file.open("./../resources/highscore", fstream::in | fstream::out);
    }
    getline(file,line);
    while (!file.eof()) {
        ScoreRow* row = new ScoreRow;
        if (!file.eof()){
            row->rank = Text(line, *src->getFont(1));
            row->rank.setFillColor(Color::White);
            row->rank.setOutlineColor(Color::Black);
            row->rank.setCharacterSize(40);
            row->rank.setOutlineThickness(1);
            row->rank.setPosition(235, 340 + 90*i);
            getline(file,line);
        }
        if (!file.eof()){
            row->name = Text(line, *src->getFont(1));
            row->name.setFillColor(Color::White);
            row->name.setOutlineColor(Color::Black);
            row->name.setCharacterSize(40);
            row->name.setOutlineThickness(1);
            row->name.setPosition(640 - row->name.getLocalBounds().width/2, 340 + 90*i);
            getline(file,line);
        }
        if (!file.eof()){
            row->score = Text(line, *src->getFont(1));
            row->score.setFillColor(Color::White);
            row->score.setOutlineColor(Color::Black);
            row->score.setCharacterSize(40);
            row->score.setOutlineThickness(1);
            row->score.setPosition(990 - row->score.getLocalBounds().width/2, 340 + 90*i);
            getline(file,line);
        }
        i++;
        scores.push_back(row);
    }
    file.close();
}

void Highscore::setTextPlayer(Text* text){
    player = text;
}

void Highscore::setTextScore(Text* text){
    score = text;
}

void Highscore::draw(){
    for (ScoreRow* row : scores){
        src->getWindow()->draw(row->rank);
        src->getWindow()->draw(row->name);
        src->getWindow()->draw(row->score);
    }
}

bool Highscore::insert(){
    int input = src->getLastInput();
    if (input != NULL){
        if (input == 8 && !player_name.empty()) {
            player_name.pop_back();
        } else if (player_name.length() < 6 && input > 32 && input < 127) {
            player_name += static_cast<char>(input);
        }
        src->setLastInput(NULL);
    }
    player->setString(player_name);
    player->setPosition(880 - player->getLocalBounds().width/2, 360);
    if (Keyboard::isKeyPressed(Keyboard::Key::Return)){
        checkNewScore(player,score);
        return true;
    }
    return false;
}

void Highscore::checkNewScore(Text* player, Text* score){
    list<ScoreRow*>::iterator it = scores.begin();
    list<ScoreRow*>::iterator end = scores.end();
    int score_i = stoi((string)score->getString());
    int i = 0;
    bool new_high = it == end;
    while (!new_high && it != end){
        if (score_i > stoi((string)(*it)->score.getString())){
            new_high = true;
            // TODO: remove cout << "DETECTED NEW HIGH SCORE";
            cout << "DETECTED NEW HIGH SCORE";
            i++;
        } else {
            i++;
            it++;
        }
    }
    if (new_high){
        ScoreRow* newscore = new ScoreRow;
        newscore->name = (*it)->name;
        newscore->name.setString(player->getString());
        newscore->rank = (*it)->rank;
        newscore->score = (*it)->score;
        newscore->score.setString(score->getString());
        scores.insert(it, newscore);
        while (it != end){
            (*it)->rank.setString("#" + to_string(i+1));
            (*it)->rank.move(0, 90);
            (*it)->name.setPosition(640 - (*it)->name.getLocalBounds().width/2, 340 + 90*i);
            (*it)->score.setPosition(990 - (*it)->score.getLocalBounds().width/2, 340 + 90*i);
            it++;
            i++;
        }
        while (scores.size() > 3) scores.pop_back();
        file.open("./../resources/highscore", fstream::in | fstream::out | fstream::trunc);
        it = scores.begin();
        while (it != end){
            file << (string)(*it)->rank.getString() << "\n";
            file << (string)(*it)->name.getString() << "\n";
            file << (string)(*it)->score.getString() << "\n";
            it++;
        }
        file.close();
    }
}
