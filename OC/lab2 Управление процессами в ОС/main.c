#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>


int main() {
    char filename1[64];
    char filename2[64];
    scanf("%s", filename1);
    scanf("%s", filename2);
	int fd1[2];
    int fd2[2];
    int f1 = creat(filename1, S_IWRITE | S_IREAD);
    int f2 = creat(filename2, S_IWRITE | S_IREAD);
    if (pipe(fd1) == -1 || pipe(fd2) == -1 || f1 == -1 || f2 == -1 ) {
        printf("error");
        exit(EXIT_FAILURE);
    }
    int id = fork();
    if (id == -1) {
        printf("error");
        exit(EXIT_FAILURE);
    } else if (id == 0) {                                        //CHILD1 
        //printf("child1: %d\n", getpid());
        if (close(fd1[1]) == -1 || close(fd2[1]) == -1 || close(fd2[0]) == -1 || dup2(fd1[0], fileno(stdin)) == -1 
        || dup2(f1, fileno(stdout)) == -1 || close(fd1[0]) == -1 || execl("child1", 0)) {
            printf("error");
            exit(EXIT_FAILURE);
        }
    } else {
        int id2 = fork();
        if (id2 == -1) {
            printf("error");
            exit(EXIT_FAILURE);
        } else if (id2 == 0) {                                   //CHILD2  
            //printf("child2: %d\n", getpid());
            if (close(fd2[1])== -1 || close(fd1[1]) == -1 || close(fd1[0]) == -1 || dup2(fd2[0], fileno(stdin)) == -1 
            || dup2(f2, fileno(stdout)) == -1 || close(fd2[0]) == -1 || execl("child1", 0)) {
                printf("error22");
                exit(EXIT_FAILURE);
            }
        } else {                                                 //PARENT
            //printf("parent: %d\n", getppid());
            if (close(fd1[0]) == -1 || close(fd2[0]) == -1) {
                printf("error");
                exit(EXIT_FAILURE);
            } 
            char fl = 0;
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
                    if (count != 0) {
                        str[count] = '\n';
                        size = count + 1;
                        count = 0;
                        fl = 0;
                    } else {
                        fl = 1;
                    }
                } 
                if (count == 0 && fl == 0) {
                    if (rand() % 9 + 1 < 4) {
                        //printf("2\n");
                        if (write(fd2[1], str, sizeof(char) * size) == -1) {
                            printf("error");
                            exit(EXIT_FAILURE);
                        }
                    } else {
                        //printf("1\n");
                        if (write(fd1[1], str, sizeof(char) * size) == -1){
                            printf("error");
                            exit(EXIT_FAILURE);
                        }
                    }
                }
            }
            if (close(fd1[1]) == -1 || close(fd2[1]) == -1 ) {
                printf("error");
                exit(EXIT_FAILURE);
            }
        }
    }
    
    if (close(f1) == -1 || close(f2) == -1) {
        printf("error");
        exit(EXIT_FAILURE);
    }
	return 0;
}
