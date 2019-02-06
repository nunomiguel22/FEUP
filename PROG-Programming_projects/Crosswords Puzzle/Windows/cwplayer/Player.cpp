/*Turma 8, Grupo 1, Trabalho 2 Parte 2(cwplayer)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araújo Ferreira
*/

#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iomanip>
#include "Player.h"
#include "Console.h"
#include <chrono>

void Player::setName(string cName) {
	Player::name = cName;
}

string Player::getName() {
	return Player::name;
}

int Player::getAlternativeClues() {
	return Player::altClues;
}

double Player::getElapsedTime() {
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
	Player::elapsedTime = ((double)Player::end - Player::start);
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
	Console console;
	if (Player::altClues <= 5) {
		console.setcolor(GREEN);
		cout << "Alternative Clues: " << Player::altClues << endl;
		console.setcolor(WHITE);
	}
	else {
		if (Player::altClues <= 10) {
			console.setcolor(YELLOW);
			cout << "Alternative Clues: " << Player::altClues << endl;
			console.setcolor(WHITE);
		}
		else {
			console.setcolor(RED);
			cout << "Alternative Clues: " << Player::altClues << endl;
			console.setcolor(WHITE);
		}
	}




}