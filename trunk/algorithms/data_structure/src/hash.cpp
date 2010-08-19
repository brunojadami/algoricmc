#include<list>
#include<pair>
#include<utility>
#include<algorithms>
using namespace std;

template<class K, class V> struct Hash{
	list<pair<K, V> > *hash;	/*!<Tabela hash. */
	int (*hashFunction)(K key);	/*!< \f$hashFunction\mathbin: K \rightarrow Z \f$ */
	int buckets;			/*!<Número de baldes do hash. */

	/*! \brief Cria um hash com \f{emph}{{buckets}\f} posições.
	 *
	 * O hash é criado com \f{emph}{{buckets}\f} posições. Não é possível 
	 * alterar o número de posições após ter sido criado.
	 *
	 * \param[in] buckets Número de baldes(posições) totais 
	 * do hash.
	 * \param[in] hashFunction Função hash.
	 *
	 * \note Preferencialmente, use números primos para \f{emph}{{buckets}\f}.
	 * Aqui estão listadas algumas funções hash interessantes:
	 *
	 * \todo Listar boas funções hash.
	 */ 
	Hash(int (*)(K) hashFunction, int buckets){
		this->buckets = buckets;
		hash = new list<T&>[buckets];
		this->hashFunction = hashFunction;
	};

	/*! \brief Destrutor. */
	~Hash(){ delete[] hash; hash = hashFunction = 0; };
		
	/*! \brief Insere value no hash.
	 *
	 * Calcula a posição na qual \f{emph}{{value}\f} será inserido usando
	 * \f{emph}{{hashFunction(key)}.\f}
	 * 
	 * \param[in] key Chave de value.
	 * \param[in] value Elemento que seŕa inserido no hash.
	 * */
	void put(K key, V value){
		int position = hashFunction(key) % buckets;
		hash[position].push_front(make_pair(key, value));
	};

	/*! \brief Recupera um elemento no hash.
	 *
	 * Recupera o elemento cuja chave é \f{emph}{{key}\f}.
	 *
	 * \param[in] key Chave do elemento desejado.
	 *
	 * \return Retorna um iterador para o \f{emph}{{pair<key, value>}\f},
	 * identificado por \f{emph}{{key}\f}. Se não existir esse 
	 * par, retorna \f{emph}{{NULL}\f}.
	 */
	list<pair<K, V> >::iterator get(K key){
		int position = hashFunction(key) % buckets;
		list<pair<K, V> >::iterator it;
		for(it = hash[position].begin(); it != hash[position].end(); it++)
			if(it->first == key)
				return it;
		return 0;
	};
};
