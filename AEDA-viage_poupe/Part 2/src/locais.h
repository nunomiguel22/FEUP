#pragma once

#include <string>
#include <vector>
#include <queue>
#include "BST.h"

/**
 * CLASS Paragem
 * Esta Classe cria paragens de comboio
 *
 */

class Paragem {
	std::string nome;
	double latitude;
	double longitude;
	unsigned int numeroclientes;
public:
	/**
	 * Construtor de Paragem
	 *
	 */
	Paragem(){};
	/**
	 * Construtor de Paragem
	 * @param nome Nome da paragem
	 * @param latitude Latitude da Paragem
	 * @param longitude Longitude da Paragem
	 */
	Paragem(std::string nome, double latitude, double longitude);
	/**
	 * Construtor de Paragem
	 * @param nome Nome da paragem
	 * @param latitude Latitude da Paragem
	 * @param longitude Longitude da Paragem
	 * @param numclientes Numero de clientes da Paragem
	 */
	Paragem(std::string nome, double latitude, double longitude, int numclientes);
	/**
	 * Destrutor de Paragem
	 */
	~Paragem(){};
	/**
	 * @return Nome da paragem
	 */
	std::string getNome() const;
	/**
	 * @return Latitude da paragem
	 */
	double getLatitude() const;
	/**
	 * @return Longitude da paragem
	 */
	double getLongitude() const;
	/**
	 * @return Numero de clientes que ja saiu nessa paragem
	 */
	int getNumClientes() const;
	/**
	 * @brief Aumenta o numero de clientes por 1
	 */
	void aumentaNumClientes();
	/**
	 * @brief Diminui o numero de clientes por 1
	 */
	void diminuiNumClientes();
	/**
	 * @brief Altera o nome da paragem
	 *
	 * @param nome Nome da paragem
	 */
	void setNome(std::string nome);
	/**
	 * @brief Altera a latitude da paragem
	 *
	 * @param nome Nome da paragem
	 */
	void setLatitude(double latitude);
	/**
	 * @brief Altera a longitude da paragem
	 *
	 * @param nome Nome da paragem
	 */
	void setLongitude(double longitude);
	/**
	 * @brief Devolve a distancia da paragem a outro local
	 *
	 * @param latitude Latitude do local
	 * * @param longitude Longitude do local
	 */
	double distancia(double latitude, double longitude);
	/**
	 * @param p Paragem com a qual se vai comparar
	 *
	 * @return true se a paragem for menor que p (menor numero de clientes ou menor nome caso sejam iguais)
	 */
	bool operator < (const Paragem &p) const;
	/**
	 * @param p Paragem com a qual se vai comparar
	 *
	 * @return true se a paragem for igual a p (igual numero de clientes e igual nome)
	 */
	bool operator == (const Paragem &p) const;
};


/**
 * CLASS Paragens
 * Esta Classe guarda todas as paragens de comboio
 *
 */
class Paragens {
	std::vector<Paragem> paragens;
	BST<Paragem> paragensbst;
	
public:
	Paragens(): paragensbst(Paragem()){};
	/**
	 * @brief Adiciona uma paragem
	 *
	 * @param p1 Paragem
	 */
	void addParagem(Paragem &p1);
	/**
	 * @brief Devolve uma paragem
	 *
	 * @param id id da paragem
	 * @return Paragem guardada
	 */
	Paragem* getParagem(int id);
	/**
	 * @brief Aumenta o número de clientes por 1
	 *
	 * @param nome Nome (localidade) da paragem a alterar
	 */
	void aumentaNumClientes(string nome);
	/**
	 * @brief Diminui o número de clientes por 1
	 *
	 * @param nome Nome (localidade) da paragem a alterar
	 */
	void diminuiNumClientes(string nome);
	/**
	 * @brief Imprime no ecra todas as paragens
	 */
	void printParagens() const;
	/**
	 * @brief Imprime no ecra todas as paragens pela ordem da BST
	 */
	void printParagensBST() const;
	/**
	 * @brief Verifica vector paragens
	 *
	 * @return Verdade se o vector paragens estiver vazio, falso senao
	 */
	bool emptyParagens() const;
	/**
	 * @brief Verifica numero de paragens
	 *
	 * @return Numero de paragens
	 */
	int sizeParagens() const;
	/**
	 * @brief Imprime no ecra todas as paragens
	 *
	 * @param id id da paragem
	 */
	void deleteParagem(int id);
	/**
	 * @brief Encontra uma paragem
	 *
	 * @param nome Nome da paragem
	 * @return Devolve a paragem se encontrada, Paragem com nome "Nenhuma" senao encontrada
	 */
	Paragem* findParagem (std::string nome);
	/**
	 * @brief Guarda as paragens em "paragens.txt"
	 */
	void saveParagens();
	/**
	 * @brief Carrega as paragens em "paragens.txt"
	 */
	void loadParagens();
};

/**
 * CLASS Oficina
 * Esta Classe cria oficinas de comboios
 *
 */
class Oficina {
	std::string nome;
	double latitude;
	double longitude;
	unsigned int disponibilidade;
public:
	/**
	 * Construtor de Oficina
	 *
	 */
	Oficina(){};
	/**
	 * @brief Construtor de Paragem
	 * @param nome Nome da paragem
	 * @param latitude Latitude da Paragem
	 * @param longitude Longitude da Paragem
	 */
	Oficina(std::string nome, double latitude, double longitude);
	/**
	 * @brief Construtor de Paragem ao carregar ficheiros
	 * @param nome Nome da paragem
	 * @param latitude Latitude da Paragem
	 * @param longitude Longitude da Paragem
	 * @param disp Numero de dias ate estar disponivel
	 */
	Oficina(std::string nome, double latitude, double longitude, unsigned int disp);
	/**
	 * @brief Destrutor de Paragem
	 *
	 */
	~Oficina(){};
	/**
	 * @return nome da oficina
	 */
	std::string getNome() const;
	/**
	 * @return Latitude da oficina
	 */
	double getLatitude() const;
	/**
	 * @return Longitude da oficina
	 */
	double getLongitude() const;
	/**
	 * @return disponibilidade da oficina
	 */
	double getDisponibilidade() const;
	/**
	 * @brief Altera o nome da oficina
	 *
	 * @param nome Nome da oficina
	 */
	void setNome(std::string nome);
	/**
	 * @brief Altera a latitude da oficina
	 *
	 * @param latitude latitude da oficina
	 */
	void setLatitude(double latitude);
	/**
	 * @brief Altera a longitude da oficina
	 *
	 * @param longitude longitude da oficina
	 */
	void setLongitude(double longitude);
	/**
	 * @brief Altera o disponibilidade da oficina
	 *
	 * @param val valor a ser somar a disponibilidade
	 */
	void setDisponibilidade(int val);
	/**
	 * @return true if object is smaller than 01
	 */
	bool operator < (Oficina &o1);

};

/**
 * CLASS Oficinas
 * Esta Classe guarda e gere oficinas de comboios
 *
 */
class Oficinas {
	std::priority_queue <Oficina *> oficinas;
public:
	/**
	 * @brief Construtor de Oficinas
	 *
	 */
	Oficinas(){};
	/**
	 * @return Fila de prioridade com todas as oficinas
	 */
	std::priority_queue <Oficina *> getOficinas() const;
	/**
	 * @brief Adiciona oficina a fila de prioridade
	 * @param o1 Oficina
	 */
	void addOficina (Oficina *o1);
	/**
	 * @brief Imprime no ecra todas as paragens
	 */
	void printOficinas() const;
	/**
	 * @return Verdade quando nao existem oficinas, falso caso contrario
	 */
	bool emptyOficinas() const;
	/**
	 * @return Numero de oficinas
	 */
	int sizeOficinas() const;
	/**
	 * @brief Apaga uma oficina
	 */
	void deleteOficina(int id);
	/**
	 * @brief Guarda as oficinas em "oficinas.txt"
	 */
	void saveOficinas();
	/**
	 * @brief Carrega as oficinas em "oficinas.txt"
	 */
	void loadOficinas();
	/**
	 * @brief Encontra oficina com dado nome
	 * @param nome nome da oficina
	 * @returns apontador para a oficina
	 */
	Oficina* findOficina(std::string nome);
};


