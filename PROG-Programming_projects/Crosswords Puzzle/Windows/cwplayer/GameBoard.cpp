/*Turma 8, Grupo 1, Trabalho 2 Parte 2(cwplayer)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araújo Ferreira
*/

#include "GameBoard.h"

GameBoard::GameBoard(string board, string wordFile) : file(board), dictionary(wordFile) {
	//initialize random seed
	srand((unsigned int)time(NULL));
	GameBoard::file = FileManager(board);
	GameBoard::dictionary = Dictionary(wordFile);
	GameBoard::file.convFileToVector();
	GameBoard::boardLines = GameBoard::file.getAllLines();
	GameBoard::file.closeFileStream();
	GameBoard::processLines();
	GameBoard::getSynonyms();
	GameBoard::getClues();
	GameBoard::boardWidth = GameBoard::boardMatrix[0].size();
	GameBoard::boardHeight = GameBoard::boardMatrix.size();
}

void GameBoard::processLines() {
	string line = "";
	bool boardFlag = false;
	for (unsigned int i = 0; i < GameBoard::boardLines.size(); i++) {
		line = GameBoard::boardLines.at(i);

		if (line.length() == 0) {
			continue;
		}

		//Check if is a solution
		if ((line[0] >= 'A' && line[0] <= 'Z') &&
			(line[1] >= 'a' && line[1] <= 'z') &&
			(line[2] == 'H' || line[2] == 'V')) {
			GameBoard::addSolution(line);
			continue;
		}

		for (unsigned int j = 0; j < line.length(); j++) {
			if (line[j] == '#' ||
				(line[j] >= 'A' && line[j] <= 'Z')) {
				boardFlag = true;
			}
			else {
				boardFlag = false;
				break;
			}

		}
		if (boardFlag) {
			GameBoard::addToBoard(line);
		}

	}
}

void GameBoard::addSolution(string s) {
	string key = "";
	string value = "";
	key += s[0];
	key += s[1];
	key += s[2];

	for (unsigned int i = 3; i < s.length(); i++) {
		value += s[i];
	}

	if (key.length() > 0 && value.length() > 0) {
		GameBoard::solutions.insert(make_pair(key, value));
	}
}

void GameBoard::addToBoard(string s) {
	vector<char> line;
	for (unsigned int i = 0; i < s.length(); i++) {
		if (s[i] == '#') {
			line.push_back(s[i]);
		}
		else {
			line.push_back(' ');
		}
	}
	GameBoard::boardMatrix.push_back(line);
}

void GameBoard::getSynonyms() {
	map<string, string>::iterator it = GameBoard::solutions.begin();
	if (GameBoard::dictionary.isOpen()) {
		while (it != GameBoard::solutions.end()) {
			map <string, vector<string>> aux = GameBoard::dictionary.getMatchedWord(it->second);
			if (!(aux.size() > 0)) {
				GameBoard::error = true;
				cout << "Something went wrong while reading the Dictionary..." << endl;
				cout << "The word: " << it->second << " was not found." << endl;
			}
			GameBoard::synomys.insert(make_pair(aux.begin()->first, aux.begin()->second));
			it++;
		}
	}
}

void GameBoard::getClues() {
	map<string, string>::iterator itSol = GameBoard::solutions.begin();

	while (itSol != GameBoard::solutions.end()) {
		vector<string> s = GameBoard::synomys.at(itSol->second);
		int index = rand() % s.size();

		if (itSol->first[2] == 'H') {
			string pos = "";
			pos += itSol->first[0];
			pos += itSol->first[1];
			GameBoard::horizontals.insert(make_pair(pos, s[index]));
		}

		if (itSol->first[2] == 'V') {
			string pos = "";
			pos += itSol->first[0];
			pos += itSol->first[1];
			GameBoard::verticals.insert(make_pair(pos, s[index]));
		}

		itSol++;
	}

}

bool GameBoard::isGood() {
	return GameBoard::error;
}

bool GameBoard::isFull() {
	for (unsigned int i = 0; i < GameBoard::boardMatrix.size(); i++) {
		for (unsigned int j = 0; j < GameBoard::boardMatrix[i].size(); j++) {
			if (GameBoard::boardMatrix[i][j] == ' ') {
				return false;
			}
		}
	}

	return true;
}

bool GameBoard::isCorrect() {
	return GameBoard::boardCorrect;
}

void GameBoard::updateUserInputs(string direction, string word) {
	string wordUpper = "";
	for (unsigned int i = 0; i < word.length(); i++) {
		wordUpper += toupper(word[i]);
	}

	if (GameBoard::userInputs.find(direction) != GameBoard::userInputs.end()) {
		GameBoard::userInputs.at(direction) = wordUpper;
	}
	else {
		GameBoard::userInputs.insert(make_pair(direction, wordUpper));
	}
}

bool GameBoard::checkIfItisAWord(char direction, int line, int column) {

	string position = "";
	int x = line;
	int y = column;


	while (GameBoard::boardMatrix[line][column] != '#' && GameBoard::boardMatrix[x][y] != ' ') {
		position = "";
		position += (char)(x + 'A');
		position += (char)(y + 'a');
		position += direction;

		auto it = GameBoard::userInputs.find(position);

		if (it != GameBoard::userInputs.end()) {
			return true;
		}

		if ((x == 0 && direction == 'V') || (y == 0 && direction == 'H')) {
			break;
		}

		if (direction == 'H' && y > 0) {
			y--;
		}

		if (direction == 'V' && x > 0) {
			x--;
		}

	}

	return false;
}

int GameBoard::updateBoardHorizontal(string direction, string word, bool insert) {
	int line = (int)direction[0] - (int)'A';
	int column = (int)direction[1] - (int)'a';

	for (unsigned int i = column, j = 0; i < word.length() + column; i++, j++) {

		/**** Remove Word ******/
		if (word == "-") {
			auto it = GameBoard::userInputs.find(direction);

			if (it == GameBoard::userInputs.end()) {
				return 8;
			}

			if (j == it->second.length()) {

				GameBoard::userInputs.erase(it);
				return 0;
			}


			if (line == 0) {
				if (GameBoard::boardMatrix[line + 1][j + column] == '#' ||
					GameBoard::boardMatrix[line + 1][j + column] == ' ') {

					GameBoard::boardMatrix[line][j + column] = ' ';
				}
				else {

					if (GameBoard::checkIfItisAWord(direction[2], line + 1, j + column)) {
						GameBoard::boardMatrix[line][j + column] = ' ';
					}
				}

				i = -1;
				continue;
			}

			if (line == GameBoard::boardHeight - 1) {
				if (GameBoard::boardMatrix[line - 1][j + column] == '#' ||
					GameBoard::boardMatrix[line - 1][j + column] == ' ') {

					GameBoard::boardMatrix[line][j + column] = ' ';
				}
				else {
					if (GameBoard::checkIfItisAWord(direction[2], line - 1, j + column)) {

						GameBoard::boardMatrix[line][j + column] = ' ';
					}
				}

				i = -1;
				continue;
			}

			if ((GameBoard::boardMatrix[line + 1][j + column] == '#' ||
				GameBoard::boardMatrix[line + 1][j + column] == ' ' ||
				GameBoard::checkIfItisAWord(direction[2], line + 1, j + column))
				&&
				(GameBoard::boardMatrix[line - 1][j + column] == '#' ||
					GameBoard::boardMatrix[line - 1][j + column] == ' ' ||
					GameBoard::checkIfItisAWord(direction[2], line - 1, j + column))) {

				GameBoard::boardMatrix[line][j + column] = ' ';

				i = -1;
				continue;
			}
			i = -1;
			continue;
		}


		/***** Insert Word ******/
		if (insert == true) {
			GameBoard::boardMatrix[line][i] = toupper(word[j]);
			if (j == word.length() - 1) {
				GameBoard::updateUserInputs(direction, word);
				return 0;
			}
		}

		/***** Check if the word can be placed *****/

		if (GameBoard::boardMatrix[line][i] == ' ') {
			continue;
		}
		else {
			if (GameBoard::boardMatrix[line][i] == toupper(word[j])) {
				continue;
			}
			else {
				if (line == 0) {
					if (GameBoard::boardMatrix[line + 1][i] == '#' || GameBoard::boardMatrix[line + 1][i] == ' ') continue;
				}

				if (line == GameBoard::boardHeight) {
					if (GameBoard::boardMatrix[line - 1][i] == '#' || GameBoard::boardMatrix[line - 1][i] == ' ') continue;
				}

				if ((GameBoard::boardMatrix[line + 1][i] == '#' || GameBoard::boardMatrix[line + 1][i] == ' ') &&
					(GameBoard::boardMatrix[line - 1][i] == '#' || GameBoard::boardMatrix[line - 1][i] == ' ')) {
					continue;
				}
				return 9;
			}
		}
	}

	return GameBoard::updateBoardHorizontal(direction, word, true);

}

int GameBoard::updateBoardVertical(string direction, string word, bool insert) {
	int line = (int)direction[0] - (int)'A';
	int column = (int)direction[1] - (int)'a';

	for (unsigned int i = line, j = 0; i < word.length() + line; i++, j++) {

		/**** Remove Word ******/
		if (word == "-") {
			auto it = GameBoard::userInputs.find(direction);

			if (it == GameBoard::userInputs.end()) {
				return 8;
			}

			if (j == it->second.length()) {
				GameBoard::userInputs.erase(it);
				return 0;
			}


			if (column == 0) {
				if (GameBoard::boardMatrix[j + line][column + 1] == '#' ||
					GameBoard::boardMatrix[j + line][column + 1] == ' ') {
					GameBoard::boardMatrix[j + line][column] = ' ';

				}
				else {

					if (GameBoard::checkIfItisAWord(direction[2], j + line, column + 1)) {
						GameBoard::boardMatrix[j + line][column] = ' ';
					}
				}

				i = -1;
				continue;
			}

			if (column == GameBoard::boardWidth - 1) {
				if (GameBoard::boardMatrix[j + line][column - 1] == '#' ||
					GameBoard::boardMatrix[j + line][column - 1] == ' ') {
					GameBoard::boardMatrix[j + line][column] = ' ';
				}
				else {

					if (GameBoard::checkIfItisAWord(direction[2], j + line, column - 1)) {
						GameBoard::boardMatrix[j + line][column] = ' ';
					}
				}

				i = -1;
				continue;
			}

			if ((GameBoard::boardMatrix[j + line][column + 1] == '#' ||
				GameBoard::boardMatrix[j + line][column + 1] == ' ' ||
				GameBoard::checkIfItisAWord(direction[2], j + line, column + 1))
				&&
				(GameBoard::boardMatrix[j + line][column - 1] == '#' ||
					GameBoard::boardMatrix[j + line][column - 1] == ' ' ||
					GameBoard::checkIfItisAWord(direction[2], j + line, column - 1))) {

				GameBoard::boardMatrix[j + line][column] = ' ';
				i = -1;
				continue;
			}
			i = -1;
			continue;
		}


		/***** Insert Word ******/
		if (insert == true) {
			GameBoard::boardMatrix[i][column] = toupper(word[j]);
			if (j == word.length() - 1) {
				GameBoard::updateUserInputs(direction, word);
				return 0;
			}
		}

		/***** Check if the word can be placed or replaced *****/

		if (GameBoard::boardMatrix[i][column] == ' ') {
			continue;
		}
		else {
			if (GameBoard::boardMatrix[i][column] == toupper(word[j])) {
				continue;
			}
			else {
				if (column == 0) {
					if (GameBoard::boardMatrix[i][column + 1] == '#' || GameBoard::boardMatrix[i][column + 1] == ' ') continue;
				}

				if (column == GameBoard::boardWidth) {
					if (GameBoard::boardMatrix[i][column - 1] == '#' || GameBoard::boardMatrix[i][column - 1] == ' ') continue;
				}

				if ((GameBoard::boardMatrix[i][column + 1] == '#' || GameBoard::boardMatrix[i][column + 1] == ' ') &&
					(GameBoard::boardMatrix[i][column - 1] == '#' || GameBoard::boardMatrix[i][column - 1] == ' ')) {
					continue;
				}
				return 9;
			}
		}
	}

	return GameBoard::updateBoardVertical(direction, word, true);

}

void GameBoard::updateClue(string direction) {
	vector <string> synonyms = GameBoard::synomys.at(GameBoard::solutions.at(direction));
	int index = rand() % synonyms.size();

	if (direction[2] == 'H') {
		GameBoard::horizontals.at(direction.substr(0, 2)) = synonyms.at(index);
	}
	else {
		if (direction[2] == 'V') {
			GameBoard::verticals.at(direction.substr(0, 2)) = synonyms.at(index);
		}
	}
}


int GameBoard::validateOption(string direction, string word) {
	//Return 0 OK; Others error

	if (direction.length() != 3) {
		return 1;
	}
	int height = direction[0];
	int width = direction[1];
	string s;

	if (!(height >= 65 && height <= 90 )) {
		return 2;
	}

	
	if (!(width >= 97 && width <= 122)) {
		return 3;
	}

	auto it = GameBoard::solutions.find(direction);

	if (it == GameBoard::solutions.end()) {
		return 4;
	}

	if (word != "") {

		if (word == "?") {
			GameBoard::printClue(direction);
			return 5;
		}

		if (word == "+") {
			GameBoard::updateClue(direction);
			GameBoard::printClue(direction);
			return 6;
		}


		if (word != "-" && word.length() != GameBoard::solutions.at(direction).length())
		{
			return 7;
		}


		if (direction[2] == 'H') {
			return GameBoard::updateBoardHorizontal(direction, word);
		}

		if (direction[2] == 'V') {
			return GameBoard::updateBoardVertical(direction, word);
		}
	}

	return 0;

}

void GameBoard::printClue(string direction) {
	Console console;
	string clue = "";
	if (direction[2] == 'H') {
		clue = GameBoard::horizontals.at(direction.substr(0, 2));
	}
	else {
		if (direction[2] == 'V') {
			clue = GameBoard::verticals.at(direction.substr(0, 2));
		}
	}
	console.setcolor(GREEN);
	cout << "  > " << "Clue: " << clue;
	console.setcolor(WHITE);
}

void GameBoard::print() {
	Console console;
	cout << ' ';
	cout << ' ';
	for (int k = 0; k < GameBoard::boardWidth; k++) {
		console.setcolor(LIGHTCYAN);
		cout << (char)(97 + k);
		cout << ' ';
	}
	cout << endl;
	//Add an extra line between letters and Board
	for (int i = 0; i < GameBoard::boardHeight; i++) {
		console.setcolor(LIGHTCYAN);
		cout << (char)(65 + i);
		cout << ' ';
		for (int j = 0; j < GameBoard::boardWidth; j++) {
			switch (GameBoard::boardMatrix.at(i).at(j)) {
			case '#':   console.printCharacter(RED, LIGHTMAGENTA, ' ');
				console.printCharacter(RED, LIGHTMAGENTA, ' ');
				break;
			case ' ':   console.printCharacter(LIGHTRED, CYAN, '_');
				console.printCharacter(LIGHTRED, CYAN, ' ');
				break;

			default:    console.printCharacter(LIGHTRED, CYAN, GameBoard::boardMatrix.at(i).at(j));
				console.printCharacter(LIGHTRED, CYAN, ' ');
			}
		}
		cout << endl;
	}
}

void GameBoard::printClues() {
	map<string, string>::iterator itH = GameBoard::horizontals.begin();
	map<string, string>::iterator itV = GameBoard::verticals.begin();

	cout << endl;
	cout << setfill(' ');
	cout << setw(23) << left << "Horizontals";
	cout << "Verticals";
	cout << endl;
	cout << setfill('-') << setw(46) << "-";
	cout << endl;

	cout << setfill(' ');
	while (itH != GameBoard::horizontals.end() || itV != GameBoard::verticals.end()) {
		if (itH != GameBoard::horizontals.end()) {
			cout << setw(23) << left << itH->first + ": " + itH->second;
			itH++;
		}
		else {
			cout << setfill(' ') << setw(23);
		}

		if (itV != GameBoard::verticals.end()) {
			cout << setw(23) << left << itV->first + ": " + itV->second;
			itV++;
		}

		cout << endl;
	}

	cout << setfill('-') << setw(COUT_SIZE) << "-";
	cout << endl;

}

void GameBoard::checkAnswers() {
	GameBoard::boardCorrect = true;
	map<string, string>::iterator itH = GameBoard::horizontals.begin();
	map<string, string>::iterator itV = GameBoard::verticals.begin();
	string pos = "";
	Console console;

	cout << endl;
	cout << setfill(' ');
	cout << setw(23) << left << "Horizontals";
	cout << "Verticals";
	cout << endl;
	cout << setfill('-') << setw(46) << "-";
	cout << endl;
	cout << setfill(' ');

	while (itH != GameBoard::horizontals.end() || itV != GameBoard::verticals.end()) {
		if (itH != GameBoard::horizontals.end()) {
			pos = itH->first + 'H';
			if (GameBoard::solutions.at(pos) == GameBoard::userInputs.at(pos)) {
				console.setcolor(GREEN);
				cout << setw(23) << left << itH->first + ": " + GameBoard::userInputs.at(pos);
				console.setcolor(WHITE);
				itH++;
			}
			else {
				console.setcolor(RED);
				cout << setw(23) << left << itH->first + ": " + GameBoard::userInputs.at(pos);
				console.setcolor(WHITE);
				GameBoard::boardCorrect = false;
				itH++;
			}
		}
		else {
			cout << setfill(' ') << setw(23);
		}

		if (itV != GameBoard::verticals.end()) {
			pos = itV->first + 'V';
			if (GameBoard::solutions.at(pos) == GameBoard::userInputs.at(pos)) {
				console.setcolor(GREEN);
				cout << setw(23) << left << itV->first + ": " + GameBoard::userInputs.at(pos);
				console.setcolor(WHITE);
				itV++;
			}
			else {
				console.setcolor(RED);
				cout << setw(23) << left << itV->first + ": " + GameBoard::userInputs.at(pos);
				console.setcolor(WHITE);
				GameBoard::boardCorrect = false;
				itV++;
			}
		}
		cout << endl;
	}

	cout << setfill('-') << setw(COUT_SIZE) << "-";
	cout << endl;

}

int GameBoard::getBoardWidth() {
	return GameBoard::boardWidth;
}

int GameBoard::getBoardHeight() {
	return GameBoard::boardHeight;
}