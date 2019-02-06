/*Turma 8, Grupo 1, Trabalho 2 Parte 2(cwplayer)
Nuno Miguel Fernandes Marques
Ricardo Jorge de Araújo Ferreira
*/

#include "Dictionary.h"

Dictionary::Dictionary(string fileName ): dictionary(fileName){
    Dictionary::dictionary = FileManager(fileName);
}

string Dictionary::getHeader(string s){
    string header = "";
    for(int i=0; i<s.length(); i++){
        if(s[i] == ':'){
            break;
        }

        header += toupper(s[i]);
    }

    return header;
}

vector<string> Dictionary::getSynonyms(size_t begin, string s) {
    string aux = s.substr(begin, s.length()-begin);
    aux = dictionary.trimSpaces(aux);
    return dictionary.explode(',' , aux);
}

map<string, vector<string>> Dictionary::getMatchedWord(string word) {
    string key = "";
    vector<string> value;
    map<string, vector<string>> map;
    while(Dictionary::dictionary.hasMoreLines()){
        string aux = Dictionary::dictionary.getNextLine();
        if(!word.compare(Dictionary::getHeader(aux))){
            key = Dictionary::getHeader(aux);
            value = Dictionary::getSynonyms(key.length()+1, aux);
            map.insert(make_pair(key, value));
            break;
        }
    }
    return map;
}

bool Dictionary::isOpen(){
    return Dictionary::dictionary.isOpen();
}

void Dictionary::open() {
    Dictionary::dictionary.setFile("Dictionary.txt");
}

void Dictionary::close() {
    Dictionary::dictionary.closeFileStream();
}