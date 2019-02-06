/*Turma 8, Grupo 1, Trabalho 2 Parte 1(cwcreator)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araújo Ferreira
*/

#include "Verifications.h"

using namespace std;


//Return whether the word is a simple word(A-Z) or not
bool simpleWord(string word) {

	if (word.empty())
		return false;

	for (size_t i = 0; i < word.length(); i++) {
		if (word[i] < 'A' || word[i] > 'Z')
			return false;
	}
	return true;
}

//Return whether the word exists in valid word list of the dictionary or not
bool dictionaryWord(string word, vector<vector <string>> v1) {

	for (size_t i = 0; i < v1.size(); i++) {
		if (word == v1.at(i).at(0))
			return true;
	}
	return false;
}

//Return whether the word already exists on the board or not
bool existingWord(vector<vector <string>> v1, string word) {

	for (size_t i = 0; i < v1.size(); i++) {
		if (word == v1.at(i).at(1))
			return true;
	}
	return false;
}

//Return whether the word fits the board or not
bool wordFitsBoard(int x, int y, string posDir, int wordLength) {

	int startingX = posDir[1] - 97;
	int startingY = posDir[0] - 65;

	if (posDir[2] == 'V' && (startingY + wordLength > y)) {
		return false;
	}
	if (posDir[2] == 'H' && (startingX + wordLength > x))
		return false;

	return true;
}

//Return whether the position and direction string is in the correct format or not
bool correctPosDir(string posDir, int x, int y) {

	if (posDir.size() > 3 || posDir.empty())
		return false;

	if (posDir[0] < 'A' || posDir[0] > y + 64 || posDir[1] < 'a' || posDir[1] > x + 96 || (posDir[2] != 'H' && posDir[2] != 'V'))
		return false;
	return true;
}

//Return whether all the user inputs are correct or not
bool correctUserInputs(vector<vector<string>> userInputs, dictionary d1) {

	vector<vector<string>> tempDictionary = d1.returnWordList();
	bool result;

	cout << "Verifying if all word on the board are valid ..." << endl;

	for (size_t i = 0; i < userInputs.size(); i++) {
		for (size_t j = 0; j < tempDictionary.size(); j++) {
			if (userInputs.at(i).at(1) == tempDictionary.at(j).at(0)) {
				result = true;
				break;
			}
			else result = false;
		}
		if (result == false)
			return false;
	}
	return true;
}