#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "student.h"


/* 파일에 저장된 모든 학생 정보를 읽어서 츨력한다. */
int listdb(char* filename) {
    struct student rec;
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "파일 열기 오류 \n");
        return 1;
    }
    printf("-----------------------------------\n");
    printf("%10s %6s %6s\n", "학번", "이름", "점수");
    printf("-----------------------------------\n"); 

    while (fread(&rec, sizeof(rec), 1, fp) > 0) {
        if (rec.id != 0)
            printf("%10d %6s %6d\n", rec.id, rec.name, rec.score);
    } 
    printf("-----------------------------------\n");
    fclose(fp);
    return 0;
}

/* 학번을 입력받아 해당 학생의 레코드를 파일에서 읽어 출력한다. */
int querydb(char * filename){
    printf("querydb START_ID: %d\n", START_ID);
    struct student rec;
    char c;
    int id;
    FILE *fp;
    if ((fp = fopen(filename, "rb")) == NULL) {
        fprintf(stderr, "파일 열기 오류\n");
        exit(2);
    }
    do {
        printf("검색할 학생의 학번 입력: ");
        if (scanf("%d", &id) == 1) {
            fseek(fp, (id - START_ID) *sizeof(rec), SEEK_SET);
            printf("(id - START_ID) *sizeof(rec): %d\n", (id - START_ID) *sizeof(rec));

            if ((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.id != 0)) {
                printf("학번: %8d 이름: %4s\n", rec.id, rec.name, rec.score);
            }
            else printf("레코드 %d 없음\n", id);

            printf("계속하겠습니까?(Y/N)");
            scanf(" %c", &c);
        } 
    }
    while (c == 'Y');
    fclose(fp);
    return 0;
}
/* 학번을 입력받아 해당 학생 레코드를 수정한다. */
int updatedb(char *filename){
    struct student rec;
    int id;
    char c;
    FILE *fp;

    if ((fp = fopen(filename, "rb+")) == NULL) {
        fprintf(stderr, "파일 열기 오류\n");
        exit(2);
    }

    do {
        printf("파일 위치(FILE *fp): %d", *fp);
        printf("수정할 학생의 학번 입력: ");
        if (scanf("%d", &id) == 1) {
            printf("%d", id);

            printf("fseek이전 fp: %d", *fp);

            fseek(fp, (id - START_ID)*sizeof(rec), SEEK_SET);

            printf("fseek이후 fp: %d", *fp);
            printf("fseek이후 id: %d", id);
            printf("fseek이후 sid: %d", START_ID);
            printf("fseek이후 s(rec): %d", sizeof(rec));

            if ((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.id != 0)) { 
                // printf("fread이후 fp: %d", &fp);
                printf("학번: %8d 이름: %4s 점수: %4d\n", rec.id, rec.name, rec.score);
                printf("새로운 점수 입력: ");
                scanf("%d", &rec.score);
                fseek(fp, (long)-sizeof(rec), SEEK_CUR);
                fwrite(&rec, sizeof(rec), 1, fp);
            }
            else printf("레코드 %d 없음\n", id);
        }
        else printf("입력오류\n");
        printf("계속하겠습니까?(Y/N)");
        scanf(" %c",&c);
    }
    while (c == 'Y');
    fclose(fp);
    return 0;
}
/* 학생 정보를 입력받아 데이터베이스 파일에 저장한다. */
int insertdb(char * filename){
    struct student rec;
    FILE *fp;
    char c;
    fp = fopen(filename, "ab");
    printf("파일 위치(FILE *fp): %d", &fp);
    do 
    {
        printf("새로운 학생 정보 등록을 시작합니다.\n");
        printf("학번 : ");
        scanf("%d", &rec.id);
        printf("이름 : ");
        scanf("%s", rec.name);
        printf("성적 : ");
        scanf("%hd", &rec.score);

        printf("[insert] fseek이전 fp: %d", fp);
        printf("[insert] fseek이전 *fp: %d", *fp);
        printf("[insert] fseek이전 &fp: %d", &fp);

        fseek(fp, (rec.id - START_ID)*sizeof(rec), SEEK_SET);

        printf("[insert] fseek이후 fp: %d", *fp);
        printf("fseek이후 id: %d", rec.id);
        printf("fseek이후 sid: %d", START_ID);
        printf("fseek이후 s(rec): %d", sizeof(rec));

        printf("아니 왜 출력이?");
        // printf("%d", &rec.id);
        printf("%d", rec.id);

        fwrite(&rec, sizeof(rec), 1, fp);

        printf("fwrite *fp: %d", *fp);
        printf("fwrite &fp: %d", &fp);

        printf("새로운 학생 정보가 %d에 등록되었습니다.\n계속하겠습니까?(Y/N)", (rec.id - START_ID)*sizeof(rec));

        scanf(" %c",&c);



    }
    while (c == 'Y');
    fclose(fp);
    return 0;
}
/* 학생 학번을 입력받아 해당 학생 정보를 데이터베이스 파일에서 삭제한다. */
 int deletedb(char *filename) {
    int id;
    char c;
    FILE *fp;
    struct student rec;

    if ((fp = fopen(filename, "rb+")) == NULL) {
        perror(filename);
        return 1;
    }
    do {
        printf("삭제할 학생의 학번 입력: ");
        if (scanf("%d", &id) == 1) {
            fseek(fp, (id - START_ID) * sizeof(rec), SEEK_SET);
            if ((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.id != 0)) {
                rec.id = 0; // 학생 정보 삭제를 위해 학번을 0으로 설정
                fseek(fp, -sizeof(rec), SEEK_CUR);
                fwrite(&rec, sizeof(rec), 1, fp);
                printf("학번이 %d인 학생 정보가 삭제되었습니다.\n", id);
            } else {
                printf("레코드 %d 없음\n", id);
            }
        } else {
            printf("입력 오류\n");
            break;
        }
        printf("계속하겠습니까?(Y/N)");
        scanf(" %c", &c);
    } while (c == 'Y' || c == 'y');

    fclose(fp);
    return 0;
 }