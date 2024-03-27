#include "h.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int x;
    while (scanf("%d", &x) > 0) {
        if (x == 1) {
            int a;
            int b;
            scanf("%d%d", &a, &b);
            printf("%d\n", CountPrimeNum(a, b));
        } else if (x == 2) {
            long a;
            scanf("%ld", &a);
            char * str = Trans(a);
            printf("%s\n", str);
            free(str);
        }
    }
}
