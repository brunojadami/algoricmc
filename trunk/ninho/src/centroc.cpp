#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>

#define ERR 1e-8

using namespace std;

/*
	Achando o centro do circulo dado 3 pontos, ver se os pontos nao sao 
	colineares usando a funcao colinea.. problema C da nacional N^4
*/

int N;
double x[101],y[101];
double dists[100][100];
pair<double, double> center[100][100][100];

bool colinea(int p, int q, int r)
{
	int res = (x[r]-x[q])*(y[p]-y[q])-(y[r]-y[q])*(x[p]-x[q]);
	return res == 0;
}

bool good(pair<double, double>& a, pair<double, double>& b)
{
	return a.first-b.first < ERR && a.first-b.first > -ERR && a.second-b.second < ERR && a.second-b.second > -ERR;
}

void findCenter(int i, int j, int k)
{
	double ma, mb;
	double cx, cy;
	int a, b, c; // retas ba, bc
	if (x[i] == x[j]) // testando o melhor ponto pra nao formar vertical
	{
		a = i;
		b = k;
		c = j;
	}
	else if (x[i] == x[k])
	{
		a = i;
		b = j;
		c = k;
	}
	else
	{
		a = j;
		b = i;
		c = k;
	}	
	ma = (y[b]-y[a])/(x[b]-x[a]);
	mb = (y[c]-y[b])/(x[c]-x[b]);
	cx = (ma*mb*(y[a]-y[c])+mb*(x[a]+x[b])-ma*(x[b]+x[c]))/(2*(mb-ma));
	if (ma > -ERR && ma < ERR)
		cy = -1/mb*(cx - (x[b]+x[c])/2) + (y[b]+y[c])/2;
	else
		cy = -1/ma*(cx - (x[a]+x[b])/2) + (y[a]+y[b])/2;
	
	center[i][j][k] = make_pair(cx, cy);
}

