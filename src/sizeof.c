#include <stdio.h>

int main(void) {
    printf("char = %d\n", sizeof(char));
    printf("short = %d\n", sizeof(short));
    printf("int = %d\n", sizeof(int));
    printf("long = %d\n", sizeof(long));
    printf("long long = %d\n", sizeof(long long));
    printf("pointer = %d\n", sizeof(void*));
}
