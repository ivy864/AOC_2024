#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getsimilarity(int *nums, int num, int len) {
    int sim = 0; 
    for (int i = 0; i < len; i++) {
        if (nums[i] == num) {
            sim++;
        }
    }

    return sim;
}

int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    char line[256];

    int num1, num2;

    int lnums[1000];
    int rnums[1000];

    int its = 0;
    while (fgets(line, 256, input)) {
        num1 = strtol(strtok(line, "   "), NULL, 10);
        num2 = strtol(strtok(NULL, "   "), NULL, 10);
        lnums[its] = num1;
        rnums[its] = num2;
        its++;
    }

    int total = 0;
    for (int i = 0; i < its; i++) {
        total += getsimilarity(rnums, lnums[i], its) * lnums[i];
    }

    printf("total: %d\n", total);
    return EXIT_SUCCESS;
}

