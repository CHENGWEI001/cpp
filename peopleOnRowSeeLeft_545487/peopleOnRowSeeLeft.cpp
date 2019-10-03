#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

// https://www.1point3acres.com/bbs/thread-545487-1-1.html

/*
N个人站一列，每个人是一个int代表高度。A代表任意一个人，B在A前面。如果AB之间没有比B高的，那么定义A能看到B。
让输出列最后那个人能看到的人数。
public int count(int[] people)

[3,6,2,5] : 2

[3,6,2,5] : 2
   ^

currMax = 6
i = 0
ans = 2
followup1: 定义A能够看到B为，AB之间没有比A高也没有比B高的。输出全部人各能看到几个人。public int[] count(int[] people)
followup2: 如果列中每个人的高度都不同，怎么处理。
followup3: 如果有很多人，但是他们身高都差不多，怎么处理。

*/
int count(vector<int> &h) {
    int currMax = -1;
    int n = h.size();
    int ans = 0;
    for (int i = n-2; i >= 0; i--) {
        if (h[i] >= currMax) {
            ans++;
        }
        currMax = max(currMax, h[i]);
    }
    return ans;
}

/*
followup1: 定义A能够看到B为，AB之间没有比A高也没有比B高的。
输出全部人各能看到几个人。public int[] count(int[] people)
( assume we are looking for look right and left # of people this
person can see )
( also I think problem might need to clarify a bit ,
because "AB之间没有比A高也没有比B高的", if follow this rule,
5 5 3
B   A
B can't see A
A can't see B ( due to middle 5 high than A)

to follow the rule, we need to look at stack until st end or
see item > curr height, to know how many people previous can be seen
by current peroson. then pop as long as st.back() < currH

But this way worst case is O(n^2), like below case:
5 5 5 5 , at i = 3, st = [5,5,5] , we look all item in st,
and didn't pop any thing from st

我也觉得不对，比2高的只能算一个，另外一个被挡住了。我觉得follow up 1 比 2 难一些，非常诡异。
都要用单调栈
followup 1: 相等不踢掉，可是如果有来一个相等的，就要算有多少个相等的，全算进去，如果前面还有大的，要加1；更快的就要记住所有的栈里的重复的次数，相同就踢掉，只保留一个。
followup 2: 没有重复即直接pop，计数，如果结束还有，加1，没有就不加

*/

vector<int> count2(vector<int> &h) {
    int n = h.size();
    vector<int> ans(n, 0);
    vector<int> st;
    // first calculate look toward left
    for (int i = 0; i < n; i++) {
        ans[i] += st.size();
        while (st.size() && st.back() < h[i]) {
            st.pop_back();
        }
        st.push_back(h[i]);
    }
    // second calculate look toward right
    st.clear();
    for (int i = n-1; i >= 0; i--) {
        ans[i] += st.size();
        while (st.size() && st.back() < h[i]) {
            st.pop_back();
        }
        st.push_back(h[i]);
    }
    return ans;
}

/*
[7,4,2] : 2 , for 7 , no one higher than 7 in the middle , so can see 7

[8,8,7, 9] : 3

[3,6,2,5] : 2
*/

int test1(vector<int> &arr) {
    return count(arr);
}

/*

[3,6,2,5] : [1, ]
*/

int test2(vector<int> &arr) {
}

int main() {
    vector<pair<vector<int>, int>> tests = {
        {{7,4,2}, {2}},
        {{8,8,7,9}, {3}},
        {{3,6,2,5}, {2}},
    };
    for (int i = 0; i < tests.size(); i++) {
        auto &t = tests[i];
        int res = test1(t.first);
        printf("res:%d, exp:%d\n", res, t.second);
    }
    return 0;
}