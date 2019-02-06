#ifndef MAQUINISTAS_H_
#define MAQUINISTAS_H_

#include <unordered_set>
#include "datashoras.h"
#include "viagens.h"
#include "bilheteira.h"

using namespace std;
/**
* CLASS MAQUINISTA \n
* cria um novo maquinista dos comboios da CP
*
*/

class Maquinista
{
	string nome, apelido;
	bool ativo;
	unsigned id;
	vector<Viagem*> viagens;
public:
	/**
	* Construtor:
	* Se queremos adicionar um maquinista que já não se encontra ao serviço, o 4 parametro deverá ser
	* false, dado este não ser um maquinista atual
	*
	* @param primeiro nome do maquinistas
	* @param apelidos do maquinistas
	* @param identificacao do maquinistas
	* @param se o maqinista está atualmente ao serviço ou não
	*/
	Maquinista(string nome, string apelido, int id, int atual);
	
	/**
	* Construtor:
	*  Se se esta a adicionar um maquinista atual, não é necessario indicar o boleano se
	*  este é ou não um membro ativo, porque será um maquinista novo
	*
	* @param primeiro nome do maquinistas
	* @param apelidos do maquinistas serados por espaço
	* @param identificacao do maquinistas
	* @param vetor de viagens pelas quais o maquinista esta encarregue
	*/
	Maquinista(string nome, string apelido, int id);

	/**
	* Construtor:
	*  Se se esta a adicionar um maquinista atual, não é necessario indicar o boleano se 
	*  este é ou não um membro ativo, porque será um maquinista novo
	*
	* @param primeiro nome do maquinistas
	* @param apelidos do maquinistas serados por espaço
	* @param identificacao do maquinistas
	* @param vetor de viagens pelas quais o maquinista esta encarregue
	*/
	Maquinista(string nome, string apelido, int id, vector<Viagem *> viagens) ;

	/**
	* altera o nome do maquinista
	* @param novo nome
	*/	
	void novoNome(string n) { nome = n; }

	/**
	* altera o apelido do maquinista
	* @param novo apelido
	*/
	void novoApelido(string a) { apelido = a; }

	/**
	* altera o id do maquinista
	* @param novo id
	*/
	void novoId(int i) { id = i; }

	/**
	*  Metodo que retorna membro-dado
	*  @return o primeiro nome do maquinista
	*/
	string getNome() const { return nome; } ;

	/**
	*  Metodo que retorna membro-dado
	*	@return uma string com todos os apelidos do maquinista
	*/
	string getApelido() const { return apelido; } ;

	/**
	*  Metodo que retorna membro-dado
	*	@return o número de identificação do maquinista
	*/
	unsigned getId() const { return id; } ;

	/**
	*  Metodo que retorna membro-dado
	*	@return o estado ativo ou não do maquinista
	*/
	bool getAtivo() const { return ativo; };

	/**
	*  Metodo que retorna membro-dado de viagens
	*	@return vetor com apontadores para viagens associadas a um maquinista
	*/
	vector<Viagem *> getViagens() const { return viagens; } ;
	
	/*
	* Altera o estado (atual ou não) do maquinista. \n
	* Se este esta ativo, desativa-o e vice-versa.
	*/
	void alteraEstado();

	/**
	 * Faz overload ao operador de saida para dar output da informacao do maquinista como parâmetro
	 * na forma de tabela
	 *
	 * @param os Referencia para ofstream onde guardar a informacao
	 * @param M referência para o maquinista
	 *
	 * @return o estado, o número de identificação, o primeiro nome e todos os apelidos do maquinista.
	 */
	friend ostream & operator << (ostream &out, const Maquinista & M);

	/**
	* adiciona uma viagem ao maquinista
	* @param viagem a ser adicionada
	*
	* @return sucesso ou nao da adiçao da viagem
	*/
	bool adicionaViagem(Viagem *v);

	/**
	* elimina todas as viagens associadas a um maquinista. \n 
	* útil na reforma de um maquinista
	* 
	*/
	bool eliminaViagens();

	/**
	* elimina uma viagem associada a um maquinista. \n
	* @param id da viagens, que coicide com a posicao no vetor de viagens
	* @return sucesso na eliminacao da viagem
	*/
	bool eliminaViagem(unsigned int id);
	
	/**
	* redefinição do operador de igualdade
	* @param Maquinista
	*  @return igualdade ou nao dos maquinista
	*/
	bool operator== (Maquinista M3);
	
};

/**
*	redefiniçao do operador de igualdade\n
*  sendo a identificaçao de cada mquinistas única, dois maquinistas com o mesmo número de identificaçao
*   são o mesmo maquinista, se não forem este não deverá de ser aceite para a tabela de dispersão
*   @return se os maquinistas são iguais
*/
struct eqMaquinista {
	bool operator() (const Maquinista& M1, const Maquinista M2) const{
		return M1.getId()  == M2.getId();
	}
};

/**
*	Função hash \n
* utiliza o id do maquinista
* @return o valor que define o lugar na tabela de dispersão
*/
struct hstr {
	int operator() (const Maquinista &maquinista) const {	
		return maquinista.getId();
	}
};

/**
* Cria a tabela de dipersão
*/
typedef unordered_set<Maquinista, hstr , eqMaquinista> tabHMaq;

/**
*	CLASS MAQUINISTAS \n
*   Classe associada a tabela de dispersão
*
*/
class Maquinistas
{
	tabHMaq maquinistas;
public:
	/**
	* Construtor:
	* Inicia a tabela de dispersao vazia
	*
	*/
	Maquinistas() {};

	/** 
	*  Procura um maquinista pelo numero de identificaçao
	* @param maquinistas com a identificacao que se procura
	*
	* @return sucesso ou nao da procura de um maquinista
	*/
	 bool encontraMaquinista(Maquinista *M00);

	/**
	*  Elimina todos os maquinistas da tabela de dispersão
	*
	*/
	void clearMaquinistas();

	/**
	* Dependendo do estado atual do maquinista (ativo ou reformado) \n
	*  altera o estado de ativo de um maquinista, para desativo e elimina as viagens a este atribuidas ou
	*  altera o estado de reformado de um maquinista, para ativo
	*  @param maquinista a reformar-se ou a voltar a ser contratado
	* @return sucesso ou nao da procura de um maquinista para a reforma ou reativacao
	*/
	bool alteraEstado(Maquinista *M1);

	/**
	*
	* Ve o estado da tabela
	* @return um booleano com o estados vazio ou não da tabela de dispersão
	*/
	bool emptyMaquinistas();
	
	/*
	* extrai do ficheiro com os maquinistas os registos dos maquinistas guardados,
	* tanto os maquinista em serviço como os os antigos
	* @return se foi possível adicionar todos os maquinistas
	*/
	bool loadMaquinistas(Frota *f, string nome);

	/**
	* Guarda todos os maquinistas da tabela de dispersão
	* no ficheiro maquinistas.txt
	*/
	void saveMaquinistas();

	/** 
	* Guarda um novo maquinistas no ficheiro com os maquinistas
	* @param maquinistas a adicionar ao ficheiro
	*/
	void saveMaquinista(Maquinista *maq);

	/**
	* Adiciona um maquinista a tabela de dispersao
	* designada de maquinistas
	* @param maquinistas a adicionar a tabela de dispersão
	* @return o sucesso ou não da operaçao de inserção
	*/
	bool adicionaMaquinista(Maquinista *trabalhador);

	/**
	*  Se nos enganarmos a colocar um maquinista na 
	*  tabela podemos editar o erro
	*  @param maquinista enrado
	*  @param maquinista com o nome correto
	*  @return o sucesso ou não da operaçao de ediçao
	*/
	bool editaMaquinista(Maquinista *trabalhador1, Maquinista *trabalhador2);

	/**
	*  Se quisermos eliminar um maquinas, porque por exemplo faleceu,
	*  nao podendo ser reconstratado, podemos elimna-lo da nossa tabela
	*  @param maquinista que quermos eliminar da tabela
	*  @return o sucesso ou não da operaçao de eliminacao
	*/
	bool eliminaMaquinista(Maquinista *trabalhador);

	/**
	*  Mosta todos os maquinistas que se encontram na tabela de dispersão. \n
	*  Na respetiva ordem, número de identificação, nome
	*/
	void showMaquinistas();

	/**
	*  Mosta todos os maquinistas que se encontram na tabela de dispersão e as suas viagens associadas. \n
	*	Se o maquinistas estiver reformado tem um estado que o indica. Quando uma maquinista ainda nao
	*  tem viagens associadas, quer seja por ser novo ou ser reformado, a lista de maquinistas continua.
	*/
	void showMaquinistaseViagens();

	/**
	*  Mosta o maquinista passado por argumento. \n
	*  Na respetiva ordem, número de identificação, nome
	*  @param maquinista queremos os dados
	*/
	void showMaquinista(Maquinista *M1);

	/**
	* elimina uma vigem do maquinista passado no parametro 1 \n
	* A operacao pode nao ser sucedida se o maquinista nao existe ou se a viagens nao existe
	* @param maquinista queremos eliminar uma viagem
	*  @param  posicao no vetor de viagens do maquinista
	* @return sucesso ou nao da operacao
	*/
	bool EliminaViagemDoId(Maquinista* M1 , int id);
	/**
	*  Mosta as viagens do maquinista passado por argumento. \n
	*  A um maquinista reformado nao podem estar atribuidas viagens
	*  @param maquinista queremos os dados das viagens atribuidas
	*  @return se existem ou nao viagens atribuidas
	*/
	bool showViagensMaquinistas( Maquinista* M1) const;

	/**
	* @return o numero de maquinistas na tabela de dispersao
	*/
	unsigned int numeroDeMaquinistas();
	
	/**
	* atribui ao maquinista no 1 argumento a viagem passada no 2 argumento
	* 
	*  @param maquinista a quem vamos atribuir a viagem
	*  @param viagem que queremos atribuir
	*/
	bool atribuiViagem( Maquinista* M1, Viagem * v);

};


#endif /*MAQUINISTAS_H_*/
