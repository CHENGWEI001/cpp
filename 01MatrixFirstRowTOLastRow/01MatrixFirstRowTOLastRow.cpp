#include <vector>
#include <queue>
#include <stdio.h>
#include <algorithm>

using namespace std;

void printPath(vector<vector<int>> &pi, int n, int i, int j) {
    vector<pair<int, int>> path;
    int curr = i*n+j;
    while (curr != -1) {
        path.push_back({curr/n, curr%n});
        curr = pi[curr/n][curr%n];
    }
    reverse(path.begin(), path.end());
    for (auto &p: path) {
        printf("(%d,%d)\n", p.first, p.second);
    }
}

bool check(vector<vector<int>> &grid) {
    int d[5] = {-1,0,1,0,-1};
    queue<pair<int, int>> q;
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<bool>> vis(m, vector<bool>(n, false));
    vector<vector<int>> pi(m, vector<int>(n, -1));
    for (int j = 0; j < n; j++) {
        if (grid[0][j] == 1) {
            q.push({0,j});
            vis[0][j] = true;
        }
    }
    while (q.size()) {
        auto curr = q.front();
        q.pop();
        int i = curr.first;
        int j = curr.second;
        if (i == m-1) {
            printPath(pi, n, i, j);
            return true;
        }
        for (int k = 0; k < 4; k++) {
            int x = i + d[k];
            int y = j + d[k+1];
            if (x < 0 || x >= m || y < 0 || y >= n || vis[x][y] || grid[x][y] == 0) {
                continue;
            }
            q.push({x, y});
            vis[x][y] = true;
            pi[x][y] = i*n+j;
        }
    }
    return false;
}

int main() {
    // 1 is walkable
    // 0 is obsacle
    // check if able to reach last row from first row
    vector<vector<int>> grid = {
        {1,1,1,1},
        {0,0,0,1},
        {0,1,0,1},
        {0,0,1,1},
    };
    printf("res:%d", check(grid)? 1: 0);
    return 0;
}