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
    if ((pid1 = fork()) == 0) {
        printf("Hello pid=%d\n", getpid());
    }
    
    if ((pid2 = fork()) == 0) {
        printf("Good morning pid=%d\n", getpid());
    }
    
}