#include <stdio.h>
#include <string>
#include <vector>
#include <string.h>

using namespace std;

struct TrieNode {
    TrieNode *ch[26];
    TrieNode() {
        memset(&ch[0], 0, 26*sizeof(TrieNode*));
    }
    ~TrieNode() {
        for (int i = 0; i < 26; i++) {
            if (ch[i]) {
                delete ch[i];
            }
        }
    }
};

void substringList(string &s) {
    TrieNode root;
    TrieNode *curr = &root;
    vector<vector<int>> ans;
    int start = 0;
    int n = s.size();
    for (int i = 0; i < n; i++) {
        if (curr->ch[s[i]-'a'] == NULL) {
            curr->ch[s[i]-'a'] = new TrieNode();
            curr = &root;
            ans.push_back({start, i});
            start = i+1;
        } else {
            curr = curr->ch[s[i]-'a'];
        }
    }
    for (auto &p: ans) {
        printf("%s\n", s.substr(p[0], p[1] - p[0] + 1).c_str());
    }
}

void test() {
    string s = "ababcccccc";
    substringList(s);
}

int main() {
    test();
    return 0;
}