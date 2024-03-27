#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

int main() {
    //необходимо указать полный путь к библиотекам 
    char * lib1 = "/Users/valeriabudnikova/Desktop/ALL/3S/OC/lab5/libim1.so";
    char * lib2 = "/Users/valeriabudnikova/Desktop/ALL/3S/OC/lab5/libim2.so";
    char * nameCount = "CountPrimeNum";
    char * nameTr = "Trans";

    void * handle;

    int (*CountPrimeNum) (int, int);
    char * (*Trans) (long);

    handle = dlopen(lib1, RTLD_LAZY);
    if (!handle) {
        printf("error_open");
        exit(EXIT_FAILURE);
    }
    
    char * error;
    CountPrimeNum = dlsym(handle, nameCount);
    Trans = dlsym(handle, nameTr);

    if ((error = dlerror()) != NULL)  {
        printf("error_dlsym");
        exit(EXIT_FAILURE);
    }

    int x;
    int f = 1;
    while (scanf("%d", &x) > 0) {
        if (x == 0) {
            int err = dlclose(handle);
            if (err != 0) {
                printf("error_close");
                exit(EXIT_FAILURE);
            }
            if (f == 1) {
                handle = dlopen(lib2, RTLD_LAZY);
                f = 2;
            } else {
                handle = dlopen(lib1, RTLD_LAZY);
                f = 1;
            }
            if (!handle) {
                printf("error_open");
                exit(EXIT_FAILURE);
            }
            CountPrimeNum = dlsym(handle, nameCount);
            Trans = dlsym(handle, nameTr);

            if ((error = dlerror()) != NULL)  {
                printf("error_dlsym");
                exit(EXIT_FAILURE);
            }
        } else if (x == 1) {
            int a;
            int b;
            scanf("%d%d", &a, &b);
            printf("%d\n", (*CountPrimeNum)(a, b));
        } else if (x == 2) {
            long a;
            scanf("%ld", &a);
            printf("%s\n", (*Trans)(a));
        }
    }
    int err = dlclose(handle);
    if (err != 0) {
        printf("error_close");
        exit(EXIT_FAILURE);
    }
}
