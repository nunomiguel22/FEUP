/*Turma 8, Grupo 1, Trabalho 2 Parte 1(cwcreator)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araújo Ferreira
*/

/*                       BOARD METHODS                               */

#include "Board.h"

using namespace std;

//New puzzle contructor
board::board(int xcoor, int ycoor) {
	x = xcoor;
	y = ycoor;
}

//Reloaded puzzle contructor
board::board(vector<string> v1) { savedContents = v1; }

//Return functions
int board::retX() { return x; }
int board::retY() { return y; }
vector<vector<char>> board::returnWordTable() { return wordTable; }
std::vector<std::vector<string>> board::returnUserInputs() { return savedUserInputs; }

//Load Board from file to char vector used for board construction
void board::reloadBoard() {

	string line;
	string wordTemp;

	//Get number of lines and columns of saved board
	for (size_t i = 2; i < savedContents.size(); i++)
		if (savedContents.at(i).empty())
			y = i - 2;
	x = savedContents.at(2).length() / 2;
	create();

	//Reload board using saved user inputs
	for (size_t i = 0; i < savedUserInputs.size(); i++) {
		string posDir = savedUserInputs.at(i).at(0);
		string word = savedUserInputs.at(i).at(1);

		alter(posDir, word);
	}
	show();
}

//Load user inputs from file to 2D string vector
void board::reloadUserInputs() {

	string tempWord;
	vector<string> tempWordVector;
	unsigned int spaceCounter = 0;
	unsigned int startingPos;

	//Get the starting position of the user inputs segment of the file
	for (size_t i = 0; i < savedContents.size(); i++) {
		if (savedContents.at(i).empty())
			spaceCounter++;
		if (spaceCounter == 2) {
			startingPos = ++i;
			break;
		}
	}

	//Load user inputs to 2D vector
	for (size_t i = startingPos; i < savedContents.size(); i++) {
		for (size_t j = 0; j < savedContents.at(i).length(); j++) {
			if (j == savedContents.at(i).length() - 1) {
				tempWord = tempWord + savedContents.at(i)[j];
				tempWordVector.push_back(tempWord);
				tempWord = "";
				break;
			}

			if (savedContents.at(i)[j] != ' ')
				tempWord = tempWord + savedContents.at(i)[j];
			else {

				tempWordVector.push_back(tempWord);
				tempWord = "";

			}
		}
		savedUserInputs.push_back(tempWordVector);
		tempWordVector.resize(0);
	}
}

//Create initial board, with x for columns and y for lines
void board::create() {

	//Resize char vector to adequate size and fill with dots
	wordTable.resize(y + 1);
	for (int i = 0; i <= y; i++) {
		wordTable[i].resize(x + 1);
		fill(wordTable[i].begin(), wordTable[i].end(), '.');

	}

	wordTable[0][0] = ' '; //First cell of the board is empty

	//Load vertical and horizontal headlines
	for (unsigned int j = 1; j < wordTable[0].size(); j++) {
		wordTable[0][j] = 96 + j;
	}
	for (unsigned int i = 1; i < wordTable.size(); i++) {
		wordTable[i][0] = 64 + i;
	}
}

//Place words on the board char vector
bool board::alter(string position, string word) {

	int startingY = position[0] - 64; //Line where the first letter will be located on the char vector
	int startingX = position[1] - 96; //Column where the first letter will be located on the char vector
	Console console;

	//If the operation was to delete a word or ask for suggestions, do nothing
	if (word == "-" || word == "?")
		return false;

	/*If the word does not conflict with other words on the board, or goes out of bounds of the board,
		place word on char vector using black cells('#') when necessary
	*/
	if (!wordMatch(position, word)) {
		console.setcolor(LIGHTRED);
		cout << endl << "Word does not match with existing words" << endl;
		console.setcolor(WHITE);
		return false;
	}
	else {
		if (position[2] == 'V') {
			if (wordTable[startingY - 1][startingX] == '.')
				wordTable[startingY - 1][startingX] = '#';

			if (startingY + word.length() < wordTable.size())
				if (wordTable[startingY + word.length()][startingX] == '.')
					wordTable[startingY + word.length()][startingX] = '#';


			for (unsigned int i = 0; i < word.length(); i++) {
				wordTable[i + startingY][startingX] = word[i];
			}
		}
		else {

			if (wordTable[startingY][startingX - 1] == '.')
				wordTable[startingY][startingX - 1] = '#';

			if (startingX + word.length() < wordTable[0].size())
				if (wordTable[startingY][startingX + word.length()] == '.')
					wordTable[startingY][startingX + word.length()] = '#';


			for (unsigned int j = 0; j < word.length(); j++) {
				wordTable[startingY][startingX + j] = word[j];
			}
		}
	}
	return true;
}

//Print the board, using the char vector with the board contents and the correct colors
void board::show() {
	Console console;
	console.setcolor(LIGHTRED, BLACK);
	cout << endl << " "; //start by printing a space to align horizontal and vertical headline

	//Print horizontal headline
	for (size_t j = 0; j < wordTable[0].size(); j++)
		cout << wordTable[0][j] << " ";
	cout << endl;

	//Print rest of the board
	for (unsigned int i = 1; i < wordTable.size(); i++) {

		console.setcolor(LIGHTRED, BLACK);
		cout << wordTable[i][0] << " ";
		console.setcolor(BLACK, WHITE);

		for (unsigned int j = 1; j < wordTable[i].size(); j++) {
			cout << " ";
			if (wordTable[i][j] == '#')
				console.setcolor(LIGHTGRAY, BLACK);
			else console.setcolor(BLACK, WHITE);

			cout << wordTable[i][j];
			console.setcolor(BLACK, WHITE);
		}
		cout << " ";
		cout << endl;
	}
	console.setcolor(WHITE, BLACK);
}

//Return whether the board is full or not
bool board::full() {

	//If there is a '.' in the board vector the table is not yet full
	for (unsigned int i = 1; i < wordTable.size(); i++)
		for (unsigned int j = 1; j < wordTable.at(i).size(); j++)
			if (wordTable.at(i).at(j) == '.')
				return false;
	return true;
}

//Return whether the word matches with existing words on the board or not
bool board::wordMatch(string position, string word) {

	int startingY = position[0] - 64;
	int startingX = position[1] - 96;

	if (position[2] == 'V') {
		if (wordTable.at(startingY - 1).at(startingX) != '.' && startingY - 1 != 0 && wordTable.at(startingY - 1).at(startingX) != '#')
			return false;

		for (unsigned int i = 0; i < word.length(); i++) {
			if (wordTable.at(i + startingY).at(startingX) != word[i] && (wordTable.at(i + startingY).at(startingX) != '.'))
				return false;
		}
	}
	else {
		if (wordTable.at(startingY).at(startingX - 1) != '.' && startingX - 1 != 0 && wordTable.at(startingY).at(startingX - 1) != '#')
			return false;

		for (unsigned int j = 0; j < word.length(); j++) {
			if (wordTable.at(startingY).at(startingX + j) != word[j] && wordTable.at(startingY).at(startingX + j) != '.')
				return false;
		}
	}
	return true;
}

//Finish incomplete board by filling it the dots with black cells
void board::finish() {
	for (size_t i = 1; i < wordTable.size(); i++)
		for (size_t j = 1; j < wordTable.at(i).size(); j++) {
			if (wordTable.at(i).at(j) == '.')
				wordTable.at(i).at(j) = '#';
		}
}

//Delete word from board
void board::del(vector<vector<string>> delUserInputs) {
	savedUserInputs = delUserInputs;
	if (savedUserInputs.empty()) {
		create();
		show();
	}
	else {
		create();

		//Reload board using saved user inputs
		for (size_t i = 0; i < savedUserInputs.size(); i++) {
			string posDir = savedUserInputs.at(i).at(0);
			string word = savedUserInputs.at(i).at(1);

			alter(posDir, word);
		}

		show();
	}

}

