/*Turma 8, Grupo 1, Trabalho 2 Parte 1(cwcreator)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araújo Ferreira
*/

#include "dictionary.h"
#include "console.h"
#include "verifications.h"
#include "board.h"
#include <fstream>

using namespace std;

//Save current Board, its user inputs, and the dictionary used to a text file
void save(vector<vector<char>> v1, vector<vector<string>> v2, string dicName, string boardFilename) {

	Console console;
	ifstream testFile;
	ofstream txtFile;
	string prefix = "b";
	string prefix0 = "b0";
	string prefix00 = "b00";
	string extension = ".txt";
	string filename;

	//When boardFilename is not empty it means this puzzle has been reload and is saved with the same filename
	if (!boardFilename.empty())
		filename = boardFilename;
	else {//When boardFilename is empty it means this is a new puzzle and a new name is generated with the bxxx.txt format automatically
		for (unsigned int i = 1; i < 1000; i++) {
			if (i < 10)
				filename = prefix00 + to_string(i) + extension;
			else if (i < 100)
				filename = prefix0 + to_string(i) + extension;
			else filename = prefix + to_string(i) + extension;
			testFile.open(filename);
			if (!testFile.is_open()) {
				testFile.close();
				break;
			}
			testFile.close();
			filename.clear();
		}
	}

	//When 999 save files already exist, warn and overwrite b999.txy
	if (filename.empty()) {
		console.setcolor(YELLOW);
		cout << endl << "b001.txt through b999.txt already exist, b999.txt will be overwritten with the new board" << endl;
		console.setcolor(WHITE);
		filename = "b999.txt";
	}

	cout << endl << "Saving board into file ..." << endl;

	txtFile.open(filename);

	//Print dictionary name to file
	txtFile << dicName << endl << endl;

	//Print Board to file
	for (size_t i = 1; i < v1.size(); i++) {
		for (size_t j = 1; j < v1.at(i).size(); j++)
			txtFile << v1.at(i).at(j) << ' ';
		txtFile << endl;
	}
	txtFile << endl;

	//Print user inputs to file
	for (size_t i = 0; i < v2.size(); i++)
		txtFile << v2.at(i).at(0) << ' ' << v2.at(i).at(1) << endl;
	txtFile.close();

	//Success message
	console.setcolor(LIGHTGREEN);
	cout << endl << "The Board has been saved as " << filename << endl;
	console.setcolor(WHITE);
}

//Remove entry from userInputs
bool del(vector<vector <string>> &userInputs, string posDir) {
	int line = -1;
	//Find the correct index on the vector
	for (size_t i = 0; i < userInputs.size(); i++) {
		if (posDir == userInputs.at(i).at(0)) {
			line = i;
			break;
		}
	}
	//If the position and direction given is not found in user inputs return false
	if (line == -1)
		return false;

	//Erase the input from the vector
	userInputs.erase(userInputs.begin() + line);

	return true;
}

bool fullBoard(vector<string> contents) {

	//Get number of lines and columns of saved board
	for (size_t i = 2; i < contents.size(); i++)
		for (size_t j = 0; j < contents.at(i).length(); j++) {
			if (contents.at(i).empty())
				return true;
			if (contents.at(i)[j] == '.')
				return false;
		}
	return true;
}

//Board building function for new or reloaded boards
void boardBuilding(string dictFilename, board b1, dictionary d1, int x, int y, string boardFilename) {

	vector<vector <string>>		dictionaryWordList = d1.returnWordList();
	vector<vector <string>>		userInputs = b1.returnUserInputs();
	vector<string>				suggestedList;
	vector<vector <char>>		boardContents;
	char fullUserAnswer;
	Console console;

	//Keep asking for position/direction and word until user finishes the board or enters (CTRL-Z)
	while (!b1.full()) {
		string posDir;
		string word = " ";
		vector <string> temp;


		//Get position/direction
		while (!correctPosDir(posDir, x, y, b1)) {
			char userAnswer; //Used for dialog situations when asking for position/direction

			cout << endl << "Position ( LCD / CTRL-Z = stop )  ? ";
			cin >> posDir;

			//When user enters (CTRL-Z) / (CTRL-D)
			if (cin.eof()) {
				console.setcolor(YELLOW);
				cout << endl << "Enter 'S' to SAVE and CONTINUE later, 'F' to FINISH the current board or 'D' to DISCARD it: ";
				console.setcolor(WHITE);
				cin.clear();
				cin >> userAnswer;
				userAnswer = toupper(userAnswer);
				//cout << endl;
				if (userAnswer == 'D') //Discard
					return;
				while (cin.fail() || (userAnswer != 'S' && userAnswer != 'F' && userAnswer != 'D')) {//invalid input
					if (cin.eof())
						cin.clear();
					else {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					console.setcolor(LIGHTRED);
					cout << endl << "Invalid input, enter S, F or D." << endl;
					console.setcolor(YELLOW);
					cout << endl << "Enter 'S' to save and continue later, 'F' to finish this board or 'D' to discard it: ";
					console.setcolor(WHITE);
					cin >> userAnswer;

					userAnswer = toupper(userAnswer);
					if (userAnswer == 'D')//Discard after first entering an invalid input
						return;
				}
				//Save board as is to continue later
				if (userAnswer == 'S') {
					boardContents = b1.returnWordTable();
					cout << endl << "The board will now be saved, it can be reloaded and finished later by using the 'resume puzzle' menu option." << endl;
					save(boardContents, userInputs, dictFilename, boardFilename);
					cin.clear();
					cin.ignore();
					cout << endl << "Press 'Enter' to continue:";
					getchar();
				}
				//Fill board with black cells and save
				else {
					b1.finish();//Fill with black cells
					boardContents = b1.returnWordTable();
					cout << endl << "The remaining open spaces on the board have been filled with black cells, the board is ready to be used in cwplayer." << endl;
					save(boardContents, userInputs, dictFilename, boardFilename); //Pass Current board vector, Current user inputs, dictionary filename, and board filename(empty if new board) to save function		
					cin.clear();
					cin.ignore();
					cout << endl << "Press 'Enter' to continue:";
					getchar();
				}
				return;
			}

			//Position/direction error message
			if (!correctPosDir(posDir, x, y, b1)) {
				console.setcolor(LIGHTRED);
				cout << endl << "Incorrect position and direction entry, read instructions and try again" << endl;
				console.setcolor(WHITE);
			}
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		//Get word
		while (!simpleWord(word) || !dictionaryWord(word, dictionaryWordList) || existingWord(userInputs, word) || !wordFitsBoard(x, y, posDir, word.length())) {

			cout << "Word ( - = remove / ? = help )  ? ";
			cin >> word;
			while (cin.eof() || cin.fail()) {
				cout << "Invalid input, try again" << endl;
				cout << "Word ( - = remove / ? = help )  ? ";
				cin.clear();
				cin >> word;
			}
			//Deleting a word
			if (word == "-") {
				if (del(userInputs, posDir)) {//del function attempts to remove the word from the inputs vector, returns if it was successful
					b1.del(userInputs); //Board::del function then reloads the board using the user inputs vector
					console.setcolor(LIGHTGREEN);
					cout << endl << "The selected word has been removed from the board" << endl;
					console.setcolor(WHITE);
					break;
				}
				else { //If the position was not valid (no word was removed), print error message
					console.setcolor(LIGHTRED);
					cout << endl << "No word with STARTING position and direction: '" << posDir << "' found." << endl;
					console.setcolor(WHITE);
					cout << "To delete a word enter its starting position and direction, and then enter '-' when asked for a word" << endl;

					break;
				}
			}

			//Give the user suggestions
			if (word == "?") {
				suggestedList = d1.suggested(posDir, b1.returnWordTable());
				//Remove word suggestions that already exist on the board
				for (unsigned int i = 0; i < suggestedList.size(); i++)
					if (existingWord(userInputs, suggestedList.at(i)))
						suggestedList.erase(suggestedList.begin() + i);
				//Print message when no suggestions are available
				if (suggestedList.empty()) {
					console.setcolor(LIGHTRED);
					cout << endl << "No suggested words available (or word already exists) for position " << posDir << ". Try a different position." << endl;
					console.setcolor(WHITE);
					break;
				}
				else {//Print all word suggestions
					cout << endl << "Suggested word(s) for position " << posDir << ":" << endl << endl;
					for (size_t i = 0; i < suggestedList.size(); i++) {
						cout << suggestedList.at(i);
						if (i != suggestedList.size() - 1)
							cout << ", ";
					}
					cout << "." << endl << endl;
					word = "";
					continue;
				}
			}

			for (size_t i = 0; i < word.length(); i++)
				word[i] = toupper(word[i]);

			//Word error messages
			console.setcolor(LIGHTRED);
			if (!simpleWord(word)) {
				cout << endl << "Word is not simple (a-Z), try again" << endl;
				console.setcolor(WHITE);
			}
			else if (!dictionaryWord(word, dictionaryWordList)) {
				cout << endl << "Word does not exist in the dictionary, try again" << endl << endl;
				console.setcolor(WHITE);
			}
			else if (existingWord(userInputs, word)) {
				cout << endl << "Word already exists on the board, try again" << endl << endl;
				console.setcolor(WHITE);
			}
			else if (!wordFitsBoard(x, y, posDir, word.length())) {
				cout << endl << "Word does not fit the board, try again" << endl << endl;
				console.setcolor(WHITE);
			}
			console.setcolor(WHITE);
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		//If the word is added to board, show updated board and save the user inputs to a 2D vector
		if (b1.alter(posDir, word)) {
			b1.show();
			temp.push_back(posDir);
			temp.push_back(word);
			userInputs.push_back(temp);
		}
	}

	//When board is full, ask if user wants to save
	cout << "The board is full, to save the board enter 'S' , or to discard it enter 'D' ? ( S/D ) ";
	cin >> fullUserAnswer;
	fullUserAnswer = toupper(fullUserAnswer);

	while (cin.fail() || (fullUserAnswer != 'S' && fullUserAnswer != 'D')) {
		if (cin.eof())
			cin.clear();
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		console.setcolor(LIGHTRED);
		cout << endl << "Invalid input, enter S or D, try again" << endl;
		console.setcolor(WHITE);
		cout << endl << "The board is full, do you with to save the board ( S ) , or discard it ( D ) ? ( S/D ) ";
		cin >> fullUserAnswer;
		fullUserAnswer = toupper(fullUserAnswer);
	}

	if (fullUserAnswer == 'S') {
		//Final verification if all inputs are valid	
		if (!correctUserInputs(userInputs, d1)) {
			console.setcolor(LIGHTRED);
			cout << "Invalid words found, cannot save board" << endl;
			console.setcolor(WHITE);
		}
		else {
			boardContents = b1.returnWordTable();
			save(boardContents, userInputs, dictFilename, boardFilename);
		}
	}

	cout << "Press 'Enter' to continue to the main menu" << endl;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin >> fullUserAnswer;
	if (cin.eof())
	{
		cin.clear();
		cout << "TEST" << endl;
	}
	else {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

//Start a new, empty board
void newPuzzle() {

	string dictFilename;
	unsigned int x = 0, y = 0;
	Console console;

	cout << endl << "---------------------------------------------------" << endl << "CREATE PUZZLE" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "Dictionary file name ? ";

	//Create dictionary
	cin.clear();
	cin.ignore();
	getline(cin, dictFilename);
	dictionary d1(dictFilename);
	d1.buildList();
	dictFilename = d1.returnFilename();

	//Create Board
	while (cin.fail() || x > 26 || x < 1 || y < 1 || y > 26) {
		cout << "Board size (lines columns) ? ";
		cin >> y >> x;
		if (cin.fail() || x > 26 || x < 1 || y < 1 || y > 26) {
			console.setcolor(LIGHTRED);
			cout << endl << "Invalid input:" << endl;
			console.setcolor(WHITE);
			cout << "The maximum allowed number of lines and columns is 25." << endl;
			cout << "Enter the number lines followed by a space and the number of columns." << endl;
			cout << "Example: '10 12'." << endl << endl;
		}
		if (cin.eof())
			cin.clear();
		else {

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	board b1(x, y);
	b1.create();
	//Show empty board
	b1.show();
	//Start building the board
	boardBuilding(dictFilename, b1, d1, x, y, "");
}

//Reload saved board
void reloadPuzzle() {

	Console console;
	string dictFilename;
	string boardFilename;
	string line;

	vector<string> reloadContents;
	ifstream txtFile;

	//Get save Filename
	cout << endl << "---------------------------------------------------" << endl << "RELOAD PUZZLE" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << endl << "Board save file name? ";
	cin >> boardFilename;
	txtFile.open(boardFilename);
	while (!txtFile.is_open()) {
		if (cin.eof())
			cin.clear();
		else {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		console.setcolor(LIGHTRED);
		cout << "Board save file not found, board save file name ? ";
		console.setcolor(WHITE);
		cin >> boardFilename;
		txtFile.open(boardFilename);
		cout << endl;
	}

	//Save all the contents of the file to a string vector
	while (getline(txtFile, line)) {
		reloadContents.push_back(line);
	}

	if (fullBoard(reloadContents)) {
		console.setcolor(LIGHTRED);
		cout << endl << "This board is already completed." << endl;
		console.setcolor(WHITE);
		cout << endl << "You may now use it in cwplayer." << endl;
		cin.clear();
		cin.ignore();
		cout << endl << "Press 'Enter' to continue to the main menu:";
		getchar();
		return;
	}


	//Rebuild dictionary
	dictFilename = reloadContents.at(0);
	dictionary d1(dictFilename);
	d1.buildList();

	//Reload the board and its user inputs
	board rb1(reloadContents);
	rb1.reloadUserInputs();
	rb1.reloadBoard();
	if (rb1.full()) {
		console.setcolor(LIGHTRED);
		cout << endl << "This board is already full" << endl;
		console.setcolor(WHITE);
		cin.clear();
		cin.ignore();
		cout << "Press 'Enter' to continue to the main menu" << endl;
		getchar();
		return;
	}

	//Start building the board again
	int x = rb1.retX();
	int y = rb1.retY();

	boardBuilding(dictFilename, rb1, d1, x, y, boardFilename);
}

//Initial interface(Main menu and instructions)
int main() {
	Console console;
	while (true) {
		//Instructions and Menu
		cout << "CROSSWORDS PUZZLE CREATOR" << endl << "==================================================" << endl;
		console.setcolor(LIGHTRED);
		cout << endl << "INTRUCTIONS:" << endl;
		console.setcolor(WHITE);
		cout << "Creating a puzzle:" << endl;
		console.setcolor(YELLOW);
		cout << " The board can have at most 25 lines and columns" << endl;
		cout << " Position ( LCD / CTRL-Z = stop ):" << endl;
		console.setcolor(WHITE);
		cout << "  LCD stands for Line Column and Direction" << endl;
		cout << "  Enter 3 letters only:" << endl;
		cout << "   Uppercase letter for lines, lowercase letter for columns and uppercase V(vertical) or H(horizontal)" << endl;
		cout << "   Example: AcV" << endl;
		cout << "  Operations cannot be done on a black cell, to remove the black cell you need to remove the word that generated it." << endl;
		console.setcolor(YELLOW);
		cout << " Words must:" << endl;
		console.setcolor(WHITE);
		cout << "  be simple(a - Z)" << endl;
		cout << "  match with other words on the board" << endl;
		cout << "  not exist on the board already" << endl;
		cout << "  fit the board" << endl;
		console.setcolor(YELLOW);
		cout << " To delete a word from the board, enter its starting position and direction, and then enter '-', when asked for a word" << endl;
		cout << " When choosing a word, you may enter '?' to get a list of all posible word that fit your chosen position/Direction" << endl;
		console.setcolor(WHITE);
		cout << "---------------------------------------------------" << endl << "OPTIONS:" << endl;
		cout << endl << "1 - Create puzzle" << endl << "2 - Resume puzzle" << endl << "0 - Exit" << endl;
		cout << endl << "Option ? ";

		int menuChoice;
		if (cin.eof())
			cin.clear();

		cin >> menuChoice;
		//Invalid input check
		while (cin.fail() || menuChoice < 0 || menuChoice > 2) {

			console.setcolor(LIGHTRED);
			cout << endl << "Invalid value!" << endl;
			console.setcolor(WHITE);
			cout << endl << "Choose a menu option (0 , 1 or 2):";
			if (cin.eof())
				cin.clear();
			else {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cin >> menuChoice;

		}

		switch (menuChoice) {
		case 0:
			return 0;
		case 1:
			newPuzzle();
			break;
		case 2:
			reloadPuzzle();
			break;
		}
	}
}