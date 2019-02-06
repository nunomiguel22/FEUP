/*Turma 8, Grupo 1, Trabalho 2 Parte 2(cwplayer)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araújo Ferreira
*/

#ifndef CROSSWORDS_DICTIONARY_H
#define CROSSWORDS_DICTIONARY_H


#include <map>
#include "FileManager.h"

class Dictionary {
    private:
        map< string, vector<string> > matchedWords;
        FileManager dictionary;
        string trimSpaces(string s);
        string getHeader(string s);
        vector< string > getSynonyms(size_t begin, string s);
    public:
        Dictionary(string fileName);
        map< string, vector<string> > getMatchedWord(string word);
        bool isOpen();
        void open();
        void close();


};


#endif //CROSSWORDS_DICTIONARY_H
