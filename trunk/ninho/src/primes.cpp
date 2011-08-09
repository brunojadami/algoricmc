#include<cstdio>
#include<algorithm>
#include<vector>
#include<iostream>
#include<cstring>
#include<math.h>
using namespace std;

const int SIZE = 10000000 + 1;
const int LIM = sqrt(SIZE) + 1;

struct Crivo{
	int composite[(SIZE >> 5) + 1];
	int factored[(SIZE >> 5) + 1];

	int primeFactor[SIZE];                  // Usado para fatoração.
	vector<pair<int, int> > factors[SIZE];  // Usado para fatoração.
	vector<int> primes;						// Para guardar os primos

	Crivo();
	void generate();
	void fatora(int);
	void printFactors(int);

	inline int bit_check(int arr[], int n){ return arr[n >> 5] & (1 << (n & 31)); };
	inline void bit_set(int arr[], int n){ arr[n >> 5] |= (1 << (n & 31)); };

	inline int isPrime(int n){ return !bit_check(composite, n); };
	inline int isFactored(int n){ return bit_check(factored, n); };
	inline void setComposite(int n){ bit_set(composite, n); };
	inline void setFactored(int n){ bit_set(factored, n); };
};

Crivo::Crivo(){};

void Crivo::generate(){
	//primes.reserve(SIZE/log(SIZE)); 	// Guarda os primos.
	long long p, i;
	for(p = 2; p < LIM; p++){
		if(isPrime(p)){
			//primes.push_back(p); 		// Guarda os primos.

			for(i = p*p; i < SIZE; i += p){ 
				setComposite(i);
				primeFactor[i] = p;
			}
		}
		//fatora(p); 					// Melhor fatorar apenas quando precisar.
	}

	//for(; p < SIZE; p++)				// Guarda os primos.
	//	if(isPrime(p)) 
	//		primes.push_back(p);
};

void Crivo::fatora(int n){
	if(isFactored(n)) return;
	setFactored(n);

	if(isPrime(n)){
			factors[n].push_back(make_pair(n,1));
			return;
	}

	int otherFactor = n / primeFactor[n];
	fatora(otherFactor);

	factors[n] = factors[otherFactor];

	vector<pair<int, int> >::iterator it;
	it = lower_bound(factors[n].begin(), factors[n].end(), make_pair(primeFactor[n], 0));

	if(it == factors[n].end() || it->first != primeFactor[n])
		factors[n].insert(it, (make_pair(primeFactor[n], 1)));
	else
		++it->second;
}

void Crivo::printFactors(int n){
	for(int i = 0; i < factors[n].size(); ++i)
		printf("Fator: %d Vezes: %d\n", factors[n][i].first, factors[n][i].second);
}

Crivo c;

int main(){
	int n;
	c.generate();
	/*while(scanf("%d", &n) != EOF){
		c.fatora(n);
		c.printFactors(n);
	}*/
	return 0;
}
