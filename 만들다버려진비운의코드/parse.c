#include <stdlib.h>
#include <string.h>
#include "parse.h"
// parse >> calculation으로 대체 (후위표기법으로 처리하면 연산자 처리가 더 편리함)

void parseExpression(const char* szBuffer, int* operand, char* operator) {
	const char* pszSep = "+-*/";
	char* pszToken = NULL;
	char* pszNextToken = NULL;

	// operator 찾기
	int cntOperator = 0;
	const char* pszBuffer = szBuffer;
	size_t result = 0;
	while ((result = strcspn(pszBuffer, pszSep)) != strlen(pszBuffer)) {
		operator[cntOperator++] = pszBuffer[result];
		pszBuffer = pszBuffer + result + 1;
	}

	// operand 찾기

	pszToken = strtok_s(szBuffer, pszSep, &pszNextToken);
	int cntOperand = 0;
	while (pszToken != NULL) {
		operand[cntOperand++] = atoi(pszToken);
		pszToken = strtok_s(NULL, pszSep, &pszNextToken);
	}

	for (int i = 0; i < cntOperand; ++i) {
		printf("%d ", operand[i]);
	}
}