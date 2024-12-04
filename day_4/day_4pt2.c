#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ismas(char c1, char c2) {
    if ((c1 == 'M' && c2 == 'S') || (c1 == 'S' && c2 == 'M')) {
        return 1;
    }
    return 0;
}

int isxmas(char d[150][150], int row, int col) {
    if (ismas(d[row+1][col+1], d[row-1][col-1]) && 
            ismas(d[row+1][col-1], d[row-1][col+1])) {

        printf("ismas: %d %d \n", row, col);

        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    char line[150][150];

    int its = 0;
    while (fgets(line[its], 150, input)) {
        its++;
    }

    int total = 0;

    for (int i = 1; i < its; i++) {
        for(int j = 1; j < strlen(line[i]); j++) {
            if (line[i][j] == 'A') {
                total += isxmas(line, i, j);
            }
        }
    }

    printf("total:%d\n", total);

    return EXIT_SUCCESS;
}
