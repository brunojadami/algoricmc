/*
	*** Euclidiano extendido, tambem para resolver equacoes diophantinas lineares ***
	
	a*x + b*y = c
	
	- se c = gcd(a, b) usar o euclidiano extendido
	- se gcd(a, b) nao divide c nao ha resposta
	- se gcd(a, b) divide c ha resposta: 
		eh so usar o euclidiano extendido e mutiplicar a resposta (x, y) por c/gcd(a, b)
	- se a ou b forem negativos, fazer com o abs deles e multiplicar a
		respectiva resposta por -1 (x se a for negativo e y se b for negativo)
	- vai achar a solucao que minimiza |x|+|y| primeiro e x <= y segundo, para solucao geral:
	
		x = x0 + b*t/g                   t eh inteiro!!
		y = y0 - a*t/g
*/

#define LL long long

// modulo pra qualquer numero (positivo ou negativo).. as funcoes abaixo so utilizam numeros positivos
int mod(int a, int m)
{
	return (a%m+m)%m;
}

// normal gcd, a e b positivos
LL gcd(LL a, LL b)
{
	if (!b) return a;
	return gcd(b, a%b);
}

// extended euclidean, a e b positivos
void gcdEx(LL a, LL b, LL& x, LL& y, LL& g)
{
	if (!b) { x = 1; y = 0; g = a; return; }
    	gcdEx(b, a%b, x, y, g);
    	LL x1 = y;
    	LL y1 = x-(a/b)*y;
    	x = x1;
    	y = y1;
}

