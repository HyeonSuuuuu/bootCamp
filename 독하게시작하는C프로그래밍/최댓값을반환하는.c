#include <stdio.h>
#include <limits.h>


int GetMax(void);


int main() {
	int maxResult = GetMax();
	if (maxResult == 0) {
		printf("�ùٸ� ���� �Է��ϼ���.\n");
	}
	printf("�ִ�:%d", maxResult);

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