#include<cstdio>
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

const int SIZE = 100 + 1;
struct Crivo{
	char isPrime[SIZE];
	char isFactored[SIZE];

	int primeFactor[SIZE];                  // Usado para fatoração.
	vector<pair<int, int> > factors[SIZE];  // Usado para fatoração.
	//vector<int> primes;					// Para guardar os primos

	Crivo();
	void generate();
	void fatora(int);
	void printFactors(int);
};

Crivo::Crivo(){
	for(int i = 0; i < SIZE; i++){
		isPrime[i] = 1;
		isFactored[i] = 0;
	}
	isFactored[1] = 1;
	isFactored[0] = 1;
};

void Crivo::generate(){
	unsigned long long p, i;
	//primes.reserve(SIZE/log(SIZE)); // Guarda os primos.
	for(p = 2; p < SIZE; p++){
		if(isPrime[p]){
			// primes.push_back(p); // Guarda os primos.
			factors[p].push_back(make_pair(p,1));
			isFactored[p] = 1;
			for(i = p*p; i < SIZE; i+=p){ 
				isPrime[i] = 0;
				primeFactor[i] = p;
			}
		}
		//fatora(p); // Melhor fatorar apenas quando precisar.
	}
};

void Crivo::fatora(int n){
	if(isFactored[n]) return;
	isFactored[n] = 1;

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
/*	int n;
	
        c.generate();
        
        c.fatora(123456);
        c.printFactors(123456);
  */      
	int n;
	c.generate();
	for(int i = 2; i < SIZE; i++)
		c.fatora(i);
	cin >> n;
	c.printFactors(n);
	return 0;
}
