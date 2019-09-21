// CPP program to print matrix downward
// https://www.geeksforgeeks.org/print-the-matrix-diagonally-downwards/
#include <bits/stdc++.h>
using namespace std;

void printMatrixDiagonallyDown(vector<vector<int> > matrix,
													int n)
{
  	for (int d = 0; d < 2*n-1; d++) {
    	for (int i = max(d-2, 0); i < n; i++) {
          	int j = d - i;
          	if (j < 0 || j >= n) {
             	continue;
            }
          	printf("%d ", matrix[i][j]);
        }
    }
}

int main()
{
	vector<vector<int> > matrix{ { 1, 2, 3 },
								{ 4, 5, 6 },
								{ 7, 8, 9 } };
	int n = 3;
	printMatrixDiagonallyDown(matrix, n);
	return 0;
}