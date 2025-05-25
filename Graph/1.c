// Add NULL check after each malloc() call
#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int vertex;
    struct Node* next;
} Node;


typedef struct {
    int num_vertices;
    Node** adj_lists;
} GraphList;


GraphList* create_graph_list(int vertices) {

    GraphList* graph = (GraphList*) malloc(sizeof(GraphList));
    graph->num_vertices = vertices;
    graph->adj_lists = (Node**) malloc(sizeof(Node*) * vertices);

    for (int i = 0; i < vertices; i++) {
        graph->adj_lists[i] = NULL;
    }

    return graph;
}


int add_edge_list(GraphList* graph, int src, int dest) {

    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->vertex = dest;
    new_node->next = graph->adj_lists[src];
    graph->adj_lists[src] = new_node;

    new_node = (Node*) malloc(sizeof(Node));
    new_node->vertex = src;
    new_node->next = graph->adj_lists[dest];
    graph->adj_lists[dest] = new_node;

    return 0;
}


int print_graph_list(GraphList* graph) {

    for (int i = 0; i < graph->num_vertices; i++) {
        Node* temp = graph->adj_lists[i];
        printf("\nAdjacency list of vertex %d\n head ", i);
        while (temp) {
            printf("-> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }

    return 0;
}


int main() {

    GraphList *list_graph = create_graph_list(4);
    add_edge_list(list_graph, 0, 1);
    add_edge_list(list_graph, 0, 2);
    add_edge_list(list_graph, 1, 2);
    add_edge_list(list_graph, 2, 3);

    print_graph_list(list_graph);

    return 0;
}