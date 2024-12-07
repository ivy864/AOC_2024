#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t numtotal(uint32_t nums[100], int numslen, uint64_t expected) {
    uint32_t op = 1;
    for (int i = 0; i < numslen - 2; i++) {
        op = op << 1;
        op = op | 1;
    }

    for (int _i = 0; _i < 2 << numslen; _i++) {
        printf("%d out of %d\n", _i, 2 << numslen);
        uint64_t total = nums[0];
        int opcur = 1;
        for (int i = 1; i < numslen; i++) {
            if (op & opcur) {
                printf(" + ");
                total += nums[i];
            }
            else {
                printf(" * ");
                total *= nums[i];
            }
            opcur = opcur << 1;
        }
        printf("\n%lu, %lu\n",expected ,total );
        if (total == expected) {
            printf("expected!\n");
            return total;
        }

        op -= 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    char line[256];

    uint64_t total = 0;
    int its = 0;
    uint32_t nums[100];
    while (fgets(line, 256, input)) {
        printf("%s", line);
        int numslen = 0;
        for (int i = 0; i < 100; i++) {
            nums[i] = 0;
        }

        char *end = strchr(line, ':');
        uint64_t fin = strtol(line, &end, 10);

        char *l = end + 2;
        end = strchr(l, ' ');
        while (end != NULL) {
            nums[numslen] = strtol(l, &end, 10);
            l = end;
            end = strchr(l, ' ');
            numslen += 1;
        }

        total += numtotal(nums, numslen, fin);
    }

    printf("total: %lu", total);

    return EXIT_SUCCESS;
}
