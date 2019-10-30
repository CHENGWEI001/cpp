#include <stdio.h>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

// load f from idx into buf with maxLen
int load(string &f, int &idx, char *buf, int maxLen) {
    int remain = f.size() - idx + 1; // we want to copy '\0' as well
    int toRead = min(maxLen, remain);
    if (toRead > 0) {
        const char *fc = f.c_str();
        memcpy(&buf[0], &fc[idx], sizeof(char)*toRead);
    }
    idx += toRead;
    // printf("toRead:%d\n", toRead);
    return toRead;
}

#define BUF_SIZE 5

void printfbuf(char* buf, int len) {
    printf("[DEBUG]:\"");
    for (int i = 0; i < len; i++) {
        printf("%c", buf[i]);
    }
    printf("\"\n");
}

vector<int> cntWordPerLine(string &s) {
    int cntWord = 0;
    int cntChar = 0;
    char buf[BUF_SIZE];
    int len = 0;
    int idx = 0;
    vector<int> ans;
    // printf("%s\n", s.c_str());
    // assume file is using \0 to indicate EOF
    while ((len = load(s, idx, buf, BUF_SIZE)) > 0) {
        int i = 0;
        // printfbuf(buf, len);
        // printf("len:%d, idx:%d, cntChar:%d, cntWord:%d, ans.size():%d, i:%d\n", len, idx, cntChar, cntWord, ans.size(), i);
        while (i < len) {
            // printf("[%d]:%c\n", i, buf[i]);
            if (buf[i] == ' ' || buf[i] == '\n' || buf[i] == '\0') {
                if (cntChar > 0) {
                    cntWord++;
                }
                cntChar = 0;
                if (buf[i] == '\n' || buf[i] == '\0') {
                    ans.push_back(cntWord);
                    cntWord = 0;
                }
            } else {
                cntChar++;
            }
            // if (s[i] == '\0') {
            //     break;
            // }
            i++;
        }
    }
    return ans;
}

void test() {
    string s = "abc\n  efg\n\n  ab  \na s dd  ";
    // string s = "a b \n\nb\nc\n  d  e";
    auto res = cntWordPerLine(s);
    for (int i = 0; i < res.size(); i++) {
        printf("[%d]:%d\n", i, res[i]);
    }
}

int main() {
    test();
}