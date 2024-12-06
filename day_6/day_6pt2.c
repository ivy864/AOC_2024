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

void printmap(char map[140][140], uint32_t mapsize) {
    printf(" ");
    for (int i = 0; i < mapsize; i++) {
        printf("%d", i);
    }
    printf("\n");
    for (int i = 0; i < mapsize; i++) {
        printf("%d%s", i, map[i]);
    }
}

int vindex(int r, int c) {
    return r * 140 + c;
}

int isloop(char map[140][140], uint32_t mapsize,char guy, int guyr, int guyc) {
    //char gy = guy;
    int gr = guyr;
    int gc = guyc;
    int turns = 0;

    uint32_t *vis = calloc(sizeof(uint32_t), 140*140);

    while(inbounds(mapsize, gr, gc)) {
        int nr = getnextr(gr, guy);
        int nc = getnextc(gc, guy);

        if (map[nr][nc] == '#') {
            guy = turn(guy);
            turns += 1;
        }
        else {
            uint32_t vg = vis[vindex(nr, nc)];
            for (int i = 0; i < 4; i++) {
                if ((char)(vg & 0xFF) == guy) {
                    printf("guy is %c at %d %d\n", guy, nr, nc);
                    return 1;
                }
                vg = vg >> 8;
                
            }
            vg = vis[vindex(gr, gc)];
            for (int i = 0; i < 4; i++) {
                char tmp = (char) (vg >> i*8) & 0xFF;
                if (tmp == guy) {
                    break;
                }
                else if (tmp == 0) {
                    vis[vindex(gr, gc)] = (vg << 8) | guy;
                }
            }

            gr = nr;
            gc = nc;
        }
    }

    return 0;
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

    int tr[3];
    int tc[3];

    int startr = guyr;
    int startc = guyc;

    int total = 0;
    int turns = 0;

    char guy = map[guyr][guyc];
    for (int i = 0; i < msize; i++) {
        for (int j = 0; j < msize; j++) {
            if (map[i][j] == '.') {
                map[i][j] = '#';
                total += isloop(map, msize, guy, guyr, guyc);
                map[i][j] = '.';
                printf("%d\n", total);
            }
        }
    }

    printf("total: %d\n", total);

    return EXIT_SUCCESS;
}
