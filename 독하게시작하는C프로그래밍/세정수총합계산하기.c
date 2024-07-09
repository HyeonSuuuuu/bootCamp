#include <stdio.h>

int main() {
	int a, b, c;
	if (3 != scanf_s("%d %d %d", &a, &b, &c)) {
		return 0;
	}
	int total = 0;
	total += a;
	total += b;
	total += c;
	printf("Total: %d", total);
}