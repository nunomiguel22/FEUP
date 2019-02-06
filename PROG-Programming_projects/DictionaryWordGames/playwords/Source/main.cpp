/*Turma 8, Grupo 1, Trabalho 1 Parte 2(playwords)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araujo Ferreira
*/

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <fstream>


using namespace std;

string makeUppercase(string word) {//Make all string characters uppercase

	for (size_t i = 0; i < word.length(); i++)
		word[i] = toupper(word[i]);
	return word;
}
bool validWord(string word) {//verify if all characters in a word are between (a-Z)

	bool result = false;
	for (size_t i = 0; i < word.length(); i++) {
		if ((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z'))
			result = true;
		else {
			result = false;
			break;
		}
	}
	return result;
}

bool validWildWord(string word) {//Verify if the string is a valid wildcard term

	bool result = false;
	for (size_t i = 0; i < word.length(); i++) {

		if ((word[i] >= 'A' && word[i] <= 'Z') || (word[i] >= 'a' && word[i] <= 'z') || word[i] == '*' || word[i] == '?')
			result = true;
		else {
			result = false;
			break;
		}
	}
	return result;
}

/**** First game auxiliars ****/
bool checkExists(vector<string> v, string s) {
	for (size_t i = 0; i < v.size(); i++) {
		if (v.at(i) == s) {
			return true;
		}
	}
	return false;
}

void firstGame(string myString, vector<string> myVector) {//Print result of the first game

	if (checkExists(myVector, myString)) {
		cout << "good one" << "\n";
	}
	else {
		cout << "Oh no..." << "\n";
	}
}

/**** Second game auxiliars ****/
string * chooseAndScramble(vector<string> v) { //Pick a word from the dictionary and scramble it

	static string a[2];
	int randIndice;
	string newWord;
	vector<char> temp;

	do { //Chooses a word with atleast 3 characters
		if (v.size() > 0) {
			randIndice = rand() % (v.size());
			a[0] = v.at(randIndice);
		}
		else {
			cerr << "The vector is empty!";
			return 0;
		}
	} while (v.at(randIndice).length() < 3);

	for (size_t i = 0; i < a[0].length(); i++) {
		temp.push_back(a[0].at(i));
	}

	for (size_t i = 0; i < temp.size(); i++) {
		int j = rand() % temp.size();
		bool goUp = true;

		while (temp.at(j) == '-') {
			if (j < (temp.size() - 1) && goUp) {
				j++;
			}
			else {
				goUp = false;
				if (j >= 0) {
					j--;
				}
				else {
					cerr << "Something went wrong!";
				}
			}
		}

		if (temp.at(j) != '-') {
			newWord += temp.at(j);
			temp.at(j) = '-';
		}
		else {
			cerr << "something went wrong while scramble";
		}
	}
	a[1] = newWord;
	return a;
}

/**** Third game auxiliars ****/
bool verifySetWord(string word, string letters) {
	bool result;
	bool letterverify;
	for (size_t i = 0; i < word.length(); i++) {
		for (size_t j = 0; j < letters.length(); j++) {
			if (!(word[i] == letters[j]))
				result = false;
			else {
				result = true;
				break;
			}
		}
		if (!result)
			return false;
	}
	for (size_t i = 0; i < letters.length(); i++) {
		for (size_t j = 0; j < word.length(); j++) {
			if (letters[i] == word[j]) {
				letterverify = true;
				break;
			}
			else letterverify = false;
		}
		if (letterverify == false)
			return false;
	}
	return true;
}

void validWordsWith(vector<string> v, string s) {

	int lettersFound = 0;
	int wordsFound = 0;
	string debugV;
	char debugSj;
	char debugVk;

	cout << "With those letters the dictionary has: " << "\n";
	for (size_t i = 0; i < v.size(); i++) {
		debugV = v[i];
		for (size_t j = 0; j < s.length(); j++) {
			debugSj = s[j];
			for (size_t k = 0; k < v[i].length(); k++) {
				debugVk = v[i][k];
				if (s[j] == v[i][k]) {
					lettersFound++;
					break;
				}
			}
		}
		if (verifySetWord(v[i], s)) {
			cout << v[i] << "\n";
			wordsFound++;
		}
		lettersFound = 0;
	}

	if (wordsFound > 0) {
		cout << "The number of words found was: " << wordsFound << "\n";
	}
	else {
		cout << wordsFound << " words" << endl;
	}
}


/**** Fourth game auxiliars ****/
vector<char> createSetOfLetters(vector<string> v) {

	vector< vector <int> > v1;
	vector< char > v2;
	size_t biggestWord = 0;
	float letterProportion = 0.0;

	for (size_t i = 0; i < v.size(); i++) { //Search for the biggest word
		if (v.at(i).length() > biggestWord) {
			biggestWord = v.at(i).length();
		}

		for (size_t j = 0; j < v.at(i).length(); j++) {

			bool auxFound = false;
			if (v1.size() == 0) {
				vector<int> firstRow;
				firstRow.push_back(v.at(i)[j]);
				firstRow.push_back(1);
				v1.push_back(firstRow);
				break;
			}
			for (size_t k = 0; k < v1.size(); k++) { //compare letters of the char vector
				int i1 = v1.at(k).at(0);
				int i2 = v1.at(k).at(1);
				if (v1.at(k).at(0) == v.at(i)[j]) {
					v1.at(k).at(1)++;
					auxFound = true;
					break;
				}
				else {
					continue;
				}
			}
			if (!auxFound) {
				vector<int> row;
				row.push_back(v.at(i)[j]);
				row.push_back(1);
				v1.push_back(row);
			}
		}
	}

	for (size_t i = 0; i < v1.size(); i++) {
		char temp = v1.at(i).at(0);
		int number = v1.at(i).at(1);
	}
	cout << "\n";

	for (size_t i = 0; i < v1.size(); i++) { //Rearrange vector in order of number of characters
		for (size_t j = 0; j < v1.size(); j++) {
			vector<int> aux;
			if (v1.at(i).at(1) > v1.at(j).at(1)) {
				aux = v1.at(i);
				v1[i] = v1.at(j);
				v1[j] = aux;
			}
		}
	}
	letterProportion = (float)v1.at(v1.size() - 1).at(1) / 2.0;

	for (size_t i = 0; i < v1.size(); i++) { // create new vector with the number of letters multiplied by the ocorrence factor
		float j = 0;
		while (j < (((float)v1.at(i).at(1)) / letterProportion)) {
			v2.push_back(v1.at(i).at(0));
			j += 1.0;
		}
	}
	for (size_t i = 0; i < v2.size(); i++) {
		char temp = v2.at(i);
	}
	return v2;
}

vector<char> chooseLettersFromSet(vector<char> set, int number) {

	vector<char> v;
	cout << "{ ";
	for (int i = 0; i < number; i++) {
		int randIndice = rand() % (set.size());
		v.push_back(set[randIndice]);
		set.erase(set.begin() + randIndice);
		cout << set.at(randIndice);
		if (i < number - 1) {
			cout << " - ";
		}
	}
	cout << " } \n";
	return v;
}

void verifyWord(string word, vector<char> v, vector<string> haystack) {

	int initialSize = v.size();
	for (size_t i = 0; i < word.length(); i++) { //For every letter of the word
		for (size_t j = 0; j < v.size(); j++) {   //All possible letters
			if (word[i] == v.at(j)) {     //Remove the letter if it exists
				v.erase(v.begin() + j);
				break;
			}
		}
	}
	if (v.size() != initialSize - word.length()) {
		cout << "The letters used are not available on the SET" << "\n";
		return;
	}
	for (size_t i = 0; i < haystack.size(); i++) {
		if (haystack.at(i) == word) {
			cout << "Valid Word, well done!" << "\n";
			return;
		}
	}
	cout << "The word isn't valid" << "\n";
}

/**** Fifth game auxiliars ****/
bool wildcardMatch(const char *str, const char *strWild)
{
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

//Interface and game setup function
int menu(vector<string> myVector) {

	int menuValue = 0; //Stores the menu value input by the user
	string myString;            //First Game (Word entered by user)
	string * scrambleWord;      //Second Game (Scrambled word from the dictionary)
	string userGuess;           //Second Game (Word entered by user)
	string chooseLetters;       //Third Game (Letters chosen by the user)
	int numberOfLetters;        //Forth Game (Number of letters to be given, chosen by the user)
	string optionWord;          //Forth Game (Word entered by the user)
	vector<char> largerSet;     //Forth Game (Set of letters to be used in the game)
	vector<char> chosenLetters; //Forth Game (Letters entered by the user)
	string searchQuery;         //Fifth Game (Query entered by the user)
	while (true) {
		//system("cls"); //clears console, ONLY WORKS ON WINDOWS
		cout << "Choose the game:" << endl << endl;
		cout << "0 - Exit" << endl;
		cout << "1 - Check if a word belongs in the dictionary" << endl;
		cout << "2 - Guess a scrambled word" << endl;
		cout << "3 - Build a set with all the words with a number of letters" << endl;
		cout << "4 - Guess a valid word from a set of random letters" << endl;
		cout << "5 - Wildcard Search" << endl;
		cin >> menuValue;
		while (cin.fail() || menuValue > 5 || menuValue < 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input, please choose a number from the menu:" << endl;
			cin >> menuValue;
		}

		switch (menuValue) { //Menu function
		case 1://FIRST GAME

			cin.clear();
			cin.ignore();
			while (true) {
				cout << "Please enter a word(Enter 0 to return to the main menu): " << endl;
				getline(cin, myString);
				if (myString == "0")
					break;
				if (!validWord(myString))//Invalid input check
					cout << "Invalid input" << endl;
				else {
					myString = makeUppercase(myString);
					firstGame(myString, myVector);
				}
			}
			break;

		case 2://SECOND GAME

			cin.clear();
			cin.ignore();
			while (userGuess != "0") {
				scrambleWord = chooseAndScramble(myVector);
				cout << endl << scrambleWord[1] << " - Try to guess the word in " << 3 << " turns (Enter 0 to return to the main menu)" << "\n";
				for (size_t i = 0; i < 3; i++) {
					cout << i + 1 << " - Your guess is: ";
					getline(cin, userGuess);
					if (userGuess == "0")
						break;
					while (!validWord(userGuess) || userGuess.length() != scrambleWord->length()) {//Invalid input check
						cout << "Invalid input or wrong number of characters, please try again" << endl;
						getline(cin, userGuess);
						if (userGuess == "0")
							break;
					}
					if (userGuess == "0")
						break;
					userGuess = makeUppercase(userGuess);
					if (userGuess == scrambleWord[0]) {
						cout << "Well done you guessed it!" << "\n";
						break;
					}
					else {
						if (3 != i + 1) {
							cout << "No, Try Again!" << "\n";
						}
						else cout << "You lose the word was: " << scrambleWord[0] << "\n";
					}
				}
			}
			break;

		case 3://THIRD GAME

			cin.clear();
			cin.ignore();
			while (true) {
				cout << "Please write between 1 and 5 Letters (Enter 0 to return to the main menu): " << "\n";
				getline(cin, chooseLetters);
				if (chooseLetters == "0")
					break;
				while (chooseLetters.length() < 1 || chooseLetters.length() > 5 || !validWord(chooseLetters)) {//Invalid input check
					cout << "Invalid input." << "\n";
					cout << "Please try again: (1 or 5 letters): " << "\n";
					getline(cin, chooseLetters);
					if (chooseLetters == "0")
						break;
				}
				if (chooseLetters == "0")
					break;
				chooseLetters = makeUppercase(chooseLetters);
				validWordsWith(myVector, chooseLetters);
			}
			break;

		case 4://FORTH GAME

			cout << "Sorting through the dictionary ..." << endl;
			largerSet = createSetOfLetters(myVector);
			cout << "How many letters do you wish? (Maximum of 21) (Enter 0 to return to the main menu)" << endl;
			cin >> numberOfLetters;

			while (numberOfLetters < 0 || numberOfLetters > 21) {//Invalid input check
				cout << "Invalid input, please try again" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> numberOfLetters;
			}
			if (numberOfLetters == 0)
				break;
			cin.clear();
			cin.ignore();
			while (true) {
				chosenLetters = chooseLettersFromSet(largerSet, numberOfLetters); //save the set of chosen words;
				cout << "Try to create a word (Enter 0 to return to the main menu): " << "\n";
				getline(cin, optionWord);

				if (optionWord == "0")
					break;
				optionWord = makeUppercase(optionWord);
				verifyWord(optionWord, chosenLetters, myVector);
			}
			break;

		case 5://FIFTH GAME

			cin.ignore();
			while (searchQuery != "0") {
				cout << "Make your search query (Enter 0 to return to the main menu): " << "\n";
				cin.clear();
				getline(cin, searchQuery);

				while (searchQuery != "0" && !validWildWord(searchQuery)) {//Invalid input check
					cout << "Invalid input, please try again" << endl;
					getline(cin, searchQuery);
				}
				if (searchQuery == "0")
					break;
				for (size_t i = 0; i < myVector.size(); i++) {
					if (wildcardMatch(&myVector.at(i)[0], &searchQuery[0])) {
						cout << myVector.at(i) << "\n";
					}
				}
			}
			break;
		case 0:
			return 0;
		}
	}
}

int main() {

	srand((int)time(NULL)); //Initialize RNG seed
	vector<string> myVector; //Vector where the dictionary is stored
	string line; // Stores lines from file
	string readFile; // Stores dictionary file name
	ifstream file; //ifstream to read a file

	cout << "Prepared dictionary file ? "; //gets dictionary filename
	cin >> readFile;
	cout << endl;

	file.open(readFile);//opens file
	if (file.is_open()) {

		cout << "Reading dictionary ..." << endl;
		while (getline(file, line)) {//reads file, line by line
			myVector.push_back(line); // stores in vector
		}
		file.close();
	}
	else {
		cout << "Dictionary file not found ( ._.)" << endl << endl; //Error if dictionary file not found
		return 0;
	}
	menu(myVector);//executes Menu function

	return 0;
}