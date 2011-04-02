#include<iostream>
#include<map>
#include<cmath>
#include<vector>
using namespace std;

int abs(int n){ return (int)abs((double)n); }

const int SIZE = 30 + 1;
struct Crivo{
        char isPrime[SIZE];
        
        char visited[SIZE];
        int primeFactor[SIZE];                  // Usado para fatoração.
        int otherFactor[SIZE];                  // Usado para fatoração.
        map<int, int> factors[SIZE];    // Usado para fatoração.
    //vector<int> primes;           // Para guardar os primos
  
        Crivo();
        void generate();
        void lowersTree();
        void facts(int n);
        void printFactors(int n);
};

Crivo::Crivo(){
        for(int i = 0; i < SIZE; i++){
                isPrime[i] = 1;
                primeFactor[i] = 1;
                otherFactor[i] = i;
                visited[i] = 0;
        }
};

void Crivo::generate(){
        int p = 2;
    //primes.reserve(SIZE/log(SIZE)); // Descomentar aqui e ali em baixo se quiser ir guardando os primos
        while(1){
                for(; p < SIZE && isPrime[p] == 0; p++);
        // primes.push_back(p); 
                if(p*p > SIZE) 
            {
                   //for (int i = p+1; i < SIZE; ++i)
                   //if (isPrime[i])
                   //primes.push_back(i);
                   return;
            }
                for(int i = p*p; i < SIZE; i+=p){
                        isPrime[i] = 0;
                        primeFactor[i] = p;
                        otherFactor[i] = i/p;
                }
                p++;
        }
};

void Crivo::lowersTree(){
        int comp = 4;
        while(1){
                for(; comp < SIZE && isPrime[comp] == 1; comp++);
                if(comp*comp > SIZE) return;
                
                if((comp % ((int)sqrt(comp))) == 0)
                        primeFactor[comp] = otherFactor[comp] = (int)sqrt(comp);
                for(int i = 2*comp; i < SIZE; i+=comp){
                        int tmp = i / comp;
                        int diff1 = abs(tmp - comp);
                        int diff2 = abs(otherFactor[i] - primeFactor[i]);
                        if(diff1 < diff2){
                                primeFactor[i] = comp;
                                otherFactor[i] = tmp;
                        }
                }
                comp++;
        }
};

void Crivo::facts(int n){
        if(visited[n] == 1) return;
        visited[n] = 1;
        if(isPrime[n] == 1){
                factors[n][n] = 1;
                return;
        }

        if(visited[primeFactor[n]] == 0)
                facts(primeFactor[n]);
        if(visited[otherFactor[n]] == 0)
                facts(otherFactor[n]);
        factors[n] = factors[otherFactor[n]];
        map<int,int>::iterator it;

        if(primeFactor[n] == otherFactor[n]){
                for(it = factors[n].begin(); it != factors[n].end(); it++)
                        it->second *= 2;
                return;
        }

        for(it = factors[primeFactor[n]].begin(); it != factors[primeFactor[n]].end(); it++)
                factors[n][it->first] += it->second;
        return;
};

void Crivo::printFactors(int n){
        map<int,int>::iterator it;
        for(it = factors[n].begin(); it != factors[n].end(); it++)
                cout << it->first << '\t' << it->second << endl;
};

int main(){
        Crivo c;
        c.generate();
        for(int i = 1; i < SIZE; i++){
                if(c.isPrime[i] == 1)
                        cout << i << ' ';
        }
        cout << endl;

        c.lowersTree();
        for(int i = 1; i < SIZE; i++)
                c.facts(i);

        int n;
        cin >> n;
        c.printFactors(n);
        return 0;
}

