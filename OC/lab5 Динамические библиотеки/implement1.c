#include "h.h"
#include <stdlib.h>

int CountPrimeNum(int a, int b) {
    int rez = 0;
    int fl;
    for (int i = a; i < b + 1; ++i) {
        fl = 0;
        for (int j = 2; j < i; ++j) {
            if (i % j == 0) {
                fl = 1;
            }
        }
        if (fl == 0) {
            ++rez;
        }
    }
    if (a == 1 && rez != 0) {
        --rez;
    }
    return rez;
}

char * Trans(long a) {
    char * rez;
    rez = malloc(sizeof(long) * 8);
    int f = 0;
    if (a < 0) {
        a *= -1;
        f = 1;
    }
    for (int i = sizeof(long) * 8 - 1; i >= 0; --i) {
        if ((a & 1) == 1) {
            rez[i] = '1';
        } else {
            rez[i] = '0';
        }
        a >>= 1;
    }
    if (f) {
        rez[0] = '-';
    }
    return rez;
}