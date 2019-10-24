#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strLen(char* s) {
    int i = 0;
    while (s[i]) {
        i++;
    }
    return i;
}

void swap(char *a, char *b) {
    char t = *a;
    *a = *b;
    *b = t;
}

void stringEvenSpace(char *s) {
    int numSpace = 0;
    int numWord = 0;
    int n = strLen(s);
    // first calculate how many space total and words
    int i = 0;

    while (1) {
        if (s[i] == ' ' || s[i] == '\0') {
            if (i - 1 >= 0 && s[i-1] != ' ') {
                numWord++;
            }
            if (s[i] == ' ') {
                numSpace++;
            }
        }
        i++;
        if (s[i] == '\0') {
            break;
        }
    }



    // second we need to shifting all words toward left only 1 space apart
    int idx = 0;
    i = 0;
    while (s[i]) {
        if (s[i] != ' ' || i - 1 >= 0 && s[i-1] != ' ') {
            s[idx++] = s[i];
        }
        i++;
    }
    i = idx;
    while (s[i]) {
        s[i] = ' ';
        i++;
    }

    // finally we from right to copy word and even space
    // since idx -1 might at last space
    if (idx - 1 >= 0 && s[idx-1] == ' ') {
        idx--;
    }


    // if only 1 word or no word, return trim
    if (numWord <= 1) {
        s[idx] = '\0';
        return;
    }
    int gapSize = numSpace / (numWord-1);
    i = idx-1;
    idx = n-1;
/*
__abc___c__dd_
              ^
abc____c____dd
  i
^
idx = 8
ns = 8
nw = 3

n = 14
gapSize = 4
idx = 0
*/
    // printf("\"%s\", i:%d\n", s, i);
    while (i >= 0) {
        if (s[i] == ' ') {
            for (int j = 0; j < gapSize; j++) {
                s[idx--] = ' ';
            }
        } else {
            s[idx--] = s[i];
        }
        i--;
    }
}

void test1() {
    char s[] = {"  abc   c  dd "};
    stringEvenSpace(&s[0]);
    printf("\"%s\"\n" ,s);
}

void test2() {
    char s[] = {"  abcdd  "};
    stringEvenSpace(&s[0]);
    printf("\"%s\"\n" ,s);
}

void test3() {
    char s[] = {" "};
    stringEvenSpace(&s[0]);
    printf("\"%s\"\n" ,s);
}

int main() {
    test3();
    return 0;
}