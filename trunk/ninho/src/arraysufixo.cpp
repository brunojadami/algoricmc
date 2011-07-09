#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAXN 210010
int RA[MAXN], SA[MAXN], LCP[MAXN], *FC, *SC, step;
char S[MAXN], Q[MAXN];

bool cmp(int a, int b)
{
	if (step == -1 || FC[a] != FC[b]) return FC[a] < FC[b];
	return FC[a+(1<<step)] < FC[b+(1<<step)];
}

void build(int n)
{
	for (int i=0; i < n; ++i) RA[i] = S[SA[i] = i];
	for (FC = RA, SC = LCP, step = -1; (1<<step)<n; ++step)
	{
		sort(SA, SA+n, cmp);
		int cnt = 0;
		for (int i = 0; i < n; ++i)
		{
			if (i > 0 && cmp(SA[i-1], SA[i])) ++cnt;
			SC[SA[i]] = cnt;
		}
		if (cnt==n-1) break;
		swap(FC, SC);
	}
	for (int i = 0; i < n; ++i) RA[SA[i]] = i;
}

pair<int, int> range(int n) 
{
     	int lo = 1, hi = n, m = strlen(Q), mid = lo; 

     	while (lo <= hi) 
     	{
       		mid = (lo + hi) / 2;
        	int cmp = strncmp(S + SA[mid], Q, m);
         	if (cmp == 0) // found
             		break;
         	else if (cmp > 0)
         		hi = mid - 1;
    		else
         		lo = mid + 1;
         }
	if (lo > hi)
	    	return make_pair(-1, -1); // not found
	for (lo = mid; lo >= 1 && strncmp(S + SA[lo], Q, m) == 0; lo--);
		lo++;
	for (hi = mid; hi <= n && strncmp(S + SA[hi], Q, m) == 0; hi++);
		hi--;
	return make_pair(lo, hi);
}

int main()
{
	int k, c;
	scanf("%d", &k);
	
	while (k--)
	{
		scanf("%s", S); // string principal
		S[2000] = 0;
		int len = strlen(S); 
		build(len+1); // incluir o \0
		scanf("%d", &c);
		for (int i = 0; i < c; ++i)
		{
			scanf("%s", Q); // substring
			pair<int, int> p = range(len);
			if (p.first == -1)
				printf("n\n");
			else
				printf("y\n");
		}
	}
	
	return 0;
}

