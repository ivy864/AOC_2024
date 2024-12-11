#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Stone Stone;
struct Stone {
    uint64_t val;
    Stone *next;
};

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

        next = strchr(next, ' ');
        if (next != NULL) {
            next += 1;
        }
    }
    printf("%lu\n", stones->val);

    int blinks = 75;
    char *stn = malloc(20 * sizeof(char));

    for (int i = 0; i < blinks; i++) {
        Stone *stone = stones;

        while(stone != NULL) {
            sprintf(stn, "%lu", stone->val);
            if (stone->val == 0) {
                stone->val = 1;
            }
            else if (strlen(stn) % 2 == 0) {
                stone->val = strtol(stn + (strlen(stn) / 2), NULL, 10);
                Stone *tmp = malloc(sizeof(Stone));

                stn[strlen(stn) / 2] = '\0';
                tmp->val = strtol(stn, NULL, 10);
                tmp->next = stone->next;
                stone->next = tmp;
                stone = tmp;
            }
            else {
                stone->val *= 2024;
            }

            stone = stone->next;
        }
        printf("blink %d\n", i + 1);
    }

    uint32_t total = 0;
    while (stones != NULL) {
        total += 1;
        stones = stones->next;
    }

    printf("total: %d\n", total);


    free(stn);

    return EXIT_SUCCESS;
}
