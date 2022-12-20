#include <stdlib.h>
#include <stdio.h>
#include "graf.h"

typedef struct node {
    int v;
    struct node *next;
}NODE;

typedef struct Nbr {
    NODE *head;
    NODE *tail;
}NBR;

struct Graph {
    NBR *l;
    int N;
};

void throw_error(const char *msg) {
    printf("ERROR: %s\n", msg);
    exit(-1);
}
GRAPH init_graph(const int N) {
    GRAPH g = (GRAPH)malloc(sizeof(struct Graph));
    if(g == NULL) throw_error("Not enough space");
    g -> l = (NBR*)malloc(sizeof(NBR) * N);
    if(g -> l == NULL) throw_error("Not enough space");  
    g -> N = N;
    for(int i = 0; i < N; ++i) g -> l[i].head = g -> l[i].tail = NULL;

    return g;
}
void add_edge(GRAPH g, int i, int j) {
    if(i > g -> N) throw_error("Node is not in graph");
    if(j > g -> N) throw_error("Node is not in graph");

    if(g -> l[i].head == NULL) {
        g -> l[i].head = (NODE*)malloc(sizeof(struct node));
        g -> l[i].tail = g -> l[i].head;
    }
}