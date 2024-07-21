1. 개요
비트연산자를 이용한 계산기를 구현하였습니다.

2. 설계 원칙
테스트 가능성: 각 모듈을 독립적으로 테스트 할 수 있도록 설계했습니다.
모듈화: 기능별로 모듈을 분리해 코드의 가독성과 유지보수성을 높였습니다.

3. 구조
basicOperation.c/h
역할: 사칙연산을 수행하는 함수들을 비트연산자를 사용하여 구현하였습니다.
주요 함수: Add, Sub, Mul, Div

calculation.c/h
역할: 사용자가 입력한 식을 후위표기법으로 바꾼 후 식을 계산합니다.
주요 함수: InfixToPostfix, CalculatePostfix

stack.c
역할: 후위 표기법에 쓰일 스택 자료구조를 구현합니다.
주요 함수: StackPush, StackPop, StackPeek

test.c
역할: 각 모듈의 기능을 테스트합니다.
주요 함수: StackTest01, CalculateTest01

ui.c
역할: 사용자와 상호작용을 처리합니다.
주요 함수: EventLoopRun, Calculator

파일 구조
/project
│
├── src
│   ├── basicOperation.c
│   ├── calculation.c
│   ├── stack.c
│   ├── test.c
│   └── ui.c
│
├── include
│   ├── basicOperation.h
│   ├── calculation.h
│   ├── stack.h
│   ├── test.h
│   └── ui.h
│  ReadMe.txt

모듈 상세 설명
basicOperation.c/h
int Add(int lhs, int rhs): 두 정수의 합을 반환합니다. 두 수를 xor 연산을 하여 합계를 구하고 carry는 두 수의 and 연산을 왼쪽으로 1번 shift 하여 다시 xor 연산을 반복합니다. 이 연산은 carry가 0이 될때까지 반복됩니다.

int Sub(int lhs, int rhs): 두 정수의 차를 반환합니다. rhs를 2의 보수로 만든 후 Add함수를 이용해 더하였습니다.

int Mul(int lhs, int rhs): 두 정수의 곱을 반환합니다. 두 인자중 작은 값을 right shift 하면서 최하위비트가 1인 경우에 max * right shift 한만큼 곱해 result에 더하였고 부호는 절대값으로 처리한 후 끝나고 두 인자의 부호가 다르다면 2의 보수로 바꾸었습니다.

int Div(int lhs, int rhs, int* remain): 두 정수의 몫을 반환하고 포인터로 전달받은 remain 인자로 나머지를 반환합니다. 곱과 마찬가지로 절대값으로 처리한 후 두 인자의 부호에 따라 몫과 나머지가 결정되도록 구현하였고 나머지는 양수로 나옵니다.

calculation.c/h
InfixToPostfix(const char* const infix, char* const postfix): 중위표기법을 후위표기법으로 바꾸는 작업을 합니다. 두자리 이상의 숫자도 인식할 수 있도록 숫자 사이에 공백을 두어 구분하였고 단항 연산자도 구분하기 위해 앞에 공백을 두었습니다.
CalculatePostfix(const char* postfix, int* remain): 후위표기법을 계산합니다. 연산은 basicOperation.c/h 함수를 사용하였습니다.

stack.c/h 
int형을 담을 수 있는 스택입니다.  STACK_MAX라는 매크로 변수를 가지고 있고 default는 256입니다.

test.c/h
구현한 모듈이 잘 작동하는지 테스트하기 위한 모듈입니다.

ui.c/h
사용자와 상호작용을 처리합니다.
