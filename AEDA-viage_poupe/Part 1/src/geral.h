#ifndef GERAL_H_
#define GERAL_H_

#include "datashoras.h"
#include "bilheteira.h"
#include "cartao.h"
#include "viagens.h"
#include "comboios.h"

Datas* getDataActual();
Horas* getHoraActual();

void menuInformacao(BaseClientes *r, Frota *f, Bilheteira *b);
void menuComCartao(BaseClientes *r, Bilheteira *b);
void menuSemCartao(BaseClientes *r, Bilheteira *b);
void menuAdministracao(BaseClientes *r, Frota *f, Bilheteira *b);

int menuInput(int nOptions);
int userIntInput();
double userDoubleInput();

#endif
