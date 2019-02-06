/*Turma 8, Grupo 1, Trabalho 2 Parte 2(cwplayer)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araújo Ferreira
*/

#pragma once

#include <iostream>
#include <string>

using namespace std;

class Player {
private:
	string name = "";
	time_t start;
	time_t end;
	int altClues = 0;
	double elapsedTime = 0;
public:
	void setName(string cName);
	string getName();
	int getAlternativeClues();
	double getElapsedTime();
	void incrementAltClues();
	void printAlternativeClues();
	void updateStartTime();
	void printStartTime();
	void updateEndTime();
	void printEndTime();
	void updateElapsedTime();
	void printElapsedInSeconds();
};

