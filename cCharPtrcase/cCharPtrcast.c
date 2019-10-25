#include<stdio.h>
#include<string.h>

struct test{
    char buf[8];
};

int main(void) {
  struct test t;
    t.buf[0] = '1';
    t.buf[1] = '\0';
    char *a = "te";
    // *((char**)&(t.buf[0])) = (char*)a;
    memcpy(&t.buf[0], &a, sizeof(char*));
    printf("%s\n", *((char**)&(t.buf[0])));
    printf("%s\n", a);
}