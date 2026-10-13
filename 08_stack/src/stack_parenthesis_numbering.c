

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef int element;

// 스택 구조체
typedef struct {
    element data[MAX];
    int top;
} StackType;

// 스택 초기화
void init(StackType* s)
{
    s->top = -1;
}

// 스택 공백 검사
int is_empty(StackType* s)
{
    return s->top == -1;
}

// 스택 포화 검사
int is_full(StackType* s)
{
    return s->top == MAX - 1;
}

// 스택 삽입
void push(StackType* s, element item)
{
    if (is_full(s)) {
        printf("스택 포화 에러\n");
        exit(1);
    }

    s->data[++(s->top)] = item;
}

// 스택 삭제
element pop(StackType* s)
{
    if (is_empty(s)) {
        printf("스택 공백 에러\n");
        exit(1);
    }

    return s->data[(s->top)--];
}

// 메인 함수
int main(void)
{
    char exp[MAX];
    StackType s;
    int count = 0;

    init(&s);

    printf("수식 입력: ");
    scanf("%99s", exp);

    printf("괄호수 : ");

    for (int i = 0; i < strlen(exp); i++) {

        // 왼쪽 괄호를 만나면
        if (exp[i] == '(') {
            count++;
            push(&s, count);
            printf("%d ", count);
        }

        // 오른쪽 괄호를 만나면
        else if (exp[i] == ')') {
            printf("%d ", pop(&s));
        }
    }

    printf("\n");

    return 0;
}
