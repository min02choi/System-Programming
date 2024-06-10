#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <ctype.h>

#define MAXARG 256
#define MAXLINE 512

int main() {
    char buf[256];
    char *args[MAXARG];
    char *s;
    char *save;
    int argn;
    static const char delim[] = " \t\n"; /* 공백, 탭, 개행으로 이루어진 구분자 선언 */
    int pid[MAXARG], status;
    int i, ch;
    int fd;

    while (1) { /* 무한 반복 */
        printf("[SHELL] "); /* 프롬프트 출력 */
        fgets(buf, sizeof(buf), stdin);

        ch = 1;
        for (i = 0; buf[i] != '\0'; i++) {
            if (buf[i] == '&') {
                ch = 2; break;
            } else if (buf[i] == '>') {
                ch = 3; break;
            } else if (buf[i] == '<') {
                ch = 4; break;
            } else if (buf[i] == ';') {
                ch = 5; break;
            } else if (buf[i] == '|') {
                ch = 6; break;
            } else if (isdigit(buf[0])) {
                ch = 7; break;
            }
        }

        if (ch == 1) {
            argn = 0;
            s = strtok_r(buf, delim, &save); /* 문자열에서 delim을 기준으로 단어를 잘라냄 */

            while (s) {
                args[argn++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args[argn] = NULL; /* 인수가 더 없음을 의미하는 문자 추가 */
            if (argn == 0) /* 명령어가 없으면 루프 계속 */
                continue;
            if (!strcmp(args[0], "quit")) /* ‘quit’이면 while 문 벗어남 */
                break;

            if ((pid[0] = fork()) == -1) /* fork 호출에 실패하면 */
                perror("fork failed");
            else if (pid[0] == 0) { /* 부모 프로세스는 자식 프로세스가 종료되기를 기다림 */
                execvp(args[0], args);
                fprintf(stderr, "%s: 실행 불가\n", args[0]);
                exit(1);
            } else { /* 자식 프로세스는 execvp를 이용하여 arg[0] 실행 */
                waitpid(pid[0], &status, 0);
            }
        }

        if (ch == 2) {
            char *cmd;
            cmd = strtok_r(buf, "&", &save); /* 문자열에서&을 기준으로 단어를 잘라냄 */
            argn = 0;
            s = strtok_r(cmd, delim, &save); /* 문자열에서 delim을 기준으로 단어를 잘라냄 */
            while (s) {
                args[argn++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args[argn] = NULL; /* 인수가 더 없음을 의미하는 문자 추가 */
            if ((pid[0] = fork()) == 0) {
                execvp(args[0], args);
                fprintf(stderr, "%s: 실행 불가\n", args[0]);
                exit(5);
            } else {
                printf("%s %d\n", cmd, pid[0]);
            }
        }

        if (ch == 3) {
            char *file, *cmd;
            cmd = strtok_r(buf, ">", &save); /* 문자열에서 > 을 기준으로 단어를 잘라냄 */
            file = strtok_r(NULL, " >", &save);
            argn = 0;
            s = strtok_r(cmd, delim, &save); /* 문자열에서 delim을 기준으로 단어를 잘라냄 */
            while (s) {
                args[argn++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args[argn] = NULL; /* 인수가 더 없음을 의미하는 문자 추가 */
            if ((pid[0] = fork()) == 0) {
                fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0600);
                dup2(fd, 1);
                close(fd);
                execvp(args[0], args);
                fprintf(stderr, "%s: 실행 불가\n", args[0]);
                exit(3);
            } else {
                waitpid(pid[0], &status, 0);
            }
        }

        if (ch == 4) {
            char *file, *cmd;
            cmd = strtok_r(buf, "<", &save); /* 문자열에서 < 을 기준으로 단어를 잘라냄 */
            file = strtok_r(NULL, " <", &save);
            argn = 0;
            s = strtok_r(cmd, delim, &save); /* 문자열에서 delim을 기준으로 단어를 잘라냄 */
            while (s) {
                args[argn++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args[argn] = NULL; /* 인수가 더 없음을 의미하는 문자 추가 */
            if ((pid[0] = fork()) == 0) {
                fd = open(file, O_RDONLY);
                dup2(fd, 0);
                close(fd);
                execvp(args[0], args);
                fprintf(stderr, "%s: 실행 불가\n", args[0]);
                exit(4);
            } else {
                waitpid(pid[0], &status, 0);
            }
        }

        if (ch == 5) {
            char *args1[MAXARG];
            int argn1;
            argn = 0;
            s = strtok_r(buf, ";", &save); /* 문자열에서 ; 을 기준으로 단어를 잘라냄 */
            while (s) {
                args[argn++] = s;
                s = strtok_r(NULL, ";", &save);
            }
            args[argn] = NULL; /* 인수가 더 없음을 의미하는 문자 추가 */
            for (i = 0; i < argn; i++) {
                s = strtok_r(args[i], delim, &save);
                argn1 = 0;
                while (s) {
                    args1[argn1++] = s;
                    s = strtok_r(NULL, delim, &save);
                }
                args1[argn1] = NULL; /* 인수가 더 없음을 의미하는 문자 추가 */
                if ((pid[i] = fork()) == 0) {
                    execvp(args1[0], args1);
                    fprintf(stderr, "%s: 실행 불가\n", args1[0]);
                    exit(2);
                } else {
                    waitpid(pid[i], &status, 0);
                }
            }
        }

        if (ch == 6) {
            char *cmd1, *cmd2;
            char *args1[MAXARG];
            int argn1 = 0;
            argn = 0;

            FILE *fpin, *fout;
            char command1[MAXLINE] = "";
            char command2[MAXLINE] = "";
            char buffer[MAXLINE];

            // 문자열에서 |을 기준으로 단어를 잘라냄
            cmd1 = strtok_r(buf, "|", &save);
            cmd2 = strtok_r(NULL, "|", &save);

            // cmd1 에서 delim을 기준으로 단어를 잘라냄
            s = strtok_r(cmd1, delim, &save);
            while (s) {
                args[argn++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args[argn] = NULL;  /* 인수가 더 없음을 의미하는 문자 추가  */

            /* cmd2 에서 delim을 기준으로 단어를 잘라냄 */
            s = strtok_r(cmd2, delim, &save);
            while (s) {
                args1[argn1++] = s;
                s = strtok_r(NULL, delim, &save);
            }
            args1[argn1] = NULL;

            for (int i = 0; args[i] != NULL; i++) {
                strcat(command1, args[i]);
                strcat(command1, " ");
            }

            for (int i = 0; args1[i] != NULL; i++) {
                strcat(command2, args1[i]);
                strcat(command2, " ");
            }

            /* cmd1 명령 실행 및 출력 파이프 열기 */
            if ((fpin = popen(command1, "r")) == NULL) {
                perror("popen cmd1");
                pclose(fout);   // 이거 하면 안되나?
                exit(6);
            }

            /* cmd2 명령 실행 및 입력 파이프 열기 */
            if ((fout = popen(command2, "w")) == NULL) {
                perror("popen cmd2");
                pclose(fpin);
                exit(6);
            }

            /* cmd1의 출력을 읽어서 cmd2의 입력으로 전달 */
            while (fgets(buffer, sizeof(buffer), fpin) != NULL) {
                fputs(buffer, fout);
            }

            pclose(fpin);
            pclose(fout);
        }

    }

    return 0;
}