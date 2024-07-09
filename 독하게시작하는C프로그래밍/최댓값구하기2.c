#include <stdio.h>
#include <limits.h>
int main() {
	int a, b, c;
	if (3 != scanf_s("%d %d %d", &a, &b, &c)) {
		return 0;
	}
	int max = INT_MIN;
	max = (max > a) ? max : a;
	max = (max > b) ? max : b;
	max = (max > c) ? max : c;

	printf("MAX: %d\n", max);

}