#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


char type(mode_t);
int IsExcutable(mode_t mode);
void printClass(char *pathname, char *file, struct stat *st);


int IsExcutable(mode_t mode) {
    int i;
    for (i = 0; i < 3; i++) {
        if (mode & (S_IXUSR >> i*3))
            return 1;
    }
    return 0;
}

void printClass(char *pathname, char *file, struct stat *st) {
    char class;
    if (type(st->st_mode)=='d')
        class='/';
    else if (type(st->st_mode)=='l')
        class='@';
    else if (type(st->st_mode)=='p')
        class='|';
    else if (type(st->st_mode)=='s')
        class='=';
    else if (type(st->st_mode)=='p')
        class='|';
    else if (type(st->st_mode)=='-') {
        if (IsExcutable(st->st_mode))
            class = '*';
        else
            class ='\0';
    }
    else class = '\0';
    printf("%s%c\n", file, class);
        
}

int main(int argc, char **argv) {
    DIR *dp;
    char *dir;
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ+1];

    if (argc == 1)
        dir = ".";      // 인수가 없으면 현재 디렉을 기준으로 함
    else
        dir = argv[1];

    if ((dp = opendir(dir)) == NULL)    // 디렉토리 열기
        perror(dir);
    while ((d = readdir(dp)) != NULL) { // 디렉토리 내의 각 파일에 대해
        sprintf(path, "%s/%s", dir, d->d_name); // 파일 경로명 만들기
        // lstat: 인수로 파일의 경로명과 포인터를 받음
        if (lstat(path, &st) < 0) // 파일 상태 정보 가져오기
            perror(path);
        else
            printClass(path, d->d_name, &st);
    }
    closedir(dp);
    exit(0);
}

/* 파일 타입을 리턴 */
char type(mode_t mode) {
    if (S_ISREG(mode))
        return('-');
    if (S_ISDIR(mode))
        return('d');
    if (S_ISCHR(mode))
        return('c');
    if (S_ISBLK(mode))
        return('b');
    if (S_ISLNK(mode))
        return('l');
    if (S_ISFIFO(mode))
        return('p');
    if (S_ISSOCK(mode))
        return('s');
}