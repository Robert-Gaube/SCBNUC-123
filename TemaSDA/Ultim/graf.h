#ifndef GRAF_H
#define GRAF_H

typedef struct Graph* GRAPH;

int coord_to_node(int row, int col);
void node_to_coord(int num, int *row, int *col);
GRAPH init_graph(const int);
void add_edge(GRAPH, int, int);
int distance(GRAPH, int, int);
void print_path(GRAPH g, int i, int j);
void show_edges(GRAPH);
void dealloc(GRAPH);

#endif /* GRAF_H */