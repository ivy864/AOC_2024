#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 245501973
// 129952405336
// 129952405336
// 35400223840086
// 35400223840089
// 34566890506161
// 71493195288102
uint64_t mincost(int64_t ax, int64_t ay, int64_t bx, int64_t by, int64_t px,
                 int64_t py) {
    px += 10000000000000ULL;
    py += 10000000000000ULL;

    long double b = ((px * ay) - (py * ax)) / (long double)((bx * ay) - (by * ax));
    long double a = (px - (b * bx)) / (long double) ax;

    if ((px - (bx * (uint64_t)b)) % ax == 0 && (py - (by * (uint64_t)b)) % ay == 0) {
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

        uint64_t cost = mincost(ax, ay, bx, by, px, py);
        printf("cost: %lu\n\n", cost);
        total += cost;

        // consume blank line
        fgets(line, 256, input);
    }

    printf("total: %lu\n", total);
    return EXIT_SUCCESS;
}
