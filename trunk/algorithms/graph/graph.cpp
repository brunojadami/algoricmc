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
 */
const int VT = 10;
/* Numero maximo de arestas no grafo. */
const int AR = VT * VT;
/* Cuidado para naum dar overflow no valor de 
 * infinito. */
const int INFINITY = 99999;
typedef int Weight;

struct grafo{
	/* Vertices de destino. */
	int dest[AR];
	/* Fluxo nas arestas e capacidade.
	 * M eh o vetor usado na busca em largura para achar
	 * o fluxo minimo do caminho atual. */ 
	int fluxo[AR], cap[AR], M[VT];
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
	/* Armazena o resultado de buscas e indica os predecessores 
	 * de cada vertice em uma busca. */
	vector<int> busca;
	int prev_busca[VT], prev_aresta[VT];
	
	/* Metodos. Como regra geral, os vetores vis e prev_busca e
	 * o vector busca devem ser limpados antes de uma chamada
	 * para os metodos.
	 *
	 * dijkstra e bellman_ford jah "limpam" os vetores prev e
	 * dist.
	 */ 
	void inic(int n);
	void aresta(int src, int dst, Weight p, int cap);
	void print();
	void dfs(int n);
	void bfs(int n);
	void dijkstra(int src);
	int bellman_ford(int src);
	int edmonds_karp(int src, int dst);
	int bfs_fluxo(int src, int dst);
	int inverso(int v);
};

int grafo::inverso(int v){
	return (v ^ 1);
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

void grafo::dfs(int n){
	/* Busca em profundidade. */
	int i, j;
	vis[n] = 1;
	busca.push_back(n);
	for(i = 0; i < nadj[n]; i++){
		j = dest[adj[n][i]];
		if(vis[j] == 0){
			prev_busca[j] = n;
			dfs(j);
		}
	}
}

void grafo::bfs(int n){
	/* Busca em largura. */
	int i, j, atual;
	queue<int> fila;
	vis[n] = 1;
	fila.push(n);
	while(fila.empty() == 0){
		atual = fila.front();
		busca.push_back(atual);
		fila.pop();
		for(i = 0; i < nadj[atual]; i++){
			j = dest[adj[atual][i]];
			if(vis[j]++ == 0){
				prev_busca[j] = atual;
				fila.push(j);
			}
		}
	}
}

int grafo::bfs_fluxo(int src, int dst){
	/* Busca em largura, versao
	 * para algoritmos de fluxo.
	 */ 
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
		busca.push_back(atual);
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

void grafo::dijkstra(int src){
	/* Algoritmo de Dijkstra.
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
		/* =====================================
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
		   =====================================
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

int grafo::edmonds_karp(int src, int dst){
	/* Calcula fluxo maximo em O(VE^2). 
	 * Limpa o vetor de fluxos antes*/
	int flow = 0, m, j, i;
	for(i = 0; i < nar; i++)
		fluxo[i] = 0;
	while(1){
		m = bfs_fluxo(src, dst);
		if(m == 0)
			return flow;
		flow += m;
		j = dst;
		while(j != src){
			fluxo[prev_aresta[j]] += m;
			fluxo[inverso(prev_aresta[j])] -= m;
			j = prev_busca[j];
		}
	}
}

int main(){
	grafo g;
	int n, u, v, c, a;
	cin >> n >> a;
	g.inic(n);
	for(int i = 0; i < a; i++){
		cin >> u >> v >> c;
		g.aresta(u,v,0,c);
	}
	cin >> u >> v;
	cout << g.edmonds_karp(u,v) << endl;
	return 0;
}
