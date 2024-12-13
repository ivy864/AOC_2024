#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge Edge;
struct Edge {
    char dir;
    uint32_t in;
    uint32_t out;
    uint32_t startp;
    uint32_t endp;
    Edge *next;
};

typedef struct Cost Cost;
struct Cost {
    uint32_t plots;
    Edge *fence;
    int edgecorrection;
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

void addfence(Cost *cost, char dir, int in, int out, int p) {
    Edge *fencearr = cost->fence;
    Edge *fence = fencearr;
    int dupe = -1;
    while (fence != NULL) {
        if (fence->dir == dir && fence->in == in && fence->out == out) {
            if (p + 1 == fence->startp || p - 1 == fence->startp) {
                fence->startp = p;
                dupe += 1;
            }
            else if (p - 1 == fence->endp || p + 1 == fence->endp) {
                fence->endp = p;
                dupe += 1;
            }
            else if (p == fence->startp || p == fence->endp) {
                return;
            }
        }
        fence = fence->next;
    }
    if (dupe == -1) {
        printf("new edge\n");
        printf("dir: %c, in: %d out: %d, p: %d\n", dir, in, out, p);

        Edge *newfence = malloc(sizeof(Edge));
        newfence->dir = dir;
        newfence->in = in;
        newfence->out = out;
        newfence->startp = p;
        newfence->endp = p;

        newfence->next = fencearr;
        cost->fence = newfence;
    }
    else if (dupe > 0) {
        cost->edgecorrection += dupe;        
    }
}

// functional programmers fear me
void _calccost(char map[145][145], char *visited, int msize, int sr,
             int sc, Cost *cost) {
    if (visited[(sr * msize) + sc] != 0) {
        return;
    }
    visited[(sr * msize) + sc] = 1;
    char ptype = map[sr][sc];

    // add to fence linked list if there's an edge
    if (comparetype(map, sr - 1, sc, ptype, msize) == 0) {
        addfence(cost, 'R', sr, sr - 1, sc);
    }
    if (comparetype(map, sr + 1, sc, ptype, msize) == 0) {
        addfence(cost, 'R', sr, sr + 1, sc);
    }
    if (comparetype(map, sr, sc - 1, ptype, msize) == 0) {
        addfence(cost, 'C', sc, sc - 1, sr);
    }
    if (comparetype(map, sr, sc + 1, ptype, msize) == 0) {
        addfence(cost, 'C', sc, sc + 1, sr);
    }
    
    // recursively call _calccost on tiles in plot
    if (comparetype(map, sr - 1, sc, ptype, msize)) {
        _calccost(map, visited, msize, sr - 1, sc, cost);
    }
    if (comparetype(map, sr + 1, sc, ptype, msize)) {
        _calccost(map, visited, msize, sr + 1, sc, cost);
    }
    if (comparetype(map, sr, sc - 1, ptype, msize)) {
        _calccost(map, visited, msize, sr, sc - 1, cost);
    }
    if (comparetype(map, sr, sc + 1, ptype, msize)) {
        _calccost(map, visited, msize, sr, sc + 1, cost);
    }
    Edge *fence = cost->fence;
    while (fence != NULL) {
        fence = fence->next;
    }

    cost->plots += 1;

    return;
}

uint32_t calccost(char map[145][145], char *visited, int msize, int sr,
             int sc) {
    Cost *cost = malloc(sizeof(Cost)); 
    cost->plots = 0;
    cost->fence = NULL;
    cost->edgecorrection = 0;
    _calccost(map, visited, msize, sr, sc, cost);

    Edge *fence = cost->fence;
    uint32_t edges = 0;
    while (fence != NULL) {
        edges += 1;

        Edge *tmp = fence->next;
        free(fence);
        fence = tmp;
    }

    uint32_t regcost = cost->plots * (edges - cost->edgecorrection);

    printf("region: %c, cost: %d, edges: %d\n\n", map[sr][sc], regcost, edges);

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

    //char visited[140][140];
    char *visited = malloc(sizeof(char) * 140 * 140);
    uint64_t total = 0;
    
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
