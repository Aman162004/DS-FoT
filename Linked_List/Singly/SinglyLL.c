#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
typedef struct Node {
    int Data;
    struct Node *Next;
} Node;

// Define the structure for the linked list (ADT)
typedef struct LinkedList {
    Node *head; // Pointer to the head of the linked list
} LinkedList;

// Function to create a new linked list
LinkedList* createLinkedList() {
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL; // Initialize the head to NULL
    return list;
}

// Function to create a new node
Node* createNode(int data) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->Data = data;
    newNode->Next = NULL;

    return newNode;
}

// Function to traverse and print the linked list
void traverseLinkedList(LinkedList *list) {
    Node *ptr = list->head;
    while (ptr != NULL) {
        printf("Element: %d\n", ptr->Data);
        ptr = ptr->Next;
    }
}

// Function to insert a new node at the beginning of the linked list
void insertAtFirst(LinkedList *list, int data) {
    Node *newNode = createNode(data);
    newNode->Next = list->head;
    list->head = newNode;
}

// Function to insert a new node at the end of the linked list
void insertAtEnd(LinkedList *list, int data) {
    Node *newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }
    Node *ptr = list->head;
    while (ptr->Next != NULL) {
        ptr = ptr->Next;
    }
    ptr->Next = newNode;
}

// Function to insert a new node at a specific index in the linked list
void insertAtIndex(LinkedList *list, int data, int index) {
    if (index == 0) {
        insertAtFirst(list, data);
        return;
    }
    Node *newNode = createNode(data);
    Node *ptr = list->head;
    int i = 0;
    while (ptr != NULL && i < index - 1) {
        ptr = ptr->Next;
        i++;
    }
    if (ptr == NULL) {
        printf("Index out of bounds.\n");
        free(newNode);
        return;
    }
    newNode->Next = ptr->Next;
    ptr->Next = newNode;
}

// Function to delete the first node of the linked list
void deleteAtFirst(LinkedList *list) {
    if (list->head == NULL) return;
    Node *ptr = list->head;
    list->head = list->head->Next;
    free(ptr);
}

// Function to delete a node at a specific index in the linked list
void deleteAtIndex(LinkedList *list, int index) {
    if (index == 0) {
        deleteAtFirst(list);
        return;
    }
    Node *ptr = list->head;
    Node *prev = NULL;
    int i = 0;
    while (ptr != NULL && i < index) {
        prev = ptr;
        ptr = ptr->Next;
        i++;
    }
    if (ptr == NULL) {
        printf("Index out of bounds.\n");
        return;
    }
    prev->Next = ptr->Next;
    free(ptr);
}

// Function to delete the last node of the linked list
void deleteAtEnd(LinkedList *list) {
    if (list->head == NULL) return;
    if (list->head->Next == NULL) {
        free(list->head);
        list->head = NULL;
        return;
    }
    Node *ptr = list->head;
    Node *prev = NULL;
    while (ptr->Next != NULL) {
        prev = ptr;
        ptr = ptr->Next;
    }
    prev->Next = NULL;
    free(ptr);
}

// Function to delete a node by value in the linked list
void deleteByValue(LinkedList *list, int value) {
    if (list->head == NULL) return;
    if (list->head->Data == value) {
        deleteAtFirst(list);
        return;
    }
    Node *ptr = list->head;
    Node *prev = NULL;
    while (ptr != NULL && ptr->Data != value) {
        prev = ptr;
        ptr = ptr->Next;
    }
    if (ptr == NULL) {
        printf("Value not found in the list.\n");
        return;
    }
    prev->Next = ptr->Next;
    free(ptr);
}

void tosearchelements(LinkedList* list,int num){
    Node* ptr = list->head;
    int index = 0;
    while (ptr!=NULL)
    {
        if (ptr->Data==num)
        {
            return index;
        }
        ptr=ptr->Next;
        index++;
    }
}

// Function to free the entire linked list
void freeLinkedList(LinkedList *list) {
    Node *ptr = list->head;
    while (ptr != NULL) {
        Node *temp = ptr;
        ptr = ptr->Next;
        free(temp);
    }
    free(list);
}

// Main function to demonstrate the linked list ADT
int main() {
    LinkedList *list = createLinkedList();

    // Insert elements
    insertAtFirst(list, 10);
    insertAtFirst(list, 20);
    insertAtEnd(list, 30);
    insertAtIndex(list, 25, 2);

    printf("Linked list after insertions:\n");
    traverseLinkedList(list);

    // Delete elements
    deleteAtFirst(list);
    printf("\nLinked list after deleting the first element:\n");
    traverseLinkedList(list);

    deleteAtEnd(list);
    printf("\nLinked list after deleting the last element:\n");
    traverseLinkedList(list);

    deleteByValue(list, 25);
    printf("\nLinked list after deleting by value (25):\n");
    traverseLinkedList(list);

    // Free the linked list
    freeLinkedList(list);

    return 0;
}