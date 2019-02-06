#ifndef DATASHORAS_H_
#define DATASHORAS_H_

#include <vector>
#include <sstream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <limits>

class Registo;
class Compra;
class Datas;
class Horas;

/**
 * CLASS DATAS\n
 * Esta class cria objectos com datas e trata de todas as suas operacoes
 *
 */
class Datas {
	unsigned int ano;
	unsigned int mes;
	unsigned int dia;
public:
	/**
	 * Construtor de datas por strings\n
	 */
	Datas(){};
	/**
	 * Contrutor de datas por inteiros
	 * @param a Ano
	 * @param m Mes
	 * @param d Dia
	 */
	Datas(unsigned int a, unsigned int m, unsigned int d){
		if (d > 31 || d < 1 || m > 12 || m < 1)
			throw DataInvalida();


		ano= a; mes = m; dia = d;
	}
	/**
	 * Construtor de datas por strings\n
	 * Faz parse a string tem excepcoes para formatos errados
	 * @param d String com data no formato DD-MM-AAAA
	 */
	Datas(std::string d){

		std::string tempDia = "";
		std::string tempMes = "";
		std::string tempAno = "";

		if (d.length() != 10)
			throw FormatoStringInvalido();

		for (unsigned int i = 0; i < d.length(); i++){

			if (d.at(i) < '0' && d.at(i) > '9' && d.at(i) != '-')
				throw FormatoStringInvalido();

			if (d.at(i) == '-'){
				continue;
			}

			if (tempDia.length() < 2){
				tempDia += d.at(i);
				continue;
			}
			if (tempMes.length() < 2) {
				tempMes += d.at(i);
				continue;
			}
			if (tempAno.length() < 4){
				tempAno += d.at(i);
				continue;
			}
			else break;
		}

		if (tempDia.length() < 2)
			throw FormatoStringInvalido();

		if (tempMes.length() < 2)
			throw FormatoStringInvalido();

		if (tempAno.length() < 4	)
			throw FormatoStringInvalido();


		int tDia = std::stoi(tempDia);
		int tMes = std::stoi(tempMes);
		int tAno = std::stoi(tempAno);

		if (tDia > 31 || tDia < 1 || tMes > 12 || tMes < 1)
			throw DataInvalida();

		dia = tDia;
		mes = tMes;
		ano = tAno;

	}
	/**
	 * @return Ano
	 */
	unsigned int getAno() const {return ano;}
	/**
	 * @return Mes
	 */
	unsigned int getMes() const {return mes;}
	/**
	 * @return Dia
	 */
	unsigned int getDia() const {return dia;}
	/**
	 * @return Numero de horas totais desde o ano 2000, util para comparacao direta
	 * de um momento especifico
	 */
	double getTotalHours() const{

		double hours = (ano - 2000) * 365.2425;

		switch(mes){
		case 2:
			hours += 31;
			break;
		case 3:
			hours += 59;
			break;
		case 4:
			hours += 90;
			break;
		case 5:
			hours += 120;
			break;
		case 6:
			hours += 151;
			break;
		case 7:
			hours += 181;
			break;
		case 8:
			hours += 212;
			break;
		case 9:
			hours += 243;
			break;
		case 10:
			hours += 273;
			break;
		case 11:
			hours+= 304;
			break;
		case 12:
			hours += 334;
			break;
		}

		hours += dia;


		return hours * 24;
	}
	/**
	 * Excepcao
	 */
	class DataInvalida {};
	/**
	 * Excepcao
	 */
	class FormatoStringInvalido{};

	

	/**
	 * Faz overload ao operador de saida para imprimir a data no formato(DD-MM-AAAA)\n
	 * @param os Referencia para ofstream
	 * @param d1 Referencia para data
	 */
	friend std::ostream& operator << (std::ostream &os, const Datas &d1){
		os << std::right << std::setw(2) << std::setfill('0') << d1.dia << "-"
				<< std::setw(2) << std::setfill('0') << d1.mes << "-" << d1.ano;
		return os;
	}
	/**
	 * Redefinicao do operador maior
	 * @param d1 Referencia para a data com a qual se vai comparar
	 * @return True se d1 e menor
	 */
	bool operator > (const Datas &d1){

		if (this->ano > d1.ano)
			return true;
		if (this->ano == d1.ano){
			if (this->mes > d1.mes)
				return true;
			if (this->mes == d1.mes){
				if (this->dia > d1.dia)
					return true;
			}
		}
	return false;
	}
	/**
	 * Redefinicao do operador comparacao
	 * @param d1 Referencia para a data com a qual se vai comparar
	 * @return True se as duas datas sao iguais
	 */
	bool operator == (const Datas &d1){
		if ( this->ano == d1.ano && this->mes == d1.mes && this->dia == d1.dia)
			return true;

	return false;
	}
	/**
	 * Redefinicao do operador menor
	 * @param Referencia para a data com a qual se vai comparar
	 * @return True se d1 e maior
	 */
	bool operator < (const Datas &d1){

		if (this->ano < d1.ano)
			return true;
		if (this->ano == d1.ano){
			if (this->mes < d1.mes)
				return true;
			if (this->mes == d1.mes){
				if (this->dia < d1.dia)
					return true;
			}
		}
	return false;
	}
};

/**
 * CLASS DATAS\n
 * Esta class cria objectos com datas e trata de todas as suas operacoes
 *
 */
class Horas {
	unsigned int hora;
	unsigned int min;
public:
	/**
	 * Contrutor de horas usando inteiros
	 */
	Horas(){};
	/**
	 * Contrutor de horas usando inteiros
	 * @param h Horas
	 * @param m Minutos
	 */
	Horas(unsigned int h, unsigned int m){
		hora = h; min = m;
	}
	/**
	 * Construtor de datas usando string
	 * Faz parse a string tem excepcoes para formatos errados
	 * @param h String com hora no formato HH-MM
	 */
	Horas (std::string h){
		if (h.length() != 5)
			throw FormatoStringInvalido();

		std::string tempHora = "";
		std::string tempMin = "";

		for (unsigned int i = 0; i < h.length(); i++){
			if (h.at(i) < '0' && h.at(i) > '9' && h.at(i) != ':')
				throw FormatoStringInvalido();

			if (h.at(i) == ':'){
				continue;
			}

			if (tempHora.length() < 2){
				tempHora += h.at(i);
				continue;
			}
			if (tempMin.length() < 2) {
				tempMin += h.at(i);
				continue;
			}
		}

		if (tempHora.length() < 2 || tempMin.length() < 2)
			throw FormatoStringInvalido();

		int tHora = std::stoi(tempHora);
		int tMin = std::stoi(tempMin);

		if (tHora > 23 || tHora < 0 || tMin > 59 || tMin < 0 )
			throw HoraInvalida();

		hora = tHora;
		min = tMin;
	}
	/**
	 * @return Horas
	 */
	unsigned int getHora() const {return hora;}
	/**
	 * @return Minutos
	 */
	unsigned int getMin() const {return min;}
	/**
	 * @return Numero total de horas
	 */
	double getTotalHours() const {
		double hmin = (double)min/60;
		return (double)hora + hmin;
	}
	/**
	 * Excepcao
	 */
	class HoraInvalida{};
	/**
	 * Excepcao
	 */
	class FormatoStringInvalido{};
	/**
	 * @param os Referencia para ofstream onde guardar a informacao
	 * @param h1 Referencia para horas
	 */
	friend std::ostream& operator << (std::ostream &os, const Horas &h1){
		os << std::right << std::setfill('0') << std::setw(2) << h1.hora << ":"
				<< std::setfill('0') << std::setw(2) <<h1.min;
		return os;
	}
	/**
	 * Redefinicao do operador maior
	 * @param h1 Referencia para a hora com a qual se vai comparar
	 * @return True se h1 e menor
	 */
	bool operator > (const Horas &h1){
		if (this->hora > h1.hora)
			return true;
		if (this->hora == h1.hora){
			if (this->min > h1.min)
				return true;
		}
	return false;
	}
	/**
	 * Redefinicao do operador comparacao
	 * @param h1 Referencia para a hora com a qual se vai comparar
	 * @return True se as duas horas sao iguais
	 */
	bool operator == (const Horas &h1){
		if ( this->hora == h1.hora && this->min == h1.min )
			return true;

	return false;
	}
	/**
	 * Redefinicao do operador menor
	 * @param h1 Referencia para a hora com a qual se vai comparar
	 * @return True se h1 e maior
	 */
	bool operator < (const Horas &h1){
		if (this->hora < h1.hora)
			return true;
		if (this->hora == h1.hora){
			if (this->min < h1.min)
				return true;
		}
	return false;
	}

};




#endif
