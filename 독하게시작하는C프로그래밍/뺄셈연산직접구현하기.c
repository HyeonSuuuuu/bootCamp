#include<stdio.h>

int main() {
	int a, b;
	if (2 != scanf_s("%d %d", &a, &b)) {
		return 0;
	}
	int result = a + ~b + 1;
	printf("%d", result);
}