#include <stdio.h>
#include <limits.h>


int GetMax(void);


int main() {
	int maxResult = GetMax();
	if (maxResult == 0) {
		printf("올바른 값을 입력하세요.\n");
	}
	printf("최댓값:%d", maxResult);

}

int GetMax(void) {
	int arr[3];
	for (int i = 0; i < 3; ++i) {
		if (1 != scanf_s("%d", &arr[i])) {
			return 0;
		}
	}

	int max = INT_MIN;
	for (int i = 0; i < 3; ++i) {
		if (max < arr[i])
			max = arr[i];
	}
	return max;
}