#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 198648

typedef struct edge edge;
typedef struct node node;

struct edge {
    node *to;
    node *from;
    uint32_t length;
    edge *next;
};

struct node {
    edge *edges;    
    uint32_t index;
    uint32_t r;
    uint32_t c;
    uint64_t dist;
    int visited;
};

typedef struct {
    node **nodes;
    uint32_t len;
} min_heap;

typedef struct {
    node *node;
    uint32_t dist;
    int new;
} next_node;

typedef struct nodestack nodestack;
struct nodestack {
    nodestack *next;
    node *node;
};

typedef struct edgelist edgelist;
struct edgelist {
    edgelist *next;
    edge *edge;
};


void printmap(char map[150][150], int msize) {
    for (int i = 0; i < msize; i++) {
        printf("%s", map[i]);
    }
}

// return 1 if node in graph
int ingraph(node **graph, uint32_t nodes, uint32_t r, uint32_t c) {
    //printf("ingraph nodes: %d\n", nodes);
    for (uint32_t i = 0; i < nodes; i++) {
        //printf("gr %d gc %d r %d c %d\n", graph[i]->r, graph[i]->c, r, c);
        if (graph[i]->r == r && graph[i]->c == c) {
            return 1;
        }
    }

    return 0;
}


uint32_t getnode(node **graph, uint32_t *nodes, uint32_t r, uint32_t c) {
    for (uint32_t i = 0; i < *nodes; i++) {
        if (graph[i]->r == r && graph[i]->c == c) {
            return i;
        }
    }

    graph[*nodes] = malloc(sizeof(node));

    graph[*nodes]->r = r;
    graph[*nodes]->c = c;
    graph[*nodes]->index = *nodes;
    graph[*nodes]->edges = NULL;
    graph[*nodes]->dist = UINT64_MAX;
    graph[*nodes]->visited = 0;

    *nodes += 1;

    //printf("nodes: %d\n", *nodes);
    return *nodes - 1;
}

int isnode(int r, int c, char map[150][150], uint32_t dr, uint32_t dc) {
    uint32_t dirs;

    if (map[r][c] == '#') {
        return 0;
    }

    if (dr != 0) {
        if (map[r + 1][c] != '.' || map[r - 1][c] != '.') {
            return 1;
        }
        else if (map[r][c + 1] == '.' || map[r][c - 1] == '.') {
            return 1;
        }
    }
    else if (dc != 0) {
        if (map[r][c + 1] != '.' || map[r][c - 1] != '.') {
            return 1;
        }
        else if (map[r + 1][c] == '.' || map[r - 1][c] == '.') {
            return 1;
        }
    }

    return 0;
}

next_node *nextnode(node **graph, uint32_t *numnodes, char map[150][150], node *n, uint32_t dr, uint32_t dc) {
    uint32_t r = n->r + dr;
    uint32_t c = n->c + dc;
    
    uint32_t dist = 1;
    while(isnode(r, c, map, dr, dc) != 1) {
        r += dr;
        c += dc;
        dist += 1;
    }

    next_node *next = malloc(sizeof(next_node));

    //printf("in: %d\n",ingraph(graph, *numnodes, r, c));
    //printf("r: %d c: %d\n", r, c);

    uint32_t nni = getnode(graph, numnodes, r, c);
    next->node = graph[nni];
    next->dist = dist;

    if (ingraph(graph, *numnodes, r, c) == 0) {
        next->new = 1;
    }
    else {
        edge *tmp = n->edges;
        while (tmp != NULL) {
            if (tmp->to->r == r && tmp->to->c == c) {
                free(next);
                return NULL;
            }
            tmp = tmp->next;
        }
        next->new = 0;
    }

    return next;

}

void traversegraph(node **graph, uint32_t *numnodes, char map[150][150], node* n, uint32_t dr, uint32_t dc) {
    if (map[n->r + 1][n->c] != '#') {
        next_node *next = nextnode(graph, numnodes, map, n, 1, 0);

        if (next != NULL) {
            edge *tmp = malloc(sizeof(edge));
            tmp->next = n->edges;
            tmp->from = n;
            tmp->to = next->node;
            tmp->length = next->dist;

            if (!(dr == 1 && dc == 0)) {
                tmp->length += 1000;
            }

            printf("from: %d %d to: %d %d edgesize: %d\n", n->r, n->c, tmp->to->r, tmp->to->c, tmp->length);
            printf("dr: %d, dc: %d r: 1\n", dr, dc);

            n->edges = tmp;

            free(next);

            traversegraph(graph, numnodes, map, tmp->to, 1, 0);
        }
    }
    if (map[n->r - 1][n->c] != '#') {
        next_node *next = nextnode(graph, numnodes, map, n, -1, 0);

        if (next != NULL) {

            edge *tmp = malloc(sizeof(edge));
            tmp->next = n->edges;
            tmp->from = n;
            tmp->to = next->node;
            tmp->length = next->dist;

            if (!(dr == -1 && dc == 0)) {
                tmp->length += 1000;
            }

            printf("from: %d %d to: %d %d edgesize: %d\n", n->r, n->c, tmp->to->r, tmp->to->c, tmp->length);
            printf("dr: %d, dc: %d r: -1\n", dr, dc);

            n->edges = tmp;

            free(next);


            traversegraph(graph, numnodes, map, tmp->to, -1, 0);
        }
    }
    if (map[n->r][n->c + 1] != '#') {
        next_node *next = nextnode(graph, numnodes, map, n, 0, 1);
        if (next != NULL) {
            edge *tmp = malloc(sizeof(edge));
            tmp->next = n->edges;
            tmp->from = n;
            tmp->to = next->node;
            tmp->length = next->dist;

            if (!(dr == 0 && dc == 1)) {
                tmp->length += 1000;
            }

            printf("from: %d %d to: %d %d edgesize: %d\n", n->r, n->c, tmp->to->r, tmp->to->c, tmp->length);
            printf("dr: %d, dc: %d c: 1\n", dr, dc);
            n->edges = tmp;

            free(next);

            traversegraph(graph, numnodes, map, tmp->to, 0, 1);
        }
    }
    if (map[n->r][n->c - 1] != '#') {
        next_node *next = nextnode(graph, numnodes, map, n, 0, -1);
        if (next != NULL) {
            edge *tmp = malloc(sizeof(edge));
            tmp->next = n->edges;
            tmp->from = n;
            tmp->to = next->node;
            tmp->length = next->dist;

            if (!(dr == 0 && dc == -1)) {
                tmp->length += 1000;
            }
            printf("dr: %d, dc: %d c: -1\n", dr, dc);

            printf("from: %d %d to: %d %d edgesize: %d\n", n->r, n->c, tmp->to->r, tmp->to->c, tmp->length);
            n->edges = tmp;

            free(next);

            traversegraph(graph, numnodes, map, tmp->to, 0, -1);
        }
    }
}

edgelist *el_getmin(edgelist *el) {
    edgelist *min = el;

    while (el != NULL)  {
        if (el->edge->length < min->edge->length) {
            min = el;
        }
    }


    return min;
}

void el_free(edgelist *el, edgelist *elstart) {
    if (el->next == NULL) {
        edgelist *prevel = NULL;

        while (elstart != NULL) {
            prevel = elstart;
            elstart = elstart->next;
        }

        prevel->next = NULL;
        free(el);
    }
    else {
        el->edge = el->next->edge;
        el->next = el->next->next;
        free (el->next);
    }
}


int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[1], "r");

    if (input == NULL) {
        printf("Bad input.");
        return 1;
    }

    char map[150][150];

    int its = 0;
    while (fgets(map[its], 150, input)) {
        its++;
    }
    printmap(map, its);
    printf("\n");
    
    node **graph = malloc(sizeof(node *) * its * its);
    uint32_t nodes = 0;

    for (int i = its - 1; i >= 0; i -= 1) {
        char *start = strchr(map[i], 'S');
        if (start != NULL) {
            //printf("start pos: %d %lu\n", i, start - map[i]);
            uint32_t np = getnode(graph, &nodes, i, start - map[i]);
            graph[np]->dist = 0;

            break;
        }
    }
    uint32_t er, ec;
    for (int i = 0; i < its; i++) {
        char *end = strchr(map[i], 'E');
        if (end != NULL) {
            //printf("end pos: %d %lu\n", i, end - map[i]);
            er = i; 
            ec = end - map[i];
            //printf("er: %d ec: %d\n", er, ec);
        }
    }
    map[graph[0]->r][graph[0]->c] = '.';
    map[er][ec] = '.';

    // populate graph hopefully
    traversegraph(graph, &nodes, map, graph[0], 0, 1);

    node *endnode = graph[getnode(graph, &nodes, er, ec)];

    edgelist *el = NULL;
    edge *egs = graph[0]->edges;
    graph[0]->visited = 1;
    graph[0]->dist = 0;

    while (egs != NULL) {
        edgelist *tmp = malloc(sizeof(edgelist));
        tmp->next = el;
        tmp->edge = egs;
        el = tmp;
        
        egs->to->dist = egs->length;

        egs = egs->next;
    }

    while (el != NULL) {
        edgelist *min = el;
        edgelist *findmin = el;

        while (findmin != NULL)  {
            if (findmin->edge->length < min->edge->length) {
                min = findmin;
            }
            findmin = findmin->next;
        }

        node *target = min->edge->to;

        // free min
        if (el == min) {
            el = el->next;
            free(min);
        }
        else if (min->next == NULL) {
            edgelist *prevel = NULL;
            edgelist *tmp = el;

            while (tmp->next != NULL) {
                prevel = tmp;
                tmp = tmp->next;
            }

            prevel->next = NULL;
            free(min);
        }
        else {
            edgelist *tmp = min->next;
            min->edge = tmp->edge;
            min->next = tmp->next;
            free (tmp);
        }


        // do stuff if not visited
        if (target->visited == 0) {
            target->visited = 1;
            edge *tmp = target->edges;

            while (tmp != NULL) {
                if (tmp->to->dist > target->dist + tmp->length) {
                    tmp->to->dist = target->dist + tmp->length;
                    printf("node: %d dist: %d\n", tmp->to->index, tmp->length);
                }
                edgelist *new_el = malloc(sizeof(edgelist));
                new_el->edge = tmp;
                new_el->next = el;
                el = new_el;
                tmp = tmp->next;
            }
        }

        egs = target->edges;
    }


    printf("distance: %lu\n", endnode->dist);

    return EXIT_SUCCESS;
}
