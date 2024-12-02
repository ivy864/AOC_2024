#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int issafe(int *num, int len, int ignore) {
    int direction;
    int diff;

    for (int i = 0; i < len - 1; i++) {
        if (i == ignore) {
            if (i == 0) {
                direction = num[2] - num[1];
                direction = abs(direction) / direction ;
            }
            continue;
        }
        else if (i == 0) {
            if (ignore == 1) {
                direction = num[i + 2] - num[i];
            }
            else {
                direction = num[i + 1] - num[i];
            }
            direction = abs(direction) / direction ;
        }
        if (i + 1 == ignore) {
            if (ignore == len - 1) {
                return 1;
            }
            diff = num[i + 2] - num[i];
        }
        else {
            diff = num[i + 1] - num[i];
        }

        if (direction != abs(diff) / diff) {
            return 0;
        }
        else if (abs(diff) > 3 || diff == 0) {
            return 0;
        }
    }

    return 1;
}


int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    char line[256];

    int its = 0;
    int safe = 0;

    int islnsafe = 0;
    while (fgets(line, 256, input)) {
        printf("%s", line);
        islnsafe = 0;

        int nums[20];
        int numcount = 1;
        nums[0] = strtol(strtok(line, " "), NULL, 10);
        char *nexttok = strtok(NULL, " ");
        

        while (nexttok != NULL) {
            nums[numcount] = strtol(nexttok, NULL, 10);
            nexttok = strtok(NULL, " ");
            numcount++;
        }
        islnsafe = issafe(nums, numcount, -1);
        printf("safty: %d\n", islnsafe);
        if (!islnsafe) {
            for (int i = 0; i < numcount; i++) {
                islnsafe = issafe(nums, numcount, i);
                printf("removed element %d. safty: %d\n", i, islnsafe);
                if (islnsafe) {
                    break;
                }
            }
        }
        safe += islnsafe;

    }

    printf("safe: %d\n", safe);

    return EXIT_SUCCESS;
}
