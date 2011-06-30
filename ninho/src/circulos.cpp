#include <cmath>
#include <cstdio>

using namespace std;

/*
	UVA 10005 Packing Polygons.

 	Problema dos circulos, pra ver se um circulo de circunferencia R engloba todos os pontos.
 	Da pra fazer em O(n^4) mas desse jeito aqui eh O(n^3). O algoritmo eh bem simples, pega os
 	pontos 2 a 2 e desses dois pontos existem 2 circunferencias de raio R, testa as duas
 	com todos os outros pontos. Prova: lembrar do bambole!
*/

int N,x[99],y[99]; // coordenadas dos pontos eh so inteira no problema

// checando a circunferencia com centro c e de raio R com todos os outros pontos
bool check(double &cx, double &cy, double &R){
    for(int i=0;i<N;++i) if((cx-x[i])*(cx-x[i])+(cy-y[i])*(cy-y[i])>R*R+1e-8) return false;
    return true;
}

int main(){
    double R,cx1,cy1,cx2,cy2,dx1,dy1,L,dx2,dy2;
    bool found;
    
    while(true){
        scanf("%d", &N);
        if(N==0) break;
        
        for(int i=0;i<N;++i) scanf("%d%d", &x[i], &y[i]);
        scanf("%lf", &R);
        
        found = false;
        
        // pra cada par de ponto
        for(int i=0;i<N;++i){
            for(int j=i+1;j<N;++j){
                dx1 = (x[i]-x[j])/2.0;
                dy1 = (y[i]-y[j])/2.0;
                
                L = sqrt(dx1*dx1+dy1*dy1);
                if(L>R) continue; // checa se a distancia dos dois pontos eh possivel fazer uma circuferencia de raio R
                
                // manipulando as equacoes vc acha os dois centros possiveis
                dx2 = -dy1*sqrt(R*R-L*L)/L;
                dy2 = dx1*sqrt(R*R-L*L)/L;
                
                cx1 = x[j]+dx1+dx2;
                cy1 = y[j]+dy1+dy2;
                
                cx2 = x[j]+dx1-dx2;
                cy2 = y[j]+dy1-dy2;
                
                // checando as duas circunferencias
                if(check(cx1,cy1,R) || check(cx2,cy2,R)) 
                {
                	found = true;
                	j = N;
                	break;
                }
            }
        }
        
        if(found) printf("The polygon can be packed in the circle.\n");
        else printf("There is no way of packing that polygon.\n");
    }
    
    return 0;
}

