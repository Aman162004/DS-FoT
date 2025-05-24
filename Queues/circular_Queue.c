#include <stdio.h>
#include <stdlib.h>

typedef struct queue {
    int *items;
    int front, rear, size, capacity;
} queue;

// Create a circular queue
queue* CreateQueue(int capacity) {
    queue* q = (queue*)malloc(sizeof(queue));
    q->capacity = capacity;
    q->items = (int*)malloc(capacity * sizeof(int));
    q->front = -1;
    q->rear = -1;
    q->size = 0;
    return q;
}

// Check if queue is full
int isFull(queue* q) {
    return q->size == q->capacity;
}

// Check if queue is empty
int isEmpty(queue* q) {
    return q->size == 0;
}

// Enqueue operation
void enqueue(queue* q, int value) {
    if (isFull(q)) {
        printf("Circular Queue Overflow\n");
        return;
    }
    if (isEmpty(q))
        q->front = 0;
    q->rear = (q->rear + 1) % q->capacity;
    q->items[q->rear] = value;
    q->size++;
}

// Dequeue operation
int dequeue(queue* q) {
    if (isEmpty(q)) {
        printf("Circular Queue Underflow\n");
        return -1;
    }
    int value = q->items[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    if (q->size == 0) {
        q->front = -1;
        q->rear = -1;
    }
    return value;
}

// Display the circular queue
void display(queue* q) {
    if (isEmpty(q)) {
        printf("Circular Queue is empty\n");
        return;
    }
    printf("Circular Queue: ");
    int i = q->front;
    for (int count = 0; count < q->size; count++) {
        printf("%d ", q->items[i]);
        i = (i + 1) % q->capacity;
    }
    printf("\n");
}

// Free the queue
void freeQueue(queue* q) {
    free(q->items);
    free(q);
}

// Main function to test
int main() {
    int cap;
    printf("Enter capacity of circular queue: ");
    scanf("%d", &cap);

    if (cap <= 0) {
        printf("Capacity must be positive.\n");
        return 1;
    }

    queue* q = CreateQueue(cap);
    
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    display(q);

    printf("Dequeued: %d\n", dequeue(q));
    display(q);

    enqueue(q, 40);
    enqueue(q, 50);
    display(q);

    enqueue(q, 60); // check overflow
    display(q);

    freeQueue(q);
    return 0;
}
