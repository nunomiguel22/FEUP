#include "locais.h"
#include "math.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;


Paragem::Paragem(string nome, double latitude, double longitude){
	this->nome = nome;
	this->latitude = latitude;
	this->longitude = longitude;
	this->numeroclientes = 0;
}

Paragem::Paragem(string nome, double latitude, double longitude, int numclientes){
	this->nome = nome;
	this->latitude = latitude;
	this->longitude = longitude;
	this->numeroclientes = numclientes;
}

string Paragem::getNome() const { return this->nome; }

double Paragem::getLatitude() const {return this->latitude;}

double Paragem::getLongitude() const{ return this->longitude; }

int Paragem::getNumClientes() const{return this->numeroclientes; }

void Paragem::aumentaNumClientes(){this->numeroclientes++;}

void Paragem::diminuiNumClientes(){this->numeroclientes--;}

void Paragem::setNome(std::string nome) { this->nome = nome; }

void Paragem::setLatitude(double latitude) { this->latitude = latitude; }

void Paragem::setLongitude(double longitude) { this->longitude = longitude; }

double Paragem::distancia(double latitude, double longitude){

	//Formula de haversine
	double gpr = 3.14159265358979323846264338327950288 / 180;
	double raioTerra = 6371;

	double distLat = (latitude - this->getLatitude()) * gpr;
	double distLong = (longitude - this->getLongitude()) * gpr;

	double p1lat = this->getLatitude() * gpr;
	double p2lat = latitude * gpr;

	double a = sin(distLat/2) * sin(distLat/2) + sin(distLong/2) * sin(distLong/2) *
			cos(p1lat) * cos(p2lat);
	double c = 2 * atan2(sqrt(a), sqrt(1-a));

	return c * raioTerra;
}

bool Paragem::operator < (const Paragem &p) const {
	if (getNumClientes()==p.getNumClientes()) return getNome()<p.getNome();
	else return getNumClientes()<p.getNumClientes();}

bool Paragem::operator == (const Paragem &p) const {
	return (getNumClientes()==p.getNumClientes() && getNome()==p.getNome());}



void Paragens::addParagem(Paragem &p1){
	paragens.push_back(p1);
	paragensbst.insert(p1);}

Paragem* Paragens::getParagem(int id){return &paragens.at(id);}

void Paragens::aumentaNumClientes(string nome){
	Paragem *par = findParagem(nome);
	paragensbst.remove(*par);
	par->aumentaNumClientes();
	paragensbst.insert(*par);
}

void Paragens::diminuiNumClientes(string nome){
	Paragem *par = findParagem(nome);
	paragensbst.remove(*par);
	par->diminuiNumClientes();
	paragensbst.insert(*par);
}

void Paragens::printParagens() const{
	cout << left << setw(6) << "id" << setw(18) << "Localidade" << setw(12) <<  "Clientes" << endl;;

	for (unsigned int i = 0; i < paragens.size(); i++)
		cout << left <<setw(6) << i << setw(18) << paragens.at(i).getNome() << setw(12) <<  paragens.at(i).getNumClientes()<< endl;
}

void Paragens::printParagensBST() const
{
	if (emptyParagens())
	 	cout << endl << "Nao ha paragens."<< endl;
	else{
		cout << endl << "Lista de paragens ordenadas pela BST:" << endl;
		BSTItrIn<Paragem> it(paragensbst);
		int x=0;
     	while (!it.isAtEnd()){
			x++;
			cout << setw(2) << x << " - " << setw(2) <<it.retrieve().getNumClientes() << " - " << it.retrieve().getNome() << endl;
			it.advance();
		}
	}
}

bool Paragens::emptyParagens() const{
	if (paragens.empty())
		return true;
	return false;
}

int Paragens::sizeParagens() const {return paragens.size();}

void Paragens::deleteParagem(int id) {
	paragensbst.remove(paragens.at(id));
	delete &paragens.at(id);
	paragens.erase(paragens.begin() + id);
}

Paragem* Paragens::findParagem (std::string nome){
	for (unsigned int i = 0; i < paragens.size(); i++){
		if (paragens.at(i).getNome() == nome)
			return &paragens.at(i);
	}

	Paragem *temp = new Paragem("Nenhuma", 0 , 0);

	return temp;
}

void Paragens::saveParagens() {

	ofstream mfile;

	mfile.open("paragens.txt");

	for (unsigned int i = 0; i < paragens.size(); i++) {
		mfile << paragens.at(i).getNome() << endl << paragens.at(i).getLatitude() << endl << paragens.at(i).getLongitude()
				<< endl << paragens.at(i).getNumClientes() << endl;
	}

	mfile.close();

}

void Paragens::loadParagens() {
	ifstream mfile;

	mfile.open("paragens.txt");


	while (!mfile.eof()) {
			string nome;
			double latitude, longitude;
			int clientes;

			getline(mfile, nome);
			if (nome.empty())
				break;
			mfile >> latitude;
			mfile >> longitude;
			mfile >> clientes;
			Paragem temp(nome, latitude, longitude, clientes);
			paragens.push_back(temp);
			paragensbst.insert(temp);
			mfile.ignore(1);
		}
	mfile.close();

}

Oficina::Oficina(string nome, double latitude, double longitude){
	this->nome = nome;
	this->latitude = latitude;
	this->longitude = longitude;
	this->disponibilidade = 0;
}

Oficina::Oficina(std::string nome, double latitude, double longitude, unsigned int disp){
	this->nome = nome;
	this->latitude = latitude;
	this->longitude = longitude;
	this->disponibilidade = disp;

}

string Oficina::getNome() const { return nome; }

double Oficina::getLatitude() const { return latitude; }

double Oficina::getLongitude() const { return longitude; }

double Oficina::getDisponibilidade() const { return disponibilidade; }

void  Oficina::setNome(std::string nome) { this->nome = nome; }

void  Oficina::setLatitude(double latitude) { this->latitude = latitude; }

void  Oficina::setLongitude(double longitude) { this->longitude = longitude; }

void  Oficina::setDisponibilidade(int val) { disponibilidade = val; }

bool Oficina::operator < (Oficina &o1) {
	if (this->getDisponibilidade() < o1.getDisponibilidade())
		return true;

	return false;
}

priority_queue <Oficina *> Oficinas::getOficinas() const {return oficinas;}

void Oficinas::addOficina (Oficina *o1){
	oficinas.push(o1);
}

void Oficinas::printOficinas() const{
	priority_queue <Oficina *> temp = oficinas;
	unsigned int size = temp.size();
	cout << "id " << " Disp.(dias)" << "   Nome " << endl << endl;
	for (unsigned int i = 0; i < size; i++){
		cout << i << "   " << left << setw(11) << temp.top()->getDisponibilidade() << "   " << temp.top()->getNome() << endl;
		temp.pop();
	}
}

bool Oficinas::emptyOficinas() const{
	if (oficinas.empty())
		return true;
	return false;
}

int Oficinas::sizeOficinas() const {return oficinas.size();}

void Oficinas::deleteOficina(int id){

	vector<Oficina *> v1;

	for (int i = 0; i < id; i++){
		v1.push_back (oficinas.top());
		oficinas.pop();
	}
	delete oficinas.top();
	oficinas.pop();

	for (unsigned int i = 0; i < v1.size(); i++)
		oficinas.push(v1.at(i));
}

void Oficinas::saveOficinas() {

	ofstream mfile;

	priority_queue<Oficina *> temp = oficinas;

	mfile.open("oficinas.txt");

	for (unsigned int i = temp.size(); i != 0; i--) {
		mfile << temp.top()->getNome() << endl << temp.top()->getLatitude() << endl << temp.top()->getLongitude()
				<< endl << temp.top()->getDisponibilidade() << endl;
		temp.pop();
	}

	mfile.close();

}

void Oficinas::loadOficinas() {
	ifstream mfile;

	mfile.open("oficinas.txt");


	while (!mfile.eof()) {
			string nome;
			double latitude, longitude;
			int disp;

			getline(mfile, nome);
			if (nome.empty())
				break;
			mfile >> latitude;
			mfile >> longitude;
			mfile >> disp;
			Oficina *temp = new Oficina(nome, latitude, longitude, disp);
			oficinas.push(temp);
			mfile.ignore(1);
		}

	mfile.close();

}

Oficina* Oficinas::findOficina(std::string nome){

	priority_queue <Oficina *> temp = oficinas;

	for (unsigned int i = temp.size(); i != 0; i--){
		if (temp.top()->getNome() == nome)
			return temp.top();
		else temp.pop();
	}

	return NULL;
}

