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

        prevnum = strtol(strtok(line, " "), NULL, 10);
        char *nexttok = strtok(NULL, " ");
        int diff = 0;
        int prevdiff = 0;
        int issafe = 1;
        int first = 1;
        int removed = 0;

        while (nexttok != NULL) {
            num = strtol(nexttok, NULL, 10);

            //islinesafe = issafe(num, prevnum, diff);

            /*
            if (!islinesafe && prevprevnum != 0x7fffffff) {
                islinesafe = issafe(num, prevprevnum, prevdiff);
            }
            if (!islinesafe) {
                printf("break\n");
                break;
            }
            */

            printf("n: %d, pn: %d, ppn: %d, safe: %d\n", num, prevnum, prevprevnum, issafe);
            if (prevnum - num == 0) {
                issafe = 0;
                goto recheck;
            }
            else if (diff > 0 && prevnum - num < 0 ) {
                issafe = 0;
                goto recheck;
            }
            else if (diff < 0 && prevnum - num > 0 ) {
                issafe = 0;
                goto recheck;
            }
            else if (abs(prevnum - num) > 3) {
                issafe = 0;
                goto recheck;
            }
            else {
                goto nocheck;
            }

            recheck:
            if (removed) {
                goto nocheck;
            }
            removed = 1; 
            if (prevprevnum - num == 0) {
                issafe = -1;
            }
            else if (prevdiff > 0 && prevprevnum - num < 0 ) {
                issafe = -1;
            }
            else if (prevdiff < 0 && prevprevnum - num > 0 ) {
                issafe = -1;
            }
            else if (abs(prevprevnum - num) > 3) {
                issafe = -1;
            }
            issafe += 1;
            printf("safe is now %d\n", issafe);
            if (issafe == 1) {
                diff = prevprevnum - num;
                prevnum = num;
                nexttok = strtok(NULL, " ");
                continue;
            }

            nocheck:

            prevdiff = diff;
            diff = prevnum - num;

            prevprevnum = prevnum;
            prevnum = num;

            nexttok = strtok(NULL, " ");
        }

        printf("%d\n", issafe);
        safe += issafe;

        prevprevnum = 0x7fffffff;

        its++;
    }

    printf("safe: %d\n", safe);

    return EXIT_SUCCESS;
}
