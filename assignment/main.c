#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "student.h"


int listdb(char* filename);
int querydb(char * filename);
int updatedb(char *filename);
int insertdb(char * filename);
int deletedb(char * filename);


int main(int argc, char *argv[]){
    int selection = 0;
    if (argc < 2) {
        fprintf(stderr, "사용법 : %s file\n", argv[0]);
        printf("ㅁㄴㅇㄹㅁㄴㅇㄹ");
        exit(1);
    }
    while(1) {
    // for (int i = 0; i < 5; i++) {
        printf("\n****** 학생정보시스템******\n\n");
        printf("1. 전체 학생 보기 \n");
        printf("2. 학생 정보 검색 \n");
        printf("3. 학생 정보 수정 \n");
        printf("4. 학생 정보 등록 \n");
        printf("5. 학생 정보 삭제 \n");
        printf("6. 종료\n");
        printf("\n선택 : ");
        scanf(" %d", &selection);
        switch(selection){
            case 1:
                listdb(argv[1]);
                break;
            case 2:
                querydb(argv[1]); 
                break;
            case 3:
                updatedb(argv[1]);
                break;
            case 4:
                insertdb(argv[1]);
                break;
            case 5:
                deletedb(argv[1]);
                break;
            case 6:
                return(0);
            default:
                break;
        }
    }
    exit(0);
}
