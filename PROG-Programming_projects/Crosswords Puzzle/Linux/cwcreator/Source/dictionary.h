/*Turma 8, Grupo 1, Trabalho 2 Parte 1(cwcreator)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araújo Ferreira
*/

#pragma once
#include <vector>
#include <string>
#include <iostream>

//dictionary.cpp
class dictionary {
public:

	dictionary(std::string filename);
	void buildList();
	bool wildcardMatch(const char *str, const char *strWild);
	std::vector<std::string> suggested(std::string posDir, std::vector<std::vector<char>> b1);
	std::string wordPrep(std::string word);
	std::vector <std::vector<std::string>> returnWordList();
	std::string returnFilename();

private:
	std::string file;
	std::string word;
	std::vector <std::vector<std::string>> wordList;
};

