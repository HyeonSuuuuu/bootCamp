#include <stdio.h>

int main() {
	int input;
	while (1) {
		if (1 != scanf_s("%d", &input)) {
			return 0;
		}
		if (input > 9)
			input = 9;
		int i = 0;
		while (i < input) {
			printf("* ");
			++i;
		}
		putchar('\n');
	}
}