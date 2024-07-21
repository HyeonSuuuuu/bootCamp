#pragma once




int Priority(char operator);
int CheckBracket(const char* const infix);
int InfixToPostfix(const char* const infix, char* const postfix);
int CalculatePostfix(const char* postfix, int* remain);