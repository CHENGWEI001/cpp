#include <vector>
#include <stdio.h>
#include <unordered_set>
#include <cassert>
#include <algorithm>

using namespace std;

/*
给一个二维矩阵，每个元素都是非负整数。找到所有可能路径的最大的和。
在一条路径中，不能包含0，路径可以向上下左右延伸，每个元素只能访问一次。假设矩阵中正整数的路径不可能形成环。

我一顿暴写之后，跑了几个test cases之后，发现写成了求maximum sum of the connected component
(为毛开始面试官同意我的想法是对的，说可以开始写代码了，欲哭无泪，还是自己把问题想的太简单。）

求问大家这道题怎么做？

for this question, "假设矩阵中正整数的路径不可能形成环" is a key point to use this method"

Think about below case :
1. by using the code implemeted here, say we start from y,
we try up , right, down , left sequence, if "y up left" path is less than "y left up" path,
since we go up first, we might end up not choosing "y left up" path.

2. Originally I was wondering if I can use idea like post order then pre order to
calculate this ( note like backtack into node set visited = true, leaving set visited = false), but think about below case from x, when doing preorder, if you try to
go though the flow with below case, you would find we end up use some overlap path and
migth be hard to detect it

|
|
|
|-x--|
|    |
|----y
     |
     |
     |

*/

// below is from discussin thread
// int helper(vector<vector<int>>& matrix, vector<vector<bool>>& visited, int row, int col, int& res) {
//   int m = matrix.size(), n = matrix[0].size();
//   if (row < 0 || row >= m || col < 0 || col >= n || matrix[row][col] == 0 || visited[row][col]) return 0;
//   visited[row][col] = true;
//   int left = helper(matrix, visited, row, col - 1, res);
//   int right = helper(matrix, visited, row, col + 1, res);
//   int up = helper(matrix, visited, row - 1, col, res);
//   int down = helper(matrix, visited, row + 1, col, res);
//   vector<int> tmp = {left, right, up, down};
//   sort(tmp.begin(), tmp.end());
//   res = max(res, matrix[row][col] + tmp[3] + tmp[2]); // get the largest two directions
//   return matrix[row][col] + tmp[3];
// }

// int maxPath(vector<vector<int>>& matrix) {
//   int m = matrix.size(), n = matrix[0].size();
//   vector<vector<int>> connectedRegion(m, vector<int>(n, 0));
//   vector<vector<bool>> visited(m, vector<bool>(n, false));
//   int res = 0; // does not need to consider negative value
//   for (int i = 0; i < m; ++i) {
//     for (int j = 0; j < n; ++j) {
//       if (matrix[i][j] != 0 && !visited[i][j]) {
//         helper(matrix, visited, i, j, res);
//       }
//     }
//   }

//   return res;
// }

int dfs(int i, int j, vector<vector<int>> &grid, vector<vector<int>> &visited, int &ans) {
  int m = grid.size();
  int n = grid[0].size();
  int d[5] = {-1,0,1,0,-1};
  if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0 || visited[i][j]) {
    return 0;
  }
  visited[i][j] = true;
  vector<int> paths;
  for (int k = 0; k < 4; k++) {
    int x = i + d[k];
    int y = j + d[k+1];
    paths.push_back(dfs(x, y, grid, visited, ans));
  }
  sort(paths.begin(), paths.end());
  ans = max(ans, paths[2] + paths[3] + grid[i][j]);
  return paths[3] + grid[i][j];
}

int maxPath(vector<vector<int>> &grid) {
  int m = grid.size();
  int n = grid[0].size();
  int ans = 0;
  vector<vector<int>> visited(m, vector<int>(n, false));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 0) {
        continue;
      }
      dfs(i, j , grid, visited, ans);
    }
  }
  return ans;
}

int main(){
  vector<vector<int>> test1 = {
    {5,4,1,3},
    {1,0,1,0},
    {3,0,0,4},
    {0,1,2,0},
  };
  assert(maxPath(test1) == 17);
  printf("pass!\n");
  vector<vector<int>> test2 = {
    {5,4,1,0},
    {1,0,1,2},
    {3,0,0,4},
    {0,1,2,0}
  };
  assert(maxPath(test2) == 21);
  printf("pass!\n");
  return 0;
}
