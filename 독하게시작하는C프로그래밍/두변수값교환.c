#include <stdio.h>

int main() {
	int a, b;
	if (2 != scanf_s("%d %d",& a, &b)) {
		return 0;
	}
	
	int tmp = a;
	a = b;
	b = tmp;

	printf("a:%d, b:%d", a, b);
}