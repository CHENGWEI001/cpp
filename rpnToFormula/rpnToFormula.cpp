#include <vector>
#include <string>
#include <stdio.h>
#include <utility>

using namespace std;

/*
"63x+*y-"
       ^

V3 =
st:{6*(3+x)-y, T}
,

 */

struct Ele {
    string s;
    bool toProtect; // if more than one operand and any + or - , need to protect
};

// v2 is to take care of not including additional paren
string rpnToFormulaV2(const string &rpn) {
    vector<Ele> st;
    string ops("+-*/");
    for (char c: rpn) {
        if (ops.find(c) != string::npos) {
            Ele v2 = st.back();
            st.pop_back();
            Ele v1 = st.back();
            st.pop_back();
            if (c == '*' || c == '/') {
                if (v1.toProtect) {
                    v1.s = "(" + v1.s + ")";
                    v1.toProtect = false;
                }
                if (v2.toProtect) {
                    v2.s = "(" + v2.s + ")";
                    v2.toProtect = false;
                }
            }
            Ele v3 = Ele({v1.s + string(1, c) + v2.s, false});
            if (c == '+' || c == '-') {
                v3.toProtect = true;
            }
            st.push_back(v3);
        } else {
            st.push_back({string(1, c), false});
        }
    }
    return st.back().s;
}

// v1 is with additinal paren like ((6*(3+x))-y)
string rpnToFormulaV1(const string &rpn) {
    vector<string> st;
    string ops("+-*/");
    for (char c: rpn) {
        if (ops.find(c) != string::npos) {
            string v2 = st.back();
            st.pop_back();
            string v1 = st.back();
            st.pop_back();
            st.push_back("(" + v1 + string(1, c) + v2 + ")");
        } else {
            st.push_back(string(1,c));
        }
    }
    return st.back();
}

int main() {
    vector<pair<string, string>> testcases;
    testcases.push_back({"63x+*y-", "6*(3+x)-y"});
    testcases.push_back({"32*7+5-", "3*2+7-5"});
    for (int i = 0; i < testcases.size(); i++) {
        printf("test[%d] : in: %s, exp: %s\n", i, testcases[i].first.c_str(), testcases[i].second.c_str());
        string ans = rpnToFormulaV2(testcases[i].first.c_str());
        printf("res:%s\n\n", ans.c_str());
    }
}