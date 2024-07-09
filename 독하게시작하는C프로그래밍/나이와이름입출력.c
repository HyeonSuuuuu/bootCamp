#include<stdio.h>

int main() {
	int age = 0;
	char name[32] = {0};
	printf("나이를 입력하세요: ");
	if (1 != scanf_s("%d%*c", &age)) {
		return 0;
	}
	printf("이름를 입력하세요: ");
	gets_s(name, sizeof(name));
	printf("당신의 나이는 %d살이고 이름은 %s입니다.", age, name);
}