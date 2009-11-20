#include<stdio.h>
#include<stdlib.h>

/* Max int possible. Be careful when using it... */
#define INFINITY 0x7FFFFFFF

/* Return type of the kadane functions. */
struct tuple{
	int a, b, c, d, e;
};

struct tuple kadane(int *a, int n);
/* Calculates the maximum sum of an array.
 * The sum is return in the field tuple.a,
 * and the elements that are part of the sum
 * are in the interval [tuple.b, tuple.c].
 *
 * Notes:
 * Complexity: O(n).
 * Does not use tuple.{d, e}.
 */

struct tuple kadane_2D(void *a, int rows, int colums);
/* Maximum sum in a matrix. The sum is returned in
 * tuple.a; and the two points defining the subrectangle
 * are returned in tuple.[b,e]. tuple.{b,d} are the 
 * lines of the points, and tuple.{c,e} are their colums.
 *
 * Notes:
 * Complexity: O(n^3).
 * Does not depends on kadane(int, int).
 */ 

