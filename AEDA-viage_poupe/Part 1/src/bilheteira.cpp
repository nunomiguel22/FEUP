#include "bilheteira.h"
#include "viagens.h"
#include "cartao.h"
#include "comboios.h"
#include "geral.h"


using namespace std;

/*
 * Metodos class compra
 *
 */


//Construtor

Compra::Compra(Viagem *v, Cartao *c, double pf, Datas *dc, Horas *hc){
	v1 = v;
	c1 = c;
	precoFinal = pf;
	dCompra = dc;
	hCompra = hc;
}

//Destrutor
Compra::~Compra(){
	double vgmhoras = v1->getDataPartida()->getTotalHours() + v1->getHorasPartida()->getTotalHours();
	Datas *temp = getDataActual();
	Horas *hTemp = getHoraActual();
	double cTime = temp->getTotalHours() + hTemp->getTotalHours();
	if (cTime > vgmhoras)
		delete v1;

	delete dCompra;
	delete hCompra;
	delete temp;
	delete hTemp;
}

//Acessors

std::string Compra::getInfo() const{
	stringstream ss;

	ss << *dCompra << "      " << *hCompra << "           " << left <<setfill(' ') <<setw(9)
		<< v1->getOrigem() << setw(9) << v1->getDestino() << *v1->getDataPartida() << "      "
		<< *v1->getHorasPartida()<< "           " << left <<setw(16) << setfill(' ')
		<<v1->getPrecoBase() << setw(6) << precoFinal << endl;

	return ss.str();
}

Viagem* Compra::getViagem() const {return v1;}

Cartao* Compra::getCartao() const{return this->c1;}

Datas* Compra::getDataCompra() const {return dCompra;}

Horas* Compra::getHoraCompra() const {return hCompra;}

double Compra::getPrecoFinal() const {return precoFinal;}


//Outros

bool Compra::operator == (const Compra &c2){
	float c1hf = this->dCompra->getTotalHours() + this->hCompra->getTotalHours();
	float c2hf = c2.dCompra->getTotalHours() + c2.hCompra->getTotalHours();

	if ( (c1hf == c2hf) && (*this->v1 == *c2.v1) && (this->precoFinal == c2.precoFinal))
		return true;

	return false;
}

/*
 * Metodos class Bilheteira
 *
 */

//Construtor

Bilheteira::Bilheteira(Frota *frt){
	f = frt;
}

//Destructor

Bilheteira::~Bilheteira(){
	for (unsigned int i = 0; i < viagens.size(); i++)
		delete viagens.at(i);
}

//Acessors

int Bilheteira::getNumViagens() const {return viagens.size();}

Viagem* Bilheteira::getViagem(int id) {return viagens.at(id);}

string Bilheteira::getInfo(){
	updateViagens();
	stringstream ss;

	ss << left <<"id  " << setw(10) << "Origem" << setw(10) << "Destino" << setw(15)
			<< "Distancia(KM)" << setw(9) << "Comboio" << setw(13) << "Data"
			<< setw(8) <<  "Hora" << setw(16) << "Preco base(€)"<< setw(7) << "Vagas" << "\n";

	for (unsigned int i = 0; i < viagens.size(); i++){
		ss << i << "   " << viagens.at(i)->getInfo();
	}

	return ss.str();
}

//Outros

void Bilheteira::adicionaViagem(Viagem *v1){viagens.push_back(v1);}

void Bilheteira::updateViagens(){

	//Remove viagens ja inciadas do vector

	Horas *tempHora = getHoraActual();
	Datas *tempData = getDataActual();
	float horasActual = tempData->getTotalHours() + tempHora->getTotalHours();
	for (unsigned int i = 0; i < viagens.size(); i++){
		float horasViagem = viagens.at(i)->getDataPartida()->getTotalHours() + viagens.at(i)->getHorasPartida()->getTotalHours();
		if (horasActual > horasViagem){
			if ( !(viagens.at(i)->compraRegisto()) ){
				delete viagens.at(i);
				viagens.erase(viagens.begin()+i);


			}
			else{
				viagens.erase(viagens.begin()+i);
			}
		}
	}

	//Selection Sort, organizado por viagens que saiam primeiro para viagens que saiam mais tarde

	for (unsigned int i = 0; i < viagens.size(); i++){
		double horasi = viagens.at(i)->getDataPartida()->getTotalHours() + viagens.at(i)->getHorasPartida()->getTotalHours();
		for (unsigned int j = i + 1; j < viagens.size(); j++){
			double horasj = viagens.at(j)->getDataPartida()->getTotalHours() + viagens.at(j)->getHorasPartida()->getTotalHours();

			if (horasi > horasj){
				Viagem *temp = viagens.at(i);
				viagens.at(i) = viagens.at(j);
				viagens.at(j) = temp;
			}
		}
	}
}

void Bilheteira::loadViagens(){
	ifstream mfile;

	mfile.open ("viagens.txt");

	string statline;

	getline(mfile, statline);

	while (!mfile.eof() && !statline.empty()) {

		string origem, destino;
		double distancia;
		int comboioId;
		string datavgm, horavgm;
		int vagas, comprasAnonimas;

		getline (mfile, origem);
		getline (mfile, destino);
		mfile >> distancia;
		mfile >> comboioId;
		mfile.ignore(1);

		// DATA DA VIAGEM

		Datas *dvgm;
		try{
			getline(mfile, datavgm);
			dvgm = new Datas (datavgm);
		}
		catch (Datas::DataInvalida){
			cout << "Data Invalida - Dia(1-31), Mes (1-12)" << endl;
			cout << endl << "AVISO - Dados corrompidos / incompletos" << endl;
			return;
		}
		catch (Datas::FormatoStringInvalido){
			cout << "Formato invalido - (DD-MM-AAAA)" << endl;
			cout << endl << "AVISO - Dados corrompidos / incompletos" << endl;
			return;
		}

		// HORA DA VIAGEM

		Horas *hvgm;
		try {
			getline (mfile, horavgm);
			hvgm = new Horas (horavgm);
		}
		catch (Horas::HoraInvalida){
			cout << "Hora Invalida - Hora(0-23), Min (0-59)" << endl;
			cout << endl << "AVISO - Dados corrompidos / incompletos" << endl;
			return;
		}
		catch (Horas::FormatoStringInvalido){
			cout << "Formato invalido - (HH-MM)" << endl;
			cout << endl << "AVISO - Dados corrompidos / incompletos" << endl;
			return;
		}


		mfile >> vagas;



		mfile >> comprasAnonimas;

		Viagem *temp = new Viagem(origem, destino, distancia, f->getComboio(comboioId),
				dvgm, hvgm, vagas, comprasAnonimas);

		adicionaViagem(temp);
		mfile.ignore(1);
		getline(mfile, statline);
	}

	mfile.close();
	updateViagens();
}

void Bilheteira::saveViagens(){
	updateViagens();
	ofstream mfile;

	mfile.open ("viagens.txt");

	for (unsigned int i= 0; i < viagens.size(); i++){
		mfile << "Viagem" << endl << viagens.at(i)->getOrigem() << endl
				<< viagens.at(i)->getDestino() << endl << viagens.at(i)->getDistancia()
				<< endl << viagens.at(i)->getComboio()->getId()<< endl	<< *viagens.at(i)->getDataPartida()
				<< endl << *viagens.at(i)->getHorasPartida() << endl << viagens.at(i)->getVagas()
				<< endl << viagens.at(i)->getComprasAnonimas() << endl;
	}

	mfile.close();
}
