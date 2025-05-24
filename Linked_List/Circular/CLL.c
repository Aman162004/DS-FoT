#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* Next;
} Node;

void LinkedListTraversal(Node* Head) {
    if (Head == NULL) return; // Check for empty list
    Node* ptr = Head;
    do {
        printf("Element is %d\n", ptr->data);
        ptr = ptr->Next;
    } while (ptr != Head);
}

Node* InsertAtFirst(Node* Head, int Data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->data = Data;

    if (Head == NULL) { // If the list is empty
        newNode->Next = newNode; // Point to itself
        return newNode; // New head
    }

    Node* last = Head;
    while (last->Next != Head) {
        last = last->Next; // Find the last node
    }

    // At this point, last points to the last node of this circular linked list
    last->Next = newNode; // Link last node to new node
    newNode->Next = Head; // New node points to head
    Head = newNode; // Update head to new node
    return Head; // Return new head
}

int main(int argc, char const *argv[]) {
    Node* head = NULL; // Initialize head to NULL

    // Create initial circular linked list
    head = (Node*) malloc(sizeof(Node));
    head->data = 6;
    head->Next = head; // Point to itself to make it circular

    Node* Second = (Node*) malloc(sizeof(Node));
    Second->data = 8;
    Second->Next = head; // Link second to head

    head->Next = Second; // Link head to second

    Node* Third = (Node*) malloc(sizeof(Node));
    Third->data = 10;
    Third->Next = head; // Link third to head

    Second->Next = Third; // Link second to third

    Node* Fourth = (Node*) malloc(sizeof(Node));
    Fourth->data = 20;
    Fourth->Next = head; // Link fourth to head

    Third->Next = Fourth; // Link third to fourth

    // Traverse the list
    printf("Original List:\n");
    LinkedListTraversal(head);

    // Insert a new node at the beginning
    head = InsertAtFirst(head, 66);
    
    // Traverse the list again
    printf("\nList after inserting 66 at the beginning:\n");
    LinkedListTraversal(head);

    // Free allocated memory
    if (head != NULL) {
        Node* current = head;
        Node* nextNode;
        do {
            nextNode = current->Next;
            free(current);
            current = nextNode;
        } while (current != head);
    }

    return 0;
}