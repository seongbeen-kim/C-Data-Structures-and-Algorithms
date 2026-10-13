/*

// 배열 기반 스택 구현

#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef int element;

// 스택 구조체
typedef struct {
    element stack[MAX_STACK_SIZE];
    int top;
} StackType;

// 스택 초기화
void init(StackType *s) {
    s->top = -1;
}

// 공백 상태 검사
int is_empty(StackType *s) {
    return (s->top == -1);
}

// 포화 상태 검사
int is_full(StackType *s) {
    return (s->top == MAX_STACK_SIZE - 1);
}

// 삽입 함수
void push(StackType *s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else {
        s->stack[++(s->top)] = item;
    }
}

// 삭제 함수
element pop(StackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else {
        return s->stack[(s->top)--];
    }
}
*/

/*

// 연결 리스트 기반 스택 구현

#include <stdio.h>
#include <stdlib.h>

typedef int element;

// 1. 노드 구조체
typedef struct StackNode {
    element item;
    struct StackNode *link;
} StackNode;

// 2. 스택 구조체
typedef struct {
    StackNode *top;
} LinkedStackType;

// 3. 스택 초기화
void init(LinkedStackType *s) {
    s->top = NULL;
}

// 4. 공백 상태 검사
int is_empty(LinkedStackType *s) {
    return (s->top == NULL);
}

// 5. 삽입 함수
void push(LinkedStackType *s, element item) {
    StackNode *temp =
        (StackNode *)malloc(sizeof(StackNode));

    if (temp == NULL) {
        fprintf(stderr, "메모리 할당 에러\n");
        return;
    }
    else {
        temp->item = item;
        temp->link = s->top;
        s->top = temp;
    }
}

// 6. 삭제 함수
element pop(LinkedStackType *s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택이 비어있음\n");
        exit(1);
    }
    else {
        StackNode *temp = s->top;
        element item = temp->item;

        s->top = s->top->link;

        free(temp);
        return item;
    }
}

// 7. 메인 함수
int main(void) {
    LinkedStackType s;
    init(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("pop: %d\n", pop(&s));
    printf("pop: %d\n", pop(&s));
    printf("pop: %d\n", pop(&s));

    return 0;
}
*/

