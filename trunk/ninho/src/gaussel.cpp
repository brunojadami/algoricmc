int n, m;
int mat[50][50];

bool notzero(int i, int j) // so pra double so..
{
	return mat[i][j] > 0.1 || mat[i][j] < -0.1;
}

void gauss() 
{
	int i = 0, j = 0;
	while (i < n && j < m)
	{
		int maxi = i;
		for (int k = i+1; k < n; ++k)
			if (abs(mat[k][j]) > abs(mat[maxi][j])) // fabs para double
				maxi = k;
		if (notzero(maxi, j))
		{
			for (int a = 0; a < m; ++a)
				swap(mat[i][a], mat[maxi][a]);
			//for (int a = 0; a < m; ++a) // ja ta tudo 1
				//mat[i][a] /= mat[i][j];
			for (int u = i+1; u < n; ++u)
			{
				int c = mat[u][j];
				for (int k = 0; k < m; ++k)
				{
					mat[u][k] -= mat[i][k]*c;
					mat[u][k] %= 2;
				}
			}
			++i;
		}
		++j;
	}
}

