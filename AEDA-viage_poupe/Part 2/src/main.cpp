#include "geral.h"
#include "locais.h"

using namespace std;

int main(){

	int menu = -2;

	BaseClientes r;
	Frota f;
	Bilheteira b(&f);
	Maquinistas m;
	Paragens p;
	Oficinas o;

	while (menu != -4){
		while (menu == -2){

			cout << endl << "---MENU INICIAL---" << endl << endl;
			cout << " 0 - Informacao" << endl;
			cout << " 1 - Passageiro sem cartao" << endl;
			cout << " 2 - Passageiro com cartao" << endl;
			cout << " 3 - Administracao" << endl;
			cout << " 4 - Sair" << endl;

		menu = menuInput(4);
		if (menu == -1)
			cout << "Erro: Menu nao existe, tente outra vez" << endl;
		}

		switch (menu){
		case 0:
			menuInformacao(&r, &f, &b, &m, &p, &o);
			menu = -2;
			break;
		case 1:
			menuSemCartao(&r, &b, &p);
			menu = -2;
			break;
		case 2:
			menuComCartao(&r, &b, &p);
			menu = -2;
			break;
		case 3:
			menuAdministracao(&r, &f, &b, &m, &p, &o);
			menu = -2;
			break;
		case 4:
			return 0;
		default:
			return 0;
		}
	}
	return 0;
}

