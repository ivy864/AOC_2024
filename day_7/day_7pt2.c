#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

uint64_t iv_concat(uint64_t i1, uint32_t i2) {
    char *tmp = malloc(sizeof(char) * 10);
    sprintf(tmp, "%lu%d", i1, i2);

    return((uint64_t)strtoll(tmp, NULL, 10));
}

void opincr(uint32_t *op, int opsize) {
    if (opsize == 0) {
        return;
    }
    op[0] += 1;
    int carry = 0;
    if (op[0] == 3) {
        carry = 1;
    }

    int i = 1;
    while (carry) {
        if (i > opsize) {
            return;
        }
        op[i - 1] = 0;
        op[i] += 1;
        if (op[i] != 3) {
            carry = 0;
        }
        i += 1;
    }
}

uint64_t numtotal(uint32_t nums[100], int numslen, uint64_t expected) {
    printf("\nNUMTOTAL\n");
    uint32_t *op = calloc(numslen - 1, sizeof(uint32_t));
    
    for (int _i = 0; _i < (uint32_t) pow(3, numslen - 1); _i++) {
        printf("%d out of %d\n", _i, (uint32_t) pow(2, numslen - 1));
        uint64_t total = nums[0];
        int opcur = 0;
        for (int i = 1; i < numslen; i++) {
            //printf("op: %d\n", op[opcur]);
            switch (op[opcur]) {
                case 0:
                    printf(" + ");
                    total += nums[i];
                    break;
                case 1:
                    printf(" * ");
                    total *= nums[i];
                    break;
                case 2:
                    printf(" || ");
                    total = iv_concat(total, nums[i]);
                    break;
            }

            opcur++;    
        }
        printf("\n%lu, %lu\n",expected ,total );
        if (total == expected) {
            printf("expected!\n");
            free(op);
            return total;
        }

        opincr(op, numslen - 1);
    }

    free(op);
    return 0;
}

void printnums(uint32_t nums[100], int numsize) {
    for (int i = 0; i < numsize; i++) {
        printf("%d ", nums[i]);
    }
    printf("\n");
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
        printf("\n%s", line);
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
