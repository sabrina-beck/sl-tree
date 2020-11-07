#include "stack.h"

#include <stdlib.h>

StackNode* newStackNode(void* data, StackNode* next) {
    StackNode* newNode = malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = next;
    return newNode;
}

void freeStackNode(StackNode* node) {
    free(node);
}

Stack* newStack() {
    Stack* stack = malloc(sizeof(Stack));
    stack->size = 0;
    stack->top = NULL;
    return stack;
}

void push(Stack* stack, void* data) {
    StackNode* newNode = newStackNode(data, stack->top);
    stack->top = newNode;
    stack->size++;
}

void* pop(Stack* stack){
    StackNode* poppedNode = stack->top;
    stack->top = poppedNode->next;
    stack->size--;

    void* data = poppedNode->data;
    freeStackNode(poppedNode);

    return data;
}