#include<queue>
#include<vector>
#include<algorithm>
#include<utility>
#include<string.h>
#include<stdio.h>
using namespace std;

struct Edge{
	int dst, weight, cap, flow;

	Edge(){};
	Edge(int d, int w, int c = 0, int f = 0)
		: dst(d), weight(w), cap(c), flow(c) {};

	bool operator<(const Edge &other) const{
		return dst < other.weight;
	};
};

const int MAX_NODES = 2010;
const int INF = 1000000;

#define foreach(V) for(vector<Edge>::iterator e = (V).begin(); e != (V).end(); e++)

struct Graph{
	vector<Edge> adj[MAX_NODES];
	int nNodes;

	void init(int n){ 
		for(int i = 0; i < n; i++) 
			adj[i].clear();
		nNodes = n;
   	};

	void addEdge(int src, Edge e){ adj[src].push_back(e); };
	
	// DFS that colors the graph. Colors are not overridden. 0 means no color.
	void dfs(int src, int color, int visited[]){
		visited[src] = color;
		foreach(adj[src])
			if(!visited[e->dst])
				dfs(e->dst, color, visited);
	};

	void dijkstra(int src, /* int dst, */ int dist[], int previous[]){
		priority_queue<pair<int, int> > fila;
		for(int i = 0; i < nNodes; i++){
			dist[i] = INF;
			previous[i] = -1;
		}
		dist[src] = 0;
		fila.push(make_pair(0, src));

		while(!fila.empty()){
			int current = fila.top().second;
			fila.pop();
			if(/* current == dst || */ dist[current] == INF) return;
			if(previous[current] != -1) continue; // Already processed.

			foreach(adj[current]){
				int tmp = dist[current] + e->weight;
				if(tmp < dist[e->dst]){
					dist[e->dst] = tmp;
					previous[e->dst] = current;
					fila.push(make_pair(-dist[e->dst], e->dst));
				}
			}
		}
	};

	// Returns true if the graph contains a negative cycle.
	bool bellmanFord(int src, int dist[], int previous[]){
		for(int i = 0; i < nNodes; i++){
			dist[i] = INF;
			previous[i] = -1;
		}
		dist[src] = 0;

		for(int k = 1; k <= nNodes; k++){
			for(int i = 0; i < nNodes; i++)
				foreach(adj[i]){
					int tmp = dist[i] + e->weight;
					if(tmp < dist[e->dst]){
						if(k == nNodes) 	// Negative cycle detected.
							return true;
						dist[e->dst] = tmp;
						previous[e->dst] = i;
					}
				}
		}
		return false;
	};
};
