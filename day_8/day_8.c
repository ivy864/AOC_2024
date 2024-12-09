#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inbounds(int r, int c, int bounds) {
    if (r < 0 || c < 0 || r >= bounds || c >= bounds) {
        return 0;
    }

    return 1;
}

int getden(int n1, int n2) {
    int den = 0;
    for (int i = 1; i <= abs(n1) && i <= abs(n2); i++) {
        if (n1 % i == 0 && n2 % i == 0) {
            den = i;
        }
    }

    return den;
}

void printnodes(int anode[60][60], int msize) {
    for (int i = 0; i < msize; i++) {
        for (int j = 0; j < msize; j++) {
            if (anode[i][j] != 0) {
                printf("X ");
            }
            else {
                printf("%d ", anode[i][j]);
            }
        }
        printf("\n");
    }
}

int hsuniqand(char map[60][60], int msize, int ndr, int ndc,
              int anode[60][60]) {
    char freq = map[ndr][ndc];
    int anodes = 0;

    for (int i = 0; i < msize; i++) {
        for (int j = 0; j < msize; j++) {
            if (map[i][j] == freq && i != ndr && j != ndc) {
                int gcd = getden((i - ndr), (j - ndc));

                int count = 0;
                int rx = ((i - ndr) / gcd);
                int cx = ((j - ndc) / gcd);

                while(inbounds(ndr + (rx * count), ndc + (cx * count), msize)) {
                    if (anode[ndr + (rx * count)][ndc + (cx * count)] == 0) {
                        anodes += 1;
                    }
                    anode[ndr + (rx * count)][ndc + (cx * count)] += 1;
                    count++;
                }
            }
        }
    }
    printnodes(anode, msize);

    return anodes;
}

int main(int argc, char* argv[]) {
    FILE* input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    char line[256];

    int antinodes[60][60];
    for (int i = 0; i < 60; i++) {
        for (int j = 0; j < 60; j++) {
            antinodes[i][j] = 0;
        }
    }

    char map[60][60];

    int its = 0;
    uint64_t total = 0;
    while (fgets(map[its], 60, input)) {
        its++;
    }

    for (int i = 0; i < its; i++) {
        for (int j = 0; j < its; j++) {
            if (map[i][j] != '.') {
                total += hsuniqand(map, its, i, j, antinodes);
            }
        }
    }

    printf("total: %ld\n", total);

    return EXIT_SUCCESS;
}
