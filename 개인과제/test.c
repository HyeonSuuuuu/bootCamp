#include "test.h"
#include "stack.h"




void StackTest01(void)
{
	Stack s;
	StackInit(&s);
	for (int i = 0; i < STACK_MAX + 3; ++i) {
		StackPush(&s, 3);
	}
	for (int i = 0; i < STACK_MAX + 3; ++i) {
		StackPop(&s);
	}
	for (int i = 0; i < STACK_MAX; ++i) {
		StackPush(&s, ')');
	}
	StackPop(&s);
	printf("top[%d] value[%c]", s.top, s.items[s.top]);
}

void CalculateTest01(void)
{
	char formula[10][100] = {
		"3-4*2/1",   // result -5
		"3+5*(4-2)/12", // result 3
		"(12341+32103)/4*2+(32-30)", // result 22224
		"(3+4*(3-1)/(3-2)*2-3)-(3*2)", //result 10
		"3+4*(3-1)/2", // result 7
		"123,dsfoqwqe", // result x
		"3%3", // result x
		"123+3+3+3+3+3", //result 138 
		"3*3*3*3*3*3/3/3/3/3/3/3", //result 1
		"(3+4)*(3+4)", // result 49
	};

	int result = 0;
	for (int i = 0; i < 10; ++i) {
		if (i == 2)
			printf("2");
		char szPostfix[STACK_MAX * 2] = { 0 };
		int result = InfixToPostfix(formula[i], szPostfix);
		if (result == -1)
			printf("잘못된 입력값\n");
		else {
			printf("%s - postFix: %s", formula[i], szPostfix);
			int result = CalculatePostfix(szPostfix);
			printf("result %d\n", result);
		}
	}


}