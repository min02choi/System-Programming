#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main() {
    char buf[] = "good afternoon";
    FILE *fd1, *fd2;
    printf("%d\n", sizeof(buf));
    fd1 = open("test", O_RDWR);
    write(fd1, buf, sizeof(buf));
    fd2 = open("test", O_RDWR);
    write(fd2, buf, sizeof(buf));
}