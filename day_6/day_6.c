#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int inbounds(uint32_t mapsize, int guyr, int guyc) {
    if (0 > guyr || 0 > guyc || mapsize <= guyr || mapsize <= guyc) {
        return 0;
    }
    

    return 1;
}

char turn(char guy) {
    switch (guy) {
        case '^': 
            return '>';
            break;
        case '>':
            return 'v';
            break;
        case 'v':
            return '<';
            break;
        case '<':
            return '^';
            break;
    }

    return '\0';
}
int getnextr(int guyr, char guy) {
    switch (guy) {
        case '^': 
            return guyr - 1;
            break;
        case '>':
            return guyr;
            break;
        case 'v':
            return guyr + 1;
            break;
        case '<':
            return guyr;
            break;
    }
    return 2000000;
}
int getnextc(int guyc, char guy) {
    switch (guy) {
        case '^': 
            return guyc;
            break;
        case '>':
            return guyc + 1;
            break;
        case 'v':
            return guyc;
            break;
        case '<':
            return guyc - 1;
            break;
    }
    return 2000000;
}

int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    int its = 0;
    char map[140][140];
    uint32_t msize = 0;
    while (fgets(map[msize], 140, input)) {
        msize++;
    }

    int guyr, guyc;

    for(int i = 0; i < msize; i++) {
        char *loc = strpbrk((char*) map[i], "^<>v");
        if (loc != NULL) {
            guyr = i;
            guyc =  loc - map[i];
            break;
        }
    }

    int total = 0;
    while(inbounds(msize, guyr, guyc)) {
        char guy = map[guyr][guyc];

        int nextr = getnextr(guyr, guy);
        int nextc = getnextc(guyc, guy);

        if (map[nextr][nextc] == '#') {
            map[guyr][guyc] = turn(guy);
        }
        else {
            if (map[nextr][nextc] != 'X') {
                total += 1;
            }
            map[guyr][guyc] = 'X';
            map[nextr][nextc] = guy;
            //printf("r: %d, c: %d\n", guyr, guyc);
            guyr = nextr;
            guyc = nextc;
            //printf("r: %d, c: %d\n\n", guyr, guyc);
        }
    }

    printf("total: %d\n", total);

    return EXIT_SUCCESS;
}
