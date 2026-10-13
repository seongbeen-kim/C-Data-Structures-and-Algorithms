
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100

typedef int element;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

// 스택 초기화
void init(StackType* s)
{
    s->top = -1;
}

// 스택 삽입
void push(StackType* s, element item)
{
    if (s->top == MAX_STACK_SIZE - 1) {
        printf("스택 포화 에러\n");
        exit(1);
    }
    s->data[++(s->top)] = item;
}

// 스택 삭제
element pop(StackType* s)
{
    if (s->top == -1) {
        printf("스택 공백 에러\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

// 후위 표기식 계산 함수
int eval(char exp[])
{
    int op1, op2, value;
    int len = strlen(exp);
    char ch;
    StackType s;

    init(&s);

    for (int i = 0; i < len; i++) {
        ch = exp[i];

        // 피연산자이면 스택에 삽입
        if (ch >= '0' && ch <= '9') {
            value = ch - '0';
            push(&s, value);
        }
        // 연산자이면 계산
        else {
            op2 = pop(&s);
            op1 = pop(&s);

            switch (ch) {
            case '+':
                push(&s, op1 + op2);
                break;
            case '-':
                push(&s, op1 - op2);
                break;
            case '*':
                push(&s, op1 * op2);
                break;
            case '/':
                if (op2 == 0) {
                    printf("0으로 나눌 수 없습니다.\n");
                    exit(1);
                }
                push(&s, op1 / op2);
                break;
            default:
                printf("잘못된 연산자입니다.\n");
                exit(1);
            }
        }
    }
    return pop(&s);
}

int main(void)
{
    char exp[MAX_STACK_SIZE];

    printf("후위 표기식을 입력하세요: ");
    scanf("%99s", exp);

    printf("계산 결과 = %d\n", eval(exp));

    return 0;
}
