#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

typedef int MatType;

struct Matrix{
	void* mat;
	int nRows, nCols;

	Matrix(int nRows, int nCols){
		this->nRows = nRows;
		this->nCols = nCols;
		mat = malloc(sizeof(MatType[nRows][nCols]));
	};

	~Matrix(){
		if(mat != NULL)
			free(mat);
		mat = NULL;
	};

	MatType* operator[](int i){
		return ((MatType(*)[nCols])mat)[i];
	};

	void print();

	void operator+=(Matrix &other);
	void operator=(Matrix &other);
	void operator*=(Matrix &other);
};

void Matrix::operator=(Matrix &other){
	memcpy(mat, other.mat, sizeof(MatType[nRows][nCols]));
};

void Matrix::print(){
	for(int i = 0; i < nRows; i++){
		for(int j = 0; j < nCols; j++)
			cout << (*this)[i][j] << ' ';
		cout << endl;
	}
};

void Matrix::operator+=(Matrix &other){
	for(int i = 0; i < nRows; i++)
		for(int j = 0; j < nCols; j++)
			(*this)[i][j] += other[i][j];
};

void Matrix::operator*=(Matrix &other){
	Matrix tmp(nRows, nCols);
	for(int i = 0; i < nRows; i++)
		for(int j = 0; j < nCols; j++){
			tmp[i][j] = 0;
			for(int k = 0; k < nRows; k++)
				tmp[i][j] += (*this)[i][k] * other[k][j];
		}
	swap(mat, tmp.mat);
};



int main(){
	int a, b;
	cin >> a >> b;
	Matrix m(a, b);
	for(int i = 0; i < m.nRows; i++)
		for(int j = 0; j < m.nCols; j++)
			cin >> m[i][j];
	m.print();
	return 0;
}


