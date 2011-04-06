#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

const int SIZE = 1000000 + 1;
struct Crivo{
        char isPrime[SIZE];
        
        int primeFactor[SIZE];                  // Usado para fatoração.
        int otherFactor[SIZE];                  // Usado para fatoração.
        vector<pair<int, int> > factors[SIZE];  // Usado para fatoração.
	//vector<int> primes;	// Para guardar os primos
  
        Crivo();
        void generate();
        void fatora(int n);
        void printFactors(int n);
};

Crivo::Crivo(){
        for(int i = 0; i < SIZE; i++){
                isPrime[i] = 1;
                primeFactor[i] = i;
                otherFactor[i] = -1;
        }
};

void Crivo::generate(){
        int p = 2;
	//primes.reserve(SIZE/log(SIZE)); // Descomentar aqui e ali em baixo se quiser ir guardando os primos
        for(; p < SIZE; p++) 
        {
        	if (isPrime[p])
        	{
			// primes.push_back(p);
		        for(unsigned long long i = p*p; i < SIZE; i+=p){
		                isPrime[i] = 0;
		                primeFactor[i] = p;
		                otherFactor[i] = i/p;
		        }
		}
		fatora(p);
        }
};

void Crivo::fatora(int n)
{
	if (otherFactor[n] == -2) // ja foi fatorado
		return;
	if (otherFactor[n] == -1) // se for primo
	{
		factors[n].push_back(make_pair(n, 1));
		otherFactor[n] = -2;
		return;
	}
	
	fatora(otherFactor[n]);
	
	factors[n] = factors[otherFactor[n]];
	
	//sort(factors[n].begin(), factors[n].end());
	
	vector<pair<int, int> >::iterator it = lower_bound(factors[n].begin(), factors[n].end(), make_pair(primeFactor[n], 0));
	if (it == factors[n].end() || it->first != primeFactor[n])
	{
		factors[n].push_back(make_pair(primeFactor[n], 1));
		sort(factors[n].begin(), factors[n].end());
	}
	else
		it->second++;
	
	otherFactor[n] = -2;
}

void Crivo::printFactors(int n)
{
	for (vector<pair<int, int> >::iterator it = factors[n].begin(), end = factors[n].end(); it != end; ++it)
		printf("Fator: %d Vezes: %d\n", it->first, it->second);
}

Crivo c;

int main(){
	int n;
	
        c.generate();
        
        return 0;
}



