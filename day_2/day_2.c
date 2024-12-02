#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    char line[256];

    int its = 0;
    int safe = 0;

    int prevnum, num;
    while (fgets(line, 256, input)) {
        printf("line: %s", line);
        prevnum = strtol(strtok(line, " "), NULL, 10);
        char *nexttok = strtok(NULL, " ");
        int diff = 0;
        int issafe = 1;
        int first = 1;

        while (nexttok != NULL) {
            num = strtol(nexttok, NULL, 10);
            if (prevnum - num == 0) {
                issafe = 0;
                printf("zero\n");
            }
            else if (diff > 0 && prevnum - num < 0 ) {
                
                issafe = 0;
                printf("thing1\n");
            }
            else if (diff < 0 && prevnum - num > 0 ) {
                issafe = 0;
                printf("thing2\n");
            }
            else if (abs(prevnum - num) > 3) {
                issafe = 0;
                printf("thing:%d\n",abs(prevnum - num));
            }
            printf("issafe: %d\n", issafe);

            diff = prevnum - num;
            prevnum = num;
            nexttok = strtok(NULL, " ");
        }

        safe += issafe;


        its++;
    }

    printf("safe: %d\n", safe);
    printf("its: %d\n", its);

    return EXIT_SUCCESS;
}
