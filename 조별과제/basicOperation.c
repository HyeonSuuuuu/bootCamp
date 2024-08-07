#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "basicOperation.h"





char* Add(char* lhs, char* rhs) // 처음 ~ 공백이 나올때 까지: 해당 포인터의 num값
 { // 버그 아직 못잡음
	char* pszResult = (char*)calloc(MAX_DIGIT_NUMBER,sizeof(char));
	int lenLhs = strlen(lhs);
	int lenRhs = strlen(rhs);
	if (lhs[lenLhs-1] == '+') // 부호처리
		lhs[lenLhs-- - 1] = '\0';
	if (rhs[lenRhs - 1] == '+')
		rhs[lenRhs-- - 1] = '\0';
	if (lhs[lenLhs - 1] == '-' && isdigit(rhs[lenRhs - 1])) {
		lhs[lenLhs - 1] = '\0';
		free(pszResult);
		return Sub(rhs, lhs);
	}
	if (rhs[lenRhs - 1] == '-' && isdigit(lhs[lenLhs - 1])) {
		lhs[lenRhs - 1] = '\0';
		free(pszResult);
		return Sub(lhs, rhs);
	}
	int maxLen = (lenLhs > lenRhs) ? lenLhs : lenRhs;
	char carry = 0;
	char tmp;
	int i;
	for (int i = 0; i < maxLen; ++i) {
		if (isdigit(lhs[i]) && isdigit(rhs[i])) {
			tmp = lhs[i] - '0' + rhs[i] + carry;
			carry = 0;
			if (!isdigit(tmp)) {
				tmp -= 10;
				carry = 1;
			}
			pszResult[i] = tmp;
		}
		else if (isdigit(lhs[i])) {
			pszResult[i] = lhs[i];
		}
		else if (isdigit(rhs[i])) {
			pszResult[i] = rhs[i];
		}
		else {
			if (lhs[i] == '-')
				pszResult[i] = '-';
			else
				break;
		}
	}

	ReverseString(pszResult);

	return pszResult;
}
char* Sub(char* lhs, char* rhs)
{  // 버그 아직 못잡음
	char* pszResult = (char*)calloc(MAX_DIGIT_NUMBER, sizeof(char));
	int lenLhs = strlen(lhs);
	int lenRhs = strlen(rhs);
	if (lhs[lenLhs - 1] == '+') // 부호처리
		lhs[lenLhs-- - 1] = '\0';
	if (rhs[lenRhs - 1] == '+')
		rhs[lenRhs-- - 1] = '\0';
	if (rhs[lenRhs - 1] == '-' && isdigit(lhs[lenLhs - 1])) {
		rhs[lenRhs - 1] = '\0';
		free(pszResult);
		return Add(lhs, rhs);
	}
	if (lhs[lenLhs - 1] == '-' && isdigit(rhs[lenRhs - 1])) {
		rhs[lenRhs - 1] = '-';
		free(pszResult);
		return Add(lhs, rhs);
	}
	char* pszTmp = NULL;
	if (lenLhs < lenRhs) { // lenRhs가 '-'로 인해 더 긴 경우도 생각해야함
		pszTmp = lhs;
		lhs = rhs;
		rhs = pszTmp;
	}
	// 만약 길이가 같은 경우에도 처리해야함
	char tmp;
	char carry = 0;
	for (int i = 0; i < lenLhs; ++i) {
		if (isdigit(lhs[i]) && isdigit(rhs[i])) {
			tmp = lhs[i] - rhs[i] - carry;
			carry = 0;
			if (tmp < 0) {
				carry = 1;
				tmp += 10;
			}
			tmp += '0';
			pszResult[i] = tmp;
		}
		else if (isdigit(lhs[i])) {
			if (carry == 1) {
				lhs[i] -= carry;
				carry = 0;
			}
			pszResult[i] = lhs[i];
		}
		else {
			if ((lhs[i] == '-' && pszTmp == NULL) || lhs[i] != '-' && pszTmp != NULL)
				pszResult[i] = '-';
			else
				break;
		}
	}

	ReverseString(pszResult);

	return pszResult;
}
char* Mul(char* lhs, const char* rhs)
{
	char* pszResult = (char*)calloc(MAX_DIGIT_NUMBER, sizeof(char));

	return pszResult;
}
char* Div(const char* lhs, const char* rhs, char* remain) // 나눗셈이 여러번이라 나머지가 여러개인 경우: 나머지 합산
{
	char* pszResult = (char*)calloc(MAX_DIGIT_NUMBER, sizeof(char));

	
	return pszResult;
}

void ReverseString(char* pszTarget)
{

	int lenTarget = 0;
	while (pszTarget[lenTarget] != '\0') {
		lenTarget++;
	}
	char tmp;
	for (int i = 0; i < lenTarget / 2; ++i) {
		tmp = pszTarget[i];
		pszTarget[i] = pszTarget[lenTarget - i - 1];
		pszTarget[lenTarget - i - 1] = tmp;
	}
}
