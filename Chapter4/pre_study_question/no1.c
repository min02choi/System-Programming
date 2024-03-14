# include <stdio.h>

void ascii_to_hex() {
    char c1 = '0';
    char c2 = '1';
    char c3 = 'A';

    printf("16진수 >> %x, %x, %x\n", c1, c2, c3);
}

void ascii_to_bin() {
    char c1 = '0';
    char c2 = '1';
    char c3 = 'A';

    int n = 52;

    int bin[10] = {0};

    printf("2진수 >> ");
    for (int i = 7; i >= 0; i--) {
        int result = n >> i & 1;
        printf("%d", result);
    }
}

int main() {
    // 1. ‘0’, ‘1’, ‘A’ 의 아스키 코드 값을 16진수 나타내면?
    ascii_to_hex();
    ascii_to_bin();

}