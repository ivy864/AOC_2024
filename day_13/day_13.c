#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t mincost(int32_t ax, int32_t ay, int32_t bx, int32_t by, int32_t px,
                 int32_t py) {
    uint32_t maxb = -1; 

    for (int i = 0; i < 500; i++) {
        if (bx * i > px || by * i > py) {
            break;
        }
        if ((px - (bx * i)) % ax == 0 && (py - (by * i)) % ay == 0) {
            maxb = i;
        }
    }
    
    int32_t numa = abs(((int32_t)px - ((int32_t)bx * (int32_t)maxb)) / ax);
    if (maxb == -1) {
        return 0;
    }

    printf("a press: %d, b press: %d\n", numa, maxb);

    if (numa > 100 || maxb > 100) {
        return 0;
    }
    return numa * 3 + maxb;
}

int main(int argc, char* argv[]) {
    FILE* input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    char line[256];

    uint64_t total = 0;
    while (fgets(line, 256, input)) {
        int32_t ax, ay, bx, by, px, py;

        ax = strtol(strstr(line, "X+") + 2, NULL, 10);
        ay = strtol(strstr(line, "Y+") + 2, NULL, 10);

        fgets(line, 256, input);

        bx = strtol(strstr(line, "X+") + 2, NULL, 10);
        by = strtol(strstr(line, "Y+") + 2, NULL, 10);

        fgets(line, 256, input);

        px = strtol(strstr(line, "X=") + 2, NULL, 10);
        py = strtol(strstr(line, "Y=") + 2, NULL, 10);

        printf("ax: %d, ay: %d, bx: %d, by: %d, px: %d, py: %d\n", ax, ay, bx,
               by, px, py);

        uint32_t cost = mincost(ax, ay, bx, by, px, py);
        printf("cost: %d\n\n", cost);
        total += cost;

        // consume blank line
        fgets(line, 256, input);
    }

    printf("total: %lu\n", total);
    return EXIT_SUCCESS;
}
