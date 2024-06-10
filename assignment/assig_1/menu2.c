#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "student.h"


// 학생 정보 조회
int listdb(char* filename) {
    struct student rec;
    int fd;

    if ((fd = open(filename, O_RDONLY)) < 0) {
        fprintf(stderr, "파일 열기 오류 \n");
        return 1;
    }
    
    printf("-----------------------------------\n");
    printf("%10s %6s %6s\n", "학번", "이름", "점수");
    printf("-----------------------------------\n");

    while (read(fd, &rec, sizeof(rec)) > 0) {
        if (rec.id != 0)
            printf("%10d %6s %6d\n", rec.id, rec.name, rec.score);
    }
    printf("-----------------------------------\n");
    close(fd);
    return 0;
}

// 학생 정보 검색
int querydb(char *filename) {
    struct student rec;
    char c;
    int id;
    int fd;

    if ((fd = open(filename, O_RDONLY)) < 0) {
        fprintf(stderr, "파일 열기 오류\n");
        return 1;
    }

    do {
        printf("검색할 학생의 학번 입력: ");
        if (scanf("%d", &id) == 1) {
            off_t offset = (id - START_ID) * sizeof(rec);
            printf("(id - START_ID) * sizeof(rec): %ld\n", offset);
            if (lseek(fd, offset, SEEK_SET) != -1 && read(fd, &rec, sizeof(rec)) > 0 && rec.id != 0) {
                printf("학번: %8d 이름: %s 점수: %d\n", rec.id, rec.name, rec.score);
            }
            else {
                printf("레코드 %d 없음\n", id);
            }
            printf("계속하겠습니까?(Y/N)");
            scanf(" %c", &c);
        }
    } while (c == 'Y' || c == 'y');

    close(fd);
    return 0;
}

// 학생 정보 수정
int updatedb(char *filename) {
    struct student rec;
    int id;
    char c;
    int fd;

    if ((fd = open(filename, O_RDWR)) < 0) {
        fprintf(stderr, "파일 열기 오류\n");
        return 1;
    }

    do {
        printf("수정할 학생의 학번 입력: ");
        if (scanf("%d", &id) == 1) {
            off_t offset = (id - START_ID) * sizeof(rec);
            printf("(id - START_ID) * sizeof(rec): %ld\n", offset);
            if (lseek(fd, offset, SEEK_SET) != -1 && read(fd, &rec, sizeof(rec)) > 0 && rec.id != 0) {
                printf("학번: %8d 이름: %s 점수: %d\n", rec.id, rec.name, rec.score);
                printf("새로운 점수 입력: ");
                scanf("%d", &rec.score);
                lseek(fd, offset, SEEK_SET);
                write(fd, &rec, sizeof(rec));
            }
            else {
                printf("레코드 %d 없음\n", id);
            }
        }
        else {
            printf("입력오류\n");
        }
        printf("계속하겠습니까?(Y/N)");
        scanf(" %c", &c);
    } while (c == 'Y' || c == 'y');

    close(fd);
    return 0;
}

// 학생정보 추가
int insertdb(char *filename) {
    struct student rec;
    char c;
    int fd;

    if ((fd = open(filename, O_RDWR)) < 0) {
        fprintf(stderr, "파일 열기 오류\n");
        return 1;
    }

    do {
        printf("새로운 학생 정보 등록을 시작합니다.\n");
        printf("학번 : ");
        scanf("%d", &rec.id);
        printf("이름 : ");
        scanf("%s", rec.name);
        printf("성적 : ");
        scanf("%d", &rec.score);
        
        off_t offset = (rec.id - START_ID) * sizeof(rec);
        printf("(rec.id - START_ID) * sizeof(rec): %ld\n", offset);
        if (lseek(fd, offset, SEEK_SET) != -1 && write(fd, &rec, sizeof(rec)) == sizeof(rec)) {
            printf("새로운 학생 정보가 등록되었습니다.\n계속하겠습니까?(Y/N)");
            scanf(" %c", &c);
        }
        else {
            printf("등록 실패\n");
            close(fd);
            return 1;
        }
    } while (c == 'Y' || c == 'y');

    close(fd);
    return 0;
}

// 학생 정보 삭제
int deletedb(char *filename) {
    int id;
    char c;
    int fd;
    struct student rec;

    if ((fd = open(filename, O_RDWR)) < 0) {
        perror(filename);
        return 1;
    }

    do {
        printf("삭제할 학생의 학번 입력: ");
        if (scanf("%d", &id) == 1) {
            off_t offset = (id - START_ID) * sizeof(rec);
            printf("(id - START_ID) * sizeof(rec): %ld\n", offset);
            if (lseek(fd, offset, SEEK_SET) != -1 && read(fd, &rec, sizeof(rec)) > 0 && rec.id != 0) {
                rec.id = 0; 
                lseek(fd, -sizeof(rec), SEEK_CUR);
                if (write(fd, &rec, sizeof(rec)) == sizeof(rec)) {
                    printf("학번이 %d인 학생 정보가 삭제되었습니다.\n", id);
                } else {
                    printf("삭제 실패\n");
                    close(fd);
                    return 1;
                }
            }
            else {
                printf("레코드 %d 없음\n", id);
            }
        }
        else {
            printf("입력 오류\n");
            break;
        }
        printf("계속하겠습니까?(Y/N)");
        scanf(" %c", &c);
    } while (c == 'Y' || c == 'y');

    close(fd);
    return 0;
}