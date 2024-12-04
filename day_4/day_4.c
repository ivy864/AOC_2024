#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkxmas(char c1, char c2, char c3, char c4) {
    if (c1 == 'X' && c2 == 'M' && c3 == 'A' && c4 == 'S') {
        return 1;
    }
    return 0;
}
int checkoffsets(char d[150][150], int row, int col) {
    int count = 0;

    count += checkxmas(d[row][col], d[row][col+1], d[row][col+2], d[row][col+3]);

    if (col >= 3) {
        count += checkxmas(d[row][col], d[row][col-1], d[row][col-2], d[row][col-3]);

        count += checkxmas(d[row][col], d[row+1][col-1], d[row+2][col-2], d[row+3][col-3]);
    }
    count += checkxmas(d[row][col], d[row+1][col], d[row+2][col], d[row+3][col]);
    if (row >= 3) {
        count += checkxmas(d[row][col], d[row-1][col], d[row-2][col], d[row-3][col]);

        count += checkxmas(d[row][col], d[row-1][col+1], d[row-2][col+2], d[row-3][col+3]);
        if (col >= 3) {
            count += checkxmas(d[row][col], d[row-1][col-1], d[row-2][col-2], d[row-3][col-3]);
        }
    }
    count += checkxmas(d[row][col], d[row+1][col+1], d[row+2][col+2], d[row+3][col+3]);

    return count;
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

    for (int i = 0; i < its; i++) {
        for(int j = 0; j < strlen(line[i]); j++) {
            total += checkoffsets(line, i, j);
        }
    }

    printf("total:%d\n", total);

    return EXIT_SUCCESS;
}
