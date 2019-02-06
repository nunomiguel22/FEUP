/*Turma 8, Grupo 1, Trabalho 2 Parte 2(cwplayer)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araújo Ferreira
*/

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Console.h"

using namespace std;

class FileManager {
private:
	fstream file;
	string line;
	Console console;
	vector<string> fileLines;
	int actualLine = 0;
	bool endOfLines = false;

public:
	FileManager();
	FileManager(string fileName);
	void convFileToVector();
	bool hasMoreLines();
	string getNextLine();
	vector<string> getAllLines();
	void setFile(string fileName);
	bool isOpen();
	void printOnScreen();
	//void printBoard();
	void closeFileStream();
	//aux functions
	string trimSpaces(string s);
	vector<string> explode(char c, string s);
	int save(string filename, string playerScore);
};

