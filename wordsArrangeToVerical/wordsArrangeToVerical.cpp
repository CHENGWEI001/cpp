#include <vector>
#include <stdio.h>

using namespace std;

vector<string> wordArrange(vector<string> &words, string &logo) {
    int idx = 0;
    int last = -1; // last idx the idx char match in rows
    vector<string> rows({""});
    for (int i = 0; i < words.size(); i++) {
        int j = 0;
        for (j = 0; j < words[i].size(); j++) {
            if (words[i][j] == logo[idx]) {
                idx++;
                break;
            }
        }
        if (j < words[i].size() && idx > 1) {
            rows.push_back(string(last - j, ' '));
        }
    }
}

int main() {
    return 0;
}