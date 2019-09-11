//https://1o24bbs.com/t/topic/12341
// https://leetcode.com/discuss/interview-question/379770/facebook-phone-screen

#include <cstring>
#include <algorithm>
#include <stdio.h>
#include <assert.h>
#include <iostream>

using namespace std;

string rmparan(string &s) {
	int nl = 0; // # of '('
	int nr = 0; // # of ')'
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(') {
			nl++;
		} else {
            if (nl > 0) {
                nl--;
            } else {
                nr++;
            }
        }
	}
    string ans;
    vector<bool> take(s.size(), true);
    // for ')' , if we get nr > 0 , like case '())'' or ')' , both are okay to remove from left
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ')' && nr > 0) {
            take[i] = false;
            nr--;
        }
    }
    // for '(' , if nl > 0 , that means right side doesn't have any ')' to pair with it , so remove
	// from right
    for (int i = s.size()-1; i >= 0; i--) {
        if (s[i] == '(' && nl > 0) {
            take[i] = false;
            nl--;
        }
    }
    for (int i = 0; i < s.size(); i++) {
        if (take[i]) {
            ans.push_back(s[i]);
        }
    }
    return ans;
}

int main() {
    string s = "))())";
    cout << rmparan(s) << endl;

    s = "(())()(()(()()(";
    cout << rmparan(s) << endl;

    s = "(())))";
    cout << rmparan(s) << endl;


    return 0;
}