#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "stack.h"
#include "calculation.h"
#include "test.h"
 
int main() {

	EventLoopRun();

	return 0;
}


MY_MENU PrintMenu(void)
{
	MY_MENU input = 0;
	system("cls");
	printf("[1] 사칙연산\t[0]나가기\n");
	if (1 != scanf_s("%d", &input)) {
		while (getchar() != '\n');
		return -1;
	}
	return input;
}

void EventLoopRun()
{
	MY_MENU menu = 0;
	while ((menu = PrintMenu()) != 0) {
		switch (menu) {
		case MENU_CALCULATION:
			Calculator();
			break;
		case MENU_EXIT:
			break;
		default:
			continue;
		}
		_getch();
	}
}



void Calculator()
{
	printf("식을 입력해 주세요\n");
	char szBuffer[STACK_MAX] = { 0 };
	if (1 != scanf_s("%s", szBuffer, STACK_MAX)) {
		printf("잘못된 입력값입니다.\n");
		return;
	}
	if (!CheckBracket(szBuffer)) {
		printf("괄호 짝이 맞지 않습니다.\n");
			return;
	}
	char szPostfix[STACK_MAX*2] = { 0 };

	if (-1 == InfixToPostfix(szBuffer, szPostfix)) {
		printf("식에는 +-*/()정수만 사용 가능합니다.\n");
		return;
	}
	int remain = 0;
	int result = CalculatePostfix(szPostfix, &remain);

	printf("결과값: %d\n나머지: %d\n", result, remain);
}