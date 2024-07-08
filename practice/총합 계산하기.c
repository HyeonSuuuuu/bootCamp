#include <stdio.h>

int main() {
	int i = 0;
	int total = 0;
	int input;
	while (i < 10) {
		if (1 != scanf_s("%d", &input)) {
			return 0;
		}
		total += input;
		++i;
	}
	printf("Total: %d", total);
}