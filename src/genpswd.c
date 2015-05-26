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
    int ctype; // 字種
    int weight; // 出現の重み
    char *s; // 文字列
};


struct StrType stype[] = {
    {C_NUMERIC,   2, "1234567890"},
    {C_LOWERCASE, 2, "abcdefghijklmnopqrstuvwxyz"},
    {C_UPPERCASE, 2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
    {C_SYMBOL, 1, "!\"#$%&'()@`+*<>?_\\{}[]=~|.,"},
    {C_END, 0, ""}
};

int main(int argc, char *argv[]) {
    int num = 8; // 生成文字数
    char buf[1024]; // 候補文字

    if (argc >= 2) {
        num = atol(argv[1]);
    }

    srand(time(NULL));

    // 候補文字生成
    buf[0] = '\0';
    for (int i = 0 ; stype[i].ctype != C_END ; i ++) {
        for (int j = 0; j < stype[i].weight; j++) {
            strcat(buf,stype[i].s);
        }
    }

    int len = strlen(buf); // 候補文字列長

    // プロセスID回分のシャッフル
    for (int i = 0; i < getpid(); i++) {
        int pos1 = rand() % len;
        int pos2 = rand() % len;
        if (pos1 != pos1) {
            char tmp = buf[pos1];
            buf[pos1] = buf[pos2];
            buf[pos2] = tmp;
        }
    }

    // ランダムに文字を生成
    while (num--) {
        int pos = rand() % len;
        putchar(buf[pos]);
    }

    return 0;
}
