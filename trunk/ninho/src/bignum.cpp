#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MOD 10000000000000000LL // base (10^4), nao colocar muito grande por causa da divisao
#define DIGS "16" // o numero de digitos decimais da base (MOD)
#define TAM 3 // o numero deve ter no max (4*TAM) digitos

struct Big // bignum pra numeros positivos!
{
	unsigned long long bn[TAM];
	int nb;
	
	void imprime() {
		int i = nb - 1;
	    	printf("%llu", bn[i--]);
	   	for (; i >= 0; i--)
			printf("%0"DIGS"llu", bn[i]);
		printf("\n");
	}
	
	void strto(const char *s) { // cuidado com os barra n e r
		int i = 0, b = 1, n = strlen(s)-1, j = 0;
		nb = 1;
		memset(bn, 0, sizeof bn);
		for (; j <= n && s[j] == '0'; ++j); // tirar os leadings 0
		for (; n >= j; n--) {
			bn[i] += b*(s[n]-'0');
			b *= 10;
			if (b == MOD && n > 0) { b = 1; i++; }
		}
		nb = i+1;
	}
	
	void soma(Big& b, Big& c) {
		long long unsigned acc = 0;
		memset(c.bn, 0, sizeof c.bn);
		c.nb = max(nb, b.nb);
		for (int i = 0; i < c.nb; i++) {
			c.bn[i] = bn[i] + b.bn[i] + acc;
			acc = c.bn[i]/MOD;
			c.bn[i] %= MOD;
		}
		if (acc > 0) c.bn[c.nb++] = acc;
	}
	
	void mult(Big& b, Big& c) {
		unsigned long long i, j, acc;
		memset(c.bn, 0, sizeof c.bn);
		for (i = 0; i < nb; i++) {
			for (j = 0, acc = 0; j < b.nb; j++) {
				c.bn[i+j] += acc + (bn[i]*b.bn[j]);
				acc = c.bn[i+j] / MOD;
				c.bn[i+j] %= MOD;
			}
			if (acc) c.bn[i+j] += acc;
		}

		if (nb == 1 && bn[0] == 0 || b.nb == 1 && b.bn[0] == 0)
			c.nb = 2; // se o resultado der 0 vai ter 1 nb, colocar 2 pq ali em baixo vai fazer 2-1=1
		else
			c.nb = nb+b.nb;
		c.nb = (c.bn[c.nb-1]) ? c.nb : (c.nb-1);
	}
	
	void sub(Big& b, Big& c) // this maior q b!
	{
		int i, cc, nbc;
    		long long unsigned acc = 0;
		for (i = 0; i < nb; i++) {
                	if (bn[i] < (b.bn[i] + acc)) {
                		c.bn[i] = MOD + bn[i] - b.bn[i] - acc;
                    		acc = 1;
                		} else {
					c.bn[i] = bn[i] - b.bn[i] - acc;
					acc = 0;
				}
            	}
            	for (c.nb = nb; c.bn[c.nb-1] == 0; c.nb--) ;
	}
};

