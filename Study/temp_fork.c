#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>


int main() {
    int pid1, pid2;
    int status;
    pid1 = fork();
    pid2 = fork();
    if (pid1 == 0) {
        printf("[Child 1]: Hello World! pid=%d\n", getpid());
    }
    if (pid2 == 0) {
        printf("[Child 2]: Hello World! pid=%d\n", getpid());
    }
    else {
        wait(&status);
        printf("[PARENT]: Hello World! pid=%d\n", getpid());
    }

}