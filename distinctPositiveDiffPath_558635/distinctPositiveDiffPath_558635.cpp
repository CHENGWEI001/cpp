/*
题目很简单。 给两个input : [17 , 3]  , 计算他们的positive difference, 现在数组是[17 , 3 , 17] , 然后再向数组里添加一个不存在的positive diff ， until no non-exist difference can be added。 枚举所有可能的path

比如我举得这个例子:
[17 , 3] -> [17 , 3 , 14] -> [17 , 3 , 14 , 11 ] ->[17 , 3 , 14 , 11 , 8] -> [17 , 3 , 14 , 11 , 8 , 6 ] -> [17 , 3 , 14 , 11 , 8 , 6 , 2] - > [17 , 3 , 14 , 11 , 8 , 6 , 2 , 4] -> .....
[17 , 3] -> [17 , 3 , 14] -> [17 , 3 , 14 , 11 ] ->[17 , 3 , 14 , 11 , 8] -> [17 , 3 , 14 , 11 , 8 , 5] -> [17 , 3 , 14 , 11 , 8 , 5 , 9] - > [17 , 3 , 14 , 11 , 8 , 5 , 9 , 6] -> .....
...
...
*/

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <unordered_set>

using namespace std;

/*


newCands = [,6, 8]
path = [17,3,14,11]
vis[17,3,14,11]

cand = 11
Cands = [11]
path = [17,3,14]
vis[17,3,14]
---------------------
cand = 14
newCands = [11]
path = [17,3,14]
vis[17,3,14]

initpath [17 , 3]
cands = [14]
vis[17,3]
*/

// caller responsible to push back new value to end of path
// and update all cands with this new value
// use path.size() >= 7 is just to trim result to no more than 7
void helper(vector<int> &path, unordered_set<int> &cands, unordered_set<int> &vis, vector<vector<int>> &ans) {
    if (!cands.size() || path.size() >= 7) {
        ans.push_back(path);
        return;
    }
    for (int cand: cands) {
        unordered_set<int> newCands = cands;
        for (int v: path) {
            int d = abs(v - cand);
            if (newCands.count(d) || vis.count(d)) {
                continue;
            }
            newCands.insert(d);
        }
        newCands.erase(cand);
        path.push_back(cand);
        vis.insert(cand);
        helper(path, newCands, vis, ans);
        vis.erase(cand);
        path.pop_back();
    }
}



vector<vector<int>> distinctPositiveDiffPath(vector<int> &initpath) {
    vector<vector<int>> ans;
    unordered_set<int> vis;
    unordered_set<int> cands;
    if (initpath.size() < 2) {
        return {initpath};
    }
    vis.insert(initpath[0]);
    vis.insert(initpath[1]);
    int d = abs(initpath[0] - initpath[1]);
    if (!vis.count(d)) {
        cands.insert(d);
    }
    helper(initpath, cands, vis, ans);
    return ans;
}

void test(vector<int> &testcase) {
    auto res = distinctPositiveDiffPath(testcase);
    for (auto &r: res) {
        for (int v: r) {
            printf("%d, ", v);
        }
        printf("\n");
    }
}

int main() {
    vector<vector<int>> testcases = {
        {17,3},
    };
    test(testcases[0]);
    return 0;
}