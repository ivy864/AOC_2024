#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stone Stone;
struct Stone {
    uint64_t val;
    uint64_t ammt;
    Stone *next;
};

Stone *findStone(Stone *stones, uint64_t stoneval) {
    while (stones != NULL) {
        if (stones->val == stoneval) {
            return stones;
        }
        stones = stones->next;
    }

    return NULL;
}

Stone *placeStone(Stone *stones, uint64_t stoneval, uint64_t ammt) {
    Stone *stone = findStone(stones, stoneval);
    if (stone == NULL) {
        Stone *tmp = malloc(sizeof(Stone));
        tmp->ammt = ammt;
        tmp->val = stoneval;
        
        tmp->next = stones;
        return tmp;
    }
    else {
        stone->ammt += ammt;
        return stones;
    }
}

void printstones(Stone *stones) {
    while (stones != NULL) {
        printf("%lu ", stones->val);
        stones = stones->next;
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    char line[256];

    int its = 0;

    while (fgets(line, 256, input)) {
        its++;
    }


    char *next = line;
    Stone *stones = NULL;

    while(next != NULL) {
        Stone *tmp = malloc(sizeof(Stone));
        tmp->next = stones;
        stones = tmp;
        stones->val = strtol(next, NULL, 10);
        stones->ammt = 1;

        next = strchr(next, ' ');
        if (next != NULL) {
            next += 1;
        }
    }

    int blinks = 75;
    char *stn = malloc(20 * sizeof(char));

    Stone *nxtstns;
    Stone *stone = stones;
    for (int i = 0; i < blinks; i++) {
        printf("blink %d\n", i + 1);
        nxtstns = NULL;

        while(stone != NULL) {
            printf("val: %lu\n", stone->val);
            if (stone->ammt > 0) {
                sprintf(stn, "%lu", stone->val);
                if (stone->val == 0) {
                    nxtstns = placeStone(nxtstns, 1, stone->ammt);
                }
                else if (strlen(stn) % 2 == 0) {
                    uint64_t n1 = strtol(stn + (strlen(stn) / 2), NULL, 10);
                    stn[strlen(stn) / 2] = '\0';
                    uint64_t n2 = strtol(stn, NULL, 10);

                    nxtstns = placeStone(nxtstns, n1, stone->ammt);
                    nxtstns = placeStone(nxtstns, n2, stone->ammt);
                }
                else {
                    nxtstns = placeStone(nxtstns, stone->val * 2024, stone->ammt);
                }
            }
            Stone *tmp = stone->next; 
            free(stone);
            stone = tmp;
            printf("stone done\n");
        }

        stone = nxtstns;
    }

    // 18446744073709551615
    // 18446744061351728800
    // 219838428124832
    uint64_t total = 0;
    while (nxtstns != NULL) {
        total += nxtstns->ammt;
        nxtstns = nxtstns->next;
    }

    printf("total: %lu\n", total);


    free(stn);

    return EXIT_SUCCESS;
}
