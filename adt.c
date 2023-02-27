#include "adt.h"


void initStack(struct Stack* stack) {
    stack->top = NULL;
}


int isEmptyStack(struct Stack* stack) {
    return (stack->top == NULL);
}


void push(struct Stack* stack, int id, node_type nodeType) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->id = id;
    newNode->nodeType = nodeType; 
    newNode->next = stack->top;
    stack->top = newNode;
}


int pop(struct Stack* stack) {
    if (isEmptyStack(stack)) {
        printf("ERROR: Stack is empty!\n");
        return -1;
    } 
    
    else {
        int id = stack->top->id;
        struct Node* temp = stack->top;
        stack->top = stack->top->next;
        free(temp);
        return id;
    }
}