#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "stack.h"
#include "basicOperation.h"
#include "calculation.h"


int Priority(char operator)
{
	if (operator == '+' || operator == '-')
		return 1;
	else if (operator == '*' || operator == '/')
		return 2;
	else if (operator =='(' || operator == ')')
		return 0;
	else
		return -1;

}


int CheckBracket(const char* const infix)
{
	int cntBracket = 0;
	for (int i = 0; i < strlen(infix); ++i) {
		if (infix[i] == '(') {
			cntBracket++;
		}
		else if (infix[i] == ')') {
			cntBracket--;
		}
	}

	if (cntBracket != 0)
		return 0;

	return 1;
}


int InfixToPostfix(const char* const infix, char* const postfix)
{
	Stack s;
	StackInit(&s);
	int cntIn = 0;
	int cntPost = 0;
	int priority = 0;
	int tmp = 0;


	while (infix[cntIn] != '\0') {
		if (isdigit(infix[cntIn])) {
			postfix[cntPost++] = infix[cntIn];
			while(isdigit(infix[cntIn+1]))
				postfix[cntPost++] = infix[++cntIn];
			postfix[cntPost++] = ' ';
		}
		else {
			priority = Priority(infix[cntIn]); 
			if (priority == -1)
				return -1;
			else if (infix[cntIn] == '(') {
				StackPush(&s, infix[cntIn]);
			}
			else if (infix[cntIn] == ')') {
				while (StackPeek(&s) != '(') {
					postfix[cntPost++] = StackPop(&s);
				}
				StackPop(&s); // '(' ³¯¸®±â
			}
			else {
				if(!StackIsEmpty(&s) && StackPeek(&s) == '(')
					StackPush(&s, infix[cntIn]);
				else {
					while (!StackIsEmpty(&s) && priority <= Priority(StackPeek(&s))) {
						postfix[cntPost++] = StackPop(&s);
					}
					StackPush(&s, infix[cntIn]);
				}
			}
		}
		cntIn++;
	}
	while (!StackIsEmpty(&s)) {
		postfix[cntPost++] = StackPop(&s);
	}
	return 1;
}

int CalculatePostfix(const char* postfix, int* remain)
{
	Stack s;
	StackInit(&s);
	int cntPost = 0;
	int lhs = 0, rhs = 0;
	while (postfix[cntPost] != '\0') {
		
		if (isdigit(postfix[cntPost])) {
			int cntTmp = 0;
			char tmp[10] = { 0 };
			while (postfix[cntPost] != ' ') {
				tmp[cntTmp++] = postfix[cntPost++];
			}
			StackPush(&s, atoi(tmp));
		}
		else {
			rhs = StackPop(&s);
			lhs = StackPop(&s);
			switch (postfix[cntPost]) {
			case '+':
				StackPush(&s, Add(lhs, rhs));
				break;
			case '-':
				StackPush(&s, Sub(lhs, rhs));
				break;
			case '*':
				StackPush(&s, Mul(lhs, rhs));
				break;
			case '/':
				StackPush(&s, Div(lhs, rhs, remain));
				break;
			}
		}
		cntPost++;
	}

	return StackPop(&s);
}