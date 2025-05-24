#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int Data;
    struct Node* Next;
    struct Node* prev;
}Node;

typedef struct Doubly_Linked_list
{
    Node* Head;
}Doubly_Linked_list;

Doubly_Linked_list* CreateList(){
    Doubly_Linked_list* list = (Doubly_Linked_list*) malloc (sizeof(Doubly_Linked_list));
    list->Head=NULL;
    return list;
}

Node* CreateNode (int value){
    Node* NewNode = (Node*) malloc (sizeof(Node));
    NewNode->Data=value;
    NewNode->Next=NULL;
    NewNode->prev=NULL;
    return NewNode;
}

void insertatFirst(Doubly_Linked_list* list, int value){
    Node* NewNode = CreateNode(value);
    NewNode->Next=list->Head;
    if (list->Head!=NULL)
    {
        list->Head->prev=NewNode;
    }
    list->Head=NewNode;
}

void insertatend (Doubly_Linked_list* list,int value){
    Node* NewNode = (Node*) malloc (sizeof(Node));
    if (list->Head==NULL){
        list->Head=NewNode;
        return;
    }
    Node* ptr = list->Head;
    while (ptr->Next!=NULL)
    {
        ptr=ptr->Next;
    }
    ptr->Next=NewNode;
    NewNode->prev=ptr;
}

void insertAtIndex(Doubly_Linked_list* list, int value, int index){
    if (list->Head==NULL)
    {
        return insertatFirst(list,value);
    }
    Node* NewNode = CreateNode(value);
    Node* ptr = list->Head;
    int i = 0;
    while (i<index-1 && ptr!=NULL)
    {
       ptr = ptr->Next;
       i++;
    }
    if (ptr==NULL)
    {
        printf("Index out of bond\n");
        free(NewNode);
        return;
    }
    NewNode->Next=ptr->Next;
    NewNode->prev=ptr;
    if (ptr->Next=NULL)
    {
        ptr->Next->prev=NewNode;
    }
    ptr->Next=NewNode;
}

void traverseForward(Doubly_Linked_list* list){
    Node* ptr = list->Head;
    printf("List Forward: ");
    while (ptr!=NULL)
    {
        printf("%d ",ptr->Data);
        ptr=ptr->Next;
    }
    printf("\n");
}

void traverseBackward(Doubly_Linked_list* list){
    if (list->Head==NULL)
    {
        return;
    }
    Node* ptr = list->Head;
    while (ptr->Next!=NULL)
    {
        ptr = ptr->Next;
    }
    printf("List Backward: ");
    while (ptr!=NULL)
    {
        printf("%d", ptr->Data);
        ptr=ptr->prev;
    }
    printf("\n");
}

void deleteatfirst(Doubly_Linked_list* list){
    if (list->Head==NULL)
    {
        return;
    }
    Node* ptr = list->Head;
    list->Head=list->Head->Next;
    if (list->Head!=NULL)
    {
        list->Head->prev=NULL;
    }
    free(ptr);
}

void deleteatindex(Doubly_Linked_list* list, int index){
    if (index=0)
    {
        return deleteatfirst;
    }
    Node* ptr = list->Head;
    int i = 0;
    while (i<index && ptr->Next!=NULL)
    {
        ptr = ptr->Next;
        i++;
    }
    if (ptr = NULL)
    {
        printf("Index Out of Bound\n");
        return;
    }
    if (ptr->prev!=NULL)
    {
        ptr=ptr->Next=ptr->Next;
    }
    if (ptr->Next!=NULL)
    {
        ptr=ptr->prev=ptr->prev;
    }
    free(ptr);
}

void deleteAtEnd(Doubly_Linked_list* list){
    if (list->Head==NULL)
    {
        return;
    }
    Node* ptr = list->Head;
    if (ptr->Next==NULL)
    {
        free(ptr);
        list->Head=NULL;
        return;
    }
    while (ptr->Next!=NULL)
    {
        ptr=ptr->Next;
    }
    ptr->prev->Next=NULL;
    free(ptr);
}

void freelist(Doubly_Linked_list* list){
    Node* ptr = list->Head;
    while (ptr!=NULL)
    {
        Node* temp = ptr;
        ptr = ptr->Next;
        free(temp);
    }
    free(list);
}

int main() {
    Doubly_Linked_list *list = createList();

    insertatFirst(list, 10);
    insertatFirst(list, 20);
    insertatend(list, 30);
    insertAtIndex(list, 25, 2);

    printf("After insertions:\n");
    traverseForward(list);
    traverseForward(list);

    deleteatfirst(list);
    printf("\nAfter deleting first:\n");
    traverseForward(list);

    deleteAtEnd(list);
    printf("\nAfter deleting last:\n");
    traverseForward(list);

    // deleteByValue(list, 25);
    // printf("\nAfter deleting by value 25:\n");
    // traverseForward(list);

    freeList(list);

    return 0;
}