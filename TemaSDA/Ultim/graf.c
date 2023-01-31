#include <stdlib.h>
#include <stdio.h>
#include "graf.h"

int coord_to_node(int row, int col) {
    return (col - 1) * 8 + row - 1;
}
void node_to_coord(int num, int *row, int *col ) {
    *col = num / 8 + 1;
    *row = num % 8 + 1;
}

void throw_error(const char *msg) {
    printf("ERROR: %s\n", msg);
    exit(-1);
}

typedef struct queue {
    int start, end;
    int elems[1000];
}QUEUE;

QUEUE init_queue() {
    QUEUE queue;
    queue.start = 0;
    queue.end = -1;
    return queue;
}
int queue_is_empty(QUEUE queue) {
    return (queue.end < queue.start);
}
void push_queue(QUEUE *queue, int e) {
    queue -> elems[++queue -> end] = e;
}
int pop_queue(QUEUE *queue) {
    if(queue_is_empty(*queue)) throw_error("Queue empty when trying to pop");
    
    queue -> start++;
    return queue -> elems[queue -> start - 1];
}


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
    int *parents;
};

GRAPH init_graph(const int N) {
    if(N < 1) throw_error("Number of nodes too small or negative");
    GRAPH g = (GRAPH)malloc(sizeof(struct Graph));
    if(g == NULL) throw_error("Not enough space");
    g -> l = (NBR*)malloc(sizeof(NBR) * N);
    if(g -> l == NULL) throw_error("Not enough space");  
    g -> parents = (int*)malloc(sizeof(int) * N);
    if(g -> parents == NULL) throw_error("Not enough space");
    g -> parents[0] = -2;
    g -> N = N;
    for(int i = 0; i < N; ++i) g -> l[i].head = g -> l[i].tail = NULL;

    return g;
}
void add_edge(GRAPH g, int i, int j) {
    if(i > g -> N) throw_error("Node is not in graph");
    if(j > g -> N) throw_error("Node is not in graph");

    if(g -> l[i].head == NULL) {
        g -> l[i].head = (NODE*)malloc(sizeof(struct node));
        if(g -> l[i].head == NULL) throw_error("Not enough space");
        g -> l[i].head -> next = NULL;
        g -> l[i].head -> v = j;
        g -> l[i].tail = g -> l[i].head;
    }
    else {
        NODE *node = (NODE*)malloc(sizeof(struct node));
        if(node == NULL) throw_error("Not enough space");
        node -> next = NULL;
        node -> v = j;
        g -> l[i].tail -> next = node;
        node -> next = NULL;
        g -> l[i].tail = node;
    }
}
int distance(GRAPH g, int x, int y) {
    int visited[100], i, dist = -1;
    for(i = 0; i < g -> N; ++i) visited[i] = 0;

    QUEUE queue = init_queue();
    push_queue(&queue, x);
    visited[x] = 1;
    g -> parents[x] = -1;

    int node, nbr;
    NODE *head;
    while(!queue_is_empty(queue)) {
        dist++;
        node = pop_queue(&queue);
        if(node == y) return dist;
        head = g -> l[node].head;
        while(head) {
            nbr = head -> v;
            if(!visited[nbr]) {
                push_queue(&queue, nbr);
                g -> parents[nbr] = node;
                visited[nbr] = 1;
            }
            head = head -> next;
        }
    }
    return 0;
}
void print_reverse(GRAPH g, int parent, int i) {
    if(parent == i || parent == -1) {
        int row, col, temp = parent;
        node_to_coord(temp, &row, &col);
        printf("[%c %d] ", 'A' + col - 1, row);
        return;
    }
    print_reverse(g, g -> parents[parent], i);
    int row, col, temp = parent;
    node_to_coord(temp, &row, &col);
    printf(" -> [%c %d]", 'A' + col - 1, row);
}
void print_path(GRAPH g, int i, int j) {
    if(g -> parents[0] == -2) throw_error("No paths were created");

    print_reverse(g, j, i);
    puts("");
}
void show_edges(GRAPH g) {
    int i; NODE *head;
    for(i = 0; i < g -> N; ++i) {
        printf("%d -> ", i);
        head = g -> l[i].head;
        while(head) {
            printf("%d ", head -> v);
            head = head -> next;
        }
        puts("");
    }
}
void dealloc(GRAPH g) {
    free(g -> parents);
    int i; NODE *aux;
    for(i = 0; i < g -> N; ++i) {
        while(g -> l[i].head) {
            aux = g -> l[i].head;
            g -> l[i].head = g -> l[i].head -> next;
            free(aux);
        }
    }
    free(g -> l);
    free(g);

}