#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
    int* items;
    int front, rear;
    int capacity;
} queue;

queue* CreateQueue(int capacity) {
    queue* q = (queue*)malloc(sizeof(queue));
    q->capacity = capacity;
    q->front = 0;
    q->rear = -1;
    q->items = (int*)malloc(capacity * sizeof(int));
    return q;
}

int isFull(queue* q) {
    return q->rear == q->capacity - 1;
}

int isEmpty(queue* q) {
    return q->front > q->rear;
}

void enqueue(queue* q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow\n");
        return;
    }
    q->items[++q->rear] = value;
}

int dequeue(queue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    return q->items[q->front++];
}

void display(queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue: ");
    for (int i = q->front; i <= q->rear; i++)
        printf("%d ", q->items[i]);
    printf("\n");
}

void freeQueue(queue* q) {
    free(q->items);
    free(q);
}

int main() {
    queue* q = CreateQueue(5);
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    display(q);
    printf("Dequeued: %d\n", dequeue(q));
    display(q);
    freeQueue(q);
    return 0;
}
