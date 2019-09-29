#include <vector>
#include <stdio.h>

using namespace std;

struct TrieNode {
    vector<TrieNode*> ch;
    bool isWord;
    vector<bool> dp;
    TrieNode() {
        ch.resize(26, NULL);
        isWord = true;
    }
};



int main() {
    return 0;
}