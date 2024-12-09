#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getlast(char line[20010], int size) {
    for (int i = size - 1; i > 0; i -= 2) {
        if (line[i] != 0) {
            return i;
        }
    }
    return -1;
}

void printarr(char line[2010], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", line[i]);
    }
    printf("\n");
}
int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    char line[20010];

    int its = 0;

    fgets(line, 20010, input);

    uint64_t total = 0;

    int size =  strlen(line) - 1;

    for (int i = 0; i < size; i++) {
        line[i] = line[i] - '0';
    }

    int blockpos = 0;
    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < line[i]; j++) {
                printf("%d", i/2);
                total += blockpos * (i / 2);
                blockpos++;
            }
        }
        else {
            if (getlast(line, size) < i) {
                break;
            }
            for (int j = 0; j < line[i]; j++) {
                total += blockpos * (getlast(line, size) / 2);
                printf("%d", (getlast(line, size) / 2));
                line[getlast(line, size)] -= 1;
                blockpos++;
            }
        }
    }

    
    printf("\n%lu\n", total);

    return EXIT_SUCCESS;
}
