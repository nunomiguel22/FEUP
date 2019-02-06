/*Turma 8, Grupo 1, Trabalho 2 Parte 2(cwplayer)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araújo Ferreira
*/

#ifndef CROSSWORDS_GAMEBOARD_H
#define CROSSWORDS_GAMEBOARD_H


#include <iostream>
#include "iomanip"
#include <string>
#include <map>
#include "FileManager.h"
#include "Dictionary.h"

class GameBoard {
    private:
        int boardWidth;
        int boardHeight;
        bool boardCorrect;
        vector< string > boardLines;
        map< string,string > solutions;
        map< string,string > userInputs;
        map< string, string > horizontals;
        map< string, string > verticals;
        map< string, vector<string> > synomys;
        vector< vector <char> > boardMatrix;
        FileManager file;
        Dictionary dictionary;
        bool error;
        void processLines();
        void addToBoard(string s);
        void addSolution(string s);
        void getSynonyms();
        void getClues();
        int updateBoardHorizontal(string direction, string word, bool insert = false);
        int updateBoardVertical(string direction, string word, bool insert = false);
        void updateUserInputs(string direction, string word);
    public:
        GameBoard(string board, string wordFile);
        bool isFull();
        bool isCorrect();
        int validateOption(string direction, string word="");
        int getBoardWidth();
        int getBoardHeight();
        bool isGood();
        void checkAnswers();
        void updateClue(string direction);
        void print();
        void printClues();
        void printClue(string direction);
};


#endif //CROSSWORDS_GAMEBOARD_H
