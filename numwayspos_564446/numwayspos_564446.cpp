#include <stdio.h>
#include <vector>

using namespace std;

int numWays(int K) {
    vector<vector<int>> dp(K+1, vector<int>(K+1, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= K; i++) {
        for (int j = 0; j <= K; j++) {
            dp[i][j] += dp[i-1][j];
            if (j - i >= 0) {
                dp[i][j] += dp[i][j-i]; // since the value can take multiple times, we look at dp[i][j-i]
            }
        }
    }
    return dp[K][K];
}

void test() {
    int k = 5;
    int ans = numWays(k);
    printf("K = %d, ans = %d\n", k, ans);
}

int main() {
    test();
    return 0;
}