#include "h.h"
#include <stdlib.h>

int CountPrimeNum(int a, int b) {
    int rez = 0;
    int * mas = (int *)malloc(sizeof(int) * (b + 2));
    for (int i = 0; i < b + 1; ++i) {
        mas[i] = i;
    }
    mas[1] = 0;
    for (int i = 2; i < b + 1; i++) {
        if (mas[i] != 0) {
            if (i >= a && i <= b) {
                rez++;
            }
            for (int j = i * i; j < b + 1; j += i) {
                mas[j] = 0;
            }
        }
    }
    free(mas);
    return rez;
}

char * Trans(long a) {
    char * rez;
    rez = malloc(sizeof(long) * 6);
    int f = 0;
    if (a < 0) {
        a *= -1;
        f = 1;
    }
    for (int i = sizeof(long) * 6 - 1; i >= 0; --i) {
        if (a % 3 == 0) {
            rez[i] = '0';
        } else if (a % 3 == 1) {
            rez[i] = '1';
        } else {
            rez[i] = '2';
        }
        a /= 3;
    }
    if (f) {
        rez[0] = '-';
    }
    return rez;
}