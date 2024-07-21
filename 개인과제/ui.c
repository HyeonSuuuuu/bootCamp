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
	printf("[1] ��Ģ����\t[0]������\n");
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
	printf("���� �Է��� �ּ���\n");
	char szBuffer[STACK_MAX] = { 0 };
	if (1 != scanf_s("%s", szBuffer, STACK_MAX)) {
		printf("�߸��� �Է°��Դϴ�.\n");
		return;
	}
	if (!CheckBracket(szBuffer)) {
		printf("��ȣ ¦�� ���� �ʽ��ϴ�.\n");
			return;
	}
	char szPostfix[STACK_MAX*2] = { 0 };

	if (-1 == InfixToPostfix(szBuffer, szPostfix)) {
		printf("�Ŀ��� +-*/()������ ��� �����մϴ�.\n");
		return;
	}
	int remain = 0;
	int result = CalculatePostfix(szPostfix, &remain);

	printf("�����: %d\n������: %d\n", result, remain);
}