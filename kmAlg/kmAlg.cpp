// https://blog.csdn.net/Hemk340200600/article/details/63792088

#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <assert.h>

using namespace std;

#define M 3
#define N 3

int w[M][N] = {
    {4, 3, 0},
    {4, 2, 1},
    {0, 0, 1},
};


// initially cx[x] equal max of w[x][j] | j = 0 .. N-1
void initcx(vector<int> &cx) {
    for (int x = 0; x < M; x++) {
        for (int y = 0; y < N; y++) {
            cx[x] = max(cx[x], w[x][y]);
            // printf("cx[%d]:%d\n", x, cx[x]);
        }
    }
}

bool find(int x, vector<int> &usedx, vector<int> &usedy, vector<int> &cx, vector<int> &cy, vector<int> &link) {
    usedx[x] = 1;
    for (int y = 0; y < N; y++) {
        if (usedy[y] || w[x][y] != cx[x] + cy[y]) {
            continue;
        }
        usedy[y] = 1;
        if (link[y] == -1 || find(link[y], usedx, usedy, cx, cy, link)) {
            link[y] = x;
            return true;
        }
    }
    return false;
}

int KM(vector<int> &link) {
    vector<int> usedx(M, 0);
    vector<int> usedy(N, 0);
    vector<int> cx(M, 0);
    vector<int> cy(N, 0);

    initcx(cx);

    for (int x = 0; x < M; x++) {
        printf("start x:%d\n", x);
        int r = 0;
        while (true) {
            printf("round:%d for x:%d\n", r, x);
            usedx.resize(M, 0);
            usedy.resize(N, 0);
            // for given x , if we can find pair with best score for cx[x], we move forward
            if (find(x, usedx, usedy, cx, cy, link)) {
                printf("complete for x:%d\n\n", x);
                break;
            }
            // if we can't find best pair for x, we need to relax path
            // for all visited x with all non visited y
            // basically try to find the next score that is cloest to current pair score
            int d = -1;
            for (int i = 0; i < M; i++) {
                if (usedx[i]) {
                    for (int j = 0; j < N; j++) {
                        if (!usedy[j]) {
                            // since we start from best pair score , cx[i] + cy[j] is always bigger than w[i][j]
                            int tmp = cx[i] + cy[j] - w[i][j];
                            printf("i:%d, j:%d, cx:%d, cy:%d, w:%d\n", i, j, cx[i], cy[j], w[i][j]);
                            // need to skip case when diff is 0 , this case might hit forever loop
                            if (tmp == 0) {
                                continue;
                            }
                            // we don't exp tmp < 0
                            assert(tmp >= 0);
                            if (d == -1 || d > tmp) {
                                d = tmp;
                            }
                        }
                    }
                }
            }
            printf("d is :%d\n", d);
            if (d == -1) {
                return -1;
            }
            // cx[i] -= d is to relax x
            for (int i = 0; i < M; i++) {
                if (usedx[i]) {
                    cx[i] -= d;
                }
            }
            // cy[j] += d is to maintain the balance to make previous matching pair still be able to
            // be choosen after adjusting the cx and cy
            for (int j = 0; j < N; j++) {
                if (usedy[j]) {
                    cy[j] += d;
                }
            }
        }
    }
    int ans = 0;
    for (int y = 0; y < N; y++) {
        // if (link[y] == -1) {
        //     return -1;
        // }
        ans += w[link[y]][y];
    }
    return ans;
}

int main() {
    vector<int> link(N, -1);
    int ans = KM(link);
    printf("ans:%d\n", ans);
}