#include <stdio.h>
#include <limits.h>
int main() {
	int input;
	int max = INT_MIN;
	while (1) {
		if (1 != scanf_s("%d", &input)) {
			return 0;
		}
		if (max < input)
			max = input;
		printf("MAX: %d\n", max);
	}
}