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
				StackPop(&s); // '(' 날리기
			}
			else {
				if(!StackIsEmpty(&s) && StackPeek(&s) == '(')
					StackPush(&s, infix[cntIn]);
				else if (priority == 1 && (cntIn == 0 || !isdigit(infix[cntIn - 1]))) { // 단항 연산 처리
					postfix[cntPost++] = ' '; // 단항 연산 구분
					postfix[cntPost++] = infix[cntIn++];
					if (isdigit(infix[cntIn])) {
						postfix[cntPost++] = infix[cntIn];
						while (isdigit(infix[cntIn + 1]))
							postfix[cntPost++] = infix[++cntIn];
						postfix[cntPost++] = ' ';
					}
				}
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
	int flag = 0;
	while (postfix[cntPost] != '\0') {
		
		if (postfix[cntPost] == ' ' || isdigit(postfix[cntPost])) {
			int cntTmp = 0;
			char tmp[12] = { 0 };
			if (postfix[cntPost] == ' ') { // 단항 연산 처리
				cntPost++;
				tmp[cntTmp++] = postfix[cntPost++];
			}

			while (postfix[cntPost] != ' ') {
				tmp[cntTmp++] = postfix[cntPost++];
			}
			StackPush(&s, atoi(tmp));
		}
		else {
			rhs = StackPop(&s);			lhs = StackPop(&s);
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
				flag = 1;
				StackPush(&s, Div(lhs, rhs, remain));
				break;
			}
		}
		cntPost++;
	}
	if (flag == 0)
		*remain = -1; // 나눗셈 연산이 없기 때문에 나머지 출력 x
	return StackPop(&s);
}