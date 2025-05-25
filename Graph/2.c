#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    int num_vertices;
    Node** adj_lists;
} GraphList;

typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;


Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

int is_empty(Stack* stack) {
    return stack->top == -1;
}

int is_full(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

int push(Stack* stack, int item) {
    if (is_full(stack)) {
        printf("Stack is full. Cannot push %d.\n", item);
        return INT_MAX;
    }
    stack->items[++stack->top] = item;

    return 0;
}

int pop(Stack* stack) {
    if (is_empty(stack)) {
        printf("Stack is empty. Cannot pop.\n");
        return INT_MIN;
    }
    return stack->items[stack->top--];
}

void destroy_stack(Stack* stack) {
    free(stack);
}


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

int dfs_iterative(GraphList* graph, int start_vertex) {

    int curr_vertex;
    int visited[graph->num_vertices];

    for (int i = 0; i < graph->num_vertices; i++) {
        visited[i] = 0;
    }

    Stack* stack = create_stack();
    push(stack, start_vertex);

    while (!is_empty(stack)) {
        curr_vertex = pop(stack);
        if (!visited[curr_vertex]) {
            visited[curr_vertex] = 1;
            printf("Visited %d \n", curr_vertex);
        }

        // Go through one linked list corresponding to vertex 0
        Node* temp = graph->adj_lists[curr_vertex];
        // Node* temp = graph->adj_lists[0];

        while (temp != NULL) {
            int adj_vertex = temp->vertex;
            if (!visited[adj_vertex]) {
                push(stack, adj_vertex);
            }
            temp = temp->next;
        }

    }

    destroy_stack(stack);

    return 0;
}

int main() {
    GraphList* graph = create_graph_list(5);
    add_edge_list(graph, 0, 1);
    add_edge_list(graph, 0, 2);
    add_edge_list(graph, 0, 3);
    add_edge_list(graph, 1, 2);
    add_edge_list(graph, 3, 4);

    dfs_iterative(graph, 0);

    return 0;
}