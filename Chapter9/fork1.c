#include <stdio.h>
#include <unistd.h>

/* 자식 프로세스를 생성한다. */
// 아ㅣㄴ 리턴값이 이해가 안감
int main() {
    int pid;
    printf("[%d] 프로세스 시작 \n", getpid());
    pid = fork();
    // printf("와 개신기: %s\n", pid);

    printf("[%d] 프로세스 : 리턴값 %d\n", getpid(), pid);
}