#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

/*
A = [0,4,8,16]
B = [0,2,6,12,14,20]

*/

vector<int> ansPath;

void dfs(int ia, int ib, vector<int> &A, vector<int> &B, int numB, int &ans, vector<int> &path) {
    if (ia == A.size()) {
        ans = max(ans, numB);
        if (ans == numB) {
            ansPath = path;
        }
    }
    int n = path.size();
    // to push A[ia] into path
    if (ia < A.size() && (path.size() < 2 || path[n-1] - path[n-2] == A[ia] - path[n-1])) {
        path.push_back(A[ia]);
        dfs(ia+1, ib, A, B, numB, ans, path);
        path.pop_back();
    }

    // to push B into path
    for (int i = ib; i < B.size(); i++) {
        if (path.size() < 2 || path[n-1] - path[n-2] == B[i] - path[n-1]) {
            path.push_back(B[i]);
            dfs(ia, i+1, A, B, numB+1, ans, path);
            path.pop_back();
        }
    }
}

void test() {
    vector<int> A({0,4,8,16});
    vector<int> B({0,2,6,12,14,20});
    vector<int> path;
    int ans = 0;
    dfs(0, 0, A, B, 0, ans, path);
    printf("ans:%d\n", ans);
    for (int v: ansPath) {
        printf("%d, ", v);
    }
    printf("\n");
}

int main() {
    test();
    return 0;
}