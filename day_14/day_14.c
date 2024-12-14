#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BATHROOM_ROWS 103
#define BATHROOM_COLS 101

/*
#define BATHROOM_ROWS 7
#define BATHROOM_COLS 11
*/

typedef struct Node Node;
struct Node {
    Node *next;
    int32_t vx;
    int32_t vy;
    uint32_t turn;
};

uint32_t indexbathroom(int r, int c) { return (r * BATHROOM_COLS) + c; }

void placerobot(Node *robot, Node **bathroom, uint32_t r, uint32_t c) {
    uint32_t robpos = indexbathroom(r, c);
    robot->next = bathroom[robpos];
    bathroom[robpos] = robot;
}

void tick(Node **bathroom, uint32_t ticknum) {
    for (int r = 0; r < BATHROOM_ROWS; r++) {

        for (int c = 0; c < BATHROOM_COLS; c++) {
            Node *bot = bathroom[indexbathroom(r, c)];
            Node *prev = NULL;
            while (bot != NULL) {
                if (bot->turn == ticknum) {
                    prev = bot;
                    bot = bot->next;
                    continue;
                }
                bot->turn = ticknum;
                int32_t br = r + bot->vy;
                int32_t bc = c + bot->vx;

                if (br < 0) {
                    br = BATHROOM_ROWS + br;
                }
                else if (br >= BATHROOM_ROWS) {
                    br = br - BATHROOM_ROWS;
                }
                if (bc < 0) {
                    bc = BATHROOM_COLS + bc;
                }
                else if (bc >= BATHROOM_COLS) {
                    bc = bc - BATHROOM_COLS;
                }

                if (prev != NULL) {
                    prev->next = bot->next;
                }
                else {
                    bathroom[indexbathroom(r, c)] = bot->next;
                }
                Node *tmp = bot->next;
                placerobot(bot, bathroom, br, bc);
                bot = tmp;
            }
        }
    }
}

uint32_t _countbots(Node *bots) {
    uint32_t numbots = 0;
    while (bots != NULL) {
        numbots += 1;
        bots = bots->next;
    }

    return numbots;
}

uint64_t countbots(Node **bathroom) {
    uint64_t q1 = 0;
    uint64_t q2 = 0;
    uint64_t q3 = 0;
    uint64_t q4 = 0;

    for (int r = 0; r < BATHROOM_ROWS / 2; r++) {
        for (int c = 0; c < BATHROOM_COLS / 2; c++) {
            q1 += _countbots(bathroom[indexbathroom(r, c)]);
            q2 += _countbots(
                bathroom[indexbathroom(r + (BATHROOM_ROWS / 2) + 1, c)]);
            q3 += _countbots(
                bathroom[indexbathroom(r, c + (BATHROOM_COLS / 2) + 1)]);
            q4 += _countbots(bathroom[indexbathroom(
                r + (BATHROOM_ROWS / 2) + 1, c + (BATHROOM_COLS / 2) + 1)]);
        }
    }

    printf("q1: %d, q2: %d, q3: %d, q4: %d\n", q1, q2, q3, q4);
    return q1 * q2 * q3 * q4;
}

void printbathroom(Node **bathroom) {
    for (int r = 0; r < BATHROOM_ROWS; r++) {
        for (int c = 0; c < BATHROOM_COLS; c++) {
            uint32_t bots = _countbots(bathroom[indexbathroom(r, c)]);
            if (bots == 0) {
                printf(" ");
            }
            else {
                printf("%d", bots);
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    char line[256];

    Node **bathroom = calloc(BATHROOM_COLS * BATHROOM_ROWS, sizeof(Node));

    while (fgets(line, 256, input)) {
        Node *bot = malloc(sizeof(Node));
        bot->next = NULL;
        bot->turn = -1;

        uint32_t c = strtol(line + 2, NULL, 10);
        char *pos = strchr(line, ',');
        uint32_t r = strtol(pos + 1, NULL, 10);
        placerobot(bot, bathroom, r, c);

        pos = strstr(line, "v=");
        bot->vx = strtol(pos + 2, NULL, 10);
        pos = strchr(pos, ',');
        bot->vy = strtol(pos + 1, NULL, 10);
    }

    printbathroom(bathroom);

    for (int i = 0; i < 10000; i++) {
        tick(bathroom, i);
        printf("second %d\n", i + 1);
        printbathroom(bathroom);
        printf("\n");
    }

    printf("bots: %lu\n", countbots(bathroom));

    return EXIT_SUCCESS;
}
