#include<stdio.h>
#include<stdlib.h>

/* Max int possible. Be careful when using it... */
#define INFINITY 0x7FFFFFFF 

struct tuple{
	int a, b, c, d, e;
};

struct tuple kadane(int *a, int n){
	/* Maximum subarray problem. Returns 
	 * the sum of its elements, contained in
	 * the range [final.b, final.c].
	 * a is the input array, n is its size.
	 *
	 * Notes:
	 * Complexity: O(n).
	 * Does not use tuple.{d, e}.
	 *
	 * From Algorithmist:
	 *
	 * Kadane's Algorithm(arr[1..n])
	 * begin
    	 * (max, a, b) := (-INFINITY, 0, 0)
    	 * curr := 0
    	 * aa := 1
    	 * for bb := 1 to n do
         *	curr := curr + arr[bb]
         *	if curr > max then
         *   	(max, a, b) := (curr, aa, bb)
         *	endif
         *
         *	if curr < 0 then
         *   	curr := 0
         *   	aa := bb + 1
         *	endif
    	 * endfor
         *
    	 * return (max, a, b)
	 * end
	 */
	int curr, start, end;
	struct tuple final, flag;
	final.a = flag.a = -INFINITY;
	final.b = final.c = start = curr = 0;
	for(end = 0; end < n; end++){
		curr += a[end];
		if(flag.a < a[end]){
			flag.a = a[end];
			flag.b = flag.c = end;
		}
		if(curr > final.a){
			final.a = curr;
			final.b = start;
			final.c = end;
		}
		if(curr < 0){
			curr = 0;
			start = end + 1;
		}
	}
	if(flag.a < 0)
		return flag;
	return final;
}

struct tuple kadane_2D(void *a, int rows, int colums){
	/* Kadane 2D. The subrectangle is defined by
	 * the points (final.b, final.c) and
	 * (final.d, final.e).
	 *
	 * Notes:
	 * Does not depend on kadane(int*, int).
	 * Complexity: O(n^3).
	 *
	 * From Algorithmist:
	 * First, calculate the vertical prefix sum 
	 * for all columns (an O(n2) algorithm).
	 *
	 * Uses the vertical prefix sum to allow us to imagine 
	 * each column sum as if it is a single element 
	 * of a one-dimensional array across all columns 
	 * (one dimensional array with one row and n columns).
	 * 
	 * Then, assumes that the maximum sub-array will be between 
	 * row a and row b, inclusive. There are only O(n2) a, b 
	 * pairs such that a < b. Tries each of them. 
	 *
	 * Applying the Kadane's algorithm inside each a and b 
	 * combination gives the total complexity of O(n^3). 
	 */ 
	int i, i2, j, b4, colum_start, curr;
	struct tuple final, flag;
	final.a = flag.a = -INFINITY;
	final.b = final.c = final.d = final.e = 0;
	/* Matrix that stores the prefix sum.
	 * Has an initial line, which contains
	 * only zeroes.
	 */ 
	int **p = (int**)malloc(sizeof(int*) * ++rows);
	/* Allocates memory and calculates the prefix sums. */
	p[0] = (int*)calloc(colums, sizeof(int));
	for(i = 1, b4 = 0; i < rows; i++, b4++){
		p[i] = (int*)malloc(sizeof(int) * colums);
		for(j = 0; j < colums; j++){
			if(((int (*)[colums])a)[b4][j] > flag.a){
				flag.a = ((int (*)[colums])a)[b4][j];
				flag.b = flag.d = i - 1;
				flag.c = flag.e = j;
			}
			p[i][j] = ((int (*)[colums])a)[b4][j] + p[b4][j];
		}
	}

	if(flag.a < 0)
		goto kadane_2D_end;

	for(i = 1, b4 = 0; i < rows; i++, b4++){
		for(i2 = i; i2 < rows; i2++){
			curr = colum_start = 0;
			for(j = 0; j < colums; j++){
				curr += p[i2][j] - p[b4][j];
				if(curr > final.a){
					final.a = curr;
					final.b = i - 1;	/* row_start */
					final.c = colum_start;	/* colum_start */
					final.d = i2 - 1;	/* row_end */
					final.e = j;		/* colum_end */
				}
				if(curr < 0){
					curr = 0;
					colum_start = j + 1;
				}
			}
		}
	}

kadane_2D_end:
	for(i = 0; i < rows; i++)
		free(p[i]);
	free(p);
	if(flag.a < 0)
		return flag;
	return final;
}
