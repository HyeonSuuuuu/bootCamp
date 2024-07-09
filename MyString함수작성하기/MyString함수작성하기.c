#include <stdio.h>

int MyStrcpy(char*, size_t, char*);

int main(int argc, char* argv[]) {
	char szBufferSrc[12] = { "TestString" };
	char szBufferDst[12] = { 0 };

	int cpyResult = MyStrcpy(szBufferDst, sizeof(szBufferDst), szBufferSrc);
	if (cpyResult == 0) {
		return 0;
	}
	puts(szBufferDst);
	return 0;
}

int MyStrcpy(char* dst, size_t size, char* src) {
	size_t lenSrc = 0;
	lenSrc = strlen(src);
	if (lenSrc + 1 > size) {
		return 0;
	}

	for (int i = 0; i < size; ++i) {
		dst[i] = src[i];
	}
}
