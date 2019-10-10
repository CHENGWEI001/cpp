#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <string>
#include <unordered_map>

using namespace std;

/*
给一个字符串列表，比如["a","ab","AI","at","an","in","am","it"]
，一个目标字符串targetStr，比如"Tim in MIT"。可以从字符串列表中取字符串出来，
对于取出来的字符串，可以取其中的一个或者多个字符并重新排列，
大小写不敏感。比如，可以取"am"，"AI"，"at"，然后每个都取出第二个字符，
组成"MIT"；也可以取"am"，"it"，取"am"的第二个字符，"it"的全部，来组成"MIT"。
求最少从字符串列表中取出多少个，经过抽取、重新排列等操作，能凑成目标字符串。
( similr to lc691)
*/

void printPath(vector<unordered_map<string, string>> &pi, vector<string> &words, string &state) {
    int i = 0;
    vector<int> path;
    for (int i = 0; i < words.size(); i++) {
        if (state != pi[i][state]) {
            path.push_back(i);
        }
        state = pi[i][state];
    }
    for (int i: path) {
        printf("%s,", words[i].c_str());
    }
    printf("\n");
}

int helper(int idx, string &tgt, string &currState, vector<string> &words, string &finalState, vector<unordered_map<string, int>> &memo, vector<unordered_map<string, string>> &pi) {
    // if (currState == finalState) {
    //     return 0;
    // }
    if (idx == words.size()) {
        // printf("%s, %s\n", currState.c_str(), finalState.c_str());
        if (currState == finalState) {
            return 0;
        } else {
            return -1;
        }
    }
    // if do this before , directly return it
    if (memo[idx].count(currState)) {
        return memo[idx][currState];
    }

    // first branch, don't use this words[idx]
    int ans = -1;
    int notUse = helper(idx+1, tgt, currState, words, finalState, memo, pi);
    ans = notUse;
    if (ans != -1) {
        pi[idx][currState] = currState;
    }
    int toUse = -1;
    string newState = currState;
    for (char c: words[idx]) {
        for (int i = 0; i < tgt.size(); i++) {
            if (tgt[i] != c || newState[i] == '1') {
                continue;
            }
            // if this c of words[idx] match , update state
            // and break
            newState[i] = '1';
            // printf("%c matched at %d\n", c, i);
            break;
        }
    }
    if (newState != currState) {
        toUse = helper(idx+1, tgt, newState, words, finalState, memo, pi);
        if (toUse != -1) {
            if (ans == -1 || ans > toUse+1) {
                ans = toUse+1;
                pi[idx][currState] = newState;
            }
        }
    }
    memo[idx][currState] = ans;
    return ans;
}

void toAllLowerCase(string &s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            s[i] += 'a' - 'A';
        }
    }
}

int constructStr(string &tgt, vector<string> &words) {
    // since we are doing case insensitive, preprocess all to lower case
    toAllLowerCase(tgt);
    for (string &w: words) {
        toAllLowerCase(w);
    }

    string initState = string(tgt.size(), '0');
    // all space ' ' to be marked as used, no need match space
    for (int i = 0; i < tgt.size(); i++) {
        if (tgt[i] == ' ') {
            initState[i] = '1';
        }
    }
    // final state is everything matched
    string finalState = string(tgt.size(), '1');
    // memo[idx][state] : from this wordIdx and given state, min words need to mark target
    vector<unordered_map<string, int>> memo(words.size());
    vector<unordered_map<string, string>> pi(words.size());
    int res = helper(0, tgt, initState, words, finalState, memo, pi);
    if (res != -1) {
        printPath(pi, words, initState);
    }
    return res;
}

void test(string &tgt, vector<string> words) {
    int res = constructStr(tgt, words);
    printf("res:%d\n", res);
}

int main() {
    string tgt = "Tim in MIT";
    vector<string> words = {"AI","at", "am","mi","tni", "tna"};
    // string tgt = "A b c";
    // vector<string> words = {"a","bc", "aBc"};
    test(tgt, words);
    return 0;
}