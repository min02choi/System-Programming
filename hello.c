#include <stdio.h>


int main() {
    printf("asdfasdf");
    printf("와 미친 된다!!!");

    int a = 1;

    char *p = "Hello";
    char m[] = "world";

    printf("%s %s\n", p, m);

    p = m;

    while(*p) {
        putchar(*p++);
    }


    char colors[3][10] = {"red", "cian", "black"};
    char *ptr[3] = {"red", "cian", "black"};

    return 0;
}