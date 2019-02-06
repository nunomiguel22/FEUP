/*Turma 8, Grupo 1, Trabalho 2 Parte 1(cwcreator)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araújo Ferreira
*/

/*                       DICTIONARY METHODS                               */
#include "dictionary.h"
#include <fstream>
#include "console.h"

using namespace std;

//Dictionary constructor
dictionary::dictionary(string filename) {
	file = filename;
}

//Return the valid word list
vector <vector <string>> dictionary::returnWordList() {
	return dictionary::wordList;
}

//Return capitalized word with no spaces
string dictionary::wordPrep(string word) {

	if (word == " ")
		return word;

	for (size_t i = 0; i < word.length(); i++)
		word[i] = toupper(word[i]);

	return word;
}

//Return the dictionary filename
std::string dictionary::returnFilename() {
	return file;
}

//Build list with all valid words from the given dictionaryk
void dictionary::buildList() {

	ifstream dict;
	ofstream saveFile;
	string line;
	string wordTemp;
	Console console;

	dict.open(file);
	while (!dict.is_open()) {
		console.setcolor(LIGHTRED);
		cout << endl << "Dictionary not found" << endl << endl;
		console.setcolor(WHITE);
		cout << "Dictionary file name ? ";
		if (cin.eof()) 
			cin.clear();
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		getline(cin, file);
		dict.open(file);
		cout << endl;
	}
	while (getline(dict, line)) {
		vector <string> temp;
		//Separate words in every line and add to list if the word is valid
		for (size_t i = 0; i < line.length(); i++) {
			if (line[i] != ':' && i != line.length() - 1)
				wordTemp += line[i];
			else {
				wordTemp = wordPrep(wordTemp);
				temp.push_back(wordTemp);
				wordTemp = "";
				i++;
			}
		}
		wordList.push_back(temp);
	}
	dict.close();
}

//Return vector with the suggested words that fit the given position
vector<string> dictionary::suggested(string posDir, vector<vector<char>> b1) {

	string wildcardWord;
	int startingY = posDir[0] - 64; //Line where the first letter will be located on the char vector
	int startingX = posDir[1] - 96; //Column where the first letter will be located on the char vector
	vector<string> suggestedList;
	string tempWord;

	//Create the wildcard word
	if (posDir[2] == 'V') {
		for (size_t i = startingY; i < b1.size(); i++) {
			if (b1.at(i).at(startingX) == '#')
				break;
			if (b1.at(i).at(startingX) == '.')
				wildcardWord += '?';
			else (wildcardWord += b1.at(i).at(startingX));
		}
	}
	else {
		for (size_t j = startingX; j < b1.at(startingY).size(); j++) {
			if (b1.at(startingY).at(j) == '#')
				break;
			if (b1.at(startingY).at(j) == '.')
				wildcardWord += '?';
			else (wildcardWord += b1.at(startingY).at(j));
		}
	}

	//Return empty vector if there is already a completed word on the board, on the given position
	if (wildcardWord.find('?') == wildcardWord.npos)
		return suggestedList;

	//Check all the words that fit the wildcard term in the dictionary
	for (size_t i = 0; i < wildcardWord.length(); i++) {

		if (i != wildcardWord.length() - 1)
			if (wildcardWord[i + 1] != '?') {
				tempWord = "";
				continue;
			}
		for (size_t j = 0; j <= i; j++)
			tempWord += wildcardWord[j];

		for (size_t k = 0; k < wordList.size(); k++) {
			if (wildcardMatch(&wordList.at(k).at(0)[0], &tempWord[0])) {
				suggestedList.push_back(wordList.at(k).at(0));
			}
		}
		tempWord = "";
	}

	return suggestedList;
}

//Wildcard matching function from project 1
bool dictionary::wildcardMatch(const char *str, const char *strWild) {

	while (*strWild) {
		if (*strWild == '?') {

			if (!*str)
				return false;

			++str;
			++strWild;
		}
		else if (*strWild == '*') {

			if (wildcardMatch(str, strWild + 1))
				return true;

			if (*str && wildcardMatch(str + 1, strWild))
				return true;
			return false;
		}
		else {

			if (toupper(*str++) != toupper(*strWild++))
				return false;
		}
	}
	return !*str && !*strWild;
}