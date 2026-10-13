
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

// 스택 구조체
typedef struct {
    char data[MAX];
    int top;
} StackType;

// 스택 초기화
void init(StackType* s)
{
    s->top = -1;
}

// 스택이 비어 있는지 확인
int is_empty(StackType* s)
{
    return s->top == -1;
}

// 스택이 가득 찼는지 확인
int is_full(StackType* s)
{
    return s->top == MAX - 1;
}

// 스택에 문자 삽입
void push(StackType* s, char item)
{
    if (is_full(s)) {
        printf("Stack overflow!\n");
        exit(1);
    }

    s->data[++s->top] = item;
}

// 스택에서 문자 삭제 및 반환
char pop(StackType* s)
{
    if (is_empty(s)) {
        printf("Stack underflow!\n");
        exit(1);
    }

    return s->data[s->top--];
}

// 스택의 맨 위 문자 확인
char peek(StackType* s)
{
    if (is_empty(s)) {
        printf("Stack is empty!\n");
        exit(1);
    }

    return s->data[s->top];
}

// 메인 함수
int main(void)
{
    char str[MAX];
    StackType s;
    int count = 0;

    init(&s);

    printf("Input String: ");
    if (scanf("%99s", str) != 1) {
        return 1;
    }

    // 문자열을 순서대로 검사
    for (int i = 0; str[i] != '\0'; i++) {
        char ch = (char)tolower((unsigned char)str[i]);

        // 스택이 비었거나 같은 문자이면 삽입
        if (is_empty(&s) || peek(&s) == ch) {
            push(&s, ch);
        }
        else {
            // 다른 문자가 나오면 기존 문자 개수 계산
            count = 0;

            while (!is_empty(&s)) {
                pop(&s);
                count++;
            }

            // 압축 결과 출력
            printf("%d%c", count,
                (char)tolower((unsigned char)str[i - 1]));

            // 새로운 문자 삽입
            push(&s, ch);
        }
    }

    // 스택에 남아 있는 마지막 문자 처리
    count = 0;

    while (!is_empty(&s)) {
        char ch = pop(&s);
        count++;

        if (is_empty(&s)) {
            printf("%d%c", count, ch);
        }
    }

    printf("\n");

    return 0;
}
