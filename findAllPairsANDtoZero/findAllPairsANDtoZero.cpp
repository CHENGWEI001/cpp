#include <vector>
#include <unordered_set>
#include <stdio.h>

using namespace std;

// gg 550837

struct TrieNode {
    TrieNode* bit[2];
    vector<int> nums;
    TrieNode() {
        bit[0] = NULL;
        bit[1] = NULL;
    }
};

void insert(TrieNode *root, int val) {
    TrieNode *curr = root;
    for (int i = 0; i < 32; i++) {
        int b = (val >> i) & 0x1;
        if (!curr->bit[b]) {
            curr->bit[b] = new TrieNode();
        }
        curr = curr->bit[b];
    }
    curr->nums.push_back(val);
}

void query(TrieNode *root, int val, int idx, vector<int> &ans) {
    if (!root) {
        return;
    }
    if (idx == 32) {
        for (int n: root->nums) {
            ans.push_back(n);
        }
    }
    TrieNode *curr = root;
    int b = (val >> idx) & 0x1;
    query(curr->bit[0], val, idx+1, ans);
    if (b == 0) {
        query(curr->bit[1], val, idx+1, ans);
    }
}

vector<vector<int>> findPairANDzeor(vector<int> &nums) {
    TrieNode root;
    unordered_set<int> seen;
    vector<vector<int>> res;
    for (int n: nums) {
        if (seen.count(n)) {
            continue;
        }
        seen.insert(n);
        vector<int> cands;
        query(&root, n, 0, cands);
        for (int v: cands) {
            res.push_back({n, v});
        }
        insert(&root, n);
    }
    return res;
}

void test1() {
    vector<int> nums({1, 2,2, 6, 9, 3});
    auto res = findPairANDzeor(nums);
    for (auto &p: res) {
        printf("(%d,%d), ", p[0], p[1]);
    }
    printf("\n");
}

void test2() {
    vector<int> nums({1, 2, 6, 9, 3, 0});
    auto res = findPairANDzeor(nums);
    for (auto &p: res) {
        printf("(%d,%d), ", p[0], p[1]);
    }
    printf("\n");
}

int main() {
    test2();
    return 0;
}