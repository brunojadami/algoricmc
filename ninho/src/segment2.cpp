#include <cstdio>
#include <iostream>
#include <map>

using namespace std;

#define NN (1<<17) // menor potencia de 2 maior que o dobro da quantidade de elementos
int v[NN]; // seg1 guarda a soma do intervalo, seg2 eh o menor valor do vetor acumulado
int seg1[NN], seg2[NN], NN2, N; // do intervalo, eh especifico pra este problema dos parenteses

void segupdate(int x, int val) { // atualiza a posicao x com val
	v[x] = val;
	x += NN2;
	seg1[x] = val; // soma
	seg2[x] = val;
	while (x/2 > 0) {
		x /= 2;
		seg1[x] = seg1[2*x]+seg1[2*x+1]; // soma, do mesmo jeito vc consegue fazer o min do intervalo
		seg2[x] = min(seg2[2*x], seg1[2*x]+seg2[2*x+1]);
	}
}

void init(int n) { // inicia a arvore
	NN2 = (1<<(32-__builtin_clz(n-1))) - 1; // tamanho da arvore sem contar as folhas
	N = NN2*2+2; // tamanho da arvore + 1      (arredondando pra proxima potencia de 2!)
	for (int i = n+1; i < N; i++) v[i] = 0; // resto da arvore iniciar com nulo
	
	for (int i = NN2+1; i < N; i++)
		seg1[i] = v[i-NN2], seg2[i] = v[i-NN2]; // folhas
	for (int i = NN2; i > 0; i--) 
		seg1[i] = seg1[2*i]+seg1[2*i+1], seg2[i] = min(seg2[2*i], seg1[2*i]+seg2[2*i+1]); // intervalos
}

int segquery(int i, int j) {
	int res = 0; // res eh a soma
	i += NN2; j += NN2;
	while (i <= j) { // nunca vai contar 2x
		if (i & 1) res += seg1[i]; // so quando subir a direita
		if (!(j & 1)) res += seg1[j]; // so quando subir a esquerda
		i = (i+1)/2;
		j = (j-1)/2;
	}
	return res; // retorna a soma
}

int main()
{
	int n, t, k;
	for (int q = 1; q <= 10; ++q)
	{
		printf("Test %d:\n", q);
		scanf(" %d ", &n);
		
		for (int i = 1; i <= n; ++i)
		{
			char c;
			scanf(" %c ", &c);
			v[i] = c == '(' ? 1 : -1;
		}

		init(n);
		scanf(" %d ", &t);
		
		while (t--)
		{
			scanf(" %d ", &k);
			if (k == 0)
			{
				if (segquery(1, n) == 0 && seg2[1] >= 0) printf("YES\n");
				else printf("NO\n");
			}
			else segupdate(k, v[k] == 1 ? -1 : 1);
		}
	}
	
	return 0;
}

