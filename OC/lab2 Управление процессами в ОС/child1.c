#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void invert(char * str, int size) {
    char c;
    for (int i = 0; i < size / 2 + 1; ++i) {
        c = str[i];
        str[i] = str[size - i];
        str[size - i] = c;
    }

}

int main(int argc, char* argv[]) {
    int temp = 64;
    int size = 0;
    int count = 0;
    char * str;
    str = (char *)malloc(sizeof(char) * temp);
    char c;
    while (scanf("%c", &c) > 0) {
        if (c != '\n') {
            if (count > temp) {
                temp *= 2;
                str = (char *)realloc(str, temp);
            }
            str[count] = c;
            count++;
        } else {
            str[count] = '\0';
            invert(str, count - 1);
            printf("%s\n", str);
            count = 0;
        }
    }
    free(str);
}