#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

struct Matrix{
	int nRows, nCols;
	int *mat;
	int **rows;

	Matrix(int r, int c){
		nRows = r;
		nCols = c;
		mat = (int*)malloc(sizeof(int)*r*c);
		rows = (int**)malloc(sizeof(int*)*r);
		for(int i = 0; i < r; i++)
			rows[i] = mat + i * c;
	};

	Matrix(const Matrix &rhs){
		nRows = rhs.nRows;
		nCols = rhs.nCols;
		mat = (int*)malloc(sizeof(int)*r*c);
		rows = (int**)malloc(sizeof(int*)*r);
		for(int i = 0; i < r; i++)
			rows[i] = mat + i * c;
		memcpy(mat, rhs.mat, nRows*nCols);
	};

	~Matrix(){
		free(mat);
		free(rows);
	};

	int & at(int i, int j){
		return rows[i][j];
	};

	Matrix & operator+=(const Matrix &rhs){
		int lim = nRows * nCols;
		for(int i = 0; i < lim; i++)
			mat[i] += rhs.mat[i];
		return *this;
	};

	Matrix & operator=(const Matrix &rhs){
		if(this != &rhs){
			if(nRows*nCols != rhs.nRows*rhs.nCols){
				free(mat);
				free(rows);
				nRows = rhs.nRows;
				nCols = rhs.nCols;
				mat = (int*)malloc(sizeof(int)*nRows*nCols);
				rows = (int**)malloc(sizeof(int*)*nRows);
			};
			for(int i = 0; i < nRows; i++)
				rows[i] = mat + i * nCols;
			memcpy(mat, rhs.mat, nRows*nCols);
		}
		return *this;
	};
};

int main(){
	Matrix mat(2, 4);
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 4; j++)
			scanf("%d", &(mat.at(i,j)));

	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 4; j++)
			printf("%d ", mat.at(i, j));
		puts("");
	}
	return 0;
};
		
