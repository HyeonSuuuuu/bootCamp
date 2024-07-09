#include <stdio.h>

int main() {
	int arr[5] = { 50, 40, 10, 50, 20 };
	int tmp;
	for (int i = 0; i < 4; ++i) {
		for (int j = i + 1; j < 5; ++j) {
			if (arr[i] > arr[j]) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
	for (int i = 1; i < 5; ++i) {
		
	}
	for (int i = 0; i < 5; ++i) {
		printf("%d ", arr[i]);
	}
}