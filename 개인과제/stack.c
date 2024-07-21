#include "stack.h"

void StackInit(Stack* s)
{
	s->top = -1;
}
int StackIsEmpty(Stack* s)
{
	if (s->top == -1)
		return 1;
	return 0;
}
int StackIsFull(Stack* s)
{
	if (s->top == STACK_MAX - 1)
		return 1;
	return 0;
}
void StackPush(Stack* s, int value)
{
	if (StackIsFull(s)) {
		printf("stack full\n");
		return;
	}
	s->items[++(s->top)] = value;
}
int StackPop(Stack* s)
{
	if (StackIsEmpty(s)) {
		printf("Stack empty\n");
		return -1;
	}

	return s->items[(s->top)--];
}

int StackPeek(Stack* s)
{
	if (StackIsEmpty(s)) {
		printf("Stack empty\n");
		return -1;
	}
	return s->items[(s->top)];
}