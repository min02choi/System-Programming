#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#define SIZE 80



int main(int argc, char *argv[]) {
    int fd;
    char buf[SIZE] = {'\0'};

    if (fd = open(argv[1], O_WRONLY|O_TRUNC|O_CREAT, 0600)== -1) {
        perror(argv[1]);
    }
    printf("출력 재지정 구현|키보드로부터의 입력을 파일 %s에 저장\n", argv[1]);
    dup2(fd, 1);
    while (gets(buf) != NULL) {
        puts(buf);
    }
    exit(0);
}

// 아니 근데 뭔가 안되는거 같은데