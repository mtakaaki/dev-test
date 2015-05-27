#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

/* 省略時の文字数 */
#define DEFAULT_NUM 8

/* 候補文字のワークバッファのサイズ */
#define MAXBUF 1000

enum CharType {
    CTYPE_NONE,
    CTYPE_NUMBER,
    CTYPE_LOWER,
    CTYPE_UPPER,
    CTYPE_SYMBOL
};

struct StrType {
    enum CharType ctype;
    int weight; // 出現の重み
    char *s; // 文字列
};

struct StrType stype[] = {
    {CTYPE_NUMBER, 3, "1234567890"},
    {CTYPE_LOWER, 2, "abcdefghijklmnopqrstuvwxyz"},
    {CTYPE_UPPER, 2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"},
    {CTYPE_SYMBOL, 1, "!\"#$%&'()-^\\=~|@[;:],./`{+*}<>?_"},
    {CTYPE_NONE, -1, ""}
};

int main(int argc, char *argv[]) {
    int num = DEFAULT_NUM; // 生成文字数
    char buf[MAXBUF]; // 候補文字

    if (argc >= 2) {
        num = atol(argv[1]);
    }
    if (num <= 0) {
        fprintf(stderr, "%s [Number>0]\n", argv[0]);
        exit(-1);
    }

    // 乱数初期化
    srand(time(NULL));

    // 候補文字生成
    buf[0] = '\0';
    for (int i = 0 ; stype[i].weight >= 0 ; i++) {
        if (strlen(buf) + strlen(stype[i].s) * stype[i].weight > MAXBUF) {
            fputs("Not enough buf\n", stderr);
            exit(-1);
        }

        for (int j = 0; j < stype[i].weight; j++) {
            strcat(buf,stype[i].s);
        }
    }

    int len = strlen(buf); // 候補文字列長

    // プロセスID回分のシャッフル
    for (int i = 0; i < getpid(); i++) {
        int pos1 = rand() % len;
        int pos2 = rand() % len;
        if (pos1 != pos2) {
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
    putchar('\n');

    return 0;
}
