#include "Maquinistas.h"

Maquinista::Maquinista(string n, string a, int i, vector<Viagem *> v) : nome(n), apelido(a), id(i) {
	ativo = true;
	viagens = v;
}

Maquinista::Maquinista(string n, string a, int i) : nome(n), apelido(a), id(i) {
	ativo = true;
}

Maquinista::Maquinista(string n, string a, int i, int atual) : nome(n), apelido(a), id(i)
{
	ativo = atual;
}

bool Maquinista::eliminaViagem(unsigned int id) {
	if (id >= viagens.size()) return false;
	vector<Viagem *> via;
	for (unsigned int i = 0; i < viagens.size(); i++) {
		if (i != id)
			via.push_back(viagens.at(i));
	}
	viagens = via;

	return true;
}
bool Maquinista::eliminaViagens() {
	if (!viagens.size())
		return false;
	viagens.clear();
	return true;
}

void Maquinista::alteraEstado() {
	//ativo = !ativo;
	if (ativo) {
		ativo = false;
	}
	else {
		ativo = true;
	}
}


bool Maquinista::adicionaViagem(Viagem *v) {
	viagens.push_back(v);
	return true;
}

bool Maquinista::operator== (Maquinista M3) {
	return (bool)(id = M3.getId());
}

bool Maquinistas::encontraMaquinista( Maquinista *M00) {
	tabHMaq::const_iterator it;
	it = maquinistas.find(*M00);
	if (it != maquinistas.end())
		return true;
	return false;
}

bool Maquinistas::alteraEstado(Maquinista *M1) {
	tabHMaq::const_iterator it;
	it = maquinistas.find(*M1);
	if (it == maquinistas.end()) {
		return false;
	}
	Maquinista M2(it->getNome(), it->getApelido(), it->getId(), !it->getAtivo());
	maquinistas.erase(it);
	//se se vai reforma, apagar viagens atribuidas
	if (!M2.getAtivo()) {
		M2.eliminaViagens();
	}
	pair<tabHMaq::iterator, bool> res = maquinistas.insert(M2);
	if (res.second == true)
		return true;
	return false;
}

bool Maquinistas::loadMaquinistas(Frota *f, string nome) {
	bool sucedido = true, vazio = true;
	ifstream maqfile;
	
	maqfile.open("maquinistas.txt");
	while (!maqfile.eof()) {
		int estado, id, numViagens= 0;
		string Pnome, apelidos;	
		maqfile >> estado;
		maqfile.ignore(1);
		maqfile >> id;	
		maqfile.ignore(1);
		maqfile >> Pnome;	
		
		if (Pnome == "" )
			break;
		vazio = false;
		getline(maqfile, apelidos);
		maqfile >> numViagens;
		maqfile.ignore(1);
		Maquinista M1(Pnome, apelidos, id);
		if (!estado)
			M1.alteraEstado();
		while(numViagens) {
			numViagens--;
			string origem, destino;
			double distancia;
			int comboioId;
			string datavgm, horavgm;
			int vagas, comprasAnonimas;
			
			maqfile >> origem;			
			maqfile.ignore(1);
			maqfile >> destino;
			maqfile.ignore(1);
			maqfile >> distancia;
			maqfile.ignore(1);
			maqfile >> comboioId;
			maqfile.ignore(1);
			maqfile >> vagas;
			maqfile.ignore(1);
			maqfile >> comprasAnonimas;
			maqfile.ignore(1);
			// DATA DA VIAGEM
			Datas dvgm;
			try {
				getline(maqfile, datavgm);
				dvgm = Datas (datavgm);
			}
			catch (Datas::DataInvalida) {
				cout << "Em maquinistas exixte uma data Invalida - Dia(1-31), Mes (1-12)" << endl;
				cout << endl << "AVISO - Dados corrompidos / incompletos" << endl;
				return false;
			}
			catch (Datas::FormatoStringInvalido) {
				cout << "Em maquinistas exixte um formato invalido - (DD-MM-AAAA)" << endl;
				cout << endl << "AVISO - Dados corrompidos / incompletos" << endl;
				return false;
			}

			// HORA DA VIAGEM

			Horas hvgm;
			try {
				getline(maqfile, horavgm);
				hvgm = Horas (horavgm);
			}
			catch (Horas::HoraInvalida) {
				cout << "Em maquinistas exixte uma hora Invalida - Hora(0-23), Min (0-59)" << endl;
				cout << endl << "AVISO - Dados corrompidos / incompletos" << endl;
				return false;
			}
			catch (Horas::FormatoStringInvalido) {
				cout << "Em maquinistas exixte um formato invalido - (HH-MM)" << endl;
				cout << endl << "AVISO - Dados corrompidos / incompletos" << endl;
				return false;
			}
			
			Viagem *temp = new Viagem(origem, destino, distancia, f->getComboio(comboioId),
				dvgm, hvgm, vagas, comprasAnonimas);
			M1.adicionaViagem(temp);
		}
		
		if (!adicionaMaquinista(&M1)) {
			sucedido = false;
		}
			
	}
	if (vazio) {
		cout << "O ficheiro de maquinistas está vazio! " << endl;
	}
	maqfile.close();
	return sucedido;
}

void Maquinistas::saveMaquinistas() {
	ofstream maqfile;

	maqfile.open("maquinistas.txt");
	for (auto it : this->maquinistas) {
		maqfile << it.getAtivo() << " " << it.getId() << " " << it.getNome() << " " << it.getApelido() << endl ;
		vector <Viagem*> viagens = it.getViagens();
		maqfile << viagens.size() << " ";
		for(unsigned int i=0; i < viagens.size(); i++) {
			maqfile << viagens.at(i)->getOrigem() << " " << viagens.at(i)->getDestino() << " " << viagens.at(i)->getDistancia()
				<< " " << viagens.at(i)->getComboio()->getId() << " "<< viagens.at(i)->getVagas() << " " << viagens.at(i)->getComprasAnonimas()
				<< " " << viagens.at(i)->getDataPartida() << endl << viagens.at(i)->getHorasPartida() << endl;
		}
	}	
	maqfile.close();
}

void Maquinistas::saveMaquinista(Maquinista *maq) {
	ofstream maqfile;

	maqfile.open("maquinistas.txt");

	maqfile << maq->getAtivo() << " " << maq->getId() << " " << maq->getNome() 
		<< " " << maq->getApelido() << endl;

	maqfile.close();
}
ostream & operator << (ostream &out, const Maquinista & M) {
	out << M.getAtivo() << "  " << M.getId() << " : " << M.getNome() << " " << M.getApelido() << endl;
	
	return out;
}

void Maquinistas::clearMaquinistas() {
	maquinistas.clear();	
}


bool Maquinistas::emptyMaquinistas() {
	tabHMaq::const_iterator it;
	for (auto it : this->maquinistas){
		if (it.getNome() != "") {
			return false;
		}
	}
	
	return true;
}

bool Maquinistas::adicionaMaquinista(Maquinista *trabalhador) {
	pair<tabHMaq::iterator,bool> res = maquinistas.insert(*trabalhador);
	if (res.second == true)
		return true;
	else return false;
}


bool Maquinistas::editaMaquinista(Maquinista *trabalhador1, Maquinista* trabalhador2) {
	if (!eliminaMaquinista(trabalhador1))
		return false;
	adicionaMaquinista(trabalhador2);
	return true;
}

bool Maquinistas::eliminaMaquinista(Maquinista *trabalhador) {
	tabHMaq::const_iterator it;
	it = maquinistas.find(*trabalhador);
	if (it != maquinistas.end()) {
		maquinistas.erase(it);
		return true;
	}
	
	return false;
}

unsigned int Maquinistas::numeroDeMaquinistas() {
	return maquinistas.size();
}

void Maquinistas::showMaquinistas() {
	cout << endl << "ESTADO" << setw(10) << "ID" << setw(15) << "Nome" << setw(15) << "Apelidos" << endl;
	for (auto it : this->maquinistas) {
		if (it.getAtivo()) {
			cout << "Ativo" << setw(11) << it.getId() << setw(15) << it.getNome() << setw(15) << it.getApelido() << endl;
		}
		else {
			cout << "Reformado" << setw(7) << it.getId() << setw(15) << it.getNome() << setw(15) << it.getApelido() << endl;
		}
	}
}

void Maquinistas::showMaquinistaseViagens() {
	vector <Viagem *> via;
	cout << endl << "ESTADO" << setw(10) << "ID" << setw(15) << "Nome" << setw(15) << "Apelidos" << endl;
	for (auto it : this->maquinistas  ) {
		if (it.getAtivo()) {
			cout << "Ativo" << setw(11) << it.getId() << setw(15) << it.getNome() << setw(15) << it.getApelido() << endl;
		}
		else {
			cout << "Reformado" << setw(7)<<  it.getId() << setw(15) << it.getNome()<< setw(15) << it.getApelido() << endl << endl;
		}
		via = it.getViagens();
		if (via.size()){
			cout << endl;
			cout << "Origem" << setw(10) << "Destino" << setw(15)
				<< "Distancia(KM)" << setw(9) << "Comboio" << setw(13) << "Data"
				<< setw(8) << "Hora" << setw(16) << "Preco base(€)" << setw(7) << "Vagas" << "\n";
			for (unsigned int i = 0; i < via.size(); i++) {
				cout << via.at(i)->getInfo();
			}
			cout << endl;
		}
	}	
}

void Maquinistas::showMaquinista(Maquinista *M1) {
	tabHMaq::const_iterator it;
	it = maquinistas.find(*M1);
	if (it != maquinistas.end()) {
		cout << "ESTADO" << setw(9) << "ID" << setw(15) << "Nome" << setw(15) << "Apelidos" << endl;
		if (it->getAtivo()) {
			cout << "Ativo" << setw(10);
		}
		else {
			cout << "Reformado" << setw(6);
		}
		cout << it->getId() << setw(15) << it->getNome() << setw(15) << it->getApelido() << endl;

	}
	return;
}

bool Maquinistas::EliminaViagemDoId(Maquinista* M1 , int id) {
	vector <Viagem *> via;
	tabHMaq::const_iterator it;
	it = maquinistas.find(*M1);
	Maquinista M2 = *it;
	if (it != maquinistas.end()) {
		via = it->getViagens();
		if (!via.size())
			if (it->getAtivo()) {
				cout << "ERRO: Ainda nao existem viagens associadas !! " << endl;
				return false;
			}
			else {
				cout << "Um maquinista reformado nao tem viagens associadas ! " << endl;
			}
		else {
			maquinistas.erase(M2);
			if (!M2.eliminaViagem(id))
				return false;
			pair<tabHMaq::iterator, bool> res = maquinistas.insert(M2);
			if (res.second == true)
				return true;

		}
	}
	return false;

}
bool Maquinistas::showViagensMaquinistas( Maquinista* M1 ) const {
	vector <Viagem *> via;
	tabHMaq::const_iterator it;
	it = maquinistas.find(*M1);
	if (it != maquinistas.end()) {	
		via = it->getViagens();
		if (!via.size())
			if (it->getAtivo()) {
				cout << "ERRO: Ainda nao existem viagens associadas !! " << endl;
				return false;
			}
			else {
				cout << "Um maquinista reformado nao tem viagens associadas ! " << endl;
			}
		else {
			cout << "Viagens atribuidas : " << it->getViagens().size()  << endl << endl;
			cout << setw(10) << "ID" << setw(10) << "Origem" << setw(10) << "Destino" << setw(15)
				<< "Distancia(KM)" << setw(9) << "Comboio" << setw(13) << "Data"
				<< setw(8) << "Hora" << setw(16) << "Preco base(€)" << setw(7) << "Vagas" << "\n";
			for (unsigned int i = 0; i < via.size(); i++) {
				cout << setw(10) << i << setw(10) << via.at(i)->getInfo();
			}
		}
		return true;
	}
	return false;
}

bool Maquinistas::atribuiViagem( Maquinista* M1, Viagem * v) {
	tabHMaq::const_iterator it;
	it = maquinistas.find(*M1);
	Maquinista M2 = *it;

	//so pode atribuir viegens a maquinistas que estejam ativos
	if (M1->getAtivo()) {
		maquinistas.erase(M2);
		M2.adicionaViagem(v);
		pair<tabHMaq::iterator, bool> res = maquinistas.insert(M2);
		if (res.second == true)
			return true;
	}
	return false;

	
}



