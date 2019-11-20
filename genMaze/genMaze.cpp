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
    // int m = grid.size();
    // int n = grid[0].size();
    // int i = curr.first;
    // int j = curr.second;
    // if (i < 0 || i >= m || j < 0 || j >= n) {
    //     return;
    // }
    // // if exist a path from src to tgt, and numbreak already over requirement
    // // don't go any further
    // if (seenSrc && seenTgt && numBreak > maxStep) {
    //     return;
    // }
    // // rand opportunity we don't go deeper
    // if (rand()%p1 < 1) {
    //     return;
    // }

    // int d[5] = {-1,0,1,0,-1};
    // if (grid[i][j] == 1) {
    //     grid[i][j] = 0;
    //     numBreak++;
    // }
    // if (curr == src) {
    //     seenSrc = true;
    // }
    // if (curr == tgt) {
    //     seenTgt = true;
    // }
    // int draw = rand()%4;
    // int x = i + d[draw];
    // int y = j + d[draw+1];
    // if (x == prev.first && y == prev.second) {
    //     continue;
    // }
    // dfs({x,y}, grid, src, tgt, numBreak);
}

void genMaze(vector<vector<int>> &grid, pair<int, int> src, pair<int, int> tgt) {
    // int numBreak = 0;
    // int m = grid.size();
    // int n = grid[0].size();
    // int maxLvl = 10;
    // vector<vector<bool>> visited(m, vector<bool>(n, false));
    // dfs({5,5}, grid, src, tgt, numBreak, maxLvl);
}

void makeGrid(int m , int n, vector<vector<int>> &grid) {
    grid.resize(m, vector<int>(n, 1));
    // for (int i = 0; i < m; i++) {
    //     for (int j = 0; j < n; j++) {
    //         grid[i][j] = 1;
    //     }
    // }
}

void shuffle(int d[][2]) {
    for (int i = 0; i < 4; i++) {
        int r = rand()%(4 - i);
        swap(d[i], d[r+i]);
    }
}

bool isValidWall(int i, int j, vector<vector<int>> &grid) {
    int m = grid.size();
    int n = grid[0].size();
    return i >= 0 && i < m && j >= 0 && j < n && grid[i][j] == 1;
}

void gen(int i, int j, vector<vector<int>> &grid) {
    // printf("gen:(%d,%d):%d\n", i, j, grid[i][j]);
    int d[4][2] = {
        {-1,0},
        {0,1},
        {1,0},
        {0,-1},
    };
    shuffle(d);
    for (int k = 0; k < 4; k++) {
        int x1 = i + d[k][0];
        int y1 = j + d[k][1];
        // need to break 2 at a time , otherwise you won't have any wall in between path
        int x2 = i + d[k][0]*2;
        int y2 = j + d[k][1]*2;
        if (isValidWall(x2, y2, grid)) {
            // printf("gen: to go (%d,%d):%d\n", x1, y1, grid[x1][y1]);
            grid[x1][y1] = 0;
            grid[x2][y2] = 0;
            gen(x2,y2, grid);
            // gen(x1,y1,grid);
        }
    }
}

void genMazeV2(vector<vector<int>> &grid) {
    grid[0][0] = 0;
    gen(0, 0, grid);
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
    genMazeV2(grid);
    printGrid(grid);

    return 0;
}