#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


// int main() {
//     FILE *fp;
//     int fd;

//     if ((fd = creat("myfile", 0600)) == -1) {
//         perror("myfile: ");
//     }
//     write(fd, "Hello! Linux", 12);
//     dup2(1, fd);        // 표준출력 (stdout)을 fd로 복사함
//     write(fd, "Bye! Linux", 10);
//     exit(0);
// }

int main() {
    FILE *fp;
    int fd;

    if ((fd = creat("myfile", 0600)) == -1) {
        perror("myfile: ");
    }
    write(fd, "Hello! Linux", 12);
    write(fd, "Bye! Linux", 10);
    exit(0);
}