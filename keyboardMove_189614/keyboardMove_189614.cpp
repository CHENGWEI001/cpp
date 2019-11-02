#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <unordered_map>

/*
https://www.1point3acres.com/bbs/forum.php?mod=viewthread&tid=189614&highlight=embe
a b c d e f g h
i j k l m n o p
q r s t u v w x
y z
*/


using namespace std;

void move(vector<int> &start, vector<int> &end, vector<char> &ans) {
    char hor = 'r';
    char ver = 'd';
    if (end[1] < start[1]) {
        hor = 'l';
    }
    if (end[0] < start[0]) {
        ver = 'u';
    }
    for (int i = 1; i >= 0; i--) {
        for (int j = 0; j < abs(end[i] - start[i]); j++) {
            char c = i == 1? hor: ver;
            ans.push_back(c);
        }
    }
}

void makeKeyMap(unordered_map<char, vector<int>> &keyMap) {
    for (int i = 0; i < 26; i++) {
        keyMap[i+'a'] = {i/8, i%8};
    }
}

vector<char> keyBoardMove(string &in, vector<int> &start) {
    unordered_map<char, vector<int>> keyMap;
    vector<char> ans;
    makeKeyMap(keyMap);
    auto curr = start;
    for (char c: in) {
        auto next = keyMap[c];
        // in general we go horizontal to same col, then go vertical to same row
        // but in case when start is at row3 , we probably need to move up if next is not in row3
        if (curr[0] == 3 && next[0] != 3) {
            vector<int> tmp = curr;
            tmp[0]--;
            move(curr, tmp, ans);
            curr = tmp;
        }
        move(curr, next, ans);
        ans.push_back('x');
        curr = next;
    }
    return ans;
}

void test() {
    string in = "boy";
    vector<int> start = {0,0};
    auto res = keyBoardMove(in, start);
    for (char c: res) {
        printf("%c", c);
    }
    printf("\n");
}

int main() {
    test();
    return 0;
}