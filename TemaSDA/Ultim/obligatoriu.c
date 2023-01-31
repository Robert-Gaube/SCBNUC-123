#include <stdio.h>
#include "graf.h"

int visited[100];
int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2}, dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

int valid(int i, int j) {
    if(i < 1 || i > 8 || j < 1 || j > 8) return 0;
    if(visited[coord_to_node(i, j)]) return 0;
    return 1;
}
void Back(int x, int y, GRAPH g) {
    int i, xv, yv;
    for(i = 0; i < 8; ++i) {
        xv = x + dx[i];
        yv = y + dy[i];
        if(valid(xv, yv)) {
            add_edge(g, coord_to_node(x, y), coord_to_node(xv, yv));
            visited[coord_to_node(xv, yv)] = 1;
            Back(xv, yv, g);
        }
    }
}
int main() {
    GRAPH g = init_graph(64);
    visited[coord_to_node(1, 1)] = 1;
    Back(1, 1, g);
    printf("Lungime %d: ", distance(g, 0, 63));
    print_path(g, 0, 63);
    dealloc(g);
    return 0;
}