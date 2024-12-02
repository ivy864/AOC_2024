#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
int issafe (int num, int prevnum, int diff) {
    int safe = 1;
    if (prevnum - num == 0) {
        safe = 0;
    }
    else if (diff > 0 && prevnum - num < 0 ) {
        safe = 0;
    }
    else if (diff < 0 && prevnum - num > 0 ) {
        safe = 0;
    }
    else if (abs(prevnum - num) > 3) {
        safe = 0;
    }

    return safe;
}

int issafe(int *num, int *len) {
    for (int i = 0; i < len; i++) {
    }
}

*/

int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    char line[256];

    int its = 0;
    int safe = 0;

    int prevprevnum, prevnum, num;
    while (fgets(line, 256, input)) {
        printf("%s", line);

        int nums[20];
        int numcount = 1;
        nums[0] = strtol(strtok(line, " "), NULL, 10);
        char *nexttok = strtok(NULL, " ");
        

        while (nexttok != NULL) {
            nums[numcount] = strtol(nexttok, NULL, 10);
            numcount++;
        }
        for (int i = 0; i < numcount; i++) {
        }


    }

    printf("safe: %d\n", safe);

    return EXIT_SUCCESS;
}
