#include<stdio.h>

int kadane(int n, int v[], int& inicio, int& fim){
	/* Calcula o problema do maximum subarray.
	 * Retorna a soma maxima. Os elementos estaum no
	 * intervalo [inicio, fim].
	 *
	 * n eh o tamanho do vetor de entrada.
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

int kadane_2D(int m, int n, int v[][j], int &ini_col, int& ini_lin, int& fim_col, int& fim_col){
	/* Kadane para calcular a soma maxima 
	 * numa matriz de duas dimensoes.
	 * O algoritmo calcula as somas de prefixos
	 * e, depois, aplicando o kadane normal em cada vetor.
	 * o resultado estah na matriz definida pelos parametros
	 * acima.
	 */
	int linha_atual = 0, col = m * m;
	int prefix[col][n];
	for(int i = 0; i < col; i++){




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
