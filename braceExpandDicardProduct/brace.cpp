#include <vector>
#include <string>
#include <stdio.h>
#include <utility>

using namespace std;

/*
“abc {1,2}{3,4} def”
               ^
           i
              j
 */


/*
buf: 1, 2
tmpBUf: 13, 14, 23, 24
chBuf: 3, 4
13 14 23 24
 */
void helper(string &s, int &idx, string &ans) {
    vector<string> buf({""});
    while (s[idx] == '{') {
        int j = idx;
        while (j < s.size() && s[j] != '}') {
            j++;
        }
        vector<string> tmpBuf;
        vector<char> chBuf;
        for (int i1 = idx+1; i1 < j; i1+=2) {
            chBuf.push_back(s[i1]);
        }
        for (auto &ts: buf) {
            for (char c: chBuf) {
                tmpBuf.push_back(ts + string(1, c));
            }
        }
        idx = j+1;
        buf = tmpBuf;
    }
    for (int i = 0; i < buf.size(); i++) {
        ans = ans + buf[i];
        if (i < buf.size()-1) {
            ans.push_back(' ');
        }
    }
    idx--;
}

/*
“abc {1,2}{3,4} def”
               ^

abc 13 14 23 24
    ^
 */

string braceExpand(string &s) {
    string ans;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '{') {
            helper(s, i, ans);
        } else {
            ans.push_back(s[i]);
        }
    }
    return ans;
}

int main() {
    string in = "abc {1,2}{3,4}{5,6} def";
    string out = braceExpand(in);
    printf("out:%s\n", out.c_str());
    return 0;
}