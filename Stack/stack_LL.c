#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data ;
     Node *next;
}Node;

typedef struct Stack{
    Node * top ; 
    int size ;
}Stack;


Stack * create_stack(){
    Stack * stack = (Stack*)malloc(sizeof(Stack));
    stack -> top = NULL;
    stack -> size = 0;
    return stack;
}

Node * create_node(int value , Node * next){
    Node * new_node = (Node*)malloc(sizeof(Node));
    new_node ->data = value;
    new_node ->next = next ;
    return new_node;
}

int is_empty(Stack * stack){
    return stack->top == NULL;
}

void push (Stack * stack , int value){
    Node * new_node  = create_node(value, stack-> top);
    if(new_node = NULL ){
        return ; 
    }
    stack -> top  = new_node ; 
    stack -> size ++ ; 
}

int pop (Stack * stack ){
    Node * temp = stack -> top ;
    int data = temp->data;
    stack ->top = temp -> next;
    free(temp);
    stack-> size --;
    return data;
}

int peek(Stack * stack) {
    return stack->top->data;
}

int get_size (Stack *stack){
    return stack->size;
}

void destroy_stack(Stack * stack){
    Node * current = stack -> top ; 
    while (current != NULL){
        Node * next  = current -> next ; 
        free(current);
        current = next ; 
    }
    free(stack);
}