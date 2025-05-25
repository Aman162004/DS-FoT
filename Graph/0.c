// Add NULL check after each malloc() call
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int num_vertices;
    int **adj_matrix;
} GraphMatrix;


GraphMatrix* create_graph_matrix(int vertices) {

    GraphMatrix* graph = malloc(sizeof(GraphMatrix));
    graph->num_vertices = vertices;
    graph->adj_matrix = malloc(sizeof(int*) * vertices);

    for (int i = 0; i < vertices; i++) {
        graph->adj_matrix[i] = malloc(sizeof(int) * vertices);
        for (int j = 0; j < vertices; j++) {
            if (i ==j) {
                graph->adj_matrix[i][j] = -1;    
            }
            else {
                graph->adj_matrix[i][j] = 0;
            }
        }
    }

    return graph;
}


int add_edge_matrix(GraphMatrix* graph, int src, int dest) {

    graph->adj_matrix[src][dest] = 1;
    graph->adj_matrix[dest][src] = 1;

    return 0;
}


int print_graph_matrix(GraphMatrix* graph) {

    for (int i = 0; i < graph->num_vertices; i++) {
        printf("%d: ", i);
        for (int j = 0; j < graph->num_vertices; j++) {
            printf("%d ", graph->adj_matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}


int main() {

    GraphMatrix *matrix_graph = create_graph_matrix(4);
    add_edge_matrix(matrix_graph, 0, 1);
    add_edge_matrix(matrix_graph, 0, 2);
    add_edge_matrix(matrix_graph, 1, 2);
    add_edge_matrix(matrix_graph, 2, 3);

    print_graph_matrix(matrix_graph);

    return 0;
}
