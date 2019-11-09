#include "Highscore.hpp"

Highscore::Highscore(){
    
}

Highscore::Highscore(Resources *src){
    this->src = src;
    int i = 0;
    string line;
    file.open("./../resources/highscore", fstream::in | fstream::out);
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
    Event event;
    if (player_name.length() < 7 && Keyboard::isKeyPressed(Keyboard::Key::A)){
        //if (event.key.code == Keyboard::Key::A){
            player_name.append("A");
            cout << "PREMUTO A";
        //}
    }
    if (Keyboard::isKeyPressed(Keyboard::Key::S)){
        //if (event.key.code == Keyboard::Key::A){
        player_name.pop_back();
        cout << "PREMUTO A";
        //}
    }
    player->setString(player_name);
    player->setPosition(880 - player->getLocalBounds().width/2, 360);
    if (Keyboard::isKeyPressed(Keyboard::Key::Enter)){
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
