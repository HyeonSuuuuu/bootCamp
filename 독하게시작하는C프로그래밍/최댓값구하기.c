#include <stdio.h>
#include <limits.h>
int main() {
	int max = INT_MIN;
	int input;
	while (1) {
		if (1 != scanf_s("%d", &input)) {
			return 0;
		}
		max = (max > input) ? max : input;
		printf("MAX: %d\n", max);
	}
}