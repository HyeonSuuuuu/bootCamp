#include<stdio.h>

int main() {
	int age = 0;
	char name[32] = {0};
	printf("���̸� �Է��ϼ���: ");
	if (1 != scanf_s("%d%*c", &age)) {
		return 0;
	}
	printf("�̸��� �Է��ϼ���: ");
	gets_s(name, sizeof(name));
	printf("����� ���̴� %d���̰� �̸��� %s�Դϴ�.", age, name);
}