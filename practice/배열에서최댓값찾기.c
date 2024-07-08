#include <stdio.h>
#include <limits.h>
int main() {

	/*int arr[5] = { 50, 40, 10, 50, 20 };
	int nMax = INT_MIN;
	for (int i = 0; i < 5; ++i) {
		if (nMax < arr[i])
			nMax = arr[i];
	}
	printf("MAX: %d", nMax);*/

	int arr[5] = { 50, 40, 10, 50, 20 };
	int tmp;
	for (int i = 1; i < 5; ++i) {
		if (arr[0] > arr[i]) {
			tmp = arr[0];
			arr[0] = arr[i];
			arr[i] = tmp;
		}
	}
	for (int i = 0; i < 5; ++i) {
		printf("%d ", arr[i]);
	}
}