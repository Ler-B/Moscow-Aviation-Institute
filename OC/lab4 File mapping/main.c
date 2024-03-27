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

int file(char filename[256]) {
    int f = creat(filename, S_IRWXU | S_IRWXO);
    if (errno != 0) {
        printf("%s\n", strerror(errno));
        assert(errno == 0);
    }
    return f;
}

int shmOpen(const char * name) {
    int fd = shm_open(name, O_RDWR | O_CREAT, S_IRWXO | S_IRWXU);
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

void mutex(pthread_mutex_t * mutex) {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(mutex, &attr);
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

int main() {
    errno = 0;
    const char * name_inout = "inout";
    const char * mutex_child1 = "mutex1";
    const char * mutex_child2 = "mutex2";
    const char * mutex_parent = "mutex3";
    char filename1[256];
    char filename2[256];
    scanf("%s", filename1);
    scanf("%s", filename2);

    int f1 = file(filename1);
    int f2 = file(filename2);

    int inout = shmOpen(name_inout);
    int mutex_ch1 = shmOpen(mutex_child1);
    int mutex_ch2 = shmOpen(mutex_child2);
    int mutex_par = shmOpen(mutex_parent);

    ftruncate(inout, sizeof(char));
    ftruncate(mutex_ch1, sizeof(pthread_mutex_t));
    ftruncate(mutex_ch2, sizeof(pthread_mutex_t));
    ftruncate(mutex_par, sizeof(pthread_mutex_t));
    if (errno != 0) {
        printf("%s\n", strerror(errno));
        assert(errno == 0);
    }

    char * fd = charmmap(inout);
    pthread_mutex_t * m_ch1 = mutexmmap(mutex_ch1);
    pthread_mutex_t * m_ch2 = mutexmmap(mutex_ch2);
    pthread_mutex_t * m_par = mutexmmap(mutex_par);

    mutex(m_ch1);
    mutex(m_ch2);
    mutex(m_par);

    int id = fork();
    if (id == -1) {
        printf("error");
        assert(errno == 0);
    } else if (id == 0) {                                                                //CHILD1 

        dup2(f1, fileno(stdout));
        execl("child1", name_inout, mutex_parent, mutex_child1, NULL);

    } else {

        int id2 = fork();
        if (id2 == -1) {
            printf("error");
            assert(errno == 0);
        } else if (id2 == 0) {                                                            //CHILD2  
            
            // printf("child2: %d\n", getpid());
            dup2(f2, fileno(stdout));
            execl("child1", name_inout, mutex_parent, mutex_child2, NULL);

        } else {                                                                        //PARENT
            // printf("parent: %d\n", getppid());
            char c;
            int f = 1;
            while (!0) {
                if (c == '\n') {
                    if (rand() % 9 + 1 < 4) {
                        f = 0;
                    } else {
                        f = 1;
                    }
                }
                if (f) {
                    lock_mutex(m_par);
                    if (scanf("%c", &c) <= 0) {
                        fd[0] = '\0';
                        unlock_mutex(m_ch1);
                        lock_mutex(m_par);
                        fd[0] = '\0';
                        unlock_mutex(m_ch2);
                        break;
                    }
                    fd[0] = c;
                    unlock_mutex(m_ch1);
                } else {
                    lock_mutex(m_par);
                    if (scanf("%c", &c) <= 0) {
                        fd[0] = '\0';
                        unlock_mutex(m_ch1);
                        lock_mutex(m_par);
                        fd[0] = '\0';
                        unlock_mutex(m_ch2);
                        break;
                    }
                    fd[0] = c;
                    unlock_mutex(m_ch2);
                }
            }
        }
    }

    int b1 = munmap(fd, sizeof(char));
    int b2 = munmap(m_ch1, sizeof(pthread_mutex_t));
    int b3 = munmap(m_ch2, sizeof(pthread_mutex_t));
    int b4 = munmap(m_par, sizeof(pthread_mutex_t));
    assert(b1 == 0 || b2 == 0 || b3 == 0 || b4 == 0);

    if (close(f1) == -1 || close(f2) == -1) {
        printf("error");
        assert(errno == 0);
    }
	return 0;
}
