#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 40830
// 40069t
uint32_t mincost(int32_t ax, int32_t ay, int32_t bx, int32_t by, int32_t px,
                 int32_t py) {
    float b = ((px * ay) - (py * ax)) / (float)((bx * ay) - (by * ax));
    float a = (px - (b * bx)) / (float) ax;

    if ((px - (bx * (int32_t)b)) % ax == 0 && (py - (by * (int32_t)b)) % ay == 0) {
        return a * 3 + b;
    }

    return 0;
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
