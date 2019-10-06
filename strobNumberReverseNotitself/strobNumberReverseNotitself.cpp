#include <vector>
#include <string>
#include <stdio.h>
#include <utility>
#include <unordered_map>

// https://www.1point3acres.com/bbs/thread-552910-1-1.html
// refer to https://leetcode.com/problems/confusing-number-ii/ for correct implementation

using namespace std;

string digits = "01689";
unordered_map<char, char> stroMap = {
    {'0', '0'},
    {'1', '1'},
    {'6', '9'},
    {'8', '8'},
    {'9', '6'},
};

bool stroSym(string &val) {
    int l = 0;
    int r = val.size()-1;
    while (l <= r) {
        char lc = val[l];
        char rc = val[r];
        if (lc != stroMap[rc]) {
            return false;
        }
        l++;
        r--;
    }
    return true;
}

void helper(string path, string low, string high, vector<string> &ans) {
    if (path.size() > high.size()) {
        return;
    }
    if (path.size() > 1 && path[0] == '0') {
        return;
    }
    if (path.size() >= low.size() && path.size() <= high.size()) {
        if ((path.size() == low.size() && path >= low || path.size() == high.size() && path <= high || path.size() > low.size() && path.size() < high.size()) && !stroSym(path)) {
            ans.push_back(path);
        }
    }
    for (char c: digits) {
        helper(string(1, c) + path, low, high , ans);
    }
}

vector<string> strobNumberReverseNotitself(string low, string high) {
    vector<string> ans;
    helper("", low, high, ans);
    return ans;
}

int main() {
    auto ans = strobNumberReverseNotitself("0", "535");
    for (string &s: ans) {
        printf("%s\n", s.c_str());
    }
    return 0;
}
