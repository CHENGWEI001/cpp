#include <stdlib.h>
#include <stdio.h>
#include <cassert>
#include <cstring>

class MyVector {
    int currSize = 0;
    int currCap = 0;
    int *buf = NULL;
    void init() {
        buf = (int*)malloc(sizeof(int) * currCap);
        if (buf == NULL) {
            // throw Exception("no memroy space!");
            assert(0);
        }
    }
public:
    MyVector(int n) {
        // find
        currCap = 1;
        while (currCap < n) {
            currCap <<= 1;
        }
        init();
    }

    MyVector() {
        currCap = 1;
        init();
    }

    void push_back(int val) {
        if (currSize == currCap) {
            currCap *= 2;
            int *newBuf = (int*)malloc(sizeof(int) * currCap);
            if (newBuf == NULL) {
                // throw Exception();
                assert(0);
            }
            memcpy(newBuf, buf, sizeof(int) * currSize);
            free(buf);
            buf = newBuf;
        }
        buf[currSize++] = val;
    }

    int pop_back() {
        int ret = buf[--currSize];
        if (currSize < currCap/2) {
            currCap/=2;
            int *newBuf = (int*)malloc(sizeof(int) * currCap);
            if (newBuf == NULL) {
                // throw Exception();
                assert(0);
            }
            memcpy(newBuf, buf, sizeof(int) * currSize);
            free(buf);
            buf = newBuf;
        }
        return ret;
    }

    int size() {
        return currCap;
    }

    int operator[] (int i) {
        if (i >= currSize) {
            assert(0);
        }
        return buf[i];
    }

    ~MyVector() {
        free(buf);
    }
};

int main() {
    MyVector mv(5);
    for (int i = 0; i < 10; i++) {
        mv.push_back(i);
    }
    printf("my.size():%d\n", mv.size());
    for (int i = 0; i < 10; i++) {
        printf("[%d]:%d\n", i, mv[i]);
    }
    for (int i = 0; i < 10; i++) {
        mv.pop_back();
    }
    for (int i = 0; i < 10; i++) {
        mv.push_back(i);
    }
    for (int i = 0; i < 10; i++) {
        printf("[%d]:%d\n", i, mv[i]);
    }
    printf("my.size():%d\n", mv.size());
    return 0;
}