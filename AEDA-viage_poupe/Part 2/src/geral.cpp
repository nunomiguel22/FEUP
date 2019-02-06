#include "geral.h"
//#pragma warning(disable : 4996)

using namespace std;

void menuParagens(Paragens *p);
void menuOficinas (Oficinas *o);
void menuComboios(Frota *f);
void menuCartoes(BaseClientes *r);

Datas getDataActual(){
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	Datas temp (now->tm_year+ 1900, now->tm_mon+1, now->tm_mday);
	return temp;
}

Horas getHoraActual(){
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	Horas temp(now->tm_hour, now->tm_min);
	return temp;
}

int menuInput(int nOptions){
	int menu;
	cin >> menu;
	if (cin.fail()){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Erro: Input Invalido, apenas numeros inteiros, tente outra vez" << endl;
		return -2;
	}

	if (menu > nOptions || menu < -1){
		cout << "Erro: Menu nao existe, tente outra vez" << endl;
		return -2;
	}
	return menu;
}

int userIntInput(){

	int val;
	cin >> val;
	if (cin.fail()){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Erro: Input Invalido, apenas numeros inteiros, tente outra vez." << endl;
		return -200;
	}
	return val;
}

double userDoubleInput(){
	double val;
	cin >> val;
	if (cin.fail()){
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Erro: Input Invalido, apenas numeros inteiros, tente outra vez" << endl;
		return -200;
	}
	return val;
}

bool LetrasInvalidas(string nome) {
	bool invalido = false;
	for (unsigned int i = 0; i < nome.size(); i++) {
		if (!((nome.at(i) >= 'A' && nome.at(i) <= 'Z') || (nome.at(i) >= 'a' && nome.at(i) <= 'z') || (nome.at(i) == ' ' ) || (nome.at(i) == '-')))
			invalido = true;
	}	
	return invalido;
}

string nomeValido() {
	string nome;
	bool invalido = false;
	do {
		getline(cin, nome);
		invalido = LetrasInvalidas(nome);
		if (invalido) {
			cout << "Erro: caracteres invalidos \n";
		}
	} while (invalido);
	return nome;
}

string apelidoValido() {
	bool invalido = false;
	string apelido;
	do {
		cout << "Qual o apelido ?" << endl;
		getline(cin, apelido);
		invalido = LetrasInvalidas(apelido);
		if (invalido) {
			cout << "Erro: caracteres invalidos \n";
		}	
	} while (invalido);
	return apelido;
}

Maquinista criaMaquinista() {
	string nome, apelido, viagens;
	unsigned int id;
	cout << "Qual o id do maquinista? " << endl;
	id = userIntInput();
	cin.ignore();
	cin.clear();	
	cout << "Qual o primeiro nome do maquinista ? " << endl;
	nome = nomeValido();
	apelido = apelidoValido();
	Maquinista M1(nome, apelido, id);
	return M1;
}

Viagem*  adicionaViagem(Bilheteira *b, Frota *f, Paragens *p) {
	string origem, destino, datavgm, horavgm;
	double distancia = -2;
	int id_comboio = -2;
	int numPar = 0;
	cout << endl << "---Criacao de viagem---" << endl;
	p->printParagens();
	cout << endl << "Escolha o numero de paragens:";
	numPar = userIntInput();
	cout << endl;
	if (numPar < 0 || numPar >= p->sizeParagens()){
		cout << "Valor errado!" << endl;
		return NULL;
	}
	list <Paragem> linha;

	for (int i = 1; i <= numPar; i++){
		int par;
		cout << "Insira as paragens escolhidas, paragem (" << i << "):";
		cin >> par;

		if (par < 0 || par >= p->sizeParagens()){
			cout << "Paragem nao existe!" << endl;
			return NULL;
		}

		linha.push_back (*p->getParagem(par));

	}

	origem = linha.front().getNome();

	destino = linha.back().getNome();
	distancia = linha.front().distancia(linha.back().getLatitude(), linha.back().getLongitude());

	// DATA DA VIAGEM

	Datas dvgm;
	try {
		cin.ignore();
		cin.clear();
		cout << "Data da viagem(DD-MM-AAAA): ";
		getline(cin, datavgm);
		dvgm = Datas(datavgm);
		cout << endl;
	}
	catch (Datas::DataInvalida) {
		cout << "Erro: Data Invalida - Dia(1-31), Mes (1-12)" << endl;
		return NULL;
	}
	catch (Datas::FormatoStringInvalido) {
		cout << "Erro: Formato invalido - (DD-MM-AAAA)" << endl;
		return NULL;
	}

	// HORA DA VIAGEM

	Horas hvgm;
	try {
		cout << "Hora da viagem(HH:MM): ";
		getline(cin, horavgm);
		hvgm = Horas(horavgm);
		cout << endl;
	}
	catch (Horas::HoraInvalida) {
		cout << "Erro: Hora Invalida - Hora(0-23), Min (0-59)" << endl;
		return NULL;
	}
	catch (Horas::FormatoStringInvalido) {
		cout << "Erro: Formato invalido - (HH:MM)" << endl;
		return NULL;
	}

	cout << endl << f->getInformacao() << endl;


	while (id_comboio < 0 || id_comboio >= f->getNumComboios() || f->getComboio(id_comboio)->getAvariado()) {
		cout << "Insira o Comboio que vai efectuar a viagem (-1 para cancelar): ";
		id_comboio = userIntInput();
		cout << endl;

		if (id_comboio == -1)
			return NULL;

		if ((id_comboio < -1 || id_comboio >= f->getNumComboios()) && id_comboio != -200)
			cout << "Erro: Este comboio nao existe" << endl;

		if (f->getComboio(id_comboio)->getAvariado())
			cout << "Este Comboio esta em manuntencao na oficina: " << f->getComboio(id_comboio)->getOficina()->getNome();

	}

	Comboio *c = f->getComboio(id_comboio);

	Viagem *v = new Viagem(linha, distancia, c, dvgm, hvgm, c->getLotacao(), 0);
	return v;
}

bool adicionaViagensAMaquinista(Frota *f, Bilheteira *b, Maquinista *M1, Paragens *p) {
	bool sucedido = true;
	int n = 0;
	cout << "Quantas viagens associadas ? " << endl;
	n = userIntInput();

	while (n) {
		Viagem* via = adicionaViagem(b, f, p);
		if (via != NULL) {
			M1->adicionaViagem(via);
		}
		else {
			sucedido = false;
		}
		n--;
	}
	return sucedido;
}
/*
 * Menus
 *
 *
 */

//			INFORMACAO

void menuInformacao(BaseClientes *r, Frota *f, Bilheteira *b, Maquinistas *M, Paragens *p, Oficinas *o){

	int menu = -2;

	while (menu != 7){
		while (menu == -2 || menu == -1){
			cout << endl << "---Informacao---" << endl << endl;

			cout << " 0 - Lista de Comboios" << endl;
			cout << " 1 - Lista de Viagens" << endl;
			cout << " 2 - Lista de Maquinistas " << endl;
			cout << " 3 - Lista de Maquinistas e suas repetivas viagens " << endl;
			cout << " 4 - Lista de viagens atribuidas a um maquinista " << endl;
			cout << " 5 - Lista de Paragens " << endl;
			cout << " 6 - Lista de Oficinas " << endl;
			cout << " 7 - Sair" << endl;

			menu = menuInput(7);
			if (menu == -1)
				cout << "Erro: Menu nao existe, tente outra vez" << endl;

		}
		switch (menu){
		case 0:

			menu = 7;

			if (f->getNumComboios() == 0){
				cout << endl << "Erro: Nao existem comboios" << endl;
				break;
			}

			cout << endl << "Lista de Comboios" << endl << endl;
			cout << f->getInformacao();

			break;
		case 1:
		{
			menu = 7;

			if (b->getNumViagens() == 0) {
				cout << endl << "Erro: Nao existem viagens" << endl;
				break;
			}
			cout << endl << "Lista de Viagens" << endl << endl;
			cout << b->getInfo(p);
			break;
		case 2:
			menu = 7;
			if (M->emptyMaquinistas()) {
				cout << endl << "Erro: Nao existem Maquinistas" << endl;
				break;
			}

			cout << "Lista de Maquinistas " << endl;
			M->showMaquinistas();
			break;
		}
		case 3: {
			menu = 7;
			if (M->emptyMaquinistas()) {
				cout << endl << "Erro: Nao existem Maquinistas" << endl;
				break;
			}
			cout << "Lista de Maquinistas " << endl;
			M->showMaquinistaseViagens();
			break;
		}
		case 4: {
			menu = 7;
			if (M->emptyMaquinistas()) {
				cout << endl << "Erro: Nao existem Maquinistas" << endl;
				break;
			}
			cout << endl;
			M->showMaquinistas();
			int id;
			cout << endl << "Qual o id do maquinista (-1 para cancelar)? " << endl;
			id = userIntInput();
			if (id == -1)
				return;
			Maquinista  M1("", "", id);
			cout << endl;
			M->showViagensMaquinistas(&M1);
			break;
		}
		case 5: {
			menu = 7;
			if (p->emptyParagens()) {
				cout << endl << "Erro: Nao existem paragens" << endl;
			}
			else{
				cout << endl << "Paragens:" << endl;
				p->printParagens();
			}
			break;
		}
			
		case 6:
			menu = 7;
			if (o->emptyOficinas()) {
				cout << endl << "Erro: Nao existem Oficinas" << endl;
			}
			else{
				o->printOficinas();
			}
			break;
		default:
			return;
		}
	}
}

//					MENU UTILIZADORES ANONIMOS

void menuSemCartao(BaseClientes *r, Bilheteira *b, Paragens *p){
	int menu = -2;

	while (menu != 3){

		while (menu == -2 || menu == -1){

		cout << endl << "---Passageiro sem Cartao---" << endl << endl;
		cout << endl << " 0 - Comprar Bilhete" << endl;
		cout << " 1 - Devolver Bilhete" << endl;
		cout << " 2 - Subscrever a um cartao" << endl;
		cout << " 3 - Sair" << endl;

		menu = menuInput(3);

		if (menu == -1)
			cout << "Erro: Menu nao existe, tente outra vez" << endl;
		}
		switch (menu){
		case 0:{
			// 0 - COMPRAR BILHETE
			menu = -2;
			if (b->getNumViagens() == 0){
				cout << endl << "Erro: Nao existem viagens" << endl;
				return;
			}

			int viagemId = -2;

			cout << "Lista de Viagens" << endl << endl;
			cout << endl << b->getInfo(p);
			while (viagemId >= b->getNumViagens() || viagemId < -1){

				cout << endl << "Escolha o id da viagem a reservar o bilhete (-1 para cancelar):";
				viagemId = userIntInput();
				cout << endl;

				if (viagemId == -1)
					return;

				if ((viagemId >= b->getNumViagens() || viagemId < -1) && viagemId != -200){
					cout<< endl << "Erro: Esta viagem nao existe, tente outra vez "<< endl;
				}
			}

			Viagem *temp = b->getViagem(viagemId);
			if (temp->reservaBilhete(false) == -1){
				cout << endl << "Erro: Este comboio ja esta cheio" << endl;
				break;
			}


			int origem, destino;

			temp->printParagens();
			cout << "Escolha o id paragem de origem:";
			origem = userIntInput();
			cout << endl;
			cout << "Escolha o id paragem de destino:";
			destino = userIntInput();
			cout << endl;

			if (origem >= destino){
				cout << "Paragem invalida" << endl;
				return;
			}

			list <Paragem> linha = temp->getParagens();
			list <Paragem>::iterator ori;
			list <Paragem>::iterator dest;
			ori = linha.begin();
			dest = linha.begin();
			advance(ori, origem);
			advance(dest, destino);

			double distancia = ori->distancia(dest->getLatitude(), dest->getLongitude());

			double precobase = distancia * temp->getComboio()->getPrecoKM();

			Viagem compra (ori->getNome(), dest->getNome(), temp->getDataPartida(), temp->getHorasPartida(), precobase);

			double precoFinal = compra.getPrecoFinal();
			p->aumentaNumClientes(compra.getDestino());

			cout << "Compra efectuada" << endl << endl;
			cout << "Preco Base = " << temp->getPrecoBase() << "€" << endl;
			cout << "Desconto = " <<temp->getPrecoBase() - precoFinal << "€"
					<< " (" << 100 - (precoFinal/temp->getPrecoBase() * 100) << "%)"<< endl;
			cout << "Preco Final = " << precoFinal << "€" << endl;

			return;
		}
		case 1:{ // 1 - DEVOLVER BILHETE

			if (b->getNumViagens() == 0){
				cout << endl << "Nao existem viagens" << endl;
				return;
			}

			int viagemId = -2;

			cout << "Lista de Viagens" << endl << endl;
			cout << endl << b->getInfo(p);
			while (viagemId >= b->getNumViagens() || viagemId < -1){

				cout << endl << "Escolha o id da viagem a cancelar o bilhete(-1 para cancelar):";
				viagemId = userIntInput();
				cout << endl;
				if (viagemId == -1)
					return;

				if ((viagemId >= b->getNumViagens() || viagemId < -1) && viagemId != -200){
					cout<< endl <<"Erro: Esta viagem nao existe, tente outra vez"<< endl;
				}
			}


			Viagem *temp = b->getViagem(viagemId);
			if (temp->devolveBilhete(false) == -1){
				cout << "Erro: Nao existem bilhetes sem registo para esta viagem" << endl;
				return;
			}
			p->diminuiNumClientes(temp->getDestino());
			cout << endl << "Bilhete devolvido" << endl;

			break;
		}

		case 2:{
			// 2 - SUBSCREVER A UM CARTAO
			string datans;
			int cart = -2;
			string nome;
			string profissao;
			Datas datanasc;

			if (r->getNumCartoes() == 0){
				cout << "Erro: Nao existem cartoes para subscrever" << endl;
				return;
			}

			cin.ignore();
			cin.clear();

			cout << endl << "---Subscricao de cartao---" << endl << endl;

			cout << "Nome: ";
			nome = nomeValido();

			cout << endl << "Profissao: ";
			profissao = nomeValido();

			try {
			cout << endl << "Data de Nascimento(DD-MM-AAAA): ";
			getline(cin, datans);
			cout << endl;
			datanasc = Datas(datans);
			}
			catch (Datas::DataInvalida){
				cout << "Data Invalida - Dia(1-31), Mes (1-12), tente outra vez" << endl;
				return;
			}
			catch (Datas::FormatoStringInvalido){
				cout << "Formato invalido - (DD-MM-AAAA), tente outra vez" << endl;
				return;
			}

			cout << "Tipo de Cartao: " << endl << endl;
			cout << r->getInfoCartao() << endl;;

			while (cart >= r->getNumCartoes() || cart < -1){

				cout << endl << "Escolha o cartao a subscrever:";
				cart = userIntInput();
				cout << endl;
				if (cart == -1)
					return;

				if ((cart >= r->getNumCartoes() || cart < -1) && cart != -200){
					cout<< endl <<"Erro: Este cartao nao existe, tente outra vez (-1 para cancelar)"<< endl;
				}
			}

			Registo *temp = new Registo(r->getCartao(cart), nome, profissao, datanasc);
			r->adicionaRegisto(temp);
			cout << endl << "Cartao registado, o seu ID e: " << r->getNumRegistos() -1 << endl;
			return;
		}
		case 3:
			return;
		default:
			return;
		}
	}
}


//				MENU UTILIZADORES REGISTADOS

void menuComCartao(BaseClientes *r, Bilheteira *b, Paragens *p){
	int numRegs = r->getNumRegistos();
	int id = -200;
	int menu = -2;
	bool skip = false;

	if (numRegs == 0) {
		cout << endl << "Erro: Nao existem registos." << endl;
		return;
	}

	while (id == -200 || id >= numRegs ){
		cout << "ID do seu cartao (-1 para cancelar): ";
		id = userIntInput();
		if (id >= numRegs)
			cout << "Erro: ID nao existe, tente outra vez" << endl;
		if (id == -1)
			return;
	}
	r->setId(id);

	while (menu != 5){

		cout << endl << "---Passageiro Com Cartao---" << endl << endl;

		cout << "ID: " << id << endl << endl;
		cout << r->getInformacao();

		if (!r->getRegisto()->getEstado()){ //RE-ATIVAR SUBSCRICAO
			string ans;
			cout << endl << "Subscricao desativada. Deseja re-ativar? (s/n)" << endl;
			cin.clear();
			cin.ignore();
			getline(cin, ans);
			if (ans == "s" || ans == "S"){
				cout << endl << "Cartao re-ativado" << endl << endl;
				cout << "Escolha o tipo de cartao da nova subscricao" << endl;
				r->getRegisto()->alterarEstado(true);
				menu = 2;
				skip = true;
			}
			else{
				cout << "Subscricao nao foi re-ativada" << endl;
				return;
			}
		}

		while (menu == -2 || menu == -1){
			if (!skip){
				cout << endl << " 0 - Comprar Bilhete" << endl;
				cout << " 1 - Devolver Bilhete" << endl;
				cout << " 2 - Alterar cartao subscrito" << endl;
				cout << " 3 - Remover subscricao" << endl;
				cout << " 4 - Historico de Viagens" << endl;
				cout << " 5 - Sair" << endl << endl;

				menu = menuInput(5);
				if (menu == -1)
					cout << "Erro: Menu nao existe, tente outra vez" << endl;

			}
			else break;
		}

		switch (menu){

		case 0:{
			// 0 - COMPRAR BILHETE
			menu = -2;
			if (b->getNumViagens() == 0){
				cout << endl << "Erro: Nao existem viagens" << endl;
				break;
			}

			int viagemId =  b->getNumViagens() + 1;

			cout << "Lista de Viagens" << endl << endl << endl << b->getInfo(p);

			while (viagemId >= b->getNumViagens() || viagemId < -1){

				cout << "Escolha o id da viagem a reservar (-1 para cancelar):";
				viagemId = userIntInput();
				cout << endl;

				if (viagemId == -1)
					return;

				if ((viagemId >= b->getNumViagens() || viagemId < -1) && viagemId != -200){
					cout<< endl <<"Erro: Esta viagem nao existe, tente outra vez (-1 para cancelar)"<< endl;
				}
			}

			Viagem *temp = b->getViagem(viagemId);

			if (temp->reservaBilhete(true) == -1){
				cout << endl << "Erro: Este comboio ja esta cheio" << endl;
				break;
			}

			int origem, destino;

			temp->printParagens();
			cout << "Escolha o id paragem de origem:";
			origem = userIntInput();
			cout << endl;
			cout << "Escolha o id paragem de destino:";
			destino = userIntInput();
			cout << endl;

			if (origem >= destino){
				cout << "Paragem invalida" << endl;
				return;
			}

			list <Paragem> linha = temp->getParagens();
			list <Paragem>::iterator ori;
			list <Paragem>::iterator dest;
			ori = linha.begin();
			dest = linha.begin();
			advance(ori, origem);
			advance(dest, destino);

			double distancia = ori->distancia(dest->getLatitude(), dest->getLongitude());

			double precobase = distancia * temp->getComboio()->getPrecoKM();

			Viagem compra (ori->getNome(), dest->getNome(), temp->getDataPartida(), temp->getHorasPartida(), precobase);



			double precoFinal = compra.getPrecoFinal(r->getRegisto()->getCartao());


			Compra *tempC = new Compra( compra, *r->getRegisto()->getCartao(), precoFinal, getDataActual(), getHoraActual() );
			r->getRegisto()->adicionaCompra(tempC);

			p->aumentaNumClientes(compra.getDestino());

			cout << "Compra efectuada" << endl << endl;
			cout << "Preco Base = " << temp->getPrecoBase() << "€" << endl;
			cout << "Desconto = " <<temp->getPrecoBase() - precoFinal << "€"
					<< " (" << 100 - (precoFinal/temp->getPrecoBase() * 100) << "%)"<< endl;
			cout << "Preco Final = " << precoFinal << "€" << endl << endl;

			break;
		}

		case 1:{
			// 1 - DEVOLVER BILHETE
			menu = -2;
			if (b->getNumViagens() == 0){
				cout << endl <<"Erro: Nao existem viagens ativas" << endl;
				break;
			}

			vector <Compra *> cmps = r->getRegisto()->getCompraAtiva();
			if (cmps.size() == 0){
				cout << "Erro: Ainda nao existem compras" << endl;
				break;
			}

			int compraId = -2;

			cout << "Bilhetes nao usados" << endl << endl;
			cout << r->getRegisto()->listCompraActiva() << endl;

			while (compraId >= (int)cmps.size() || compraId < -1){
				cout << "Escolha o bilhete a devolver (-1 para cancelar):";
				compraId = userIntInput();
				cout << endl;

				if (compraId == -1)
					return;

				if ((compraId >= (int)cmps.size() || compraId < -1) && compraId != -200)
				cout<<"Erro: Esse bilhete nao existe."<<endl<<endl;
			}

			cmps.at(compraId)->getViagem()->devolveBilhete(true);
			r->getRegisto()->eliminaCompra(cmps.at(compraId));

			p->diminuiNumClientes(cmps.at(compraId)->getViagem()->getDestino());

			cout << "Bilhete devolvido" << endl << endl;

			break;
		}

		case 2:{
			// 2 - ALTERAR CARTAO SUBSCRITO
			if (r->getNumCartoes() == 0){
				cout << "Erro: Nao existem cartoes para subscrever" << endl;
				return;
			}

			int cart = r->getNumCartoes() + 1;
			cout << "Tipo de Cartao: " << endl << endl;
			cout << r->getInfoCartao() << endl;;

			while (cart >= r->getNumCartoes() || cart < -1){

				cout << endl << "Escolha o cartao a subscrever:";
				cart = userIntInput();
				cout << endl;
				if (cart == -1)
					return;

				if ((cart >= r->getNumCartoes() || cart < -1) && cart != -200){
					cout<< endl <<"Erro: Este cartao nao existe, tente outra vez (-1 para cancelar)"<< endl;
				}
			}

			r->getRegisto()->alterarCartao(r->getCartao(cart));
			cout << endl << "Cartao alterado para \"" << r->getCartao(cart)->getNome() << "\"" << endl;
			return;
		}

		case 3:{
			// 3 - REMOVER SUBSCRICAO
			r->removeRegisto();
			cout << endl << "Subscricao removida, ao usar o id no futuro tem a possibilidade de re-ativar" << endl;
			return;
		}

		case 4: {
			// 4 - HISTORICO DE VIAGENS
			menu = -2;
			if (r->getRegisto()->getNumCompras() == 0){
				cout << "Erro: Ainda nao existe historico de compras" << endl;
				break;
			}

			cout << endl <<"Historico de Viagens" << endl << endl;
			cout << r->getRegisto()->getHistorico() << endl;
			break;
		}
		default:
			return;
		}

	}
}

void menuAdministracao (BaseClientes *r, Frota *f, Bilheteira *b, Maquinistas *M, Paragens *p, Oficinas *o){

	int menu = -2;

		while (menu !=  7){
			while (menu == -2 || menu == -1){
				cout << endl << "---Administracao---" << endl << endl;
				cout << " 0 - Guardar Dados" << endl;
				cout << " 1 - Carregar Dados" << endl;
				cout << " 2 - Comboios" << endl;
				cout << " 3 - Cartoes" << endl;
				cout << " 4 - Adicionar Viagens" << endl;
				cout << " 5 - Maquinistas" << endl;
				cout << " 6 - Paragens" << endl;
				cout << " 7 - Oficinas" << endl;
				cout << " 8 - Reportar Comboio Avariado" << endl;
				cout << " 9 - Sair" << endl;

				menu = menuInput(9);
				if (menu == -1)
					cout << "Erro: Menu nao existe, tente outra vez" << endl;

			}

			switch (menu){
			case 0:{

				f->saveComboios();
				r->saveCartoes();
				r->saveRegistos();
				p->saveParagens();
				b->saveViagens(p);
				M->saveMaquinistas();
				o->saveOficinas();
				cout << endl <<"Dados Gravados" << endl;
				return;
			}
			case 1:{

				o->loadOficinas();
				cout << "load oficinas " << endl;
				f->loadComboios(o);
				cout << "load comboios " << endl;
				r->loadCartoes();
				cout << "load Cartoes " << endl;
				p->loadParagens();
				cout << "load paragens " << endl;
				b->loadViagens(p);
				cout << "load Viagens " << endl;		
				r->loadRegistos();
				cout << "load registos " << endl;
				
				M->loadMaquinistas(f, "maquinistas.txt");
				cout << "load maquinistas " << endl;
				cout << endl <<"Dados Carregados" << endl;
				return;
				}

			case 2: {
				menuComboios(f);
				return;
			}
			case 3: {
				menuCartoes(r);
				return;
			}

			case 4: {
				string origem, destino, datavgm, horavgm;

				if (f->getNumComboios() == 0) {
					cout << "Nao ha comboios." << endl;
					return;
				}
				if (p->sizeParagens() == 0){
					cout << "Nao ha paragens." << endl;
					return;
				}
				cin.ignore();
				cin.clear();
				Viagem *v = adicionaViagem(b, f, p);
				if (v != NULL) {
					b->adicionaViagem(v);
					cout << "Viagem adicionada com sucesso" << endl;
				}
				else {
					cout << "A viagem nao foi adicionada com sucesso" << endl;
				}
				return;
			}
				//se relacionado com os maquinista
			case 5:
			{
				menuMaquinista(f, b, M, p);
				return;

			}
			case 6:{
				menuParagens(p);

				return;
			}
			case 7:{
				menuOficinas(o);
				return;
			}

			case 8:{
				int id_comboio = -2;
				double dist;
				cout << endl << f->getInformacao() << endl;

				while (id_comboio < 0 || id_comboio >= f->getNumComboios()) {
					cout << "Insira o Comboio que esta avariado (-1 para cancelar): ";
					id_comboio = userIntInput();
					cout << endl;

					if (id_comboio == -1)
						return;

					if ((id_comboio < -1 || id_comboio >= f->getNumComboios()) && id_comboio != -200){
						cout << "Erro: Este comboio nao existe" << endl;
						return;
					}

				}

				cout << "Distancia Maxima da oficina:";
				dist = userDoubleInput();
				cout << endl;

				f->getComboio(id_comboio)->setAvaria(o->getOficinas(), dist);

				cout << "Comboio em manuntencao na oficina " << f->getComboio(id_comboio)->getOficina()->getNome() << endl;;


				return;
			}
			default:
				return;
			}
		}
}

void menuMaquinista(Frota *f, Bilheteira *b, Maquinistas *M, Paragens *p ) {

	int menu = -2;

	while (menu != 6) {
		while (menu == -2 || menu == -1) {
			cout << endl << "---Maquinistas---" << endl << endl;
			cout << " 0 - Limpar dados carregados " << endl;
			cout << " 1 - Reformar/ Recontratar um Maquinista " << endl;
			cout << " 2 - Adicionar Maquinista" << endl;
			cout << " 3 - Editar Maquinista " << endl;
			cout << " 4 - Eliminar Maquinista " << endl;
			cout << " 5 - Sobre as viagens dos Maquinistas " << endl;
			cout << " 6 - Sair " << endl;

			menu = menuInput(6);
			if (menu == -1)
				cout << "Erro: Menu nao existe, tente outra vez" << endl;

		}

		switch (menu) {
			// Limpar dados carregados
		case 0: {
			if (M->emptyMaquinistas()) {
				cout << " Erro : Nao existem maquinistas!" << endl;
			}
			else {
				M->clearMaquinistas();
				cout << "Os dados foram eliminados do registo atual! " << endl;
			}
			return;
		}
				//reforma maquinista ou recontratacao do maquinista
		case 1: {
			if (M->emptyMaquinistas()) {
				cout << " Erro : Nao existem maquinistas!" << endl;
			}
			else {
				M->showMaquinistas();
				cout << endl << "Sobre o Maquinista a alterar o estado " << endl;
				int id;
				cout << "Qual o id do maquinista (-1 para cancelar)? " << endl;
				id = userIntInput();
				if (id == -1)
					return;
				Maquinista  M1("", "", id);
				if (M->alteraEstado(&M1))
					cout << endl << "Estado alterado !" << endl;
				else
					cout << endl << "Maquinista nao foi encontrado no registo, faca load dos dados " << endl;
			}
			return;
		}
				//Adiciona Maquinistas 
		case 2: {
			Maquinista M1 = criaMaquinista();

			if (M->adicionaMaquinista(&M1)) {
				cout << endl << "O maquinista foi adicionado com sucesso! " << endl;
			}
			else {
				cout << endl << "Nao foi possivel adicionar o maquinista! " << endl;
			}
			return;
		}
				//Editar maquinista
		case 3: {
			if (M->emptyMaquinistas()) {
				cout << " Erro : Nao existem maquinistas!" << endl;
			
			}
			else {
				M->showMaquinistas();
				cout << endl << "Sobre o Maquinista Antigo " << endl;
				int id;
				cout << "Qual o id do maquinista (-1 para cancelar)? " << endl;
				id = userIntInput();
				if (id == -1)
					return;
				Maquinista  M3("", "", id);
				cout << endl << "Sobre o maquinista Novo " << endl;
				Maquinista  M2 = criaMaquinista();
				if (M->editaMaquinista(&M3, &M2))
					cout << endl << "Troca efetuada com sucesso ! " << endl;
				else
					cout << "Maquinista antigo nao foi encontrado!" << endl;
			}
			return;
		}
				// Eliminar Maquinista

		case 4: {
			if (M->emptyMaquinistas()) {
				cout << " Erro : Nao existem maquinistas!" << endl;
				return;
			}
			else {
				M->showMaquinistas();
				cout << endl << "Sobre  maquinista que quer eliminar " << endl;
				int id;
				cout << "Qual o id do maquinista (-1 para cancelar)? " << endl;
				id = userIntInput();
				if (id == -1)
					return;
				Maquinista  M3("", "", id);
				if (M->eliminaMaquinista(&M3))
					cout << "Maquinista eliminado com sucesso! " << endl;
				else
					cout << "Maquinista nao encontrado " << endl;
			}
			return;
		}
				//atribui as viagens existentes aos Maquinistas
		case 5: {		
			menuMaquinistaViagens(f, b, M, p);
			return;
		}

		case 6:
			return;

		default:
			return;
		}

	}
}

void menuMaquinistaViagens(Frota *f, Bilheteira *b, Maquinistas *M, Paragens *p) {

	int menu = -2;

	while (menu != 3) {
		while (menu == -2 || menu == -1) {
			cout << endl << "---Viagens dos Maquinistas---" << endl << endl;
			cout << " 0 - Update de uma viagem de um maquinista" << endl;
			cout << " 1 - Atribui uma viagem a um Maquinista " << endl;
			cout << " 2 - Elimina uma viagem a um Maquinista" << endl;
			cout << " 3 - Sair " << endl;

			menu = menuInput(3);
			if (menu == -1)
				cout << "Erro: Menu nao existe, tente outra vez" << endl;

		}

		switch (menu) {
			// Limpar dados carregados
		case 0: {
			if (b->getNumViagens() == 0) {
				cout << endl << "Erro: Nao existem viagens" << endl;
				return;
			}

			if (M->emptyMaquinistas()) {
				cout << " Erro : Nao existem maquinistas!" << endl;
				return;
			}
			M->showMaquinistas();
			cout << endl << "Sobre  maquinista que quer eliminar uma viagem " << endl;
			int id;
			cout << "Qual o id do maquinista (-1 para cancelar)? " << endl;
			id = userIntInput();
			if (id == -1)
				return;
			Maquinista  M3("", "", id);
			if (!M->showViagensMaquinistas(&M3))
				return;
			cout << "Qual da viagem do maquinista (-1 para cancelar)? " << endl;
			id = userIntInput();
			if (id == -1)
				return;
			if (M->EliminaViagemDoId(&M3, id))
				cout << "Viagem eliminada com sucesso " << endl;
			else
				cout << "Viagem nao foi eliminada " << endl;
			
			int viagemId = -2;

			cout << "Lista de Viagens" << endl << endl;
			cout << endl << b->getInfo(p);
			while (viagemId >= b->getNumViagens() || viagemId < -1) {

				cout << endl << "Escolha o id da viagem que quer adicionar ao maquinista (-1 para cancelar):";
				viagemId = userIntInput();
				cout << endl;

				if (viagemId == -1)
					return;

				if ((viagemId >= b->getNumViagens() || viagemId < -1) && viagemId != -200) {
					cout << endl << "Erro: Esta viagem nao existe, tente outra vez " << endl;
				}
			}

			M->showMaquinistas();
			cout << endl << "Sobre  maquinista que quer adicionar viagens " << endl;
			cout << "Qual o id do maquinista (-1 para cancelar)? " << endl;
			id = userIntInput();
			if (id == -1)
				return;
			Maquinista  M2("", "", id);
			M->atribuiViagem(&M2, b->getViagem(viagemId));
			return;
		}
		case 1:
		{
			if (b->getNumViagens() == 0) {
				cout << endl << "Erro: Nao existem viagens" << endl;
				return;
			}

			if (M->emptyMaquinistas()) {
				cout << " Erro : Nao existem maquinistas!" << endl;
				return;
			}

			int viagemId = -2;

			cout << "Lista de Viagens" << endl << endl;
			cout << endl << b->getInfo(p);
			while (viagemId >= b->getNumViagens() || viagemId < -1) {

				cout << endl << "Escolha o id da viagem que quer adicionar ao maquinista (-1 para cancelar):";
				viagemId = userIntInput();
				cout << endl;

				if (viagemId == -1)
					return;

				if ((viagemId >= b->getNumViagens() || viagemId < -1) && viagemId != -200) {
					cout << endl << "Erro: Esta viagem nao existe, tente outra vez " << endl;
				}
			}

			M->showMaquinistas();
			cout << endl << "Sobre  maquinista que quer adicionar viagens " << endl;
			int id;
			cout << "Qual o id do maquinista (-1 para cancelar)? " << endl;
			id = userIntInput();
			if (id == -1)
				return;
			Maquinista  M3("", "", id);
			if (M->atribuiViagem(&M3, b->getViagem(viagemId)))
				cout << "Viagem atribuida " << endl;
			else cout << "ERRO: Viagem nao atribuida " << endl;
			return;
		}
		case 2: {
			if (b->getNumViagens() == 0) {
				cout << endl << "Erro: Nao existem viagens" << endl;
				return;
			}

			if (M->emptyMaquinistas()) {
				cout << " Erro : Nao existem maquinistas!" << endl;
				return;
			}
			M->showMaquinistas();
			cout << endl << "Sobre  maquinista que quer eliminar uma viagem " << endl;
			int id;
			cout << "Qual o id do maquinista (-1 para cancelar)? " << endl;
			id = userIntInput();
			if (id == -1)
				return;
			Maquinista  M3("", "", id);
			if (!M->showViagensMaquinistas(&M3))
				return;
			cout << "Qual da viagem do maquinista (-1 para cancelar)? " << endl;
			id = userIntInput();
			if (id == -1)
				return;
			if(M->EliminaViagemDoId(&M3, id))
				cout << "Viagem eliminada com sucesso " << endl;
			else
				cout << "Viagem nao foi eliminada " << endl;
			return;
		}
			
		case 3:
			return;

		default:
			return;
		}
	}
}

void menuCartoes(BaseClientes *r) {

	int menu = -2;

	while (menu != 3) {
		while (menu == -2 || menu == -1) {
			cout << endl << "---Cartoes---" << endl << endl;
			cout << " 0 - Adicionar cartao" << endl;
			cout << " 1 - Editar cartao " << endl;
			cout << " 2 - Eliminar cartao" << endl;
			cout << " 3 - Sair " << endl;

			menu = menuInput(3);
			if (menu == -1)
				cout << "Erro: Menu nao existe, tente outra vez" << endl;

		}

		switch (menu) {

		case 0: {
			double precoMensal = -2;
			int desconto = -2;
			string nome;
			cin.ignore();
			cin.clear();
			cout << endl << "---Criacao de cartao---" << endl;
			cout<<endl<<"Nome do cartao de descontos :";
			nome = nomeValido();
			do {
				cout << "Insira o desconto do cartao em percentagem (25, 50 ou 100) (-1 para cancelar): " << endl;
				desconto = userIntInput();
				cout << endl;
				if (desconto == -1)
					return;
				if (desconto == 25)
					precoMensal = 39;
				else if(desconto == 50)
					precoMensal = 69;
				else if (desconto == 100)
					precoMensal = 149;
				else cout << "Erro: Desconto invalido, so existem contratos de preco 25, 50 e 100 porcento" << endl;
				} while (desconto != 25 && desconto != 50 && desconto != 100);

			cout << "O preco mensal desta modalidadade e " << precoMensal << endl;

			desconto = 100 - desconto;
			Cartao *c1 = new Cartao(nome, precoMensal, desconto);
			r->adicionaCartao(c1);
			cout << "Cartao adicionado com sucesso" << endl;

			return;
		}
		case 1:
		{
			if (r->getNumCartoes() == 0){
				cout << "Erro: Nao existem cartoes para subscrever" << endl;
				return;
			}

			int id;

			r->getInfoCartao();
			cout << "Id do cartao a editar:";
			id = userIntInput();

			double precoMensal = -2;
			int desconto = -2;
			string nome;
			cin.ignore();
			cin.clear();
			cout<<endl<<"Nome do cartao de descontos :";
			nome = nomeValido();
			do {
				cout << "Insira o desconto do cartao em percentagem (25, 50 ou 100) (-1 para cancelar): " << endl;
				desconto = userIntInput();
				cout << endl;
				if (desconto == -1)
					return;
				if (desconto == 25)
					precoMensal = 39;
				else if(desconto == 50)
					precoMensal = 69;
				else if (desconto == 100)
					precoMensal = 149;
				else cout << "Erro: Desconto invalido, so existem contratos de preco 25, 50 e 100 porcento" << endl;
			} while (desconto != 25 && desconto != 50 && desconto != 100);

			r->getCartao(id)->setNome(nome);
			r->getCartao(id)->setPreco(precoMensal);
			r->getCartao(id)->setDesconto(desconto);

			cout << "Cartao editado com sucesso" << endl;

			return;
		}
		case 2: {

			if (r->getNumCartoes() == 0){
				cout << "Erro: Nao existem cartoes para subscrever" << endl;
				return;
			}

			int id;

			r->getInfoCartao();
			cout << "Id do cartao a remover:";
			id = userIntInput();

			r->removeCartao(id);


			cout << "Cartao removido com sucesso" << endl;

			return;
		}
		case 3: return;

		default: return;
		}
	}
}

void menuComboios(Frota *f) {

	int menu = -2;

	while (menu != 3) {
		while (menu == -2 || menu == -1) {
			cout << endl << "---Comboios---" << endl << endl;
			cout << " 0 - Adicionar comboio" << endl;
			cout << " 1 - Editar comboio " << endl;
			cout << " 2 - Eliminar comboio" << endl;
			cout << " 3 - Sair " << endl;

			menu = menuInput(3);
			if (menu == -1)
				cout << "Erro: Menu nao existe, tente outra vez" << endl;

		}

		switch (menu) {

		case 0: {
			int lotacao = -2, velocidade = -2;
			double precoKM = -2;
			string nome, tipo;
			Comboio *c;
			cin.ignore();
			cin.clear();

			cout << endl << "---Criacao de comboio---" << endl;
			cout<<endl<<"Nome:";
			getline(cin, nome);

			for (int i = 0; i < f->getNumComboios();i++){
				if (f->getComboio(i)->getNome()==nome){
					cout<<"Erro: Ja existe um comboio com esse nome."<<endl;
					continue;
				}
			}

			cout<< endl <<"Tipo ( IC para Intercidades, AP para AlfaPendular (IC/AP) ):";
			getline(cin,tipo);

			if (tipo!="IC" && tipo != "ic" && tipo != "Ic" && tipo != "iC"
				&& tipo!= "AP" && tipo != "ap" && tipo != "Ap" && tipo != "aP"){
					cout<<"Erro: Tipo invalido."<<endl;
					return;
				}

			while (lotacao < 0){
				cout << endl << "Insira lotacao do comboio (-1 para cancelar): ";
				lotacao = userIntInput();

				if (lotacao == -1)
					return;

				if (lotacao < -1 && lotacao != -200)
					cout << "Erro: Lotacao invalida, apenas sao aceites numeros inteiros positivos." << endl;
				}
			cout << endl;
			while (velocidade < 0){
				cout << "Insira a velocidade do comboio (numero inteiro) (-1 para cancelar): ";
				velocidade = userIntInput();
				cout << endl;

				if (velocidade == -1)
					return;

				if (velocidade < -1 && velocidade != -200)
					cout << "Erro: Velocidade invalida, apenas sao aceites numeros inteiros positivos." << endl;
			}

			while (precoKM < 0){
				cout << "Insira o preco por kilometro deste comboio (-1 para cancelar): ";
				precoKM = userDoubleInput();
				cout << endl;

				if (precoKM == -1)
					return;

				if (precoKM < -1 && precoKM != -200)
					cout << "Erro: Preco invalido, apenas sao aceites numeros positivos." << endl;
			}


			if (tipo!="IC" && tipo != "ic" && tipo != "Ic" && tipo != "iC")
				c = new Intercidades (lotacao, velocidade, precoKM, nome);
			else c = new AlfaPendular (lotacao, velocidade, precoKM, nome);
			f->adicionaComboio(c);

			cout << "Comboio adicionado com sucesso." << endl;

			return;
		}
		case 1:
		{
			int id;
			if (f->getNumComboios() == 0){
				cout << endl << "Erro: Nao existem comboios" << endl;
				return;
			}
			string nome, tipo;
			int lotacao = -2, velocidade = -2;
			double precoKM = -2;

			cout << endl << "Lista de Comboios" << endl << endl;
			cout << f->getInformacao();
			cout << "Escolha o comboio a editar:";
			id = userIntInput();
			cout << endl;
			cout<<endl<<"Nome:";
			getline(cin, nome);
			cout << endl;

			while (lotacao < 0){
				cout << endl << "Insira lotacao do comboio (-1 para cancelar): ";
				lotacao = userIntInput();

				if (lotacao == -1)
					return;

				if (lotacao < -1 && lotacao != -200)
					cout << "Erro: Lotacao invalida, apenas sao aceites numeros inteiros positivos." << endl;
			}

			while (velocidade < 0){
				cout << "Insira a velocidade do comboio (numero inteiro) (-1 para cancelar): ";
				velocidade = userIntInput();
				cout << endl;

				if (velocidade == -1)
					return;

				if (velocidade < -1 && velocidade != -200)
					cout << "Erro: Velocidade invalida, apenas sao aceites numeros inteiros positivos." << endl;
			}

			while (precoKM < 0){
				cout << "Insira o preco por kilometro deste comboio (-1 para cancelar): ";
				precoKM = userDoubleInput();
				cout << endl;

				if (precoKM == -1)
					return;

				if (precoKM < -1 && precoKM != -200)
					cout << "Erro: Preco invalido, apenas sao aceites numeros positivos." << endl;
			}

			f->getComboio(id)->setNome(nome);
			f->getComboio(id)->setLotacao(lotacao);
			f->getComboio(id)->setVelocidade(velocidade);
			f->getComboio(id)->setPreco(precoKM);

			cout << "Comboio editado com sucesso" << endl;
			return;
		}
		case 2: {

			int id;

			if (f->getNumComboios() == 0){
				cout << endl << "Erro: Nao existem comboios" << endl;
				return;
			}

			cout << endl << "Lista de Comboios" << endl << endl;
			cout << f->getInformacao();
			cout << "Escolha o comboio a editar:";
			id = userIntInput();
			cout << endl;

			f->removeComboio(id);

			cout << "Comboio removido com sucesso" << endl;

			return;
		}
		case 3: return;

		default: return;
		}
	}
}

void menuParagens(Paragens *p) {

	int menu = -2;

	while (menu != 4) {
		while (menu == -2 || menu == -1) {
			cout << endl << "---Paragens---" << endl << endl;
			cout << " 0 - Adicionar paragem" << endl;
			cout << " 1 - Editar paragem " << endl;
			cout << " 2 - Eliminar paragem" << endl;
			cout << " 3 - Mostrar as paragens ordenadas por numero de clientes" << endl;
			cout << " 4 - Sair " << endl;

			menu = menuInput(4);
			if (menu == -1)
				cout << "Erro: Menu nao existe, tente outra vez" << endl;

		}

		switch (menu) {

		case 0: {
			string nome;
			double lat, log;
			cin.ignore();
			cin.clear();

			cout << "Nome da paragem:";
			getline(cin, nome);
			cout << endl;
			cout << "Latitude:";
			lat = userDoubleInput();
			cout << endl;
			cout << "Longitude:";
			cout << endl;
			log = userDoubleInput();

			Paragem temp(nome, lat, log);
			p->addParagem(temp);

			cout << endl << "Paragem adicionada com sucesso" << endl;

			return;
		}
		case 1:
		{
			string nome;
			double lat, log;
			int par;
			p->printParagens();
			cout << endl << "Paragem a editar:";
			par = userIntInput();

			cout << "Nome da paragem:";
			getline(cin, nome);
			cout << endl;
			cout << "Latitude:";
			lat = userDoubleInput();
			cout << endl;
			cout << "Longitude:";
			cout << endl;
			log = userDoubleInput();

			Paragem *temp = p->getParagem(par);
			temp->setNome(nome);
			temp->setLatitude(lat);
			temp->setLongitude(log);

			cout << endl << "Paragem editada com sucesso" << endl;

			return;
		}
		case 2: {
			int par;
			p->printParagens();
			cout << "Paragem a apagar:";
			par = userIntInput();
			if (par >= p->sizeParagens() || par < 0){
				cout << endl << "Paragem nao existe" << endl;
				return;
			}
			p->deleteParagem(par);

			cout << endl << "Paragem apagada com sucesso" << endl;
			return;
		}
		case 3:{
			p->printParagensBST();
			return;}

		case 4: return;

		default: return;
		}
	}
}

void menuOficinas (Oficinas *o) {

	int menu = -2;

	while (menu != 3) {
		while (menu == -2 || menu == -1) {
			cout << endl << "---Oficinas---" << endl << endl;
			cout << " 0 - Adicionar oficina" << endl;
			cout << " 1 - Editar oficina " << endl;
			cout << " 2 - Eliminar oficina" << endl;
			cout << " 3 - Sair " << endl;

			menu = menuInput(3);
			if (menu == -1)
				cout << "Erro: Menu nao existe, tente outra vez" << endl;

		}

		switch (menu) {

		case 0: {
			string nome;
			double lat, log;
			cin.ignore();
			cin.clear();

			cout << "Nome da oficina:";
			getline(cin, nome);
			cout << endl;
			cout << "Latitude:";
			lat = userDoubleInput();
			cout << endl;
			cout << "Longitude:";
			cout << endl;
			log = userDoubleInput();

			Oficina *temp = new Oficina(nome, lat, log);
			o->addOficina(temp);

			cout << endl << "Oficina adicionada com sucesso" << endl;

			return;
		}
		case 1:
		{
			string nome;
			double lat, log;
			int ofi;
			o->printOficinas();
			cout << endl << "Oficina a editar:";
			ofi = userIntInput();
			if (ofi >= o->sizeOficinas() || ofi < 0){
				cout << endl << "Oficina nao existe" << endl;
			}

			cout << "Nome da oficina:";
			getline(cin, nome);
			cout << endl;
			cout << "Latitude:";
			lat = userDoubleInput();
			cout << endl;
			cout << "Longitude:";
			cout << endl;
			log = userDoubleInput();

			priority_queue <Oficina *> temp = o->getOficinas();

			for (int i = 0; i < ofi; i++)
				temp.pop();

			Oficina *tempofi = temp.top();
			tempofi->setNome(nome);
			tempofi->setLatitude(lat);
			tempofi->setLongitude(log);

			cout << endl << "Oficina editada com sucesso" << endl;


			return;
		}
		case 2: {
			int ofi;
			o->printOficinas();
			cout << "Oficina a apagar:";
			ofi = userIntInput();
			if (ofi >= o->sizeOficinas() || ofi < 0){
				cout << endl << "Oficina nao existe" << endl;
				return;
			}
			o->deleteOficina(ofi);

			cout << endl << "Oficina apagada com sucesso" << endl;
			return;
		}

		case 3: return;

		default: return;
		}
	}
}

