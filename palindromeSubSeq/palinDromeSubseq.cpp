#include <vector>
#include <stdio.h>
#include <string>
#include <unordered_set>

using namespace std;

/*
abda

l = 1
-------------
i = 0
j = 0
dp [0][0] : a
dp [1][1] : b
dp [2][2] : d
dp [3][3] : a


l = 2
------------
dp[0][1]  = a, b
dp[1][2] = b, d
dp[2][3] = d, a

l = 3
------------
dp[0][2] = a, b, b, d
dp[1][3] =

l = 4
----------
dp[0][3] =

abda
*/

void insert(unordered_set<string> &dst, unordered_set<string> &src) {
    for (const string &s: src) {
        dst.insert(s);
    }
}

vector<string> palinSubseq(string &s) {
    int n = s.size();
    vector<vector<unordered_set<string>>> dp(n, vector<unordered_set<string>>(n));
    vector<string> ans;
    for (int l = 1; l <= n; l++) {
        // printf("l:%d, n:%d\n", l, n);
        for (int i = 0; i + l - 1 < n; i++) {
            int j = i + l - 1;
            // printf("i:%d, j:%d, l:%d, n:%d\n", i, j, l, n);
            if (l == 1) {
                dp[i][j].insert(s.substr(i,1));
            } else if (l == 2) {
                insert(dp[i][j], dp[i+1][j]);
                insert(dp[i][j], dp[i][j-1]);
                if (s[i] == s[j]) {
                    dp[i][j].insert(s.substr(i, 2));
                    printf("%s\n", s.substr(i,2).c_str());
                }
            } else {
                insert(dp[i][j], dp[i+1][j]);
                insert(dp[i][j], dp[i][j-1]);
                if (s[i] == s[j]) {
                    for (const string &subs: dp[i+1][j-1]) {
                        dp[i][j].insert(string(1, s[i]) + subs + string(1, s[j]));
                    }
                    dp[i][j].insert(string(1, s[i]) + "" + string(1, s[j]));
                }
            }
            // printf("size:%d\n", dp[i][j].size());
        }

    }
    for (const string &s: dp[0][n-1]) {
        ans.push_back(s);
    }
    return ans;
}



int main() {
    string input("abcb");
    auto ans = palinSubseq(input);
    for (string &s: ans) {
        printf("%s\n", s.c_str());
    }
    return 0;
}