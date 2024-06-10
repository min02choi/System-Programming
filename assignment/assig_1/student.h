#ifndef _STUDENT_H_
#define _STUDENT_H_
#define MAX 24
#define START_ID 1

struct student {
    char name[MAX];
    int id;
    int score;
};

int insertdb(char *);
int querydb(char *);
int updatedb(char *);
int listdb(char *);
int deletedb(char *);

#endif