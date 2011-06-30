#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define INF -100000

struct Node
{
	int a, b;
	int com, mei, ter, res;
};

Node nodes[300000]; // ~2*2^(log2(MAX)+1)
int nums[50000]; // MAX de 50000

Node makeinf()
{
	Node node;
	node.com = INF;
	node.mei = INF;
	node.ter = INF;
	node.res = INF;
	return node;
}

void init(int p, int a) // intervalos de 1, proprio valor
{
	nodes[p].a = a;
	nodes[p].b = a;
	nodes[p].com = nums[a];
	nodes[p].mei = nums[a];
	nodes[p].ter = nums[a];
	nodes[p].res = nums[a];
}

void update(int a, int b, int p)
{
	nodes[p].a = a;
	nodes[p].b = b;
	nodes[p].com = max(nodes[p*2].com, nodes[p*2].mei+nodes[p*2+1].com); // comeca
	nodes[p].mei = nodes[p*2].mei+nodes[p*2+1].mei; // meio
	nodes[p].ter = max(nodes[p*2+1].ter, nodes[p*2+1].mei+nodes[p*2].ter); // termina
	nodes[p].res = max(nodes[p*2].ter+nodes[p*2+1].com, max(nodes[p*2].res, nodes[p*2+1].res)); // resposta
}

void build(int a, int b, int p) // construir
{
	if (a == b)
	{
		init(p, a);
		return;
	}
	build(a, (a+b)/2, p*2);
	build((a+b)/2+1, b, p*2+1);
	update(a, b, p);
}

void changed(int a, int b, int p, int c) // c eh a posicao atualizada
{
	if (a == b) // pode cair um aqui q nao seja c, mas vai ser folha msm..
	{
		init(p, a);
		return;
	}
	if (c <= (a+b)/2 && c >= a) // esta a esquerda
		changed(a, (a+b)/2, p*2, c);
	else if (c <= b && c >= (a+b)/2+1) // esta a direita
		changed((a+b)/2+1, b, p*2+1, c);
	else // nao afeta esse intervalo
		return;
	update(a, b, p);
}

Node query(int a, int b, int p) // busca, intervalo [a,b], o intervalo dos nos estao nos proprios nos
{
	if (b < nodes[p].a || a > nodes[p].b) // sem interseccao com intervalo buscado
	{
		return makeinf();
	}
	if (b >= nodes[p].b && a <= nodes[p].a) // no intervalo buscado
	{
		return nodes[p];
	}
	Node esq = query(a, b, p*2);
	Node dir = query(a, b, p*2+1);
	Node res;
	// sempre testar com infinito aqui caso nao tenha certeza de qual vai ser o menor valor
	if (esq.res == INF)
		return dir;
	if (dir.res == INF)
		return esq;
	// mesmo da inicializacao, prestar atencao nos valores de infinito..
	res.com = max(esq.com, esq.mei+dir.com);
	res.mei = esq.mei+dir.mei;
	res.ter = max(dir.ter, esq.ter+dir.mei);
	res.res = max(esq.ter+dir.com, max(esq.res, dir.res));
	return res;
}

/* CASOS DE ENTRADA EXEMPLO: SPOJ GSS3
	4
	1 2 3 4
	7
	1 1 4
	1 1 3
	0 3 -3
	1 2 4
	1 3 3
	1 1 3
	1 1 4
*/

int main()
{
	int n, m;
	 
	while (scanf("%d", &n) != EOF)
	{
		for (int i = 0; i < n; ++i)
			scanf("%d", &nums[i]);
		build(0, n-1, 1);
		scanf("%d", &m);
		for (int i = 0; i < m; ++i)
		{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			--b; // --b e --c por causa q ta comecando com 1 as posicoes
			if (a == 0) // changed
			{
				nums[b] = c;
				changed(0, n-1, 1, b);
			}
			else // query
			{
				--c;
				Node node = query(b, c, 1);
				printf("%d\n", node.res);
			}
		}
	}
	
	return 0;
}

