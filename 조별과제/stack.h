#pragma once

#define MAX_DIGIT_NUMBER 100
#define STACK_MAX 256
typedef struct {
	int items[STACK_MAX]; 
	int top;
} Stack;	

typedef struct {
	char* items[STACK_MAX];
	int top;
} PszStack;

void StackInit(Stack* s);
int StackIsEmpty(Stack* s);
int StackIsFull(Stack* s);
void StackPush(Stack* s, int value);
int StackPop(Stack* s);
int StackPeek(Stack* s);

void PszStackInit(PszStack* s);
int PszStackIsEmpty(PszStack* s);
int PszStackIsFull(PszStack* s);
void PszStackPush(PszStack* s, char* value);
char* PszStackPop(PszStack* s);
char* PszStackPeek(PszStack* s);