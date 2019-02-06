/*Turma 8, Grupo 1, Trabalho 2 Parte 2(cwplayer)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araújo Ferreira
*/

#include "Player.h"
#include <chrono>

Player::Player(){
    Player::name = "";
    Player::altClues = 0;
    Player::elapsedTime = 0;
}

void Player::setName(string cName) {
    Player::name = cName;
}

string Player::getName() {
    return Player::name;
}

int Player::getAlternativeClues(){
    return Player::altClues;
}

double Player::getElapsedTime(){
    Player::updateEndTime();
    Player::updateElapsedTime();
    return Player::elapsedTime;
}

void Player::updateStartTime() {
    auto startT = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(startT);
    Player::start = start_time;
}

void Player::printStartTime() {
    cout << put_time(localtime(&(Player::start)), "%F %H:%M:%S");
}

void Player::updateEndTime() {
    auto endT = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(endT);
    Player::end = end_time;
}

void Player::printEndTime() {
    cout << put_time(localtime(&(Player::end)), "%F %H:%M:%S");
}

void Player::updateElapsedTime() {
    Player::elapsedTime = (Player::end - Player::start);
}

void Player::incrementAltClues() {
    Player::altClues++;
}

void Player::printElapsedInSeconds() {
    Player::updateEndTime();
    Player::updateElapsedTime();
    cout << Player::elapsedTime << "s";
}

void Player::printAlternativeClues() {
    if(Player::altClues <= 5){
        cout << GREEN << "Alternative Clues: " << Player::altClues << NO_COLOR << endl;
    } else {
        if(Player::altClues <= 10){
            cout << YELLOW << "Alternative Clues: " << Player::altClues << NO_COLOR << endl;
        } else {
            cout << RED << "Alternative Clues: " << Player::altClues << NO_COLOR << endl;
        }
    }




}