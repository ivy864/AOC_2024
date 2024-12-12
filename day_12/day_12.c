#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge Edge;
struct Edge {
    Edge *next;
    int sr;
    int sc;
    int er;
    int ec;
};

typedef struct Cost Cost;
struct Cost {
    uint32_t plots;
    uint32_t fence;
};

int comparetype(char map[145][145], int r, int c, char plttype, int msize) {
    if (0 > r || 0 > c || r >= msize || c >= msize) {
        return 0;
    }
    if (map[r][c] == plttype) {
        return 1;
    }
    return 0;
}

// functional programmers fear me
void _calccost(char map[145][145], char *visited, int msize, int sr,
             int sc, Cost *cost, int prevfence) {
    if (visited[(sr * msize) + sc] != 0) {
        return;
    }
    visited[(sr * msize) + sc] = 1;
    char ptype = map[sr][sc];

    int fence = 4;
    if (comparetype(map, sr - 1, sc, ptype, msize)) {
        fence -= 1;
    }
    if (comparetype(map, sr + 1, sc, ptype, msize)) {
        fence -= 1;
    }
    if (comparetype(map, sr, sc - 1, ptype, msize)) {
        fence -= 1;
    }
    if (comparetype(map, sr, sc + 1, ptype, msize)) {
        fence -= 1;
    }
    
    if (fence >= prevfence) {
        cost->fence += (fence + 1) - prevfence;
    }

    printf("%d edges\n", cost->fence);
    if (comparetype(map, sr - 1, sc, ptype, msize)) {
        _calccost(map, visited, msize, sr - 1, sc, cost, fence);
    }
    if (comparetype(map, sr + 1, sc, ptype, msize)) {
        _calccost(map, visited, msize, sr + 1, sc, cost, fence);
    }
    if (comparetype(map, sr, sc - 1, ptype, msize)) {
        _calccost(map, visited, msize, sr, sc - 1, cost, fence);
    }
    if (comparetype(map, sr, sc + 1, ptype, msize)) {
        _calccost(map, visited, msize, sr, sc + 1, cost, fence);
    }

    //cost->fence += fence;
    cost->plots += 1;

    return;
}

uint32_t calccost(char map[145][145], char *visited, int msize, int sr,
             int sc) {
    Cost *cost = malloc(sizeof(Cost)); 
    cost->plots = 0;
    cost->fence = 0;
    _calccost(map, visited, msize, sr, sc, cost, 2);

    uint32_t regcost = cost->plots * cost->fence;

    printf("region: %c, cost: %d, edges: %d\n", map[sr][sc], regcost, cost->fence);

    free(cost);


    return regcost;
}


int main(int argc, char* argv[]) {
    FILE* input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    char map[145][145];

    int its = 0;
    while (fgets(map[its], 145, input)) {
        its++;
    }
    printf("%d\n", its);

    //char visited[140][140];
    char *visited = malloc(sizeof(char) * 140 * 140);
    uint64_t total = 0;

    /*
    char graph[140][140][140][140];

    for (int i = 0; i < 140; i++) {
        for (int j = 0; j < 140; j++) {
            for (int k = 0; k < 140; k++) {
                for (int l = 0; l < 140; l++) {
                    graph[i][j][k][l] = 0;
                }
            }
        }
    }
    */
    
    for (int i = 0; i < 140 * 140; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < its; i++) {
        for (int j = 0; j < its; j++) {
            if (visited[(i * its) + j] == 0) {
                total += calccost(map, visited, its, i, j);
            }
        }
    }

    printf("total: %lu\n", total);

    free(visited);
    return EXIT_SUCCESS;
}
