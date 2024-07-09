#include <stdio.h>

int main() {
	int arr[5] = { 3, 5, 1, 2, 4 };
	int idxMin, tmp;
	for (int i = 0; i < 4; ++i) {
		idxMin = i;
		for (int j = i + 1; j < 5; ++j) {
			if (arr[idxMin] > arr[j])
				idxMin = j;
		}
		if (i != idxMin) {
			tmp = arr[i];
			arr[i] = arr[idxMin];
			arr[idxMin] = tmp;
		}
	}
	for (int i = 0; i < 5; ++i) {
		printf("%d ", arr[i]);
	}
}