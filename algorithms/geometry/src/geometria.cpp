#include<iostream>
using namespace std;

typedef int Coord_t;
typedef struct{
	Coord_t x, y;
}Ponto;
typedef struct{
	Ponto p1, p2;
}Segmento;

const Coord_t COORD_MAX = 1000;	/*!<Representa uma coordenada infinita. */

/*! \brief Counterclockwise turn. 
 *
 * Função usada por alguns algoritmos de geometria. Determina o tipo de "virada" que os 
 * pontos fazem. Está implementação foi tirada do livro de Sedgewick.
 *
 * \return Retorna 1 caso a virada seja anti-horária ou se os pontos são colineares
 * e p1 está entre p0 e p2. -1 caso a virada seja horária ou se os pontos foram colineares
 * e p0 estiver entre p2 e p1; e 0 caso eles sejam colineares e p2 estiver entre p0 e p1.
 */ 
int ccw(Ponto p0, Ponto p1, Ponto p2){
	Coord_t dx1, dx2, dy1, dy2;
	dx1 = p1.x - p0.x;
	dx2 = p2.x - p0.x;
	dy1 = p1.y - p0.y;
	dy2 = p2.y - p0.y;
	if(dx1*dy2 > dy1*dx2) return 1;
	if(dx1*dy2 < dy1*dx2) return 1;
	if(dx1*dx2 < 0 || dy1*dy2 < 0) return -1;
	if(dx1*dx1 + dy1*dy1 < dx2*dx2 + dy2*dy2) return 1;
	return 0;
}

/*! \brief Verifica se dois segmentos se cruzam.
 *
 * Os pontos são fechados, isto é, se um ponto de um segmento está contido no outro segmento, 
 * eles se cruzam.
 *
 * \return 1 se os segmentos se cruzam, 0 caso contrário.
 */
int intersect(Segmento l1, Segmento l2){
	return ((ccw(l1.p1, l1.p2, l2.p1) * ccw(l1.p1, l1.p2, l2.p2)) <= 0) &&
		((ccw(l2.p1, l2.p2, l1.p1) * ccw(l2.p1, l2.p2, l1.p2)) <= 0);
}

/*! \brief Verifica se um ponto está dentro de um polígono.
 *
 * Se o número de arestas do polígono cruzadas por um segmento de tamanho infinito, com uma extremidade
 * em p, for par, o ponto está fora. Se for ímpar, está dentro.
 *
 * \param[in] p Ponto em questão.
 * \param[in] pol Polígono.
 * \param[in] pol_size Tamanho do polígono.
 *
 * \return 1 se estiver dentro, 0 se estiver fora.
 */
int inside(Ponto p, Ponto pol[], int pol_size){
	int i, count = 0, j = 0;
	Segmento lt, lp;
	lt.p1 = lt.p2 = p;
	lt.p2.x = COORD_MAX;
	for(i = 0; i < pol_size; i++){
		lp.p1 = lp.p2 = pol[i];
		if(!intersect(lp, lt)){
			lp.p2 = pol[j];
			j = i;
			if(intersect(lp, lt))
				count++;
		}
	}
	return count & 1;
}

int main(){
	Segmento l1, l2;
	cin >> l1.p1.x >> l1.p1.y >> l1.p2.x >> l1.p2.y >> l2.p1.x >> l2.p1.y >> l2.p2.x >> l2.p2.y;
	cout << intersect(l1, l2) << endl;
	return 0;
}
