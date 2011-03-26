#include<string>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
#include<utility>
#include<queue>
#include<algorithm>					// Possui a função min.
using namespace std;

const int MAX_NODES = 10000;		/*!<Numero máximo de nós que o Graph pode comportar. NOTA: Pode estourar a memoria estática. */
const int INFINITY = 100000;		/*!<Valor de infinito, usado por Dijkstra e outros algoritmos. */
typedef int Weight;

struct Graph{
	vector<int> destinies;				/*!<Nós de destino de uma dada aresta. */
	vector<int> flows;					/*!<Fluxo em cada aresta. */
	vector<int> capacities;				/*!<Capacidade de cada aresta. */
	//int pathCapacities[MAX_NODES];	/*!<Usado para achar a capacidade dos caminhos na busca em largura de fluxos. */
	vector<int> arcs[MAX_NODES];		/*!<Arestas de cada nó. Armazena o índice de cada aresta. */
	int nNodes;							/*!<Número de vertices no grafo. Dever ser menor ou igual a MAX_NODES. */
	vector<Weight> weights;				/*!<Peso de cada aresta. */

	/*! \brief Inicializador do grafo.
	 *
	 * Limpa o grafo inteiro e cria um grafo com nNodes vértices.
	 *
	 * \param[in] nNodes Número de vértices que o grafo tem. Deve ser menor ou igual a MAX_NODES. Default 0.
	 */ 
	void initialize(int nNodes);

	/*! \brief Insere uma aresta no grafo.
	 *
	 * \param[in] srcNode Vértice origem.
	 * \param[in] dstNode Vértice destino.
	 * \param[in] weight Peso da aresta. Default 0.
	 *
	 * \note Para usar os algoritmos de fluxo, é necessário descomentar uma parte 
	 * do código desse método. A parte está indicada em seu código. Isso faz com que o grafo insira 
	 * a aresta desejada e, além dela, uma aresta inversa, usada internamente pelos algoritmos de
	 * fluxo, para que o fluxo possa "ser mandado de volta". Essa aresta tem capacidade 0.
	 */ 
	void insertArc(int srcNode, int dstNode, Weight weight /*, int capacity*/ );

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
	 * \param[in] srcNode Nó inicial.
	 *
	 * \param[out] visited Nós que foram visitados por essa busca.
	 *
	 * \todo Implementar funcionalidade extra 4.
	 */
	void dfs(int srcNode, int visited[]);

	/*! \brief Busca em largura.
	 *
	 * Busca em largura. Também implementa algumas funcionalidades usadas 
	 * por edmondsKarp (veja a seção de funcionalidades extras no código do 
	 * método).  
	 *
	 * \param[in] srcNode Nó inicial.
	 *
	 * \note edmondsKarp faz as inicializações necessárias antes de chamar este método.
	 *
	 * \todo Implementar funcionalidade 4, e verificar funcionalidade 5.
	 * Finalizar seção de código de inicialização.
	 */ 
	void bfs(int srcNode, int visited[]);

	/*! \brief Algoritmo de Dijkstra.
	 *
	 * Algoritmo de Dijkstra. 
	 *
	 * \param[in] srcNode Nó origem.
	 *
	 * \param[out] previousNodes Predecessor de cada nó. -1 indica que não existe predecessor.
	 * \param[out] minDistances Distância total até cada nó, partindo-se de srcNode.
	 */ 
	void dijkstra(int srcNode, Weight minDistances[], int previousNodes[]);

//	/*! \brief Bellman-Ford.
//	 *
//	 * Acha a menor distância até cada nó. Funciona em grafos com
//	 * arestas cujos pesos são negativos.
//	 *
//	 * \param[in] srcNode Nó origem.
//	 *
//	 * \param[out] previousNodes Predecessor de cada nó.
//	 * \param[out] usedArcs Arestas usada pelo predecessor de cada nó para chegar nele.
//	 * \param[out] distances Distância até cada nó.
//	 *
//	 * \return 1 se existe pelo menos um ciclo negativo no grafo, 0 caso contrário.
//	 *
//	 * \note Inicializa "previousNodes" e "distances" antes de executar.
//	 */  
//	int bellmanFord(int srcNode);
//
//	/*! \brief Algoritmo de fluxo máximo de Edmonds-Karp.
//	 *
//	 * Acha o fluxo máximo no grafo. Para isso, realiza várias buscas em largura
//	 * para encontrar caminhos que adicionam fluxo.
//	 *
//	 * \param[in] srcNode Nó origem.
//	 * \param[in] dstNode Nó final.
//	 *
//	 * \param[out] flows Fluxo passando em cada aresta.
//	 * \param[out] visited Determina o Min-Cut.
//	 * \param[out] previousNodes É usada pela busca em largura.
//	 * \prama[out] usedArcs É usada pela busca em largura.
//	 *
//	 * \return Valor do fluxo máximo no grafo.
//	 *
//	 * \note O método já faz as inicializações necessárias antes de 
//	 * executar o algoritmo. Não esqueça de descomentar as linhas de código da busca 
//	 * em largura e da inserção de arestas para usar esse método.
//	 */
//	int edmondsKarp(int srcNode, int dstNode);
//
//	/*! \brief Retorna a aresta inversa.
//	 *
//	 * Método usado por algoritmos de fluxo. Retorna a aresta inversa de uma dada aresta.
//	 *
//	 * \param[in] arc Índice de uma aresta.
//	 * \return Índice da aresta inversa.
//	 */ 
//	inline int reverse(int arc);
};

//inline int Graph::reverse(int arc){
//	return (arc ^ 1);
//}

void Graph::initialize(int nNodes = 0){
	this->nNodes = nNodes;
	weights.clear();
	destinies.clear();
	// flows.clear();
	// capacities.clear();
	for(int i = 0; i < nNodes; i++)
		arcs[i].clear();
}

void Graph::insertArc(int srcNode, int dstNode, Weight weight = 0 /*, int capacity = 0 */ ){
	arcs[srcNode].push_back(destinies.size());
	weights.push_back(weight);
	destinies.push_back(dstNode);

	///////////////////////////////////
	// A parte abaixo é para fluxos. //
	///////////////////////////////////
	//
	// capacities.push_back(capacity);
	// flows.push_back(0);
	//
	// arcs[dstNode].push_back(destinies.size());
	// weights.push_back(weight);
	// capacities.push_back(0);
	// destinies.push_back(srcNode);
	// flows.push_back(0);
}

void Graph::print(){
	for(int i = 0; i < nNodes; i++){
		cout << i << " : ";
		for(int j = 0; j < arcs[i].size(); j++){
			if(capacities[arcs[i][j]] != 0)
				cout << '(' << destinies[arcs[i][j]] << ','/* << weights[arcs[i][j]] << ','*/ << capacities[arcs[i][j]] << ',' << flows[arcs[i][j]] << ") ";
		}
		cout << endl;
	}
}

void Graph::dfs(int srcNode, int visited[]){
	//////////////////////////////////////////////////////////////////
	// Funcionalidades extras:                                      //
	//                                                              //
	// 1: Retorna a ordem em que os nós foram visitados.            //
	// 2: Retorna o predecessor de cada nó.                         // 
	// 3: Arestas usadas pelos predecessores para chegarem aos nós. //
	// 4: Para a busca caso encontre o nó destino.                  //
	////////////////////////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////
	// Código de inicialização:                                     //
	// Nota: Não use esse código dentro desse método; faça a 		//
	// inicialização na main(), pois este é um método recurssivo.   //
	//                                                              //
	//	// 1: searchResult.clear();                                 //
	//	for(int i = 0; i < nNodes; i++){                            //
	//		visited[i] = 0;                                         //
	//		// 2: previousNodes[i] = -1;                            //
	//		// 3: usedArcs[i] = -1;                                 //
	//	}                                                           //
	//////////////////////////////////////////////////////////////////
		
	visited[srcNode] = 1;
	// 1: searchResult.push_back(srcNode);

	for(int i = 0; i < arcs[srcNode].size(); i++){
		int arc = arcs[srcNode][i];
		int neighbourNode = destinies[arc];

		bool isVisited( 0 != visited[neighbourNode] );
		if( !isVisited ){
			// 2: previousNodes[neighbourNode] = srcNode;
			// 3: usedArcs[neighbourNode] = arc;
			
			// Ajuste a lista de parâmetros passados para o método.
			dfs(neighbourNode, visited);
		}
	}
}

void Graph::bfs(int srcNode, int visited[]){
	//////////////////////////////////////////////////////////////////
	// Funcionalidades extras:                                      //
	//                                                              //
	// 1: Retorna a ordem em que os nós foram visitados.            //
	// 2: Retorna o predecessor de cada nó.                         // 
	// 3: Arestas usadas pelos predecessores para chegarem aos nós. //
	// 4: Para a busca caso encontre o nó destino.                  //
	// 5: Código usado por edmondsKarp.                  			//
	////////////////////////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////
	// Código de inicialização:                                     //
	//                                                              //
	//	// 1: searchResult.clear();                                 //
	//	for(int i = 0; i < nNodes; i++){                            //
	//		visited[i] = 0;                                         //
	//		// 2: previousNodes[i] = -1;                            //
	//		// 3: usedArcs[i] = -1;                                 //
	//	}                                                           //
	//////////////////////////////////////////////////////////////////
	
	visited[srcNode] = 1;
	queue<int> fila;

	fila.push(srcNode);
	while( !fila.empty() ){
		int currentNode = fila.front();
		fila.pop();
		// 1: searchResult.push_back(currentNode);

		for(int i = 0; i < arcs[currentNode].size(); i++){
			int arc = arcs[currentNode][i];
			int neighbourNode = destinies[arc];
			// 5: int residualCapacity = capacities[arc] - flows[arc];

			// 5: bool hasCapacity( residualCapacity > 0 );
			bool isVisited( 0 != visited[neighbourNode] );
			if( !isVisited ){	// 5: Adicione um "&& hasCapacity" nesse if.
				visited[neighbourNode] = 1;
				// 2: previousNodes[neighbourNode] = currentNode;
				// 3: usedArcs[neighbourNode] = arc;

				// 5: pathCapacities[neighbourNode] = min(pathCapacities[currentNode], residualCapacity);

				// 5: if(neighbourNode == dstNode)
				// 5: return pathCapacities[dstNode];
				fila.push(neighbourNode);
			}
		}
	}
}

void Graph::dijkstra(int srcNode, Weight minDistances[], int previousNodes[]){
	//////////////////////////////////////////////////////////////////
	// Funcionalidades extras:                                      //
	//                                                              //
	// 1: Arestas usadas pelos predecessores para chegarem aos nós. //
	// 2: Para a busca caso encontre o nó destino.                  //
	////////////////////////////////////////////////////////////////// 
	//////////////////////////////////////////////////////////////////
	// Código de inicialização:                                     //
	//                                                              //
	//	for(int i = 0; i < nNodes; i++)                             //
	//		// 1: usedArcs[i] = -1;                                 //
	//////////////////////////////////////////////////////////////////

	int visited[MAX_NODES];
	for(int i = 0; i < nNodes; i++){
		visited[i] = 0;
		minDistances[i] = INFINITY;
		previousNodes[i] = -1;
	}

	priority_queue<pair<Weight, int> > fila;
	fila.push(make_pair(minDistances[srcNode] = 0, srcNode));
	while( !fila.empty() ){
		int currentNode = fila.top().second;
		fila.pop();

		// 2: if(currentNode == dstNode)
		// 2:	return;

		bool isVisited( 0 != visited[currentNode] );
		if( isVisited )
			continue;
		visited[currentNode] = 1;

		for(int i = 0; i < arcs[currentNode].size(); i++){
			int arc = arcs[currentNode][i];
			int neighbourNode = destinies[arc];

			Weight newDistance = minDistances[currentNode] + weights[arc];
			if( newDistance < minDistances[neighbourNode] ){
				minDistances[neighbourNode] = newDistance;
				previousNodes[neighbourNode] = currentNode;
				// 1: usedArcs[neighbourNode] = arc;

				isVisited = ( 0 != visited[neighbourNode] );
				if( !isVisited )
					fila.push(make_pair( -minDistances[neighbourNode], neighbourNode));
			}
		}
	}
}

//int Graph::bellmanFord(int srcNode){		
//	for(int i = 0; i < nNodes; i++){
//		distances[i] = INFINITY;
//		previousNodes[i] = -1;
//	}
//	distances[srcNode] = 0;
//
//	// Relaxa as arestas (nNodes - 1) vezes.
//	for(int relaxCounter = 1; relaxCounter < nNodes; relaxCounter++){
//		bool canStop = true;			// Usada para ver se alguma aresta foi relaxada.
//		for(int i = 0; i < nNodes; i++){	// i faz o papel de "currentNode" aqui.
//			for(int j = 0; j < arcs[i].size(); j++){
//				int arc = arcs[i][j];
//				int dstNode = destinies[arc];
//				Weight newDistance = distances[i] + weights[arc];
//				if(newDistance < distances[dstNode]){
//					canStop = false;
//					distances[dstNode] = newDistance;
//					previousNodes[dstNode] = i;
//					usedArcs[dstNode] = arc;
//				}
//			}
//		}
//
//		if( canStop )				// Se nenhuma aresta foi relaxada, podemos parar.
//			return 0;
//	}
//
//	// Verifica se há ciclo negativo.
//	for(int i = 0; i < nNodes; i++){		// i faz o papel de "currentNode" aqui.
//		for(int j = 0; j < arcs[i].size(); j++){
//			int arc = arcs[i][j];
//			int dstNode = destinies[arc];
//			Weight newDistance = distances[i] + weights[arc];
//			if(newDistance < distances[dstNode])
//				return 1;
//		}
//	}
//
//	return 0;
//}
//
//int Graph::edmondsKarp(int srcNode, int dstNode){	
//	for(int i = 0; i < flows.size(); i++)
//		flows[i] = 0;
//
//	int maxFlow = 0;
//	while(1){
//		// Faz algumas inicializações e chama uma busca em
//		// largura para achar a capacidade mínima de um
//		// possível caminho.
//		for(int i = 0; i < nNodes; i++)
//			visited[i] = 0;
//		previousNodes[dstNode] = -1;
//		pathCapacities[srcNode] = INFINITY;
//		int minPathCapacity = bfs(srcNode, dstNode);
//
//		// Atualiza o fluxo máximo ou retorna.
//		if(0 == minPathCapacity)
//			return maxFlow;
//		maxFlow += minPathCapacity;
//
//		// Atualiza o fluxo nas arestas do caminho achado.
//		int j = dstNode;
//		while(j != srcNode){
//			flows[usedArcs[j]] += minPathCapacity;
//			flows[reverse(usedArcs[j])] -= minPathCapacity;
//
//			j = previousNodes[j];
//		}
//	}
//}

///////////////////////////////////////////
////// Alguns exemplos do uso da TAD //////
////// Não esqueça de ajustar        //////
////// MAX_NODES e INFINITY. 	     //////
///////////////////////////////////////////

// UVA 558 Wormholes - Rank 382 - Bellman-Ford 
/*
   int main(){
   Graph graph;
   int c, n, m, t;
   scanf("%d", &c);
   for(int i = 0; i < c; i++){
   scanf("%d%d", &n, &m);
   graph.initialize(n);
   for(int i = 0; i < m; i++){
   int x, y, t;
   scanf("%d%d%d", &x, &y, &t);
   graph.insertArc(x, y, t);
   }
   puts(graph.bellmanFord(0) == 0 ? "not possible" : "possible");
   }			
   return 0;
   }
   */

// UVA 820 Internet Bandwidth - Rank 93 - Max-flow
// Esse problema é foda, God pegou rank 6 xD.
// Pra rodar esse exemplo, tem que descomentar as linhas lah na busca
// em profundidade. Como o grafo desse problema não é direcionado, eu não
// descomentei as linhas da insertArc e ele passou no UVA, mas não sei se isso
// funciona sempre. Na dúvida, descomente lá; apesar de que isso vai fazer com que
// o grafo tenha o dobro de arestas.
//
// Para dígrafos, é preciso descomentar a insertArc.
/*
   int main(){
   Graph graph;
   int n, s, t, c, caso = 1;
   while(1){
   scanf("%d%d%d%d", &n, &s, &t, &c);
   if(n == 0) return 0;
   graph.initialize(n+1);
   for(int i = 0; i < c; i++){
   int src, dst, cap;
   scanf("%d%d%d", &src, &dst, &cap);
   graph.insertArc(src, dst, 0, cap);	// o 0 aqui eh do campo peso da aresta
   graph.insertArc(dst, src, 0, cap);
   }
//queue<int> f;
//graph.initializePreFlow(s, f);
printf("Network %d\nThe bandwidth is %d.\n\n", caso++, graph.edmondsKarp(s, t));
}
}
*/
