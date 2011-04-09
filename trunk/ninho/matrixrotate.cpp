#include <cstdio>

int n = 5;
int m[5][5];

void ahorario(int &a, int &b, int &c, int &d)
{
	int temp = d; d = c; c = b; b = a; a = temp;
}

void horario(int &a, int &b, int &c, int &d)
{
	int temp = a; a = b; b = c; c = d; d = temp;
}

void rotacionar()
{
	for(int i=0; i<n/2; i++)
		for(int j=0; j<(n+1)/2; j++)
			horario(m[i][j], m[n-1-j][i], m[n-1-i][n-1-j], m[j][n-1-i]);
}

int main()
{
	int c = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			m[i][j] = c++;
			
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			printf("%d ", m[i][j]);
		printf("\n");
	}
	
	rotacionar();
	printf("\n");
	
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			printf("%d ", m[i][j]);
		printf("\n");
	}
	return 0;
}
