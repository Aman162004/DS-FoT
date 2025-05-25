#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 10


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
    int front;
    int rear;
} Queue;


void initialize_queue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}


int is_empty(Queue *q) {
    return q->front == -1;
}


int is_full(Queue *q) {
    return q->rear == MAX_SIZE - 1;
}


int enqueue(Queue *q, int value) {
    if (is_full(q)) {
        printf("Queue is full\n");
        return -1;
    } else {
        if (is_empty(q)) {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = value;
        return 0;
    }
}


int dequeue(Queue *q) {
    if (is_empty(q)) {
        printf("Queue is empty\n");
        return INT_MIN;
    } else {
        int item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
        return item;
    }
}


GraphList* create_graph_list(int vertices) {
    GraphList* graph = malloc(sizeof(GraphList));
    graph->num_vertices = vertices;
    graph->adj_lists = malloc(sizeof(Node*) * vertices);
    for (int i = 0; i < vertices; i++) {
        graph->adj_lists[i] = NULL;
    }

    return graph;
}


int add_edge_list(GraphList* graph, int src, int dest) {
    Node* new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->vertex = dest;
    new_node->next = graph->adj_lists[src];
    graph->adj_lists[src] = new_node;


    new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        return -1;
    }
    new_node->vertex = src;
    new_node->next = graph->adj_lists[dest];
    graph->adj_lists[dest] = new_node;

    return 0;
}


int traverse_bfs_iterative(GraphList* graph, int start_vertex) {

    int curr_vertex;
    int visited[graph->num_vertices];

    for (int i = 0; i < graph->num_vertices; i++) {
        visited[i] = 0;
    }

    Queue queue;
    initialize_queue(&queue);

    visited[start_vertex] = 1;
    enqueue(&queue, start_vertex);

    while (!is_empty(&queue)) {
        curr_vertex = dequeue(&queue);
        printf("Visited %d\n", curr_vertex);

        Node* temp = graph->adj_lists[curr_vertex];
        while (temp) {
            int adj_vertex = temp->vertex;
            if (!visited[adj_vertex]) {
                visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }

    return 0;
}

int main() {

    GraphList *graph = create_graph_list(5);
    add_edge_list(graph, 0, 1);
    add_edge_list(graph, 0, 2);
    add_edge_list(graph, 0, 3);
    add_edge_list(graph, 1, 2);
    add_edge_list(graph, 3, 4);

    traverse_bfs_iterative(graph, 0);
    return 0;
}