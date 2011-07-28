#include <cstdio>
#include <cmath>

// **Handle even numbers and numbers < 3 manually on your own.**

const int MAX = 20000000 + 1, LMT = sqrt(MAX)+1; // MAX eh o maximo
int flag[MAX>>6];

#define ifc(x) (flag[x>>6]&(1<<((x>>1)&31))) // chamar ifc pra testar se eh primo, se retornar falso eh primo (if composite)
#define isc(x) (flag[x>>6]|=(1<<((x>>1)&31))) // seta x como composite

void sieve() // da pra por numa linha..
{
	for(int i = 3; i < LMT; i += 2) 
		if(!ifc(i)) 
			for(int j = i*i, k = i<<1; j < MAX; j += k) 
				isc(j);
}

// pra baxo eu fiz gambi pra pegar os primos
vector<int> primes;

int main()
{
	sieve();
	primes.push_back(2);
	primes.push_back(3);
	for(int k = 1; k < MAX; ++k)
	{
		int num = k*6-1;
		if(num < MAX && !ifc(num))
			primes.push_back(num);
		num = k*6+1;
		if(num < MAX && !ifc(num))
			primes.push_back(num);
	}
	
	return 0;
}

