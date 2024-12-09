#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getlast(char line[20010], int size, int bsize) {
    for (int i = 1; i < size; i += 2) {
        if (bsize <= line[i]) {
            return i;
        }
    }
    return -1;
}

void printarr(int *line, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", line[i]);
    }
    printf("\n");
}
void printcarr(char line[20010], int size) {
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
    char linecp[20010];

    int its = 0;

    fgets(line, 20010, input);

    uint64_t total = 0;

    int size =  strlen(line) - 1;
    uint32_t sum = 0;

    for (int i = 0; i < size; i++) {
        line[i] = line[i] - '0';
        linecp[i] = line[i];
        sum += line[i];
    }

    int *mem = calloc(sum, sizeof(int));

    int blockpos = 0;

    for (int i = 0; i < size; i++) {
        if (i % 2 == 0) {
            for (int j = 0; j < line[i]; j++) {
                mem[blockpos] = i / 2;
                blockpos++;
            }
        }
        else {
            blockpos += line[i];
        }
    }
    for (int i = size - 1; i > 0; i -= 2) {
        int last = getlast(line, size, linecp[i]);
        //printf("l:%d, n: %d, size: %d\n", last, i / 2, linecp[i]);
        if (last != -1 && last < i) {
            int off = 0;

            for (int j = 0; j < last; j++) {
                off += line[j];
                //printf("off:%d\n", off);
            }
            
            int oldoff = 0;
            for (int j = 0; j < sum; j++) {
                if (mem[j] == i / 2) {
                    oldoff = j;
                    break;
                }
            }
            for (int j = 0; j < linecp[i]; j++) {
                mem[off + j] = i / 2;
                mem[oldoff + j] = 0;
            }

            line[last] -= linecp[i];
            line[last - 1] += linecp[i];
        }
    }

    for (int i = 0; i < sum; i++) {
        total += i * mem[i];
    }

    printf("\n%lu\n", total);

    return EXIT_SUCCESS;
}
