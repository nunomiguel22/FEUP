#include "geral.h"

using namespace std;


Datas* getDataActual(){
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	Datas *temp = new Datas(now->tm_year+ 1900, now->tm_mon+1, now->tm_mday);
	return temp;
}

Horas* getHoraActual(){
	std::time_t t = std::time(0);
	std::tm* now = std::localtime(&t);
	Horas *temp = new Horas(now->tm_hour, now->tm_min);
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

/*
 * Menus
 *
 *
 */

//			INFORMACAO

void menuInformacao(BaseClientes *r, Frota *f, Bilheteira *b){

	int menu = -2;

	while (menu != 2){
		while (menu == -2 || menu == -1){
			cout << endl << "---Informacao---" << endl << endl;

			cout << endl << "0 - Lista de Comboios" << endl;
			cout << "1 - Lista de Viagens" << endl;
			cout << "2 - Sair" << endl;

			menu = menuInput(2);
			if (menu == -1)
				cout << "Erro: Menu nao existe, tente outra vez" << endl;

		}
		switch (menu){
		case 0:

			menu = 3;

			if (f->getNumComboios() == 0){
				cout << endl << "Erro: Nao existem comboios" << endl;
				break;
			}

			cout << endl << "Lista de Comboios" << endl << endl;
			cout << f->getInformacao();

			break;
		case 1:
			menu = 3;

			if (b->getNumViagens() == 0){
				cout << endl << "Erro: Nao existem viagens" << endl;
				break;
			}
			cout << endl << "Lista de Viagens" << endl << endl;
			cout << b->getInfo();
			break;
		case 2:
			return;
		default:
			return;
		}
	}
}

//					MENU UTILIZADORES ANONIMOS

void menuSemCartao(BaseClientes *r, Bilheteira *b){
	int menu = -2;

	while (menu != 3){

		while (menu == -2 || menu == -1){

		cout << endl << "---Passageiro sem Cartao---" << endl << endl;
		cout << endl << "0 - Comprar Bilhete" << endl;
		cout << "1 - Devolver Bilhete" << endl;
		cout << "2 - Subscrever a um cartao" << endl;
		cout << "3 - Sair" << endl;

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
			cout << endl << b->getInfo();
			while (viagemId >= b->getNumViagens() || viagemId < -1){

				cout << endl << "Escolha o id da viagem a cancelar o bilhete (-1 para cancelar):";
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

			double precoFinal = temp->getPrecoFinal();
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
			cout << endl << b->getInfo();
			while (viagemId >= b->getNumViagens() || viagemId < -1){

				cout << endl << "Escolha o id da viagem a reservar(-1 para cancelar):";
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
			cout << endl << "Bilhete devolvido" << endl;

			break;
		}

		case 2:{
			// 2 - SUBSCREVER A UM CARTAO
			string datans;
			int cart = -2;
			string nome;
			string profissao;
			Datas *datanasc;

			if (r->getNumCartoes() == 0){
				cout << "Erro: Nao existem cartoes para subscrever" << endl;
				return;
			}

			cin.ignore();
			cin.clear();

			cout << endl << "---Subscricao de cartao---" << endl << endl;

			cout << "Nome: ";
			getline(cin, nome);

			cout << endl << "Profissao: ";
			getline(cin,profissao);

			try {
			cout << endl << "Data de Nascimento(DD-MM-AAAA): ";
			getline(cin, datans);
			cout << endl;
			datanasc = new Datas(datans);
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

void menuComCartao(BaseClientes *r, Bilheteira *b){
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
			if (ans == "s"){
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
				cout << endl << "0 - Comprar Bilhete" << endl;
				cout << "1 - Devolver Bilhete" << endl;
				cout << "2 - Alterar cartao subscrito" << endl;
				cout << "3 - Remover subscricao" << endl;
				cout << "4 - Historico de Viagens" << endl;
				cout << "5 - Sair" << endl << endl;

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

			cout << "Lista de Viagens" << endl << endl << endl << b->getInfo();

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

			double precoFinal = temp->getPrecoFinal(r->getRegisto()->getCartao());
			Compra *tempC = new Compra( temp, r->getRegisto()->getCartao(), precoFinal, getDataActual(), getHoraActual() );
			r->getRegisto()->adicionaCompra(tempC);

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

void menuAdministracao (BaseClientes *r, Frota *f, Bilheteira *b){

	int menu = -2;

		while (menu != 5){
			while (menu == -2 || menu == -1){
				cout << endl << "---Administracao---" << endl << endl;
				cout << endl << "0 - Guardar Dados" << endl;
				cout << "1 - Carregar Dados" << endl;
				cout << "2 - Adicionar Comboios" << endl;
				cout << "3 - Adicionar Cartoes" << endl;
				cout << "4 - Adicionar Viagens" << endl;
				cout << "5 - Sair" << endl;

				menu = menuInput(5);
				if (menu == -1)
					cout << "Erro: Menu nao existe, tente outra vez" << endl;

			}

			switch (menu){
			case 0:{

				f->saveComboios();
				r->saveCartoes();
				r->saveRegistos();
				b->saveViagens();
				cout << endl <<"Dados Gravados" << endl;
				return;
			}
			case 1:{
				f->loadComboios();
				r->loadCartoes();
				r->loadRegistos();
				b->loadViagens();
				cout << endl <<"Dados Carregados" << endl;
				return;

				}

			case 2: {
				int lotacao = -2, velocidade = -2;
				double precoKM = -2;
				string nome, tipo;
				Comboio *c;
				cin.ignore();
				cin.clear();

				cout << endl << "---Criacao de comboio---" << endl;
				cout<<endl<<"Nome:";
				getline(cin,nome);

				for (int i = 0; i < f->getNumComboios();i++){
					if (f->getComboio(i)->getNome()==nome){
						cout<<"Erro: Ja existe um comboio com esse nome."<<endl;
						continue;
					}
				}

				cout<< endl <<"Tipo ( IC para Intercidades, AP para AlfaPendular (IC/AP) ):";
				getline(cin,tipo);

				if (tipo!="IC" && tipo!= "AP"){
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


				if (tipo == "IC")
					c = new Intercidades (lotacao, velocidade, precoKM, nome);
				else c = new AlfaPendular (lotacao, velocidade, precoKM, nome);
				f->adicionaComboio(c);

				cout << "Comboio adicionado com sucesso." << endl;
				return;
			}
			case 3: {
				double precoMensal = -2;
				int desconto = -2;
				string nome;
				cin.ignore();
				cin.clear();
				cout << endl << "---Criacao de cartao---" << endl;
				cout<<endl<<"Nome:";
				getline(cin,nome);

				while (precoMensal < 0){
					cout << "Insira o preco mensal deste cartao (-1 para cancelar): ";
					precoMensal = userDoubleInput();
					cout << endl;

					if (precoMensal == -1)
						return;

					if (precoMensal < -1 && precoMensal != -200)
						cout << "Erro: Preco invalido, apenas sao aceites numeros positivos" << endl;
				}

				while (desconto < 0){
					cout << "Insira o desconto do carto em percentagem (numero inteiro) (-1 para cancelar): ";
					desconto = userIntInput();
					cout << endl;

					if (desconto == -1)
						return;

					if (desconto < -1 && desconto != -200)
						cout << "Erro: Desconto invalido, apenas sao aceites numeros inteiros positivos" << endl;
				}
				desconto = 100 - desconto;
				Cartao *c1 = new Cartao(nome, precoMensal, desconto);
				r->adicionaCartao(c1);

				cout << "Cartao adicionado com sucesso" << endl;
				return;
			}

			case 4:{
				string origem,destino, datavgm, horavgm;
				double distancia = -2;
				int id_comboio = -2;

				if (f->getNumComboios()==0){
					cout<<"Nao ha comboios."<<endl;
					return;
				}
				cin.ignore();
				cin.clear();
				cout << endl << "---Criacao de viagem---"  << endl;
				cout<<endl<<"Origem:";
				getline(cin,origem);
				cout<<endl<<"Destino:";
				getline(cin,destino);

				while (distancia < 0){
					cout << "Insira a distancia da viagem (-1 para cancelar): ";
					distancia = userDoubleInput();
					cout << endl;

					if (distancia == -1)
						return;

					if (distancia < -1 && distancia != -200)
						cout << "Erro: Distancia invalida, apenas sao aceites numeros positivos" << endl;
				}

				// DATA DA VIAGEM

				Datas *dvgm;
				try{
					cin.ignore();
					cin.clear();
					cout << "Data da viagem(DD-MM-AAAA): ";
					getline(cin, datavgm);
					dvgm = new Datas (datavgm);
					cout << endl;
				}
				catch (Datas::DataInvalida){
					cout << "Erro: Data Invalida - Dia(1-31), Mes (1-12)" << endl;
					return;
				}
				catch (Datas::FormatoStringInvalido){
					cout << "Erro: Formato invalido - (DD-MM-AAAA)" << endl;
					return;
				}

				// HORA DA VIAGEM

				Horas *hvgm;
				try {
					cout << "Hora da viagem(HH:MM): ";
					getline (cin, horavgm);
					hvgm = new Horas (horavgm);
					cout << endl;
				}
				catch (Horas::HoraInvalida){
					cout << "Erro: Hora Invalida - Hora(0-23), Min (0-59)" << endl;
					return;
				}
				catch (Horas::FormatoStringInvalido){
					cout << "Erro: Formato invalido - (HH:MM)" << endl;
					return;
				}

				cout << endl << f->getInformacao() << endl;


				while (id_comboio < 0 || id_comboio >= f->getNumComboios()){
					cout << "Insira o Comboio que vai efectuar a viagem (-1 para cancelar): ";
					id_comboio = userIntInput();
					cout << endl;

					if (id_comboio == -1)
						return;

					if ((id_comboio < -1 || id_comboio >= f->getNumComboios()) && id_comboio != -200)
						cout << "Erro: Este comboio nao existe" << endl;

				}

				Comboio *c = f->getComboio(id_comboio);

				Viagem *v=new Viagem(origem, destino, distancia, c,dvgm,hvgm);
				b->adicionaViagem(v);

				cout << "Viagem adicionada com sucesso" << endl;

				return;
			}

			case 5:
				return;

			default:
				return;
			}
		}
}
