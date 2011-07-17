#include <cstdio>
#include <algorithm>
using namespace std;

#define LL long long
int p[100001], prof[100001], cost[100001]; // p eh o pai, prof eh a profundidade, cost eh o custo

/*
 	Problema A da nacional 2010.
 	LCA simplinho bateu valeu..
*/

LL LCA(int a, int b) 
{
	LL cont = 0;
	int pa = prof[a];
	int pb = prof[b];
	if (pa < pb) 
	{
		swap(a, b);
		swap(pa, pb);
	}
	while (pa != pb) 
	{
		cont += (LL)(cost[a]);
		a = p[a];
		pb++;
	}
	while (a != b) 
	{
		cont += (LL)(cost[b]);
		cont += (LL)(cost[a]);
		a = p[a];
		b = p[b];
	}
    	return cont;
}

int main() 
{
	int n, q, a, b;
	
	while (1)
	{
		p[0] = cost[0] = prof[0] = 0;
		scanf("%d", &n);
		if (!n)
			break;
		for (int i=1; i<n ;i++) 
		{
			scanf("%d %d", &a, &b);
			p[i] = a;
			cost[i] = b;
			prof[i] = prof[a]+1;
		}
		scanf("%d", &q);
		for(int i=0; i<q ;i++) 
		{
			if (i) printf(" ");
			scanf("%d %d", &a, &b);
			printf("%lld", LCA(a, b));
		}
		printf("\n");
	}
	
	return 0;
}

