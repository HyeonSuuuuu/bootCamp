#include<stdio.h>

int main() {
	int cost = 1000;
	int age;
	while (1) {
		if (1 != scanf_s("%d", &age)) {
			return 0;
		}
		if (age >= 20) {
			age = 20;
			cost = 1000;
		}
		else
			cost = 1000 * 0.75;
		printf("나이: %d, 최종요금: %d\n", age, cost);
	}

}