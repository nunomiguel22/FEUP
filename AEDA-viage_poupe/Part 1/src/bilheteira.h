#ifndef _BILHETEIRA_H
#define _BILHETEIRA_H


#include "viagens.h"
#include "comboios.h"
#include "cartao.h"
#include "datashoras.h"

/**
 * CLASS Compra
 * Esta Classe cria os objectos que vao ficar no historico dos passageiros
 *
 */


class Compra {
	Viagem *v1;
	Cartao *c1;
	double precoFinal;
	Datas *dCompra;
	Horas *hCompra;
public:
	/**
	 * Construtor da class Compra
	 * @param v Apontador para a viagem que se reservou
	 * @param c Apontador para o cartao que o cliente usou na compra
	 * @param pf Preco final
	 * @param dc Apontador para data da compra
	 * @param hc Apontador para horas da compra
	 */
	Compra(Viagem *v, Cartao *c, double pf, Datas *dc, Horas *hc);
	/**
	 * Destrutor \n
	 * Destroi os objectos da class Datas e Horas associados ao objeto compra. \n\n
	 * Destroi tambem a Viagem apenas se a Viagem ja tiver partido. \n
	 * so acontece ao desligar o proprio programa pois a viagem pode ser usada para o
	 * historico de outros passageiros.
	 */
	~Compra();
	/**
	 * @return Informacao sobre a compra numa string em forma de tabela
	 */
	std::string getInfo() const;
	/**
	 * @return Apontador para viagem comprada
	 */
	Viagem* getViagem() const;
	/**
	 * @return Apontador para cartao usado para a compra
	 */
	Cartao* getCartao() const;
	/**
	 * @return Apontador para data da compra
	 */
	Datas* getDataCompra() const;
	/**
	 * @return Apontador para hora da compra
	 */
	Horas* getHoraCompra() const;
	/**
	 * @return Preco final (ja depois de qualquer desconto) da compra
	 */
	double getPrecoFinal() const;

	/**
	 * Redefinicao do operador de comparacao
	 * @param c2 Referencia para a compra com a qual se vai comparar
	 * @return Se as duas compras sao iguais ou nao
	 */
	bool operator == (const Compra &c2);
};


/*
 * CLASS Bilheteira
 * Esta Classe guarda todas as viagens ativas e remove quando ja tiverem acontecido
 *
 */

class Bilheteira {
	std::vector<Viagem *> viagens;
	Frota *f;
public:
	/**
	 * Construtor de bilheteira
	 * @param frt Apontador para frota de comboios
	 * A frota de comboios e usada no carregamento de viagens de um ficheiro
	 */
	Bilheteira(Frota *frt);
	/**
	 * Destrutor \n
	 * Destroi todas as viagens activas
	 */
	~Bilheteira();
	/**
	 * @return Numero de viagens
	 */
	int getNumViagens() const;
	/**
	 * @param id ID da viagem
	 * @return Apontador para viagem com esse id
	 */
	Viagem* getViagem(int id);
	/**
	 * @return Informacao sobre todas as viagens numa string em forma de tabela
	 */
	std::string getInfo();

	/**
	 * @param v1 Apontador para viagem a adicionar
	 */
	void adicionaViagem(Viagem *v1);
	/**
	 * Atualiza as viagens e elimina as viagens que ja inciaram. \n
	 * Ordena o vector das viagens por ordem de partida
	 */
	void updateViagens();
	/**
	 * Abre "viagens.txt" e adiciona as viagens a bilheteira
	 */
	void loadViagens();
	/**
	 * Guarda as viagens da bilheteira em "viagens.txt"
	 */
	void saveViagens();
};


#endif
