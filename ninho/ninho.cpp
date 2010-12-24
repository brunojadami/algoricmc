#include <cstdio>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

/*=============================================================================*
/*========================= Topico: Numeros primos ============================*
/*=============================================================================*/

/* Funcao: Teste de primalidade.
   Descricao: Testa se um numero é primo ou nao.
   
   Complexidade: O(sqrt(n)).
   Entrada: 'n' é o numero a ser testado.
   Saida: 1 caso seja um numero primo, 0 caso contrario.
*/
int verificaSeEhPrimo(int n) 
{
	if (n == 2)
		return 1;
	if (n <= 1 || n % 2 == 0)
		return 0;
	int raiz = sqrt(n) + 1;
	for (int i = 3; i <= raiz; i+=2) // ideia da raiz
		if(n % i == 0)
			return 0;
	return 1;
}
/* Funcao: Teste de primalidade.
   Descricao: Precalculando primos atraves do crivo.
   
   Complexidade: O(nlog(n)).
   Entrada: 'n' é o numero ate onde quer se precalcular.
   Saida: Nenhuma, os numeros primos ficam marcados com 1 no vetor global ehprimo.
*/
#define MAX_PRIMOS 10000
char ehprimo[MAX_PRIMOS]; // todos comecam em 0
void calculaCrivo(int n) 
{
	int i, j;
	ehprimo[0] = ehprimo[1] = 0;
	ehprimo[2] = 1;
	for (i=3; i<=n; i++) // todos impares sao provaveis primos
		ehprimo[i] = i%2;
	for (i=3; i*i<=n; i+=2)
		if(ehprimo[i])
			for(j=i*i; j<=n; j+=i)
				ehprimo[j] = 0; // eh multiplo, entao nao eh primo
}
/* Funcao: Fatoracao em primos.
   Descricao: Fatora um numero em numeros primos.
   
   Complexidade: O(sqrt(n)).
   Entrada: 'x' é o numero a ser fatorado.
   Saida: Imprime usando printf todos os numeros primos que o fatoram.
*/
void fatoracaoEmPrimos(int x) 
{
	int i, c=x, raiz;
	while (c % 2 == 0) // divisivel por 2
	{
		printf("2 ");
		c /= 2;
	}
	i = 3;
	raiz = sqrt(c) + 2;
	while (i < raiz && c > 1) // ideia de testar ate a raiz
	{
		while (c % i == 0) 
		{
			printf("%d ", i);
			c /= i;
		}
		i += 2;
		raiz = sqrt(c) + 2;
	}
	if (c > 1) // se sobrar um ultimo fator
		printf("%d ", c);
}

/*=============================================================================*
/*================================ Topico: PD =================================*
/*=============================================================================*/

/* Funcao: Pegar a subsequencia de soma maxima.
   
   Complexidade: O(n).
   Entrada: 's' é a sequencia, 'n' é o numero de elementos.
   Saida: um int com a soma maxima, 'k' recebe o valor do comeco da 
   subsequencia, 'm' recebe o tamanho desta subsequencia.
   Atencao: A funcao vai retornar a subsequencia de valor maximo. Se tiver 2,
   ira retornar a com menor numero de elementos, se as 2 tiverem o mesmo numero
   de elementos, vai retornar a primeira. Para pegar a com maior numero de
   elementos, colocar ( i-j + 1 > m ) e ( max < 0 ). Para pegar a de soma minima
   colocar ( maxSum = INT_MAX ), ( max <= maxSum ) e ( max >= 0 ).
   Link: http://people.csail.mit.edu/bdean/6.046/dp/
*/
int maximumSum(int* s, int n, int& k, int& m) 
{
	int max = 0, maxSum = INT_MIN, j = 0;
	k = m = 0;
	for (int i = 0; i < n; ++i) 
	{
		max += s[i];
		if (max >= maxSum) // Se for a de soma maxima
		{
			if (max == maxSum) // Se for igual, ver qual que tem menos elementos
			{
				if (i-j + 1 < m)
				{
					k = j;
					m = i-j + 1;
				}
			}
			else // Senao essa eh a maior
			{
				k = j;
				m = i-j + 1;
			}
			maxSum = max;
		}
		if (max <= 0) // Se der 0 ja comecar outra subsequencia
		{
			j = i+1;
			max = 0;
		}
	}
	return maxSum;
}

/*=============================================================================*
/*======================== Topico: Probabilidades =============================*
/*=============================================================================*/

/* Funcao: Implementando a teoria de inclusao-exclusao, problema das garrafas quebradas topcoder.

   Entrada: N é o numero maximo da garrafa, left é onde comeca o intervalo e right onde termina, damage
   é o dano onde se deve checar se as garrafas sao divisiveis. O problema é simplesmente ver quantos
   divisores pelo damage tem no intervalo (left right). Mas com varios intervalos deve se usar o principio
   da inclusao e exclusao ( AUB = A + B - (A /\ B) ) para varios conjuntos (arremessos).
   Principio: fazer de 1 a n (n =  numero de conjuntos)
   1 - somar todos conjuntos individualmente
   2 - subtrair interseccao dos conjuntos 2 a 2
   3 - somar todas interseccoes dos conjuntos 3 a 3
   n - se impar somar, se par sub, todas interseccoes dos conjuntos n a n
   Link: http://www.topcoder.com/stat?c=problem_statement&pm=11008&rd=14244
*/
int getNumBroken(int N, vector <int> left, vector <int> right, vector <int> damage) 
{
	int res = 0, m = (1 << left.size()); // mascara pra testar todas as possibilidades de interseccao
	for (int i = 1; i < m; ++i)
	{
		long long maxLeft = -1, minRight = INT_MAX, lcm = 1, g; // divisores de a e b eh o mesmo de q mmc(a,b)
		int sign = -1; // se o numero de 1's for par, subtrair, senao somar
		for (int j = 0; j < (int)left.size(); ++j)
		{
			if (((i >> j) & 1) == 0) // se for 1, ideia da mascara, pra fazer todas as combinacoes
				continue;
			sign = -sign; // numero de 1's somou um, entao inverter sign
			maxLeft = max(maxLeft, (long long)left[j]); // pegando o intervalo de interseccao
			minRight = min(minRight, (long long)right[j]); // usando long long porque pode storar o lcm (mmc)
			g = gcd(lcm, damage[j]); // calculando o minimo multiplo comum dos damages da interseccao
			lcm = (lcm*damage[j])/g;
			if (lcm > N) // N eh o maximo numero da garrafa
				break;
		} 
		if (lcm > N || minRight < maxLeft) // se nao tem interseccao, ou se lcm passa do numero de garrafas
			continue;
		res += sign*(minRight/lcm - (maxLeft-1)/lcm); // soma/sub o numero de divisores, de 0 ate right - de 0 ate left
	}
	return res;
}




/* Funcao main */
int main()
{
	fatoracaoEmPrimos(1000); printf("\n");
	fatoracaoEmPrimos(1234); printf("\n");
	fatoracaoEmPrimos(1414); printf("\n");
	fatoracaoEmPrimos(17); printf("\n");
	return 0;
}

