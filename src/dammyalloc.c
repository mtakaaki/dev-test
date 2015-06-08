#include <stdio.h>
#include <stdlib.h>

#define DAMMY_SIZE (1000000000)

int main() {
    char *v = (char*)malloc(DAMMY_SIZE);
	int i, sum = 0;
	for (i = 0; i < DAMMY_SIZE; i++) {
		v[i] = rand();
	}
    sleep(10);
	for (i = 0; i < DAMMY_SIZE; i++) {
		sum += v[i];
	}
	printf("%d", sum);
}
