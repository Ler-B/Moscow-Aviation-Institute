#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>
#include <assert.h>

int shmOpen(const char * name) {
    int fd = shm_open(name, O_RDWR, S_IRWXO | S_IRWXU);
    if (errno != 0) {
        printf("%s\n", strerror(errno));
        assert(errno == 0);
    }
    return fd;
}

char * charmmap(int fd) {
    char * f = (char *)mmap(0, sizeof(char), PROT_READ | PROT_WRITE,  MAP_SHARED, fd, 0);
    if (errno != 0) {
        printf("%s\n", strerror(errno));
        assert(errno == 0);
    }
    return f;
}

pthread_mutex_t * mutexmmap(int fd) {
    pthread_mutex_t * f = (pthread_mutex_t *)mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE,  MAP_SHARED, fd, 0);
    if (errno != 0) {
        printf("%s\n", strerror(errno));
        assert(errno == 0);
    }
    return f;
}

void lock_mutex(pthread_mutex_t * mutex) {
    int m = pthread_mutex_lock(mutex);
    if (errno != 0) {
        printf("%s\n", strerror(errno));
        assert(errno == 0);
    }
}
void unlock_mutex(pthread_mutex_t * mutex) {
    int m = pthread_mutex_unlock(mutex);
    if (errno != 0) {
        printf("%s\n", strerror(errno));
        assert(errno == 0);
    }
}

void invert(char * str, int size) {
    char c;
    for (int i = 0; i < size / 2 + 1; ++i) {
        c = str[i];
        str[i] = str[size - i];
        str[size - i] = c;
    }
}

int main(int argc, char * argv[]) {
    errno = 0;
    if (argc == 3) {

        int inout = shmOpen(argv[0]);  
        int mutex_par = shmOpen(argv[1]);
        int mutex_ch = shmOpen(argv[2]);
        
        char * fd = charmmap(inout);
        pthread_mutex_t * m_par = mutexmmap(mutex_par);
        pthread_mutex_t * m_ch = mutexmmap(mutex_ch);

        char c;
        int temp = 64;
        int count = 0;
        char * str;
        str = (char *)malloc(sizeof(char) * temp);

        while (!0) {
            lock_mutex(m_ch);
            c = fd[0];
            if (c == '\0') {
                unlock_mutex(m_par);
                break;
            }
            if (c != '\n') {
                if (count == temp) {
                    temp *= 2;
                    str = (char *)realloc(str, temp);
                }
                str[count] = c;
                count++;
            } else {
                if (count != 0) {
                    str[count] = '\0';
                    invert(str, count - 1);
                    printf("%s\n", str);
                    count = 0;
                }
            }
            unlock_mutex(m_par);
        }
        free(str);
        int a1 = shm_unlink(argv[0]);
        int a2 = shm_unlink(argv[1]);
        int a3 = shm_unlink(argv[2]);

        int b1 = munmap(fd, sizeof(char));
        int b2 = munmap(m_ch, sizeof(pthread_mutex_t));
        int b3 = munmap(m_par, sizeof(pthread_mutex_t));
        
    } else {
        printf("ошибка аргументов для ребенка");
    }
}