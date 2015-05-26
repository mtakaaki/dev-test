#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

enum CharType {
    C_NUMERIC, 
    C_LOWERCASE,
    C_UPPERCASE,
    C_SYMBOL,
    C_END
};

struct StrType {
    int ctype;
    int weight;
    char *s;
};


struct StrType stype[] = {
    {C_NUMERIC,   2, "1234567890"},
    {C_LOWERCASE, 2, "abcdefghijklmnopqrstuvwxyz"},
    {C_UPPERCASE, 2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
    {C_SYMBOL, 1, "!\"#$%&'()@`+*<>?_\\{}[]=~|.,"},
    {C_END, 0, ""}
};

int main(int argc, char *argv[]) {
    int num = 8;
    char buf[1024];

    if (argc >= 2) {
        num = atol(argv[1]);
    }

    srand(time(NULL) + getpid());

    buf[0] = '\0';
    for (int i = 0 ; stype[i].ctype != C_END ; i ++) {
        for (int j = 0; j < stype[i].weight; j++) {
            strcat(buf,stype[i].s);
        }
    }

    int len = strlen(buf);
    while (num--) {
        int pos = rand() % len;
        putchar(buf[pos]);
    }

    return 0;
}
