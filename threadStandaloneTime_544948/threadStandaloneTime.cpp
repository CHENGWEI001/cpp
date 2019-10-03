#include <vector>
#include <stdio.h>
#include <unordered_set>
#include <algorithm>

using namespace std;

/*
|----|t0   |-------------|t0
1    3     5            10
   |----|t1
   2    4
             |-----|t2
             6     8

{0, 1, 3}
{1, 2, 4}
{0, 5, 10}
{2, 6, 8}

exp :
t0 : 1->2, 5->6, 8->10 : 4
t1 : 3->4 : 1
t2 : 0

*/

// gg 544948

/*
[0] : tid
[1] : start
[2] : end
*/

struct Ele {
    int tid;
    int etype; // 0 : start, 1 : end
    int t;
};

bool operator < (const Ele &a, const Ele &b) {
    return a.t < b.t;
}

void flush(vector<int> &ans, int tid, int start, int end) {
    ans[tid] += end - start;
}

/*
{0, 1, 3}
{1, 2, 4}
{0, 5, 10}
{2, 6, 8}

[{}]

tset = [0,1,2]

tline = [
{0, 0, 1},
{1, 0, 2},
{0, 1, 3},
{1, 1, 4},
{0, 0, 5},
{2, 0, 6},
{2, 1, 8},
{0, 1, 10}, -
]

i = 7  , flush(0, 8, 10)
cnt = 1
startTid = 0
start = 8
ans = [4,1,0]

*/

vector<int> threadStandAloneTime(vector<vector<int>> &intervals) {
    vector<Ele> tline;
    unordered_set<int> tidSet;
    for (auto &i: intervals) {
        tline.push_back({i[0], 0, i[1]});
        tline.push_back({i[0], 1, i[2]});
        tidSet.insert(i[0]); // assume tid start from 0 .. n-1
    }
    sort(tline.begin(), tline.end());
    int cnt = 0;
    int n = tidSet.size();
    int start = 0;
    int startTid = -1;
    vector<int> ans(n);
    for (auto &e: tline) {
        if (e.etype == 0) {
            // when see start event, if cnt == 0 , it is indicating
            // a possible start time for standalone interval
            if (cnt == 0) {
                startTid = e.tid;
                start = e.t;
            }
            // when see start even , if cnt == 1, that means
            // leaving a standalone event
            if (cnt == 1) {
                flush(ans, startTid, start, e.t);
            }
            cnt++;
        } else {
            // when see end event, if cnt == 2, means
            // a possible start of a standalone interval
            if (cnt == 2) {
                // starTid = e.tid; // end event don't care the e.tid
                start = e.t;
            }
            // if cnt == 2 , means end of a standalone interval
            if (cnt == 1) {
                flush(ans, e.tid, start, e.t);
            }
            cnt--;
        }
    }
    return ans;
}

void test(vector<vector<int>> &intervals) {
    auto res = threadStandAloneTime(intervals);
    for (int i = 0; i < res.size(); i++) {
        printf("res[%d]:%d\n", i, res[i]);
    }

}

int main() {
    vector<vector<int>> testvec = {
        {0, 1, 3},
        {1, 2, 4},
        {0, 5, 10},
        {2, 6, 8},
    };
    test(testvec);
    return 0;
}