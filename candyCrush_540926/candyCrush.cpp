#include <stdio.h>
// #include <utility>
#include <vector>
#include <string>

using namespace std;

// keep cancelling if we have >= 3 consecutive items
// consecutive items are considered after crushing middle ones
string candyCrush(string &s) {
    string res;
    vector<pair<char, int>> st;
    for (int i = 0; i < s.size(); i++) {
        int j = i;
        char c = s[i];
        while (j < s.size() && s[j] == c) {
            j++;
        }
        int cnt = j - i;
        if (st.size() && st.back().first == c) {
            st.back().second += cnt;
        } else {
            st.push_back({c, cnt});
        }
        if (st.size() && st.back().second >= 3) {
            st.pop_back();
        }
        i = j-1;
    }
    while (st.size()) {
        res.append(string(st.back().second, st.back().first));
        st.pop_back();
    }
    return res;
}

void test(string &in) {
    string res = candyCrush(in);
    printf("%s -> %s\n", in.c_str(), res.c_str());
}

int main() {
    vector<string> testcase({
        "acaaaacc",
        "aabaacccabba",
    });
    for (string &s: testcase) {
        test(s);
    }
    return 0;
}