#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char getvisited(char* visited, int msize, int r, int c) {
    return visited[(r * msize) + c];
}
void printvisited(char *m, int msize) {
    for (int i = 0; i < msize; i++) {
        for (int j = 0; j < msize; j++) {
            printf("%d", getvisited(m, msize, i, j));
        }
        printf("\n");
    }
}



int cnttrails(char map[70][70], int msize, int r, int c, char *visited) {
    int32_t paths = 0;

    int end = 0;

    char curr = map[r][c];
    if (curr == 9) {
        int visit = visited[(r * msize) + c];
        if (visit == 0) {
            visited[(r * msize) + c] = 1;
            return 1;
        }
        else {
            return 0;
        }
    }

    if (r - 1 >= 0 && map[r - 1][c] == curr + 1) {
        paths += cnttrails(map, msize, r - 1, c, visited);
    }
    if (r + 1 < msize && map[r + 1][c] == curr + 1) {
        paths += cnttrails(map, msize, r + 1, c, visited);
    }
    if (c - 1 >= 0 && map[r][c - 1] == curr + 1) {
        paths += cnttrails(map, msize, r, c - 1, visited);
    }
    if (c + 1 < msize && map[r][c + 1] == curr + 1) {
        paths += cnttrails(map, msize, r, c + 1, visited);
    }

    //printf("paths: %d\n", paths);
    return paths;
}

int stcnt(char map[70][70], int msize, int r, int c) {
    char *visited = calloc(msize * msize, sizeof(char));
    int trls = cnttrails(map, msize, r, c, visited);
    free(visited);
    return trls;
}

int main(int argc, char* argv[]) {
    FILE* input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    uint64_t total = 0;

    char map[70][70];

    int its = 0;
    while (fgets(map[its], 70, input)) {
        its++;
    }
    for (int i = 0; i < its; i++) {
        for (int j = 0; j < its; j++) {
            map[i][j] -= '0';
        }
    }
    printf("%d", its);

    for (int i = 0; i < its; i++) {
        for (int j = 0; j < its; j++) {
            if (map[i][j] == 0) {
                int tc = stcnt(map, its, i, j);
                printf("tc: %d\n", tc);
                total += tc;
            }
        }
    }

    printf("total: %ld\n", total);

    return EXIT_SUCCESS;
}
