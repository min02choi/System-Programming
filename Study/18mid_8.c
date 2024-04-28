#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// int main() {
//     printf("안녕하세요", sleep(1));
//     printf("리눅스입니다!", sleep(1));
//     printf("^^", sleep(1));
//     printf("\n", sleep(1));
// }


int main() {
    setbuf(stdout, NULL);
    printf("안녕하세요", sleep(1));
    printf("리눅스입니다!", sleep(1));
    printf("^^", sleep(1));
    printf("\n", sleep(1));
}