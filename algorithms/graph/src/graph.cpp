#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
#include<utility>
#include<queue>
using namespace std;

const int VT = 10;		/*!<Numero máximo de vértices que o grafo pode comportar. Pode estourar a memoria estática. */
const int AR = VT * VT;		/*!<Numero máximo de arestas que o grafo pode comportar. */
const int INFINITY = 99999;	/*!<Valor de infinito, usado por Dijkstra e outros algoritmos. */
typedef int Weight;

struct grafo{
	int dest[AR];		/*!<Vértices de destino de uma dada aresta. */
	int fluxo[AR];		/*!<Fluxo em cada aresta. */
        int cap[AR];		/*!<Capacidade de cada aresta. */
        int M[VT];		/*!<Usado para achar a capacidade dos caminhos na busca em largura de fluxos. */
	int adj[VT][VT];	/*!<Tipo de matriz de adjacência. Armazena o índice de cada aresta. */
	int nadj[VT];		/*!<Número de arestas saindo de cada vértice. */
	int nvt;		/*!<Número de vertices no grafo. Esse numero dever ser menor ou igual a VT. */
	int nar;		/*!<Número de arestas no grafo. */
	int vis[VT];		/*!<Nós visitados. 1 indica que o nó foi visitado e 0 indica que não foi nos métodos que o utilizam. */
	int dist[VT];		/*!<Distância até cada vértice. Usado por Dijkstra e Bellman-Ford. */
	int prev[VT];		/*!<Predecessor de cada vértice. Usado por Dijkstra e Bellman-Ford. */
	Weight peso[AR];	/*!<Peso de cada aresta. */
	vector<int> busca;	/*!<Armazena o resultado de uma busca. */
	int prev_busca[VT];	/*!<Predecessores de cada vértice em uma busca. */
	int prev_aresta[VT];	/*!<Aresta usada para chegar aos vértices em uma busca. */

	/*! \brief Inicializador do grafo.
	 *
	 * Após esse método ser executado, o grafo tem n nós e nenhuma aresta.
	 *
	 * \param[in] n Numero de vertices que o grafo tem. Deve ser menor ou igual a VT. Default 0.
	 */ 
	void inic(int n);
	/*! \brief Insere uma aresta no grafo.
	 *
	 * \param[in] src Vértice origem.
	 * \param[in] dst Vértice destino.
	 * \param[in] p Peso da aresta. Default 0.
	 * \param[in] c Capacidade da aresta. Default 0.
	 *
	 * \note Para usar os algoritmos de fluxo, é necessário descomentar uma parte 
	 * do código desse método. A parte está indicada em seu código. Isso faz com que o grafo insira 
	 * insira a aresta desejada e, além dela, uma aresta inversa, usada internamente pelos algoritmos de
	 * fluxo, para que o fluxo "possa ser mandado de volta".
	 */ 
	void aresta(int src, int dst, Weight p, int c);
	/*! \brief Imprime o grafo.
	 *
	 * Imprime na forma {dst, p, c, f}, onde p é o peso da aresta, c, sua capacidade
	 * e f, o fluxo nela.
	 *
	 * \todo Fazer o método imprimir c e f, e colocar uma opção de imprimir as arestas
	 * inseridas para fluxos ou não.
	 */
	void print();
	/*! \brief Busca em profundidade.
	 *
	 * \param[in] src Nó inicial.
	 * \param[out] busca Ordem em que os nós são visitados pela primeira vez.
	 * \param[out] prev_busca Predecessor de cada nó.
	 * \param[out] prev_aresta Aresta usada pelo predecessor de cada nó para chegar nele.
	 * \param[out] vis Nós que foram visitados por essa busca.
	 * \note Não limpa vis, prev_busca, prev_aresta e o vector busca internamente.
	 */
	void dfs(int src);
	/*! \brief Busca em largura.
	 *
	 * Veja os comentários da busca em profundidade. Os mesmos se aplicam aqui.
	 *
	 * \note Não limpa vis, prev_busca, prev_aresta e o vector busca internamente.
	 */ 
	void bfs(int n);
	/*! \brief Algoritmo de Dijkstra.
	 *
	 * O algoritmo para quando encontra a menor distância até o nó destino,
	 * ou acha a menor distância até cada nó, caso dst == -1.
	 *
	 * \param[in] src Nó origem.
	 * \param[in] dst Nó destino. Default -1.
	 * \param[out] prev Predecessor de cada nó. -1 indica que não existe predecessor.
	 * \param[out] vis Nós visitados.
	 * \param[out] dist Distância total até cada nó, partindo-se de src.
	 * \note Não limpa o vetor vis, e limpa prev e dist antes de executar o algoritmo.
	 * \todo Fazer o método gravar as arestas usadas no vetor prev_aresta.
	 */ 
	void dijkstra(int src, int dst);
	/*! \brief Bellman-Ford.
	 *
	 * Acha a menor distância até cada nó. Funciona em grafos com
	 * arestas cujos pesos são negativos.
	 *
	 * \param[in] src Nó origem.
	 * \param[out] prev Predecessor de cada nó.
	 * \param[out] dist Distância até cada nó.
	 * \return 1 se existe pelo menos um ciclo negativo no grafo, 0 caso contrário.
	 * \note Limp automaticamente os vetores prev e busca antes de executar o algoritmo.
	 */  
	int bellman_ford(int src);
	/*! \brief Algoritmo de fluxo máximo de Edmonds-Karp.
	 *
	 * Acha o fluxo máximo do grafo. Para isso, realiza várias buscas em largura
	 * para encontrar caminhos que adicionam fluxo.
	 *
	 * \param[in] src Nó origem.
	 * \param[in] dst Nó final.
	 * \param[out] fluxo Fluxo passando em cada aresta.
	 * \param[out] vis Determina o Min-Cut do grafo.
	 * \return Valor do fluxo máximo no grafo.
	 * \note O método limpa o vetor fluxo antes de executar o algoritmo.
	 * Utiliza os vetores prev_busca e prev_aresta, mas como parte da implementação, por 
	 * isso não são marcados como parâmetros de saída aqui.
	 * vis não é alterado por esse método diretamente, e sim pela busca para fluxos.
	 */
	int edmonds_karp(int src, int dst);
	/*! \brief Busca em largura, modificada para o ser usada por Edmonds-Karp.
	 *
	 * \param[in] src Nó origem.
	 * \param[in] dst Nó destino.
	 * \param[out] vis Nós que podem ser alcançados nesse grafo residual. Determina o Min-Cut ao final do
	 * algoritmo de Edmonds-Karp.
	 * \return Capacidade do caminho encontrado.
	 * \note Limpa o vetor vis. Atualiza os vetores prev_busca e prev_aresta para que sejam usados 
	 * por Edmonds-Karp. Esses vetores não precisam ser limpados.
	 */ 
	int bfs_fluxo(int src, int dst);
	/*! \brief Retorna a aresta inversa.
	 *
	 * Método usado por algoritmos de fluxo. Retorna a aresta inversa de uma dada aresta.
	 *
	 * \param[in] a Índice de uma aresta.
	 * \return Índice da aresta inversa.
	 */ 
	inline int inverso(int a);
};

inline int grafo::inverso(int a){
	return (a ^ 1);
}

void grafo::inic(int n = 0){
	memset(nadj, 0, sizeof(nadj));
	nvt = n;
	nar = 0;
}

void grafo::aresta(int src, int dst, Weight p = 0, int c = 0){
	adj[src][nadj[src]++] = nar;
	peso[nar] = p;
	cap[nar] = c;
	dest[nar++] = dst;

	/* Parte abaixo eh para fluxos. */
	/*
	   adj[dst][nadj[dst]++] = nar;
	   peso[nar] = p;
	   cap[nar] = 0;
	   dest[nar++] = src;
	   */
}

void grafo::print(){
	for(int i = 0; i < nvt; i++){
		cout << i << " : ";
		for(int j = 0; j < nadj[i]; j++)
			cout << '(' << dest[adj[i][j]] << ',' << peso[adj[i][j]] << ") ";
		cout << endl;
	}
}

void grafo::dfs(int src){
	/* Busca em profundidade. */
	int j;			// j = dest[adj[src][i]]

	vis[src] = 1;
	busca.push_back(src);
	for(int i = 0; i < nadj[src]; i++){
		j = dest[adj[src][i]];
		if(vis[j] == 0){
			prev_busca[j] = src;
			prev_aresta[j] = adj[src][i];
			dfs(j);
		}
	}
}

void grafo::bfs(int src){
	/* Busca em largura. */
	int j, atual;		// atual eh o vertice que foi retirado da pilha, j eh dest[adj[atual][i]]
	queue<int> fila;

	vis[src] = 1;
	fila.push(src);
	while(fila.empty() == 0){
		atual = fila.front();
		busca.push_back(atual);
		fila.pop();
		for(int i = 0; i < nadj[atual]; i++){
			j = dest[adj[atual][i]];
			if(vis[j] == 0){
				vis[j]++;
				prev_busca[j] = atual;
				prev_aresta[j] = adj[atual][i];
				fila.push(j);
			}
		}
	}
}

int grafo::bfs_fluxo(int src, int dst){
	/* Busca em largura, versao para algoritmos de fluxo. */ 
	int i, j, atual;
	queue<int> fila;
	int c_tmp, tmp;
	prev_busca[dst] = -1;
	M[src] = INFINITY;
	for(i = 0; i < nvt; i++)
		vis[i] = 0;
	vis[src] = 1;
	fila.push(src);
	while(fila.empty() == 0){
		atual = fila.front();
		fila.pop();
		for(i = 0; i < nadj[atual]; i++){
			tmp = adj[atual][i], j = dest[tmp];
			c_tmp = cap[tmp] - fluxo[tmp];
			if(c_tmp > 0 && vis[j] == 0){
				vis[j] = 1;
				M[j] = (M[atual] > c_tmp ? c_tmp : M[atual]);
				prev_busca[j] = atual;
				prev_aresta[j] = tmp;
				if(j == dst)
					return M[dst];
				fila.push(j);
			}
		}
	}
	return 0;
}

void grafo::dijkstra(int src, int dst = -1){
	/* Algoritmo de Dijkstra.
	 * A func calcula o caminho de src ateh cada vertice (ou ateh dst ser encontrado, veja o
	 * comentario abaixo). O predecessor de cada vertice fica armazenado no vetor prev. Para
	 * ver o caminho de src ateh dst, faca isso:
	 * 
	 * 1  S := empty sequence
	 * 2  u := target
	 * 3  while previous[u] is defined:
	 * 4      insert u at the beginning of S
	 * 5      u := previous[u]
	 */
	int i;		// vertice destino, que foi retirado da pilha
        int v, j;	// variaveis tipo "macro", para evitar muita digitacao
	Weight tmp;	
	priority_queue<pair<Weight, int> > pilha;

	for(i = 0; i < nvt; i++){
		dist[i] = INFINITY;
		prev[i] = -1;
	}
	pilha.push(make_pair(dist[src] = 0, src));
	while(!pilha.empty()){
		i = pilha.top().second;

		/* Retorna caso dst seja alcançado. */
		if(i == dst)
			return;

		pilha.pop();
		if(vis[i] != 0)
			continue;
		vis[i] = 1;
		for(int k = 0; k < nadj[i]; k++){
			v = adj[i][k]; j = dest[v];
			tmp = dist[i] + peso[v];
			if(tmp < dist[j]){
				dist[j] = tmp;
				prev[j] = i;
				if(vis[j] == 0)
					pilha.push(make_pair( -dist[j], j));
			}
		}
	}
}

int grafo::bellman_ford(int src){
	/* Algoritmo de Belma-Ford.
	 * Retorna 1 se houver um ciclo negativo no grafo.
	 */
	int stop = 0;		// usada para otimizar o algoritmo 
	int j, tmp;		// variaveis tipo "macro"

	for(int i = 0; i < nvt; i++){
		dist[i] = INFINITY;
		prev[i] = -1;
	}
	dist[src] = 0;
	/* Relaxa as arestas nvt - 1 vezes, pois esse eh o tamanho maximo de um caminho simples pelo
	 * grafo. A variavel stop eh usada pra sair do for caso nenhuma aresta seja relaxada. Eh
	 * apenas uma otimizacaum.
	 */ 
	for(int i = 1; i < nvt && (stop == 0); i++){
		stop = 1;
		for(int u = 0; u < nvt; u++)
			for(int v = 0; v < nadj[u]; v++){
				j = adj[u][v];
				tmp = dist[u] + peso[j];
				if(tmp < dist[dest[j]]){
					stop = 0;
					dist[dest[j]] = tmp;
					prev[dest[j]] = u;
				}
			}
	}
	/* Verifica se ha ciclo negativo. */
	for(int u = 0; u < nvt; u++)
		for(int v = 0; v < nadj[u]; v++){
			tmp = dist[u] + peso[j = adj[u][v]];
			if(tmp < dist[dest[j]])
				return 1;
		}
	return 0;
}

int grafo::edmonds_karp(int src, int dst){
	/* Calcula fluxo maximo em O(VE^2). 
	 * Limpa o vetor de fluxos antes*/
	int flow = 0, min, j;

	for(int i = 0; i < nar; i++)
		fluxo[i] = 0;
	while(1){
		min = bfs_fluxo(src, dst);
		if(min == 0)
			return flow;
		flow += min;
		j = dst;
		while(j != src){
			fluxo[prev_aresta[j]] += min;
			fluxo[inverso(prev_aresta[j])] -= min;
			j = prev_busca[j];
		}
	}
}
