#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
#include<utility>
#include<queue>
using namespace std;

/* Numero maximo de vertices no grafo.
 * O numero de vertices do grafo (quando ele for
 * inicializado) naum pode exceder esse numero. 
 *
 * CUIDADO COM SEU TAMANHO, POIS PODE ESTOURAR A 
 * MEMORIA ESTATICA. SE FOR O CASO, USE PONTEIROS.
 * */
const int VT = 100;
/* Numero maximo de arestas no grafo. */
const int AR = VT * VT;
/* Cuidado para naum dar overflow no valor de 
 * infinito. */
const int INFINITY = 99999;
typedef int Weight;

struct grafo{
	/* Vertices de destino. */
	int dest[AR];
	/* Especie de matriz de adjacencia. */
	int adj[VT][VT];
	/* Numero de arestas saindo de cada vertice,
	 * numero de vertices no grafo e numero
	 * de arestas no grafo. */
	int nadj[VT], nvt, nar, vis[VT];
	/* Vetores usados por Dijkstra e Bellman-Ford. */
	int dist[VT], prev[VT];
	/* Peso das arestas. */
	Weight peso[AR];
	/* Armazena o resultado de buscas. */
	vector<int> busca;
	
	void inic(int n);
	void aresta(int src, int dst, Weight p);
	void print();
	void dfs(int n);
	void bfs(int n);
	void dijkstra(int src);
	int bellman_ford(int src);
};

void grafo::inic(int n = 0){
	memset(nadj, 0, sizeof(nadj));
	nvt = n;
	nar = 0;
}

void grafo::aresta(int src, int dst, Weight p = 0){
	adj[src][nadj[src]++] = nar;
	peso[nar] = p;
	dest[nar++] = dst;
}

void grafo::print(){
	for(int i = 0; i < nvt; i++){
		cout << i << " : ";
		for(int j = 0; j < nadj[i]; j++)
			cout << '(' << dest[adj[i][j]] << ',' << peso[adj[i][j]] << ") ";
		cout << endl;
	}
}

void grafo::dfs(int n){
	/* Busca em profundidade.
	 * Use busca.clear() e
	 * memset(vis, 0, sizeof(vis))
	 * antes de chamar esse metodo.
	 */ 
	vis[n] = 1;
	busca.push_back(n);
	for(int i = 0; i < nadj[n]; i++)
		if(vis[dest[adj[n][i]]] == 0)
			dfs(dest[adj[n][i]]);
}

void grafo::bfs(int n){
	/* Busca em largura.
	 * Use busca.clear() e 
	 * memset(vis, 0, sizeof(vis))
	 * antes de chamar esse metodo.
	 */
	int i, atual;
	queue<int> fila;
	vis[n] = 1;
	fila.push(n);
	while(fila.empty() == 0){
		atual = fila.front();
		busca.push_back(atual);
		fila.pop();
		for(i = 0; i < nadj[atual]; i++)
			if(vis[dest[adj[atual][i]]]++ == 0)
				fila.push(dest[adj[atual][i]]);
	}
}

void grafo::dijkstra(int src){
	/* Algoritmo de Dijkstra.
	 * Use memset(vis, 0, sizeof(vis))
	 * antes.
	 * A func calcula o caminho de src
	 * ateh cada vertice( ou ateh dst ser encontrado,
	 * veja o comentario abaixo).
	 * O predecessor de cada vertice fica armazenado
	 * no vetor prev.
	 * Para ver o caminho de src ateh dst,
	 * faca isso:
	 * 
	 * 1  S := empty sequence
	 * 2  u := target
	 * 3  while previous[u] is defined:
	 * 4      insert u at the beginning of S
	 * 5      u := previous[u]
	 * 
	 */
	int i, v, j;
	Weight tmp;
	for(i = 0; i < nvt; i++){
		dist[i] = INFINITY;
		prev[i] = -1;
	}
	priority_queue<pair<Weight, int> > pilha;
	pilha.push(make_pair(dist[src] = 0, src));
	while(!pilha.empty()){
		i = pilha.top().second;
		/* ======================================================
		 * Este if faz a func retornar assim
		 * que a distancia ateh o vertice
		 * destino seja calculada. 
		 *
		 * Se tirar este if, a func calcula o 
		 * caminho minimo ateh cada vertice.
		 * Apague tb o parametro da func.
		 */ 
		/* if(i == dst)
		   return;
		   ======================================================
		   */
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
	int i, u, v, tmp, j, stop = 0;
	for(i = 0; i < nvt; i++){
		dist[i] = INFINITY;
		prev[i] = -1;
	}
	dist[src] = 0;
	/* Relaxa as arestas nvt - 1 vezes, pois esse
	 * eh o tamanho maximo de um caminho simples pelo grafo.
	 * A variavel stop eh usada pra sair do for caso nenhuma
	 * aresta seja relaxada. Eh apenas uma otimizacaum.
	 */ 
	for(i = 1; i < nvt && (stop == 0); i++){
		stop = 1;
		for(u = 0; u < nvt; u++)
			for(v = 0; v < nadj[u]; v++){
				j = adj[u][v];
				tmp = dist[u] + peso[j];
				if(tmp < dist[dest[j]]){
					stop = 0;
					dist[dest[j]] = tmp;
					prev[dest[j]] = u;
				}
			}
	}
	/* Verifica se ha ciclo negativo. Esse teste eh mais 
	 * uma iteracaum do teste acima, pode ser copiado
	 * e colado.
	 */ 
	for(u = 0; u < nvt; u++)
		for(v = 0; v < nadj[u]; v++){
			tmp = dist[u] + peso[j = adj[u][v]];
			if(tmp < dist[dest[j]])
				return 1;
		}
	return 0;
}
