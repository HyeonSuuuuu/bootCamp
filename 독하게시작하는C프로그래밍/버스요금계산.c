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
		printf("����: %d, �������: %d\n", age, cost);
	}

}