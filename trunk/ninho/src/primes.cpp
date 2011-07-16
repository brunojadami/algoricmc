#include<cstdio>
#include<algorithm>
#include<vector>
#include<iostream>
#include<cstring>
#include<math.h>
using namespace std;

const int SIZE = 1000000 + 1;
const int LIM = sqrt(SIZE) + 1;

#define bchk(arr, x) (arr[x>>6]&(1<<((x>>1)&31)))  // Bit check. chamar ifc pra testar se eh primo, se retornar falso eh primo (if composite)
#define bset(arr, x) (arr[x>>6]|=(1<<((x>>1)&31))) // Bit set

struct Crivo{
	int isComposite[SIZE >> 6];
	int isFactored[SIZE >> 6];

	int primeFactor[SIZE];                  // Usado para fatoração.
	vector<pair<int, int> > factors[SIZE];  // Usado para fatoração.
	//vector<int> primes;					// Para guardar os primos

	Crivo();
	void generate();
	void fatora(int);
	void printFactors(int);
};

Crivo::Crivo(){
//	memset(isPrime, 1, sizeof isPrime);
//	memset(isFactored, 0, sizeof isFactored);
	bset(isFactored,1);
	bset(isFactored,0);

	bset(isComposite,1);
	bset(isComposite,0);
};

void Crivo::generate(){
	//primes.reserve(SIZE/log(SIZE)); // Guarda os primos.
	for(int p = 2; p < LIM; p++){
		if(!bchk(isComposite,p)){
			// primes.push_back(p); // Guarda os primos.
			factors[p].push_back(make_pair(p,1));
			bset(isFactored,p);
			
			int i = p*p;
			if(i < 1) continue; // Overflow check.
			for(; i < SIZE; i+=p){ 
				bset(isComposite,i);
				primeFactor[i] = p;
			}
		}
		fatora(p); // Melhor fatorar apenas quando precisar.
	}
};

void Crivo::fatora(int n){
	if(bchk(isFactored,n)) return;
	bset(isFactored,n);

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
	//for(int i = 2; i < SIZE; i++)
		//c.fatora(i);
	//cin >> n;
	//c.printFactors(n);
	return 0;
}
