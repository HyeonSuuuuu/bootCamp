#include<stdio.h>

int main() {
	int score;
	printf("������ �Է��ϼ���: ");
	if (1 != scanf_s("%d", &score)) {
		return 0;
	}
	if (score > 100 || score < 0)
		return 0;
	printf("���: ");
	if (score >= 80)
		printf("�հ�");
	else
		printf("���հ�");
}