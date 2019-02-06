#ifndef _VIAGENS_H
#define _VIAGENS_H

#include "comboios.h"
#include "cartao.h"
#include "datashoras.h"

/**
 * CLASS Viagem\n
 * Esta Classe cria uma viagem e controla as vagas de essa viagem
 *
 */
class Viagem{
	std::string origem, destino;
	double distancia;
	Comboio *c1;
	Datas *dPartida;
	Horas *hPartida;
	double precoBase;
	unsigned int vagas;
	unsigned int comprasAnonimas;
public:
	/**
	 * Construtor de viagem para quando e o nova viagem
	 * @param ori Origem
	 * @param dest Destino
	 * @param dist Distancia
	 * @param c Apontador para comboio que fara a viagem
	 * @param dp Apontador para data da viagem
	 * @param hp Apontador para horas da viagem
	 */
	Viagem(std::string ori, std::string dest, double dist, Comboio *c, Datas *dp, Horas *hp);
	/**
	 * Construtor de viagem para quando a viagem e carregada de um ficheiro
	 * @param ori Origem
	 * @param dest Destino
	 * @param dp Apontador para data da viagem
	 * @param hp Apontador para horas da viagem
	 * @param precoBase Preco base da viagem
	 */
	Viagem(std::string ori, std::string dest, Datas *dp, Horas *hp,  double precoBase);
	/**
	 * Construtor de viagem para quando e carregada de um ficheiro para um objecto de compra
	 * @param ori Origem
	 * @param dest Destino
	 * @param dist Distancia
	 * @param c Apontador para comboio que fara a viagem
	 * @param dp Apontador para data da viagem
	 * @param hp Apontador para horas da viagem
	 * @param vagas Numero de lugares disponiveis para essa viagem
	 * @param comprasAnon Numero de lugares comprados anonimamente (por clientes sem cartao)
	 */
	Viagem(std::string ori, std::string dest, double dist, Comboio *c, Datas *dp, Horas *hp, int vagas, int comprasAnon);
	/**
	 * Destrutor \n
	 * Destroi os objectos Datas e Horas com o tempo da partida da viagem
	 */
	~Viagem();

	/**
	 * @return Apontador para a data (ano-mes-dia) de partida da viagem
	 */
	Datas* getDataPartida() const;
	/**
	 * @return Apontador para a hora (horas:minutos) de partida da viagem
	 */
	Horas* getHorasPartida() const;
	/**
	 * @return Preco base (sem desconto) da viagem
	 */
	double getPrecoBase () const;
	/**
	 * @return Origem da viagem
	 */
	std::string getOrigem() const;
	/**
	 * @return Destino da viagem
	 */
	std::string getDestino() const;
	/**
	 * @return Distancia da viagem
	 */
	double getDistancia() const;
	/**
	 * @return Apontador para o comboio que faz a viagem
	 */
	Comboio* getComboio() const;
	/**
	 * @return Numero de vagas da viagem
	 */
	unsigned int getVagas() const;
	/**
	 * @return Numero de compras anonimas (feitas por clientes sem cartao)
	 */
	unsigned int getComprasAnonimas() const;
	/**
	 * @return Informacao sobre a viagem
	 */
	std::string getInfo() const;

	/**
	 * @param reg Indica se o cliente tem cartao ou nao
	 * @return 1 Se ja nao da para reservar mais bilhetes
	 */
	int reservaBilhete(bool reg);
	/**
	 * @param reg Indica se o cliente tem cartao ou nao
	 * @return 1 Se ja nao da para devolver mais bilhetes
	 */
	int devolveBilhete(bool reg);
	/**
	 * @return Preco final (Depois de descontos)
	 */
	double getPrecoFinal();
	/**
	 * @param c Apontador para o comboio
	 * @return Preco final em relacao a subscricao feita
	 */
	double getPrecoFinal(Cartao *c);
	/**
	 * Redefinicao do operador comparacao
	 * @param v2 Referencia para a viagem com a qual se vai comparar
	 * @return True se as duas viagens sao iguais
	 */
	bool operator == (const Viagem &v2);
	/**
	 * @return True se ainda se podem efetuar compras nesta viagem, false se a lotacao maxima ja foi atingida
	 */
	bool compraRegisto() const;

};


#endif
