/*Turma 8, Grupo 1, Trabalho 2 Parte 1(cwcreator)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araújo Ferreira
*/

#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "dictionary.h"

//verifications.cpp
bool correctUserInputs(std::vector<std::vector<std::string>> userInputs, dictionary d1);
bool correctPosDir(std::string posDir, int x, int y);
bool wordFitsBoard(int x, int y, std::string posDir, int wordLength);
bool existingWord(std::vector<std::vector <std::string>> v1, std::string word);
bool dictionaryWord(std::string word, std::vector<std::vector <std::string>> v1);
bool simpleWord(std::string word);