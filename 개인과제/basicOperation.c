#include <stdio.h>
#include "basicOperation.h"



void printDecimalToBinary(int d)
{
	for (int i = 7; i >= 0; --i) {
		int result = d >> i & 1;
		printf("%d", result);
	}
	printf("\n");
}

int Add(int lhs, int rhs)
 {
	int sum = lhs ^ rhs;
	int carry = (lhs & rhs) << 1;
	int tmp = 0;
	while (carry != 0) {
		tmp = sum;
		sum = sum ^ carry;
		carry = (tmp & carry) << 1;
	}
	return sum;
}
int Sub(int lhs, int rhs)
{ 
	return Add(lhs, ~rhs + 1);
}
int Mul(int lhs, int rhs)
{
	int min = (lhs < rhs) ? lhs : rhs;
	int max = (lhs > rhs) ? lhs : rhs;
	int  result = 0;
	while (min > 0) {
		if(min & 0b1)
			result = Add(result, max);
		min >>= 1;
		max <<= 1;
	}
	return result;
}
int Div(int lhs, int rhs, int* remain) // 나눗셈이 여러번이라 나머지가 여러개인 경우: 나머지 합산
{
	if (rhs == 0)
		return 0;



	int result = 0;
	int tmp = 1;
	int rhsPrev = rhs;
	while (lhs >= (rhs << 1)) {
		rhs <<= 1;
		tmp <<= 1;
	}

	while (tmp > 0) {

		if (lhs >= rhs) {
			lhs = Sub(lhs, rhs);
			result = Add(result, tmp);
		}
		rhs >>= 1;
		tmp >>= 1;
	}
	*remain += Add(*remain, lhs);
	return result;
	
}