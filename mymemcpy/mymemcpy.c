#include<stdio.h>

#define max(a, b) (((a) > (b))? (a) : (b))
#define min(a, b) (((a) > (b))? (b) : (a))

typedef unsigned int uint32;

void mymemcpy(void *dst, void *src, int size) {
    char* s = (char*)src;
    char* d = (char*)dst;
    uint32 sh = (uint32)s;
    uint32 se = sh + size;
    uint32 dh = (uint32)d;
    uint32 de = dh + size;
    uint32 maxs = max(sh, dh);
    uint32 mine = min(se, de);
    // overlap and src lower than dst , need to copy backward
    if (maxs <= mine && sh < dh) {
        for (int i = size-1; i >= 0; i--) {
            d[i] = s[i];
        }
    } else {
        for (int i = 0; i < size; i++) {
            d[i] = s[i];
        }
    }
}

int main(void) {
    char a[11] = "0123456789\0";
    char b[11] = "abcdefghij\0";
    mymemcpy(&a[0], &a[5], 5);
    printf("%s\n", a);
    return 0;
}