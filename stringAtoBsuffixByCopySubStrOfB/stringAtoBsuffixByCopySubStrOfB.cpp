#include <vector>
#include <unordered_map>
#include <stdio.h>
#include <string>

using namespace std;


/*
    example :
    A = abcd
    B = deabc
    since "abc"d is matching B's de"abc" , so return 3
 */
int getNumPrefix(string &A, string &B) {
    int m = A.size();
    int n = B.size();
    if (m > n) {
        return 0;
    }
    vector<int> next(m+1);
    next[0] = -1;
    int j = -1;
    for (int i = 0; i < m; i++) {
        while (j >= 0 && A[j] != A[i]) {
            j = next[j];
        }
        j++;
        next[i+1] = j;
    }
    j = 0;
    for (int i = n - m; i < n; i++) {
        while (j >= 0 && A[j] != B[i]) {
            j = next[j];
        }
        j++;
    }
    return j;
}

/*
    example:
    A = "abcd"
    B = "dbcfda"
    1. since a is in A, we just need to make bcd to the end of B
    2. copy bc from B to the end
    3. copy d from B to the end
    4. total 2 copy
*/

int strAtoBSuffix(string &A, string &B) {
    // first to find longest prefix of A in B's suffix, so we know what is the str need to make
    // at the end of B
    // second do dp[i][j] : len of matching chars end at A[i] and B[j], note A here is after cut common prefix
    // also need hmap[i]: min copy need up to A[i]
    int np = getNumPrefix(A, B);
    A = A.substr(np);
    unordered_map<int, int> hmap;
    int m = A.size();
    int n = B.size();
    vector<int> pi(m, 0);
    vector<vector<int>> dp(m+1, vector<int> (n+1, 0));
    // dp[i][j] = A[i-1] == B[j-1]? dp[i-1][j-1] + 1: 0
    hmap[-1] = 0;
    for (int i = 0; i < m; i++) {
        hmap[i] = -1;
        for (int j = 0; j < n; j++) {
            if (A[i] == B[j]) {
                dp[i+1][j+1] = 1 + dp[i][j];
                if (hmap[i] == -1 || hmap[i] > 1 + hmap[i - dp[i+1][j+1]]) {
                    hmap[i] = 1 + hmap[i - dp[i+1][j+1]];
                    pi[i] = j;
                    // printf("pi[%d]:%d, dp[%d][%d]:%d\n", i, pi[i], i+1, j+1, dp[i+1][j+1]);
                }
            }
        }
    }
    int idx = m-1;
    while (idx != -1) {
        // int x = idx;
        // int y = pi[x];
        int len = dp[idx+1][pi[idx]+1];
        printf("idx:%d, copy %s\n", idx, B.substr(pi[idx] - len + 1, len).c_str());
        idx = idx - dp[idx+1][pi[idx]+1];

    }
    return hmap[m-1];
}

void test(string &A, string &B, int expRes) {
    int res;
    printf("testing A:%s, B:%s\n", A.c_str(), B.c_str());
    if ((res = strAtoBSuffix(A, B)) == expRes) {
        printf("PASS! res:%d\n", res);
    } else {
        printf("FAIL! res:%d\n", res);
    }
}

int main() {
    string A;
    string B;
    int res;
    A = "abcd";
    B = "dbcfda";
    res = 2;
    test(A, B, res);

    A = "dbfa";
    B = "dbcfdab";
    res = 3;
    test(A, B, res);

    A = "dbfadbcfaa";
    B = "dbcfdab";
    res = 6;
    test(A, B, res);
    return 0;
}
