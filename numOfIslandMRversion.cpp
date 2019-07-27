class UnionSet {
private:
    vector<int> father;
public:
    UnionSet() {
    }
    
    void resize(int n) {
        father.resize(n);
        for (int i = 0; i < n; i++) {
            father[i] = i;
        }        
    }
    int find(int id) {
        if (father[id] != id) {
            father[id] = find(father[id]);
        }
        return father[id];
    }
    
    void connect(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA != rootB) {
            father[rootA] = rootB;
        }
    }
};

class Solution {
public:
    typedef vector<vector<char>> PartitionGrid;
    // typedef vector<int> Father;
    typedef vector<int> PartitionRange;
    
    int numIslands(vector<vector<char>>& grid) {
        if (!grid.size() || !grid[0].size()) {
            return 0;
        }
        return scheduler(grid, 4);
    }
    
    PartitionGrid getPartitionGrid(PartitionRange &range, vector<vector<char>> &grid) {
        int startRowIdx = range[0];
        int endRowIdx = range[1];
        int startColIdx = range[2];
        int endColIdx = range[3];
        int m = endRowIdx - startRowIdx + 1;
        int n = endColIdx - startColIdx + 1;
        PartitionGrid pg = vector<vector<char>>(m, vector<char>(n, '0'));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                pg[i][j] = grid[i + startRowIdx][j + startColIdx];
            }
        }
        return pg;
    }
    
    void printGrid(vector<vector<char>> &grid) {
        int m = grid.size();
        int n = grid[0].size();
        // cout << m << "," << n << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    int checkRowBoundary(PartitionGrid &topGrid, PartitionGrid &bottomGrid, UnionSet &bottomUset, unordered_set<int> &visitedSet) {
        int mt = topGrid.size();
        int nt = topGrid[0].size();
        int mb = bottomGrid.size();
        int nb = bottomGrid[0].size();
        assert(nt == nb);
        int cnt = 0;
        for (int j = 0; j < nt; j++) {
            int rootId = bottomUset.find(0*nb+j);
            if (bottomGrid[0][j] == '0' || visitedSet.count(rootId) || topGrid[mt-1][j] == '0') {
                continue;
            }
            visitedSet.insert(rootId);
            cnt++;
        }
        return cnt;
    }

    int checkColBoundary(PartitionGrid &leftGrid, PartitionGrid &rightGrid, UnionSet &rightUset, unordered_set<int> &visitedSet) {
        int ml = leftGrid.size();
        int nl = leftGrid[0].size();
        int mr = rightGrid.size();
        int nr = rightGrid[0].size();
        assert(ml == mr);
        int cnt = 0;
        for (int i = 0; i < ml; i++) {
            int rootId = rightUset.find(i*nr+0);
            if (rightGrid[i][0] == '0' || visitedSet.count(rootId) || leftGrid[i][nl-1] == '0') {
                continue;
            }
            visitedSet.insert(rootId);
            cnt++;
        }
        return cnt;
    }    
    
    int reducer(vector<vector<PartitionGrid>> &superGrid, vector<vector<int>> &gridRes, vector<vector<UnionSet>> &gridUset) {
        int m = superGrid.size();
        int n = superGrid[0].size();
        int dir[] = {-1, 0, -1};
        int ans = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int numIsland = gridRes[i][j];     
                // visitedSet keep track the rootId that has been taken out
                // so later if we check another boundary ndoe connected with
                // this rootId, it will be skip, note visitedSet need to be 
                // use across checking row and col in case top and left boundary
                // are connected
                unordered_set<int> visitedSet;
                for (int k = 0; k < 2; k++) {
                    int x = i + dir[k];
                    int y = j + dir[k+1];
                    int additional = 0;
                    if (x < 0 || x >= m || y < 0 || y >= n) {
                        continue;
                    }
                    if (k == 0) {
                        additional = checkRowBoundary(superGrid[x][y], superGrid[i][j], gridUset[i][j], visitedSet);
                    } else {
                        additional = checkColBoundary(superGrid[x][y], superGrid[i][j], gridUset[i][j], visitedSet);
                    }
                    numIsland -= additional;
                }
                printf("reducer: i:%d, j:%d , numIsland:%d\n", i, j, numIsland);
                ans += numIsland;
            }
        }
        return ans;
    }
    
    void mapper(PartitionGrid &grid, UnionSet &uset,int &numIsland) {
        int m = grid.size();
        int n = grid[0].size();
        uset.resize(m*n);
        numIsland = 0;
        int dir[] = {-1, 0, -1};
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '0') {
                    continue;
                }
                numIsland++;
                for (int k = 0; k < 2; k++) {
                    int x = i + dir[k];
                    int y = j + dir[k+1];
                    if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != '1') {
                        continue;
                    }
                    if (uset.find(i*n+j) != uset.find(x*n+y)) {
                        numIsland--;
                        uset.connect(i*n+j, x*n+y);
                    }
                }
            }
        }
    }
    
    void makePartitionLen(vector<int> &partitionLen, int totalLen, int numParition) {
        int len = totalLen/(numParition);
        int remain = totalLen%numParition;
        for (int i = 0; i < numParition; i++) {
            int currLen = len;
            if (remain > 0) {
                currLen++;
                remain--;
            }
            partitionLen[i] = currLen;
            // printf("p[%d]:%d ", i, partitionLen[i]);
        }
        // printf("\n");
    }
    
    int scheduler(vector<vector<char>> &grid, int numMapper) {
        int gNumRows = grid.size();
        int gNumCols = grid[0].size();
        numMapper = min(numMapper, gNumRows * gNumCols);
        // cout << numMapper << endl;
        int numPartitionPerRow;
        int numPartitionPerCol;
        getNumPartionPerRowPerCol(gNumRows, gNumCols, numMapper, numPartitionPerRow, numPartitionPerCol);
        vector<int> rowPartitionLen(numPartitionPerRow, 0);
        vector<int> colPartitionLen(numPartitionPerCol, 0);
        // int partitionSizeRow = (gNumRows + numPartitionPerRow - 1)/numPartitionPerRow;
        // int partitionSizeCol = (gNumCols + numPartitionPerCol - 1)/numPartitionPerCol;
        makePartitionLen(rowPartitionLen, gNumRows, numPartitionPerRow);
        makePartitionLen(colPartitionLen, gNumCols, numPartitionPerCol);
        // printf("partitionInfo: (%d,%d)\n", numPartitionPerRow, numPartitionPerCol);
        vector<vector<PartitionGrid>> superGrid(numPartitionPerRow, vector<PartitionGrid>(numPartitionPerCol));
        vector<vector<UnionSet>> superUset(numPartitionPerRow, vector<UnionSet>(numPartitionPerCol));
        vector<vector<int>> superCnt(numPartitionPerRow, vector<int>(numPartitionPerCol, 0));
        for (int i = 0, rowIdx = 0; i < numPartitionPerRow; rowIdx += rowPartitionLen[i], i++) {
            for (int j = 0, colIdx = 0; j < numPartitionPerCol; colIdx += colPartitionLen[j], j++) {
                PartitionRange range(4, 0);
                range[0] = rowIdx; // startRowIdx
                range[1] = rowIdx + rowPartitionLen[i] - 1;
                range[2] = colIdx; // startColIdx
                range[3] = colIdx + colPartitionLen[j] - 1; // endColIdx
                // printf("(%d,%d,%d,%d)\n", range[0], range[1], range[2], range[3]);
                superGrid[i][j] = getPartitionGrid(range, grid);
                printGrid(superGrid[i][j]);
                mapper(superGrid[i][j], superUset[i][j], superCnt[i][j]);
                printf("cnt[%d][%d]:%d\n\n", i, j, superCnt[i][j]);
            }
        }
        return reducer(superGrid, superCnt, superUset);
        // return 0;
    }
    
    void getNumPartionPerRowPerCol(int m, int n, int numMapper, int &numPartitionPerRow, int &numPartitionPerCol) {
        int cand = 1;
        for (int i = 1; i*i <= numMapper; i++) {
            // printf("i:%d, numMapper:%d\n", i, numMapper);
            if (numMapper % i == 0 && m >= i && n >= numMapper/i) {
                cand = i;
            } 
            if (numMapper % i == 0 && n >= i && m >= numMapper/i) {
                cand = numMapper/i;
            }             
        }
        numPartitionPerRow = cand;
        numPartitionPerCol = numMapper/cand;
    }
    
};
