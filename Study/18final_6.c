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
    pid1 = fork();
    printf("[1] pid=%d\n", pid1);
    
    pid2 = fork();
    printf("[2] pid=%d\n", pid2);
    // 얘는 왜 1, 2, 3, 4로 순서대로 나왔지?
    // 예상: 0, 2, 1, 3
}