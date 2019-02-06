#ifndef _COMBOIOS_H
#define _COMBOIOS_H

#include "datashoras.h"
#include "locais.h"

/**
 * CLASS COMBOIO\n
 * Esta Classe e usada para criar comboios a usar nas viagens.\n
 * Class base das classes AlfaPendular e Intercidades
 *
 */
class Comboio {
protected:
	unsigned int lotacao; //capacidade do comboio
	int velocidade;
	double precoKM;
	std::string nome;
	unsigned int id;
	Paragem ultimaParagem;
	bool avariado;
	Oficina *ofic;
	double dataUltimaAvaria;
public:
	/**
	 * @brief Construtor de comboio
	 * @param numPassageiros Numero de passageiros maximo do comboio
	 * @param velocidade Velocidade do comboio
	 * @param precoKM Preco por km do comboio
	 * @param nome Nome do comboio
	 */
	Comboio(int numPassageiros, int velocidade, double precoKM, std::string nome);
	/**
	 * @return Tipo do comboio(AlfaPendular ou Intercidades)
	 */
	virtual std::string getTipo() const;
	/**
	 * @return Lotacao do comboio
	 */
	unsigned int getLotacao() const;
	/**
	 * @return Velocidade do comboio
	 */
	int getVelocidade() const;
	/**
	 * @return Preco por km do comboio
	 */
	double getPrecoKM() const;
	/**
	 * @return Nome do comboio
	 */
	std::string getNome() const;
	/**
	 * @return ID do comboio
	 */
	unsigned int getId() const;
	/**
	 * @return Ultima paragem do comboio
	 */
	Paragem getUltimaParagem() const;
	/**
	 * @return Estado funcional do comboio
	 */
	bool getAvariado() const;
	/**
	 * @return Ultima oficina que serviu o comboio
	 */
	Oficina* getOficina() const;
	/**
	 * @return Data da ultima avaria
	 */
	double getDataUltimaAvaria() const;
	/**
	 * @brief Destrutor virtual \n
	 */
	virtual ~Comboio(){};
	/**
	 * @param nome Atribuir nome
	 */
	void setNome(string nome);
	/**
	 * @param lot Atribuir lotacao
	 */
	void setLotacao(int lot);
	/**
	 * @param vel Atribuir Velocidade
	 */
	void setVelocidade(int vel);
	/**
	 * @param prc Atribuir Preco por km
	 */
	void setPreco(double prc);
	/**
	 * @param id Atribuir id
	 */
	void setId(int id);
	/**
	 * @param id Atribuir estado do comboio
	 */
	void setAvariado(bool avariado);
	/**
	 * @param p1 Atribuir ultima Paragem
	 */
	void setUltimaParagem(Paragem &p1);
	/**
	 * @param oficinas oficinas disponiveis
	 * @param distmaxima distancia maxima do comboio
	 */
	void setAvaria(std::priority_queue<Oficina *> oficinas, double distmaxima);
	/**
	 * @param dataav Data da avaria
	 */
	void setDataAvaria(double dataav);
	/**
	 * @param p1 Atribuir uma oficina
	 */
	void setOficina(Oficina *o1);
	/**
	 * @brief Faz overload ao operador de saida para dar output da informacao do comboio em
	 * forma de tabela
	 * @param os Referencia para ofstream onde guardar a informacao
	 * @param c1 Referencia para o comboio
	 */
	friend std::ostream& operator << (std::ostream &os, const Comboio &c1){
		os << c1.getNome() << "-" << c1.getTipo();
		return os;
	}

};
/**
 * CLASS AlfaPendular\n
 * Class derivada da class comboio
 *
 */
class AlfaPendular: public Comboio {
public:
	/**
	 * @brief Construtor de alfapendular
	 * @param numPassageiros Numero de passageiros maximo do comboio
	 * @param velocidade Velocidade do comboio
	 * @param precoKM Preco por km do comboio
	 * @param nome Nome do comboio
	 */
	AlfaPendular(int numPassageiros, int velocidade, double precoKM, std::string nome);
	/**
	 * @return tipo do comboio ("AP")
	 */
	std::string getTipo() const;
	/**
	 * Destrutor \n
	 * Elimina todos os dados de alfapendular
	 */
	virtual ~AlfaPendular(){};
};

/**
 * CLASS Intercidades\n
 * Class derivada da class comboio
 *
 */
class Intercidades: public Comboio {
public:
	/**
	 * @brief Construtor de intercidades
	 * @param numPassageiros Numero de passageiros maximo do comboio
	 * @param velocidade Velocidade do comboio
	 * @param precoKM Preco por km do comboio
	 * @param nome Nome do comboio
	 */
	Intercidades(int numPasseiros, int velocidade, double precoKMs, std::string nome);
	/**
	 * @return tipo do comboio ("IC")
	 */
	std::string getTipo() const;
	/**
	 * Destrutor \n
	 * Elimina todos os dados de intercidades
	 */
	virtual ~Intercidades(){};
};

/**
 * CLASS Frota\n
 * Class que guarda todos os comboios
 *
 */
class Frota{

public:
	/**
	 * @brief Destrutor \n
	 * Elimina todos os comboios da frota
	 */
	~Frota();

	std::vector <Comboio *> comboios;
	/**
	 * @return Informacao dos comboios numa string em forma de tabela
	 */
	std::string getInformacao();
	/**
	 * @param id ID do comboio
	 * @return Apontador para comboio com esse id
	 */
	Comboio* getComboio(unsigned int id) const;
	/**
	 * @return Numero de comboios da frota
	 */
	int getNumComboios() const;
	/**
	 * @param c1 Apontador para comboio a adicionar a frota
	 */
	void adicionaComboio(Comboio *c1);
	/**
	 * @brief Abre "comboios.txt" e adiciona os comboios a frota
	 */
	void loadComboios(Oficinas *o);
	/**
	 * @brief Guarda os comboios da frota em "comboios.txt"
	 */
	void saveComboios() const;
	/**
	 * @brief Verifica e atualiza comboios em manuntecao
	 */
	void updateManuntencao();
	/**
	 * @brief Remove um comboio do vector
	 */
	void removeComboio(unsigned int id);
};


#endif


