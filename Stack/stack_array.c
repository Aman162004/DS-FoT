#include <stdio.h>
#include <stdlib.h>

// Stack structure definition
typedef struct stack
{
    int *items;
    int top;
    int capacity;
}stack;

// Function to create a stack
stack* CreateStack(int capacity){
    stack *s = (stack*) malloc (sizeof(stack));
    s->items = (int*)malloc(capacity*sizeof(int));
    s->top=-1;
    s->capacity=capacity;
    return s;
}

// to free the stack
void freestack(stack* s){
    if (s)
    {
        free(s->items);
        free(s);
    }
}

// Check if stack is full
int isFull(stack* s){
    return s->top==s->capacity-1;
}

// Check if stack is empty
int isEmpty(stack* s){
    return s->top==-1;
}

// Push an element onto the stack
void push (stack* s, int value){
    if (isFull(s))
    {
        printf("Stack is already full/overflaw case\n");
        return;
    }
    s->items[++(s->top)]=value;
}

// Pop the top element
int pop(stack* s){
    if (isEmpty(s))
    {
        printf("stack is empty/underflow condition\n");
        return -1;
    }
    return s->items[(s->top)--];
}

int peek (stack* s){
    if (isEmpty(s))
    {
        printf("Stack is empty\n");
        return -1;
    }
    return s->items[s->top];
}

void display(stack* s){
    if(isEmpty(s)){
        printf("Stack is empty\n");
        return;
    }
    printf("The stack is : ");
    for (int i = s->top; i >= 0; i--)
    {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    int capacity;
    printf("Enter the capacity of the array\n");
    scanf("%d", &capacity);

    if (capacity <= 0) {
        printf("Capacity must be a positive integer.\n");
        return 1;
    }

    stack* s = CreateStack(capacity);
    if (!s) return 1;

    push(s, 10);
    push(s, 14);
    push(s, 17);
    push(s, 67);

    display(s);
    printf("The topmost element in stack is: %d\n", peek(s));
    printf("The popped element is: %d\n", pop(s));

    display(s);
    freestack(s);
    return 0;
}
