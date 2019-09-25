#include <vector>
#include <string>
#include <stdio.h>
#include <utility>

using namespace std;

bool seenSrc = false;
bool seenTgt = false;
int p1 = 5;
int p2 = 100;
int maxStep = 5;

typedef pair<int, int> pt;



void dfs(pair<int, int> curr, vector<vector<int>> &grid, pair<int, int> src, pair<int, int> tgt, int &numBreak) {
    int m = grid.size();
    int n = grid[0].size();
    int i = curr.first;
    int j = curr.second;
    if (i < 0 || i >= m || j < 0 || j >= n) {
        return;
    }
    // if exist a path from src to tgt, and numbreak already over requirement
    // don't go any further
    if (seenSrc && seenTgt && numBreak > maxStep) {
        return;
    }
    // rand opportunity we don't go deeper
    if (rand()%p1 < 1) {
        return;
    }

    int d[5] = {-1,0,1,0,-1};
    if (grid[i][j] == 1) {
        grid[i][j] = 0;
        numBreak++;
    }
    if (curr == src) {
        seenSrc = true;
    }
    if (curr == tgt) {
        seenTgt = true;
    }
    int draw = rand()%4;
    int x = i + d[draw];
    int y = j + d[draw+1];
    if (x == prev.first && y == prev.second) {
        continue;
    }
    dfs({x,y}, grid, src, tgt, numBreak);
}

void genMaze(vector<vector<int>> &grid, pair<int, int> src, pair<int, int> tgt) {
    int numBreak = 0;
    unordered_map<int, unordered_map<int, bool>> path;
    dfs({5,5}, {-1,-1}, grid, src, tgt, numBreak);
}

void makeGrid(int m , int n, vector<vector<int>> &grid) {
    grid.resize(m, vector<int>(n, 1));
    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         grid[i][j] = 1;
    //     }
    // }
}

void printGrid(vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


int main() {
    vector<vector<int>> grid;
    makeGrid(10, 10, grid);
    genMaze(grid, {1,4}, {5,7});
    printGrid(grid);

    return 0;
}