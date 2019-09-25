#include <vector>
#include <string>
#include <stdio.h>
#include <utility>

using namespace std;

/*
' +1  8 ' -> True,
' 1 d2' -> False,
'1+' -> False,
' 001' -> False,
' +1.000' -> True,
' +1.001' -> False
*/

/*
if want to use DFA, below list the state
state 0: init state
-

state 1: see + after s0

state 2: see 0 after s0 or s1

state 3: see non 0 digit after s0 or s1

state 4: see . after s2,s3

state 5: see zero after s4 or s6
state 6: see non zero digit after s5 or s4

 */

bool validPosNumLeadingZeroOkay(string num) {
    bool seenDot = false;
    bool seenPlus = false;
    bool seenDigit = false;
    bool lastDigit = false;
    for (char c: num) {
        if (c == ' ') {
            continue;
        }
        if (c >= '0' && c <= '9') {
            lastDigit = true;
        } else if (c == '+' || c == '.') {
            lastDigit = false;
            if (c == '+') {
                if (seenDigit || seenPlus) {
                    return false;
                }
                seenPlus = true;
            } else if (c == '.') {
                if (seenDot) {
                    return false;
                }
                seenDot = true;
            }
        } else {
            return false;
        }
    }
    return lastDigit;
}

bool validPosNumLeading(string num) {
    bool seenDot = false;
    bool seenPlus = false;
    bool seenDigit = false;
    bool lastDigit = false;
    bool firstZero = false;
    for (char c: num) {
        if (c == ' ') {
            continue;
        }
        if (c >= '0' && c <= '9') {
            if (firstZero) {
                return false;
            }
            // first digit is 0
            if (c == '0' && !seenDigit) {
                firstZero = true;
            }
            lastDigit = true;
            seenDigit = true;

        } else if (c == '+' || c == '.') {
            lastDigit = false;
            if (c == '+') {
                if (seenDigit || seenPlus) {
                    return false;
                }
                seenPlus = true;
            } else if (c == '.') {
                if (seenDot) {
                    return false;
                }
                seenDot = true;
            }
        } else {
            return false;
        }
    }
    return lastDigit;
}

int main() {
    vector<string> tests = {
        " +1  8 ",
        " 1 d2",
        "1+",
        " 001",
        " +1.000",
        " +1.001",
    };
    for (string &s: tests) {
        bool res = validPosNumLeading(s);
        printf("%s : %c\n", s.c_str(), res? 'T': 'F');
    }
    return 0;
}