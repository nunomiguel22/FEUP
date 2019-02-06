#include "comboios.h"
#include "geral.h"

using namespace std;

/*
 * Metodos da class Comboio
 *
 */

// Construtor

Comboio::Comboio(int numPassageiros, int velocidade, double precoKM, string nome) {
	this->lotacao = numPassageiros;
	this->velocidade = velocidade;
	this->precoKM = precoKM;
	this->nome = nome;
	id = 0;
	avariado = false;
}


 // Acessors

string Comboio::getTipo() const{return "OT";}

unsigned int Comboio::getLotacao() const{return lotacao;}

int Comboio::getVelocidade() const{return velocidade;}

double Comboio::getPrecoKM() const{return precoKM;}

string Comboio::getNome() const{ return nome;}

unsigned int Comboio::getId() const{return id;}

Paragem Comboio::getUltimaParagem() const { return ultimaParagem; }

bool Comboio::getAvariado() const {return avariado;}

Oficina* Comboio::getOficina() const {return ofic;}

double Comboio::getDataUltimaAvaria() const {return dataUltimaAvaria;}

//Outros

void Comboio::setId(int id){this->id = id;}

void Comboio::setNome(string nome){this->nome = nome;}

void Comboio::setLotacao(int lot){this->lotacao = lot;}

void Comboio::setVelocidade(int vel){this->velocidade = vel;}

void Comboio::setPreco(double prc){this->precoKM = prc;}

void Comboio::setUltimaParagem(Paragem &p1){this->ultimaParagem = p1;}

void Comboio::setAvaria(priority_queue<Oficina *> oficinas, double distmaxima){

	if (this->getAvariado())
		return;

	priority_queue <Oficina *> temp = oficinas;

	float horasActual = getHoraActual().getTotalHours() + getDataActual().getTotalHours();

	unsigned int i;
	unsigned int size = temp.size();

	for (i = 0; i < size; i++){
		double dist = this->getUltimaParagem().distancia(temp.top()->getLatitude() ,temp.top()->getLongitude());
		if ( dist < distmaxima){
			ofic = temp.top();
			temp.top()->setDisponibilidade(temp.top()->getDisponibilidade() + 3);
			this->dataUltimaAvaria = horasActual;
			this->setAvariado(true);
			break;
		}
		else temp.pop();
	}

	if (i == size)
		cout << "Nenhuma oficina está disponivel" << endl;


}

void Comboio::setDataAvaria(double dataav){this->dataUltimaAvaria = dataav;}

void Comboio::setOficina(Oficina *o1) { ofic = o1; };

void Comboio::setAvariado(bool avariado) { this->avariado = avariado; }

/*
 * Metodos da class AlfaPendular
 *
 */

//Construtor

AlfaPendular::AlfaPendular(int numPassageiros, int velocidade, double precoKM, string nome)
: Comboio(numPassageiros, velocidade, precoKM, nome){}


//Outros

string AlfaPendular::getTipo() const{return "AP";}

/*
 * Metodos da class Intercidades
 *
 */

// Construtor

Intercidades::Intercidades(int numPassageiros, int velocidade, double precoKM, string nome)
: Comboio(numPassageiros, velocidade, precoKM, nome){}

// Outros

string Intercidades::getTipo() const{return "IC";}

/*
 * Metodos da class Frota
 *
 */

//Destructor

Frota::~Frota(){
	for (unsigned int i = 0; i < comboios.size(); i++)
		delete comboios.at(i);
}

//Acessors

string Frota::getInformacao() {
	this->updateManuntencao();

	stringstream ss;
	ss << "ID" << setw(7) << "Nome" << setw(7) << "Tipo" << setw(9) << "Lotacao"
			<< setw(12) << "Velocidade"	<< setw(15) << "Preco por Km" << setw(17) <<"Ultima Paragem" << setw(10)
			<< "Avariado" << setw(10) << "Oficina" <<"\n";
				for (unsigned int i = 0; i < comboios.size();i++){
					ss << i << setw(6) << comboios.at(i)->getNome() << setw(7) << comboios.at(i)->getTipo()
							<< setw(9) << comboios.at(i)->getLotacao() << setw(8);
					ss << comboios.at(i)->getVelocidade() << " km/h" << setw(12)
							<< comboios.at(i)->getPrecoKM() << "€" << setw(17) << comboios.at(i)->getUltimaParagem().getNome();
					if (comboios.at(i)->getAvariado()){
						ss << setw(10) << "Sim" << setw(13) << comboios.at(i)->getOficina()->getNome() << endl;
					}
					else ss << setw(10) << "Nao" << endl;
				}

	return ss.str();

}

Comboio* Frota::getComboio(unsigned int id) const{
	if (id >= comboios.size())
		return NULL;	
	return comboios.at(id);
}

int Frota::getNumComboios() const{return comboios.size();}

//Outros


void Frota::adicionaComboio(Comboio *c1) {
	comboios.push_back(c1);
	c1->setId(comboios.size());
}

void Frota::loadComboios(Oficinas *o){


	ifstream mfile;

	mfile.open ("comboios.txt");

	while (!mfile.eof()) {
		string nome;
		unsigned int lotacao;
		string tipo;
		int velocidade;
		double precoKM;
		Comboio *c1;
		bool avaria;

		mfile >> nome;
		if (nome == "")
			break;
		mfile.ignore(1);
		mfile >> lotacao;
		mfile.ignore(1);
		mfile >> tipo;
		mfile.ignore(1);
		mfile >> velocidade;
		mfile.ignore(1);
		mfile >> precoKM;
		mfile.ignore(1);
		mfile >> avaria;


		if (tipo == "IC" || tipo == "ic" || tipo == "Ic" || tipo == "iC")
			c1 = new Intercidades (lotacao, velocidade, precoKM, nome);
		else c1 = new AlfaPendular (lotacao, velocidade, precoKM, nome);

		if (avaria){
			string ofinome;
			double dataavaria;
			mfile.ignore(1);
			mfile >> dataavaria;
			mfile.ignore(1);
			mfile >> ofinome;

			c1->setAvariado(true);
			Oficina *temp = o->findOficina(ofinome);
			c1->setOficina(temp);
			c1->setDataAvaria(dataavaria);
		}



		adicionaComboio(c1);
	}
	mfile.close();
}

void Frota::saveComboios() const{
	ofstream mfile;

	mfile.open ("comboios.txt");

	for (unsigned int i= 0; i < comboios.size(); i++){
		mfile << comboios.at(i)->getNome() << " " << comboios.at(i)->getLotacao() <<" " << comboios.at(i)->getTipo();
		mfile << " " << comboios.at(i)->getVelocidade() << " " << comboios.at(i)->getPrecoKM() << " " <<comboios.at(i)->getAvariado();
		if (comboios.at(i)->getAvariado())
			mfile << " " << comboios.at(i)->getDataUltimaAvaria() << " " << comboios.at(i)->getOficina()->getNome() << endl;
		else mfile << endl;



	}

	mfile.close();
}

void Frota::updateManuntencao(){

	float horasActual = getHoraActual().getTotalHours() + getDataActual().getTotalHours();

	for (unsigned int i = 0; i < comboios.size(); i++){
		if (comboios.at(i)->getAvariado()){
			if (horasActual > comboios.at(i)->getDataUltimaAvaria() + 72){
				comboios.at(i)->setAvariado(false);
				Oficina * temp = comboios.at(i)->getOficina();
				temp->setDisponibilidade(temp->getDisponibilidade() - 3);
			}
		}
	}
}

void Frota::removeComboio(unsigned int id){
	delete comboios.at(id);
	comboios.erase(comboios.begin()+id);
}



