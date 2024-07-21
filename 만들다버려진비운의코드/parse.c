#include <stdlib.h>
#include <string.h>
#include "parse.h"
// parse >> calculation���� ��ü (����ǥ������� ó���ϸ� ������ ó���� �� ����)

void parseExpression(const char* szBuffer, int* operand, char* operator) {
	const char* pszSep = "+-*/";
	char* pszToken = NULL;
	char* pszNextToken = NULL;

	// operator ã��
	int cntOperator = 0;
	const char* pszBuffer = szBuffer;
	size_t result = 0;
	while ((result = strcspn(pszBuffer, pszSep)) != strlen(pszBuffer)) {
		operator[cntOperator++] = pszBuffer[result];
		pszBuffer = pszBuffer + result + 1;
	}

	// operand ã��

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