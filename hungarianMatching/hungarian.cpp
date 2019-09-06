#include <vector>
#include <stdio.h>

using namespace std;

#define M 3
#define N 3

int w[M][N] = {
   {1,1,1},
   {0,1,0},
   {0,1,0},
};

/*
    return true if x can find a match
 */
bool find(int x, vector<bool> &visitedX, vector<bool> &visitedY, vector<int> &link) {
    visitedX[x] = true;
    for (int y = 0; y < N; y++) {
        if (visitedY[y] || w[x][y] != 1) {
            continue;
        }
        visitedY[y] = true;
        // if this y not in any pair yet, or the matching x for this y can match with other option
        if (link[y] == -1 || find(link[y],visitedX, visitedY, link)) {
            link[y] = x;
            return true;
        }
    }
    return false;
}

int main() {
    int total = 0;
    vector<bool> visitedX(M, false);
    vector<bool> visitedY(N, false);
    vector<int> link(N, -1);
    // looping through each x and find matching for them
    // link will be modified and remain over loop
    // but visitedX/Y will be reset in each round
    // since each round we want to have option to revisit all possible X/Y pair
    for (int x = 0; x < M; x++) {
        visitedX.resize(M, false);
        visitedY.resize(N, false);
        if (find(x, visitedX, visitedY, link)) {
            total++;
        }
    }
    printf("total pair: %d\n", total);
    for (int y = 0; y < N; y++) {
        printf("link[%d]: %d\n", y, link[y]);
    }

    return 0;
}