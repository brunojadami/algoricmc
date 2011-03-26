#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;

inline void snippet(int *curMax, int elem, int *result){
	*curMax += elem;
	*curMax = max(0, *curMax);
	*result = max(*curMax, *result);
}

int kadane(vector<int> &vec){
	int result = 0, curMax = 0;
	for(int i = 0; i < vec.size(); i++)
		snippet(&curMax, vec[i], &result);
	return result;
}

#define likely(x) __builtin_expect((x),1)
int kadane2D(void *mat, int nRows, int nCols){
	int (*matrix)[nCols] = (int(*)[nCols])mat;
	int subSums[nRows][nCols];
	int maxTmp, curMax, result = 0;

	for(int i = 0; i < nRows; i++){
		maxTmp = curMax = 0;
		for(int j = 0; j < nCols; j++){
			subSums[i][j] = matrix[i][j];
			if(likely(i > 0)) subSums[i][j] += subSums[i-1][j];

			snippet(&curMax, subSums[i][j], &maxTmp);
		}
		result = max(result, maxTmp);
	}

	for(int i = 0; i < nRows - 1; i++)
		for(int k = i+1; k < nRows; k++){
			maxTmp = curMax = 0;
			for(int j = 0; j < nCols; j++)
				snippet(&curMax, subSums[k][j] - subSums[i][j], &maxTmp);
			result = max(result, maxTmp);
		}
	return result;
}

int main(){
	int a[3][3];
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			cin >> a[i][j];
		}
	}
	cout << kadane2D(a, 3,3)<< endl;
	return 0;
}
