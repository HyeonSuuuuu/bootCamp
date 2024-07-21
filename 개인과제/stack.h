#pragma once


#define STACK_MAX 256

typedef struct {
	int items[STACK_MAX];
	int top;
} Stack;

void StackInit(Stack* s);
int StackIsEmpty(Stack* s);
int StackIsFull(Stack* s);
void StackPush(Stack* s, int value);
int StackPop(Stack* s);
int StackPeek(Stack* s);