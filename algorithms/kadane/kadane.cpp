#include<stdio.h>

int kadane(int n, int v[], int& inicio, int& fim){
	/* Calcula o problema do maximum subarray.
	 * Retorna a soma maxima. Os elementos estaum no
	 * intervalo [inicio, fim].
	 */ 
	int max = 0, curr = 0, i = inicio = fim = 0;
	for(int j = 0; j < n; j++){
		curr += v[j];
		if(curr > max){
			max = curr;
			inicio = i;
			fim = j;
		}
		if(curr < 0){
			curr = 0;
			i = j + 1;
		}
	}
	return max;
}

int main(){
	int n, ini, fim;
	scanf("%d", &n);
	int v[n], max;
	for(int i = 0; i < n; i++)
		scanf("%d,", &v[i]);
	max = kadane(n, v, ini, fim);
	printf("%d %d %d\n", max, ini, fim);
	return 0;
}       
