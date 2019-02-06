#include "viagens.h"
#include "geral.h"
using namespace std;

/*
 * Metodos class Viagem
 *
 *
 */

//Construtores

//Usado ao criar uma nova viagem
Viagem::Viagem(std::string ori, std::string dest, double dist, Comboio *c, Datas *dp, Horas *hp){
	origem = ori;
	destino = dest;
	distancia = dist;
	c1 = c;
	dPartida = dp;
	hPartida = hp;
	vagas = c->getLotacao();
	precoBase = c1->getPrecoKM() * distancia;
	comprasAnonimas = 0;
}

//Usado a carregar uma viagem em progresso de um ficheiro
Viagem::Viagem(std::string ori, std::string dest, double dist, Comboio *c,
		Datas *dp, Horas *hp, int vagas, int comprasAnon){
	origem = ori;
	destino = dest;
	distancia = dist;
	c1 = c;
	dPartida = dp;
	hPartida = hp;
	this->vagas = vagas;
	precoBase = c1->getPrecoKM() * distancia;
	comprasAnonimas = comprasAnon;
}

//Usado para adicionar a uma compra no historico de um passageiro (comboio, vagas irrelevantes)
Viagem::Viagem(std::string ori, std::string dest, Datas *dp, Horas *hp, double precoBase){
	origem = ori;
	destino = dest;
	distancia = 0;
	dPartida = dp;
	hPartida = hp;
	vagas = 0;
	this->precoBase = precoBase;
	comprasAnonimas = 0;
	Comboio *temp = new Comboio(0, 0, 0, "temp");
	c1 = temp;
}

//Destructor

Viagem::~Viagem(){
	delete hPartida;
	delete dPartida;
}

// Acessors

Datas* Viagem::getDataPartida() const{ return dPartida;}

Horas* Viagem::getHorasPartida() const{return hPartida;}

double Viagem::getPrecoBase () const{return precoBase;}

std::string Viagem::getOrigem() const {return origem;}

std::string Viagem::getDestino() const{return destino;}

double Viagem::getDistancia() const  {return distancia;}

Comboio* Viagem::getComboio() const {return c1;}

unsigned int Viagem::getVagas() const{return vagas;}

unsigned int Viagem::getComprasAnonimas() const{return comprasAnonimas;}

std::string Viagem::getInfo() const{
	stringstream ss;
	ss << left << setw(10) << origem << setw(10) << destino << setw(15) << distancia
			<< *c1 << "    "  << *dPartida << "   "	<< *hPartida << "   " << left << setfill(' ')
			<< setw(16) << precoBase  <<  setfill(' ') << setw(5) << vagas <<"\n";
	return ss.str();
}

//Outros

int Viagem::reservaBilhete(bool reg){
	if (vagas <= 0)
		return -1;
	vagas--;
	if (!reg)
		comprasAnonimas++;
	return 0;
}

int Viagem::devolveBilhete(bool reg){
	if (vagas >= c1->getLotacao())
		return -1;
	if (!reg){
		if (comprasAnonimas == 0)
			return -1;
		else comprasAnonimas--;
	}
	vagas++;
	return 0;
}

double Viagem::getPrecoFinal(){

	Horas *tempHora = getHoraActual();
	Datas *tempData = getDataActual();

	float horasActual = tempData->getTotalHours() + tempHora->getTotalHours();
	float horasViagem = getDataPartida()->getTotalHours() + getHorasPartida()->getTotalHours();

	if ( ( horasViagem - horasActual ) <= 48 && ( horasViagem - horasActual ) > 0
			&& vagas > (c1->getLotacao() / 2))
		return precoBase * 0.30;

	return precoBase;
}

double Viagem::getPrecoFinal(Cartao *c){
	Horas *tempHora = getHoraActual();
	Datas *tempData = getDataActual();

	float horasActual = tempData->getTotalHours() + tempHora->getTotalHours();
	float horasViagem = getDataPartida()->getTotalHours() + getHorasPartida()->getTotalHours();

	if ( ( horasViagem - horasActual ) <= 48 && ( horasViagem - horasActual ) > 0
			&& vagas > (c1->getLotacao() / 2))
		if (c->getDesconto() < 70)
			return precoBase * 0.30;

	return precoBase * ((double)c->getDesconto() / 100);
}

bool Viagem::operator == (const Viagem &v2){
	float v1hf = this->dPartida->getTotalHours()+this->hPartida->getTotalHours();
	float v2hf = v2.dPartida->getTotalHours() + v2.hPartida->getTotalHours();
	if ( (v1hf == v2hf) && (this->destino == v2.destino) && (this->origem == v2.origem) && (this->distancia == v2.distancia)
			&& this->precoBase == v2.precoBase)
		return true;
	return false;

}

bool Viagem::compraRegisto() const{
	if ( (vagas + comprasAnonimas) == c1->getLotacao())
		return false;
	return true;
}
