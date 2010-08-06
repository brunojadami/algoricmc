#include<string>
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
#include<utility>
#include<queue>
#include<algorithm>			// Possui a função min.
using namespace std;

const int MAX_NODES = 10000;		/*!<Numero máximo de nós que o Graph pode comportar. NOTA: Pode estourar a memoria estática. */
const int INFINITY = 100000;	/*!<Valor de infinito, usado por Dijkstra e outros algoritmos. */
typedef int Weight;

struct Graph{
	vector<int> destinies;		/*!<Nós de destino de uma dada aresta. */
	vector<int> flows;		/*!<Fluxo em cada aresta. */
        vector<int> capacities;		/*!<Capacidade de cada aresta. */
        int pathCapacities[MAX_NODES];	/*!<Usado para achar a capacidade dos caminhos na busca em largura de fluxos. */
	vector<int> arcs[MAX_NODES];	/*!<Arestas de cada nó. Armazena o índice de cada aresta. */
	int nNodes;			/*!<Número de vertices no Graph. Esse numero dever ser menor ou igual a MAX_NODES. */
	int visited[MAX_NODES];		/*!<Nós visitados. 1 indica que o nó foi visitado, e 0 indica que não foi, nos métodos que o utilizam. */
	int distances[MAX_NODES];	/*!<Distância até cada nó. Usado por Dijkstra e Bellman-Ford. */
	vector<Weight> weights;		/*!<Peso de cada aresta. */
	vector<int> searchResult;	/*!<Armazena o resultado de uma busca. */
	int previousNodes[MAX_NODES];	/*!<Predecessores de cada nó. Usado pelas buscas e pelo dijkstra. */
	int usedArcs[MAX_NODES];	/*!<Aresta usada para chegar aos nós em uma busca. Verifique previousNode antes de ler um valor daqui.*/

	/*! \brief Inicializador do Grafo.
	 *
	 * Limpa o grafo inteiro e cria um grafo com nNodes nós.
	 *
	 * \param[in] nNodes Numero de vertices que o Graph tem. Deve ser menor ou igual a MAX_NODES. Default 0.
	 */ 
	void initialize(int nNodes);

	/*! \brief Insere uma aresta no grafo.
	 *
	 * \param[in] srcNode Vértice origem.
	 * \param[in] dstNode Vértice destino.
	 * \param[in] weight Weight da aresta. Default 0.
	 * \param[in] capacity Capacidade da aresta. Default 0.
	 *
	 * \note Para usar os algoritmos de fluxo, é necessário descomentar uma parte 
	 * do código desse método. A parte está indicada em seu código. Isso faz com que o grafo insira 
	 * a aresta desejada e, além dela, uma aresta inversa, usada internamente pelos algoritmos de
	 * fluxo, para que o fluxo "possa ser mandado de volta". Essa aresta tem capacidade 0. Para problemas
	 * onde o grafo NÃO é direcionado, não é preciso descomentar o código (só testei isso em alguns programas,
	 * mas eles passaram).
	 */ 
	void insertArc(int srcNode, int dstNode, Weight weight, int capacity);

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
	 * \param[out] searchResult Ordem em que os nós são visitados pela primeira vez. Não é inicializado internamente.
	 * \param[out] previousNodes Predecessor de cada nó. Não é inicializado internamente.
	 * \param[out] usedArcs Arestas usada pelo predecessor de cada nó para chegar nele. Não é inicializado internamente.
	 * \param[out] visited Nós que foram visitados por essa busca. Não é inicializado internamente.
	 */
	void dfs(int srcNode);

	/*! \brief Busca em largura.
	 *
	 * Veja os comentários da busca em profundidade. Os mesmos se aplicam aqui.
	 * Também implementa algumas funcionalidades usadas por edmondsKarp. Elas 
	 * estão comentadas no código.
	 *
	 * \param[in] dstNode Nó destino. Default -1 (nenhum nó destino, visita todos os nós).
	 *
	 * \return Usado apenas pelo edmondsKarp. Retorna o valor da menor capacidade do caminho achado.
	 *
	 * \note Não inicializa "visited", "previousNodes", "usedArcs" e nem "searchResult" internamente.
	 * edmondsKarp faz as inicializações necessárias antes de chamar este método.
	 */ 
	int bfs(int srcNode, int dstNode);

	/*! \brief Algoritmo de Dijkstra.
	 *
	 * Se ("dstNode" == -1), então o algoritmo para após ter calculado a distância 
	 * mínima do nó origem para cada nó; caso contrário, o algoritmo retorna assim que achar a
	 * distância mínima até o nó destino. 
	 *
	 * \param[in] srcNode Nó origem.
	 * \param[in] dstNode Nó destino. Default -1.
	 *
	 * \param[out] previousNodes Predecessor de cada nó. -1 indica que não existe predecessor.
	 * \param[out] usedArcs Arestas usada pelo predecessor de cada nó para chegar nele.
	 * \param[out] visited Nós visitados. Não é inicializado internamente.
	 * \param[out] distances Distância total até cada nó, partindo-se de srcNode.
	 *
	 * \note Inicializa "previousNodes" e "distances" internamente antes de executar o algoritmo.
	 */ 
	void dijkstra(int srcNode, int dstNode);

	/*! \brief Bellman-Ford.
	 *
	 * Acha a menor distância até cada nó. Funciona em grafos com
	 * arestas cujos pesos são negativos.
	 *
	 * \param[in] srcNode Nó origem.
	 *
	 * \param[out] previousNodes Predecessor de cada nó.
	 * \param[out] usedArcs Arestas usada pelo predecessor de cada nó para chegar nele.
	 * \param[out] distances Distância até cada nó.
	 *
	 * \return 1 se existe pelo menos um ciclo negativo no grafo, 0 caso contrário.
	 *
	 * \note Inicializa "previousNodes" e "distances" antes de executar.
	 */  
	int bellmanFord(int srcNode);

	/*! \brief Algoritmo de fluxo máximo de Edmonds-Karp.
	 *
	 * Acha o fluxo máximo no grafo. Para isso, realiza várias buscas em largura
	 * para encontrar caminhos que adicionam fluxo.
	 *
	 * \param[in] srcNode Nó origem.
	 * \param[in] dstNode Nó final.
	 *
	 * \param[out] flows Fluxo passando em cada aresta.
	 * \param[out] visited Determina o Min-Cut.
	 * \param[out] previousNodes É usada pela busca em largura.
	 * \prama[out] usedArcs É usada pela busca em largura.
	 *
	 * \return Valor do fluxo máximo no grafo.
	 *
	 * \note O método já faz as inicializações necessárias antes de 
	 * executar o algoritmo. Não esqueça de descomentar as linhas de código da busca 
	 * em largura e da inserção de arestas para usar esse método.
	 */
	int edmondsKarp(int srcNode, int dstNode);

	/*! \brief Retorna a aresta inversa.
	 *
	 * Método usado por algoritmos de fluxo. Retorna a aresta inversa de uma dada aresta.
	 *
	 * \param[in] arc Índice de uma aresta.
	 * \return Índice da aresta inversa.
	 */ 
	inline int reverse(int arc);



	int excess[MAX_NODES];
	int heights[MAX_NODES];
	void push(int srcNode, int dstNode, int arc);
	inline void relabel(int srcNode, int dstNode);
	void initializePreFlow(int srcNode, queue<int>& excessList);
	int pushRelabel(int srcNode, int dstNode);
};

void Graph::push(int srcNode, int dstNode, int arc){
	int pushedFlow = min(excess[srcNode], capacities[arc] - flows[arc]);
	flows[arc] += pushedFlow;
	flows[reverse(arc)] -= pushedFlow;
	excess[srcNode] -= pushedFlow;
	excess[dstNode] += pushedFlow;
}

inline void Graph::relabel(int srcNode, int dstNode){
	heights[srcNode] = 1 + heights[dstNode];
}

void Graph::initializePreFlow(int srcNode, queue<int>& excessList){
	// Inicializa o pre-flow.
	for(int i = 0; i < nNodes; i++){
		heights[i] = 0;
		excess[i] = 0;
	}
	for(int i = 0; i < flows.size(); i++)
		flows[i] = 0;
	heights[srcNode] = nNodes;
	for(int i = 0; i < arcs[srcNode].size(); i++){
		int arc = arcs[srcNode][i];
		int neighbourNode = destinies[arc];
		flows[arc] += capacities[arc];
		flows[reverse(arc)] -= capacities[arc];
		excess[neighbourNode] += capacities[arc];
		excess[srcNode] -= capacities[arc];

		excessList.push(neighbourNode);
	}
}

int Graph::pushRelabel(int srcNode, int dstNode){
	pair<int, pair<int, int> > p;
	vector<pair<int, pair<int, int> > > relabelList;

	queue<int> excessList;
	initializePreFlow(srcNode, excessList);
	while( !excessList.empty() ){
		int currentNode = excessList.front();
		excessList.pop();

		bool hasExcess( 0 < excess[currentNode] );
		if( !hasExcess )
			continue;

//		print();
//		for(int i = 0; i < nNodes; i++)
//			cout << i << '\t' << excess[i] << '\t' << heights[i] << endl;
		relabelList.clear();
		for(int i = 0; i < arcs[currentNode].size() && hasExcess; i++){
			int arc = arcs[currentNode][i];
			int neighbourNode = destinies[arc];

			bool canPush( heights[currentNode] == heights[neighbourNode] + 1 );
			bool hasCapacity( 0 < capacities[arc] - flows[arc] );
			if( hasCapacity ){
				if( canPush ){
					push(currentNode, neighbourNode, arc);
					excessList.push(neighbourNode);
				}
				else{
					p.first = heights[neighbourNode];
					p.second.first = neighbourNode;
					p.second.second = arc;

					relabelList.push_back(p);
				}
			}
			hasExcess = ( 0 < excess[currentNode] );
		}
		bool canRelabel( currentNode != srcNode && currentNode != dstNode );
		if( hasExcess && canRelabel ){
			sort(relabelList.begin(), relabelList.end());
			for(int i = 0; i < relabelList.size() && hasExcess; i++){
				relabel(currentNode, relabelList[i].second.first);
				push(currentNode, relabelList[i].second.first, relabelList[i].second.second);
				excessList.push(relabelList[i].second.first);
				hasExcess = ( 0 < excess[currentNode] );
			}
		}
		if( hasExcess && currentNode != dstNode )
			excessList.push(currentNode);
	}
	return excess[dstNode];
}


inline int Graph::reverse(int arc){
	return (arc ^ 1);
}

void Graph::initialize(int nNodes = 0){
	this->nNodes = nNodes;
	weights.clear();
	flows.clear();
	destinies.clear();
	capacities.clear();
	for(int i = 0; i < nNodes; i++)
		arcs[i].clear();
}

void Graph::insertArc(int srcNode, int dstNode, Weight weight = 0, int capacity = 0){
	arcs[srcNode].push_back(destinies.size());
	weights.push_back(weight);
	capacities.push_back(capacity);
	destinies.push_back(dstNode);
	flows.push_back(0);

	// A parte abaixo é para fluxos.
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

void Graph::dfs(int srcNode){
	visited[srcNode] = 1;
	searchResult.push_back(srcNode);

	for(int i = 0; i < arcs[srcNode].size(); i++){
		int arc = arcs[srcNode][i];
	        int neighbourNode = destinies[arc];

		bool isVisited( 0 != visited[neighbourNode] );
		if( !isVisited ){
			previousNodes[neighbourNode] = srcNode;
			usedArcs[neighbourNode] = arc;
			dfs(neighbourNode);
		}
	}
}

int Graph::bfs(int srcNode, int dstNode = -1){
	visited[srcNode] = 1;

	queue<int> fila;
	fila.push(srcNode);
	while( !fila.empty() ){
		int currentNode = fila.front();
		fila.pop();
		searchResult.push_back(currentNode);
		for(int i = 0; i < arcs[currentNode].size(); i++){
			int arc = arcs[currentNode][i];
			int neighbourNode = destinies[arc];
			// int residualCapacity = capacities[arc] - flows[arc];

			// bool hasCapacity( residualCapacity > 0 );
			bool isVisited( 0 != visited[neighbourNode] );
			if( !isVisited ){	// Adicione um "&& hasCapacity" nesse if.
				visited[neighbourNode] = 1;
				previousNodes[neighbourNode] = currentNode;
				usedArcs[neighbourNode] = arc;

				// pathCapacities[neighbourNode] = min(pathCapacities[currentNode], residualCapacity);
				
			       	if(neighbourNode == dstNode)
					return pathCapacities[dstNode];
				fila.push(neighbourNode);
			}
		}
	}
	return 0;
}

void Graph::dijkstra(int srcNode, int dstNode = -1){
	for(int i = 0; i < nNodes; i++){
		distances[i] = INFINITY;
		previousNodes[i] = -1;
	}

	priority_queue<pair<Weight, int> > fila;
	fila.push(make_pair(distances[srcNode] = 0, srcNode));
	while( !fila.empty() ){
		int currentNode = fila.top().second;
		fila.pop();

		if(currentNode == dstNode)
			return;

		bool isVisited( 0 != visited[currentNode] );
		if( isVisited )
			continue;
		visited[currentNode] = 1;

		for(int i = 0; i < arcs[currentNode].size(); i++){
			int arc = arcs[currentNode][i];
		       	int neighbourNode = destinies[arc];

			Weight newDistance = distances[currentNode] + weights[arc];
			if( newDistance < distances[neighbourNode] ){
				distances[neighbourNode] = newDistance;
				previousNodes[neighbourNode] = currentNode;
				usedArcs[neighbourNode] = arc;

				isVisited = ( 0 != visited[neighbourNode] );
				if( !isVisited )
					fila.push(make_pair( -distances[neighbourNode], neighbourNode));
			}
		}
	}
}

int Graph::bellmanFord(int srcNode){		
	for(int i = 0; i < nNodes; i++){
		distances[i] = INFINITY;
		previousNodes[i] = -1;
	}
	distances[srcNode] = 0;

	// Relaxa as arestas (nNodes - 1) vezes.
	for(int relaxCounter = 1; relaxCounter < nNodes; relaxCounter++){
		bool canStop = true;			// Usada para ver se alguma aresta foi relaxada.
		for(int i = 0; i < nNodes; i++){	// i faz o papel de "currentNode" aqui.
			for(int j = 0; j < arcs[i].size(); j++){
				int arc = arcs[i][j];
				int dstNode = destinies[arc];
				Weight newDistance = distances[i] + weights[arc];
				if(newDistance < distances[dstNode]){
					canStop = false;
					distances[dstNode] = newDistance;
					previousNodes[dstNode] = i;
					usedArcs[dstNode] = arc;
				}
			}
		}

		if( canStop )				// Se nenhuma aresta foi relaxada, podemos parar.
			return 0;
	}

	// Verifica se há ciclo negativo.
	for(int i = 0; i < nNodes; i++){		// i faz o papel de "currentNode" aqui.
		for(int j = 0; j < arcs[i].size(); j++){
			int arc = arcs[i][j];
			int dstNode = destinies[arc];
			Weight newDistance = distances[i] + weights[arc];
			if(newDistance < distances[dstNode])
				return 1;
		}
	}

	return 0;
}

int Graph::edmondsKarp(int srcNode, int dstNode){	
	for(int i = 0; i < flows.size(); i++)
		flows[i] = 0;

	int maxFlow = 0;
	while(1){
		// Faz algumas inicializações e chama uma busca em
		// largura para achar a capacidade mínima de um
		// possível caminho.
		for(int i = 0; i < nNodes; i++)
			visited[i] = 0;
		previousNodes[dstNode] = -1;
		pathCapacities[srcNode] = INFINITY;
		int minPathCapacity = bfs(srcNode, dstNode);

		// Atualiza o fluxo máximo ou retorna.
		if(0 == minPathCapacity)
			return maxFlow;
		maxFlow += minPathCapacity;

		// Atualiza o fluxo nas arestas do caminho achado.
		int j = dstNode;
		while(j != srcNode){
			flows[usedArcs[j]] += minPathCapacity;
			flows[reverse(usedArcs[j])] -= minPathCapacity;

			j = previousNodes[j];
		}
	}
}

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
		printf("Network %d\nThe bandwidth is %d.\n\n", caso++, graph.pushRelabel(s, t));
	}
}

