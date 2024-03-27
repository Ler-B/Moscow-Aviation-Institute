#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

typedef struct HelpThead {
    int left, right;
    int str;
} HelpThead;

long double * a; //указатель на матрицы
int n; //длина строки/слотбца

void* ThreadFunc(void* args) {
    HelpThead help = *((HelpThead*)args);
    long double temp;
    for (int i = help.left * n; i < help.right * n; ++i) {
        if (i % n == 0 && i + help.str < n * n){
            if (a[n * help.str + help.str] != 0) {
                temp = a[i + help.str] / a[n * help.str + help.str];
            } else {
                temp = 0;
            }
        }
        a[i] -= a[i % n + help.str * n] * temp;
    }
    return 0;
}

int Min(int x, int y) {
    return x < y ? x : y;
}

signed main(int argc, char * argv[]) {
    int threadCount = 0;
    if (argc == 2){
        for(int i = 0; i < strlen(argv[1]); ++i) {
            threadCount = threadCount * 10 + (int)(argv[1][i] -'0');
        }
    }
    scanf("%d", &n);                      //количество строк(столбцов) матрицы
    a = (long double*)malloc(sizeof(long double) * n * n);
    long double * st = (long double*)malloc(sizeof(long double) * n);
    for (int i = 0; i < n * n; ++i) {
        scanf("%Lf", &a[i]);
    }
    int temp = threadCount;
    long double time_begin, time_end;
    pthread_t* threads = (pthread_t*)malloc(sizeof(pthread_t) * threadCount);
    HelpThead* HelpTheads = (HelpThead*)malloc(sizeof(HelpThead*) * threadCount);
    int k = 0;
    long double Ans = 1;
    time_begin = clock();
    while (k < n) {
        int step = (n + threadCount - 1) / threadCount;
        for (int i = 0; i < threadCount; ++i) {
            HelpTheads[i].left = i * step + 1 + k;
            HelpTheads[i].right = Min(n, (i + 1) * step) + 1 + k;
            HelpTheads[i].str = k;
            int ind = 1;
            while (a[n * k + k] == 0 && ind < n - k) {
                for (int i = 0; i < n; ++i){
                    st[i] = a[i * n + k];
                    a[i * n + k] = a[i * n + k + ind]; 
                    a[i * n + k + ind] = st[i];
                }
                ++ind;
            }
            ind = 1;
            if (Min(n, (i + 1) * step) + 1 + k > n) { HelpTheads[i].right = n; }
            if (pthread_create(&threads[i], NULL, ThreadFunc, (void*)&HelpTheads[i])) {
                printf("Error creating thread!\n");
                return -1;
            }
                // for (int h = 0; h < n * n; ++h) {          //вывод верхне-треугольной матрицы(после преобр)
                //     if (h % n == 0) {
                //         printf("\n");
                //     }
                //     printf("%Lf\t", a[h]);
                // }
                // printf("\n");
        }
        for (int i = 0; i < threadCount; ++i) {
            if (pthread_join(threads[i], NULL)) {
                printf("Error joining thread!\n");
                return -1;
            }
        }
        Ans *= a[n * k + k];
        ++k;
    }
    time_end = clock();

    //  
    printf("Count:  %d\n", threadCount);
    printf("time: %Lf ms\n", time_end - time_begin);
    printf("\nAnswer:: %Lf\n", Ans);
    free(threads);
    free(HelpTheads);
}