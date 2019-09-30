#include <vector>
#include <stdio.h>
#include  <algorithm>

using namespace std;

// https://leetcode.com/discuss/interview-question/350800
// gg 552886

/*
Input: chocolate = [6, 3, 2, 8, 7, 5], k = 3
Output: 9
Explanation:
The values in array are sweetness level in each chunk of chocolate. Since k = 3, so you have to divide this array in 3 pieces,
such that you would get maximum out of the minimum sweetness level. So, you should divide this array in
[6, 3] -> 6 + 3 = 9
[2, 8] -> 2 + 8 = 10
[7, 5] -> 7 + 5 = 12
Your other two friends will take the sweetest chunk, so they will take 12 and 10. The maximum sweetness level you could get is 9.
*/

int getMin(vector<int> &arr) {
    int minVal = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        minVal = min(minVal, arr[i]);
    }
    return minVal;
}

int getSum(vector<int> &arr) {
    int ans = 0;
    for (int n: arr) {
        ans += n;
    }
    return ans;
}

int count(vector<int> &arr, int tgt) {
    int curr = 0;
    int ans = 0;
    for (int n: arr) {
        curr += n;
        if (curr >= tgt) {
            curr = 0;
            ans++;
        }
    }
    return ans;
}

// using binary search
int maxminsweetV1(vector<int> &sweets, int k) {
    int lo = getMin(sweets);
    int hi = getSum(sweets);
    while (lo + 1 < hi) {
        int mi = lo + (hi - lo)/2;
        int numg = count(sweets, mi);
        if (numg >= k) {
            lo = mi;
        } else {
            hi = mi;
        }
    }
    if (count(sweets, hi) >= k) {
        return hi;
    } else if (count(sweets, lo) >= k)  {
        return lo;
    }
    return -1; // ex: total 3 sweets , but k = 5
}

// using DP kN^2
int maxminsweetV2(vector<int> &sweets, int k) {
    int n = sweets.size();
    vector<vector<int>> dp(k+1, vector<int>(n+1, 0));
    vector<int> pre({0});

/*
         [6, 3, 2, 8, 7, 5]

pre =   [0, 6, 9, 11, 19, 26, 31 ]
dp[1] = [0, 6, 9, 11, 19, 26, 31 ]
dp[2] =  0  0  3  5
               ^
*/
    for (int i = 0; i < sweets.size(); i++) {
        pre[i+1] = pre[i] + sweets[i];
        dp[1][i+1] = pre[i+1];
    }

    for (int i = 2; i <= k; i++) {
        for (int j = i; j <= n; j++) {
            // j = 3, i = 2
            for (int t = i-1; t < j; t++) {
                // t = 1,
                // min(dp[1][1], p[3] - p[1])
                dp[i][j] = max(dp[i][j], min(dp[i-1][t], pre[j] - pre[t]));
            }
        }
    }
    return dp[k][n];
}


// using DP kN
int maxminsweetV3(vector<int> &sweets, int k) {
    int n = sweets.size();
    vector<vector<int>> dp(k+1, vector<int>(n+1, 0));
    vector<int> pre({0});
    vector<vector<int>> pi(k+1, vector<int>(n+1, 0));

/*
         [6, 3, 2, 8, 7, 5]

pre =   [0, 6, 9, 11, 19, 26, 31 ]
dp[1] = [0, 6, 9, 11, 19, 26, 31 ]
                  ^
dp[2] =  0  0  3  5  8
                     ^
*/
    for (int i = 0; i < sweets.size(); i++) {
        pre[i+1] = pre[i] + sweets[i];
        dp[1][i+1] = pre[i+1];
    }

    for (int i = 2; i <= k; i++) {
        int t = i-1;
        for (int j = i; j <= n; j++) {
            // i = 2, j = 4
            // t = 3
            // 11 < 8
            while (t < j - 1 && dp[i-1][t] < pre[j] - pre[t]) {
                t++;
            }
            // dp [2][4] = 8
            // t = 3
            // min (11,8)
            // min(9, 10) = 9
            dp[i][j] = min(dp[i-1][t], pre[j] - pre[t]);
            pi[i][j] = t;
            if (t-1 >= i-1) {
                dp[i][j] = max(dp[i][j], min(dp[i-1][t-1], pre[j] - pre[t-1]));
                if (dp[i][j] == min(dp[i-1][t-1], pre[j] - pre[t-1])) {
                    pi[i][j] = t-1;
                }
            }
        }
    }
    int i = k;
    int j = n;
    vector<int> path;
    while (j != 0) {
        path.push_back(j - pi[i][j]);
        j = pi[i][j];
        i--;
    }
    reverse(path.begin(), path.end());
    for (int n: path) {
        printf("%d, ", n);
    }
    printf("\n");

    return dp[k][n];
}


void test1() {
    // vector<int> sweets({6, 3, 2, 8, 7, 5});
    // int k = 3;
    vector<int> sweets({6, 3, 2, 8});
    int k = 3;
    int maxmin = maxminsweetV3(sweets, k);
    printf("maxmin:%d\n", maxmin);
}

int main() {
    test1();
    return 0;
}