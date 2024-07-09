#include <stdio.h>

int main() {
	const int DEFAULT_COST = 1000;
	int cost = DEFAULT_COST;
	int age;
	while (1) {
		if (1 != scanf_s("%d", &age)) {
			return 0;
		}
		if (age >= 20)
			cost = DEFAULT_COST * 1;
		else if (age >= 14)
			cost = DEFAULT_COST * 0.75;
		else if (age >= 4)
			cost = DEFAULT_COST * 0.50;
		else if (age >= 0)
			cost = DEFAULT_COST * 0;
		else
			return 0;
		printf("나이: %d 요금: %d\n", age, cost);
	}
}