/*Turma 8, Grupo 1, Trabalho 2 Parte 1(cwcreator)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araújo Ferreira
*/

#pragma once
#include "console.h"
#include <vector>
#include <string>
#include <iostream>

//board.cpp
class board {
public:

	board(int xcoor, int ycoor);
	board(std::vector<std::string> v1);

	bool full();
	bool wordMatch(std::string position, std::string word);

	void create();
	void reloadBoard();
	void reloadUserInputs();
	bool alter(std::string position, std::string word);
	void del(std::vector<std::vector<std::string>> userInputs);
	void show();
	void finish();

	std::vector<std::vector<std::string>> returnUserInputs();
	std::vector<std::vector<char>> returnWordTable();
	int retX();
	int retY();

private:
	int x, y;
	std::vector <std::vector<char>> wordTable;
	std::vector<std::string> savedContents;
	std::vector<std::vector<std::string>> savedUserInputs;
};