#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
	char szBuffer[12] = { "HelloWorld" };
	char* pszData = NULL;
	pszData = (char*)calloc(12, sizeof(char));
	if (pszData == NULL) {
		free(pszData);
		return 0;
	}
	strcpy_s(pszData, 12, szBuffer);

	printf("%s", pszData);
	free(pszData);

	return 0;
} 