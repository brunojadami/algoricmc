// Implementation of Monotone Chain Convex Hull algorithm.
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
 
typedef double CoordType;
 
struct Point {
	CoordType x, y;
 
	bool operator <(const Point &p) const {
		return x < p.x || (x == p.x && y < p.y);
	}
};
 
// 2D cross product.
// Return a positive value, if OAB makes a counter-clockwise turn,
// negative for clockwise turn, and zero if the points are collinear.
CoordType cross(const Point &O, const Point &A, const Point &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}
 
// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convexHull(vector<Point>& P)
{
	int n = P.size(), k = 0;
	vector<Point> H(2*n);
 
	// Sort points lexicographically
	sort(P.begin(), P.end());
 
	// Build lower hull
	for (int i = 0; i < n; i++) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}
 
	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}
 
	H.resize(k-1);
	return H;
}

vector<Point> points, result;

double area(int a, int b, int c)
{
	double calc = result[a].x*result[b].y - result[a].x*result[c].y + result[b].x*result[c].y 
	- result[b].x*result[a].y + result[c].x*result[a].y - result[c].x*result[b].y;
	return calc/2.0;
}

// biggest triangle O(n)
double biggest()
{
	int n = result.size();
	// Assume points have been sorted already, as 0...(n-1)
	int A = 0, B = 1, C = 2;
	int bA= A, bB= B, bC= C; // The "best" triple of points
	double best = area(A, B, C); // Best area
	
	while (1) // loop A
	{
		while (1) // loop B
		{
			while (area(A, B, C) <= area(A, B, (C+1)%n)) // loop C
				C = (C+1)%n;
			if (area(A, B, C) <= area(A, (B+1)%n, C))
				B = (B+1)%n;
			else
				break;
		}

		double test = area(A, B, C);
		if (test > best)
		{
			bA = A; bB = B; bC = C;
			best = test;
		}

		A = (A+1)%n;
		if (A==B) B = (B+1)%n;
		if (B==C) C = (C+1)%n;
		if (A==0) break;
	}
	
	return best;
}

int main()
{
	int n;
	
	while (1)
	{
		scanf("%d", &n);
		if (n == -1)
			break;
			
		points.clear();
		
		for (int i = 0; i < n; ++i)
		{
			Point p;
			scanf("%lf%lf", &p.x, &p.y);
			points.push_back(p);
		}
		
		result = convexHull(points);
		
		double res = biggest();
		printf("%.2lf\n", res);
	}
	
	return 0;
}

