#include<stdio.h>

int main() {
	int score;
	printf("점수를 입력하세요: ");
	if (1 != scanf_s("%d", &score)) {
		return 0;
	}
	if (score > 100 || score < 0)
		return 0;
	printf("결과: ");
	if (score >= 80)
		printf("합격");
	else
		printf("불합격");
}