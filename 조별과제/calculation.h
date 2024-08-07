#pragma once



void RemoveSpace(char* pszInput);
int Priority(char operator);
int CheckBracket(const char* const infix);
int InfixToPostfix(const char* const infix, char* const postfix);
char* CalculatePostfix(char* postfix, char* remain);
void ReverseStringWithEndSpace(char* pszTarget);