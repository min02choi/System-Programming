#include <stdio.h>
#define MAXLINE 80


int main(int argc, char *argv[]) {
    FILE *fp;
    char buffer[MAXLINE];

    // fprint(argc, argv);

    if (argc != 2) {
        fprintf(stderr, "사용법: fcat 파일 이름\n");
        return 1;
    }
    // 0번쨰는 프로그래밍 인수임
    if ((fp = fopen(argv[1], "w")) == NULL) {
        fprintf(stderr, "파일 열기 오류\n");
        return 2;
    }
    // while (fgets(buffer, MAXLINE, fp) != NULL) {
    while (fgets(buffer, MAXLINE, stdin) != NULL) {
        fputs(buffer, fp);
    }
    return 0;
}