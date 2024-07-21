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
	Abs(&min);
	Abs(&max);

	int  result = 0;
	while (min > 0) {
		if(min & 0b1)
			result = Add(result, max);
		min >>= 1;
		max <<= 1;
	}
	if ((rhs < 0 && lhs > 0) || (rhs > 0 && lhs < 0))
		result = ~result + 1; // -부호 붙이기
	return result;
}
int Div(int lhs, int rhs, int* remain) // 나눗셈이 여러번이라 나머지가 여러개인 경우: 나머지 합산
{
	int tmpLhs = lhs;
	int tmpRhs = rhs;
	
	Abs(&tmpLhs);
	Abs(&tmpRhs);

	if (rhs == 0)
		return 0;


	int result = 0;
	int tmp = 1;
	int rhsPrev = tmpRhs;
	while (tmpLhs >= (tmpRhs << 1)) {
		tmpRhs <<= 1;
		tmp <<= 1;
	}

	while (tmp > 0) {

		if (tmpLhs >= tmpRhs) {
			tmpLhs = Sub(tmpLhs, tmpRhs);
			result = Add(result, tmp);
		}
		tmpRhs >>= 1;
		tmp >>= 1;
	}
	// 부호가 다를 경우 result는 음수이다.
	if (lhs < 0 && rhs > 0 || lhs > 0 && rhs < 0) {
		result = Add(~result, 1);
	}

	// lhs rhs가 음수, 음수 or 음수, 양수일 경우 나머지를 양수로 반환하기 위해 특별한 처리가 필요함.
	if (tmpLhs != 0) {
		if (lhs < 0 && rhs > 0)
			result--;
		if (lhs < 0 && rhs < 0)
			result++;
	}
	*remain += Sub(lhs, Mul(result, rhs));



	return result;
}

void Abs(int* pNum)
{
	if (*pNum < 0)
		*pNum = ~Add(*pNum, -1);
}