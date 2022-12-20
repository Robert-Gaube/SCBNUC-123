#include <stdio.h>

int coord_to_node(int row, int col) {
    return col * 8 + row - 1;
}
void node_to_coord(int num, int *row, int *col ) {
    *col = num / 8;
    *row = num % 8 + 1;
}
int main() {
    return 0;
}