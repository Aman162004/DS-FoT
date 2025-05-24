#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100 // Removed the semicolon here

typedef struct {
    int items[MAXSIZE];
    int front, rear;
} Queue;

Queue* create_queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q == NULL) { // Always check if malloc was successful
        perror("Failed to allocate queue");
        return NULL; // Return NULL on allocation failure
    }
    q->front = -1;
    q->rear = -1;
    return q; // Return the allocated queue pointer
}

void destroy_queue(Queue* q) { // Changed return type to void
    free(q);
}

int is_full(Queue* q) {
    return q->rear == MAXSIZE - 1;
}

int is_empty(Queue* q) {
    return q->front == -1 || q->front > q->rear;
}

int enqueue(Queue* q, int item) {
    if (is_full(q)) {
        printf("Queue is full.\n");
        return -1;
    }
    if (q->front == -1) {
        q->front = 0;
    }
    q->items[++q->rear] = item;
    return 0;
}

// Modified dequeue to return a status and pass value by reference
int dequeue(Queue* q, int* item) {
    if (is_empty(q)) {
        printf("Queue is empty.\n");
        return -1; // Indicate failure
    }
    *item = q->items[q->front++];
    // Optional: Reset front/rear if queue becomes completely empty
    if (q->front > q->rear) {
        q->front = -1;
        q->rear = -1;
    }
    return 0; // Indicate success
}

// Modified peek to return a status and pass value by reference
int peek(Queue* q, int* item) {
    if (is_empty(q)) {
        printf("Queue is empty.\n");
        return -1; // Indicate failure
    }
    *item = q->items[q->front];
    return 0; // Indicate success
}