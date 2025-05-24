//using linked list

#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next; 
}Node;

//Any logical Data struture i.e., ADT will contain metadata in the STRUCTURE / CLASS of ADT  
//metadata is data about data 

typedef struct{ 
    Node* top; 
    int count;
} Stack;
 
Stack* create_stack();
int is_empty(Stack* stack);
int push(Stack* stack, int data);
int pop(Stack* stack);
int peek(Stack* stack);
int get_size(Stack* stack);
int destroy_stack(Stack* stack);

int main(){

}

Stack* create_stack(){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top=NULL;
    stack->count=0;
    return stack;
}

int is_empty(Stack* stack){
    return stack->top == NULL;
}

int push(Stack* stack, int data){
    //insert_at_head() for a linked list 
    Node* newNode = (Node*)mallod(sizeof(Node));
    newNode->data=data;
    newNode->next= stack->top;
    stack->top = newNode;
    stack->count++;

    return 0;
}

int pop(Stack* stack){
    if(is_empty(stack)){
        printf("Stack is empty. Cannot pop.\n");
        return -1;
    }
    Node* temp= stack->top;
    int data= temp->data;
    stack->top=temp->next;
    free(temp);
    stack->count--;
    return data;
}

int peek(Stack* stack){
    if(is_empty(stack)){
        printf("Stack is empty.\n");
        return -1;
    }
    return stack->top->data;
}

int get_size(Stack* stack){
    return stack->count;
}

int destroy_stack(Stack* stack){
    while(!is_empty(stack)){
        pop(stack);
    }
    free(stack);

    return 0;
}