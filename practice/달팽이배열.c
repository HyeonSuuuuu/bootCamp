#include <stdio.h>

int main() {
	int arr[5][5] = { 0 };
	int cnt = 1;
	int x = -1, y = 0;
	int dir = 1;
	int len = 9;

	for (int len = 9; len > 0; len -= 2) {
		int center = len%2 ? len / 2+1 : len / 2;
		for (int i = 0; i < len; ++i) {
			if (i < center)
				x += dir;
			else
				y += dir; 
			arr[y][x] = cnt++;
		}
		dir *= -1;
	}


	for (int i = 0; i < 5; ++i){
		for (int j = 0; j < 5; ++j) {
			printf("%2d ", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}