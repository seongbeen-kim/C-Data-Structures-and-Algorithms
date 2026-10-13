// PDF 26~27쪽: 연결 리스트로 다항식 덧셈
// PPT/PDF에는 노드 구조와 덧셈 알고리즘(세 가지 비교 경우)이 설명되어 있고,
// 아래 함수들은 그 알고리즘을 실제 실행 가능하도록 작성한 추가 구현입니다.
// 각 리스트의 지수(expon)는 큰 순서대로 정렬되어 있어야 합니다.
#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode {
    int coef;               // 계수
    int expon;              // 지수
    struct PolyNode *link;  // 다음 항
} PolyNode;

PolyNode *create_term(int coef, int expon) {
    PolyNode *node = malloc(sizeof(PolyNode));
    if (node == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->coef = coef;
    node->expon = expon;
    node->link = NULL;
    return node;
}

// 지수가 내림차순이라고 가정하고 맨 끝에 항을 붙입니다.
// head: 첫 노드, tail: 마지막 노드
void append_term(PolyNode **head, PolyNode **tail, int coef, int expon) {
    if (coef == 0) return; // 계수가 0이면 항을 만들지 않음
    PolyNode *node = create_term(coef, expon);
    if (*head == NULL) *head = node;
    else (*tail)->link = node;
    *tail = node;
}

// PDF 26쪽에 나온 경우 ①~③을 구현합니다.
PolyNode *poly_add(const PolyNode *A, const PolyNode *B) {
    const PolyNode *p = A;
    const PolyNode *q = B;
    PolyNode *C = NULL;
    PolyNode *tail = NULL;

    while (p != NULL && q != NULL) {
        if (p->expon == q->expon) {            // ① 지수가 같으면 계수를 더함
            append_term(&C, &tail, p->coef + q->coef, p->expon);
            p = p->link;
            q = q->link;
        } else if (p->expon < q->expon) {      // ② q의 지수가 크면 q만 이동
            append_term(&C, &tail, q->coef, q->expon);
            q = q->link;
        } else {                              // ③ p의 지수가 크면 p만 이동
            append_term(&C, &tail, p->coef, p->expon);
            p = p->link;
        }
    }

    // PDF 27쪽: 한쪽이 NULL이면 다른 쪽에 남은 항을 모두 복사
    while (p != NULL) {
        append_term(&C, &tail, p->coef, p->expon);
        p = p->link;
    }
    while (q != NULL) {
        append_term(&C, &tail, q->coef, q->expon);
        q = q->link;
    }
    return C;
}

void print_poly(const char *name, const PolyNode *head) {
    printf("%s = ", name);
    if (head == NULL) {
        printf("0\n");
        return;
    }
    int first = 1;
    for (const PolyNode *p = head; p != NULL; p = p->link) {
        long long coef = p->coef;
        if (first) {
            if (coef < 0) printf("-");
            first = 0;
        } else {
            printf(coef < 0 ? " - " : " + ");
        }
        long long magnitude = coef < 0 ? -coef : coef;
        if (p->expon == 0) printf("%lld", magnitude);
        else if (p->expon == 1) printf("%lldx", magnitude);
        else printf("%lldx^%d", magnitude, p->expon);
    }
    printf("\n");
}

void destroy_poly(PolyNode *head) {
    while (head != NULL) {
        PolyNode *next = head->link;
        free(head);
        head = next;
    }
}

int main(void) {
    PolyNode *A = NULL, *B = NULL;
    PolyNode *tailA = NULL, *tailB = NULL;

    // PDF 예시 A = 3x^12 + 2x^8 + 1
    append_term(&A, &tailA, 3, 12);
    append_term(&A, &tailA, 2, 8);
    append_term(&A, &tailA, 1, 0);

    // PDF 예시 B = 8x^12 - 3x^10 + 10x^6
    append_term(&B, &tailB, 8, 12);
    append_term(&B, &tailB, -3, 10);
    append_term(&B, &tailB, 10, 6);

    PolyNode *C = poly_add(A, B);
    print_poly("A", A);
    print_poly("B", B);
    print_poly("A+B", C); // 11x^12 - 3x^10 + 2x^8 + 10x^6 + 1

    destroy_poly(A);
    destroy_poly(B);
    destroy_poly(C);
    return 0;
}