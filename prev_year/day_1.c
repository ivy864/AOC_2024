#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }
    int sum = 0;
    char d1, d2;
    d1 = 0;
    d2 = 0; 

    char line[256];
    while (fgets(line, 256, input)) {
        for (int i = 0; i < strlen(line); i++) {
            if (isdigit(line[i])) {
                if (d1 == 0) {
                    d1 = line[i];
                    d2 = line[i];
                }
                else {
                    d2 = line[i];
                }
            }
        }

        d1 -= '0';
        d2 -= '0';
        sum += (d1 * 10) + d2;

        d1 = 0;
        d2 = 0;
    }

    printf("sum: %d\n", sum);

    return EXIT_SUCCESS;
}
