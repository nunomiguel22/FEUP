/*Turma 8, Grupo 1, Trabalho 1 Parte 1(procdic)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araújo Ferreira
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool checkHeadline(string word) {//Verify if the string a valid headline(A-Z ;'-)

	bool validHeadline = true;
	for (size_t i = 0; i < word.length(); i++) {

		if ((word[i] < 'A' || word[i] > 'Z') && word[i] != ';' && word[i] != '\'' && word[i] != '-' && word[i] != ' ') {
			validHeadline = false;
			break;
		}
	}
	return validHeadline;
}

bool checkWord(string word) {//Verify if the string is a valid word(A-Z)

	bool validWord = true;
	for (size_t i = 0; i < word.length(); i++) {

		if (word[i] < 'A' || word[i] > 'Z') {
			validWord = false;
			break;
		}
	}
	return validWord;
}

int headlineCounter(int head) {//Print the headline dots, increment and reset the headline dot counter

	if (head == 100) {
		head = 0;
		cout << ".";
	}
	else head++;
	return head;
}

bool multiWord(string line) {//Verify if a headline has more than one word

	for (size_t i = 0; i < line.length(); i++) {
		if (line[i] == ';') {
			return true;
		}
	}
	return false;
}

string spaceEraser(string word) {//Erase spaces before and after simple words

	while (word[0] == ' ')
		word.erase(0, 1);
	while (word[word.length() - 1] == ' ')
		word.erase(word.length() - 1, 1);
	return word;
}

int main() {

	int headline = 0;//headline counter
	ifstream file; //ifstream to read a file
	ofstream saida; // of stream to write to a file
	string line; //String where the line that was read is stored
	string readFilename; //Stores the filename of the file to be read 
	string writeFilename; //Stores the filename of the file to be written by the program
	string currentLetter = "a";//Stores the current letter in our progress reading headlines, string because of case T, read below
	string wordTemp;//Stores the each simple word in a multiple word headline
	vector<string> dict;//Stores all the simple words in the dictionary

						//Ask for filenames to be used in the program
	cout << "EXTRACTION OF WORD LIST FROM DICTIONARY" << endl << "=======================================" << endl;
	cout << endl << "Dictionary file ? ";
	cin >> readFilename;
	cout << "word list file ? ";
	cin >> writeFilename;

	//Open and read file
	file.open(readFilename);
	if (file.is_open()) {
		cout << endl << "Extracting simple words from file " << readFilename << "," << endl;
		cout << "beginning with letter ..." << endl << endl;
		while (getline(file, line)) {//Read file, line by line, to the last line

			if (!line.empty() && checkHeadline(line)) {//Discard non headlines and empty lines
				headline = headlineCounter(headline);//headline progress
				if (multiWord(line)) {//verify if the headline has more than one word
					for (size_t i = 0; i < line.length(); i++) {//Go through line letter by letter

						if (line[i] != ';') {//split words in a headline when a semicolon is found
							wordTemp += line[i];
							if (i == line.length() - 1) {//Verify last word in a headline
								wordTemp = spaceEraser(wordTemp);
								if (checkWord(wordTemp)) {
									dict.push_back(wordTemp);
								}
								wordTemp = "";
							}

						}

						else {//if semicolon found, verify the temporary word
							wordTemp = spaceEraser(wordTemp);
							if (checkWord(wordTemp)) {
								dict.push_back(wordTemp);
							}
							wordTemp = "";
						}

					}
				}
				else {
					if (checkWord(line)) {//if the line doesn't countain multiple words and is a valid word add to vector
						dict.push_back(line);

						/* Verify and print when the program switches to another letter in the dictionary, except for "T", which doesn't seem
						to exist in the dictionary used, so we use the first word instead: "TA" */
						if ((line[0] != currentLetter[0] && line.length() == 1) || line == "TA") {
							currentLetter = line[0];
							cout << endl << currentLetter << endl << ".";//Print the new letter and the first dot
							headline = 0;
						}
					}
				}
			}
		}
		file.close();//Close file
	}
	else {//Error if the dictionary file is not found
		cout << "Dictionary file not found ( ._.)" << endl << endl;
		return 0;
	}

	//Print simple word information and sort vector
	cout << endl << endl << "Number of simple words = " << dict.size() << endl << endl;
	cout << "Sorting words ... " << endl << endl;
	sort(dict.begin(), dict.end()); //Alphabetical sort of the vector
	cout << "Removing duplicate words ..." << endl << endl;
	dict.erase(unique(dict.begin(), dict.end()), dict.end()); //Duplicate removal using vector.erase and unique
	cout << "Number of non-duplicate simple words = " << dict.size() << endl << endl;

	//Write vector to text file
	cout << "Saving words into file " << writeFilename << " ..." << endl << endl;
	saida.open(writeFilename);
	for (size_t i = 0; i < dict.size(); i++)
		saida << dict[i] << endl;
	saida.close();

	return 0;
}
