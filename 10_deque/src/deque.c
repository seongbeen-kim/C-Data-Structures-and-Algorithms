#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 교안 9~12쪽: 이중 연결 리스트 기반 덱(Deque)
// 16쪽 Review: delete_rear() 직접 구현
// dequeue(큐 삭제 함수)와 deque(양방향 큐)는 서로 다르다.
typedef int element;

typedef struct DlistNode {
    element data;
    struct DlistNode *llink;
    struct DlistNode *rlink;
} DlistNode;

typedef struct {
    DlistNode *head; // front
    DlistNode *tail; // rear
} DequeType;

void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

DlistNode *create_node(DlistNode *left, element item, DlistNode *right)
{
    DlistNode *node = malloc(sizeof(*node));
    if (node == NULL) {
        error("메모리 할당 실패");
    }
    node->data = item;
    node->llink = left;
    node->rlink = right;
    return node;
}

void init(DequeType *dq)
{
    dq->head = NULL;
    dq->tail = NULL;
}

int is_empty(const DequeType *dq)
{
    return dq->head == NULL;
}

void add_front(DequeType *dq, element item)
{
    DlistNode *node = create_node(NULL, item, dq->head);
    if (is_empty(dq)) {
        dq->tail = node; // 처음 삽입되는 노드
    } else {
        dq->head->llink = node;
    }
    dq->head = node;
}

void add_rear(DequeType *dq, element item)
{
    DlistNode *node = create_node(dq->tail, item, NULL);
    if (is_empty(dq)) {
        dq->head = node;
    } else {
        dq->tail->rlink = node;
    }
    dq->tail = node;
}

element delete_front(DequeType *dq)
{
    if (is_empty(dq)) {
        error("덱이 공백 상태입니다.");
    }

    DlistNode *removed = dq->head;
    element item = removed->data;
    dq->head = removed->rlink;

    if (dq->head == NULL) {
        dq->tail = NULL; // 마지막 노드까지 삭제
    } else {
        dq->head->llink = NULL;
    }
    free(removed);
    return item;
}

element delete_rear(DequeType *dq)
{
    if (is_empty(dq)) {
        error("덱이 공백 상태입니다.");
    }

    DlistNode *removed = dq->tail;
    element item = removed->data;
    dq->tail = removed->llink;

    if (dq->tail == NULL) {
        dq->head = NULL; // 마지막 노드까지 삭제
    } else {
        dq->tail->rlink = NULL;
    }
    free(removed);
    return item;
}

element get_front(const DequeType *dq)
{
    if (is_empty(dq)) {
        error("덱이 공백 상태입니다.");
    }
    return dq->head->data;
}

element get_rear(const DequeType *dq)
{
    if (is_empty(dq)) {
        error("덱이 공백 상태입니다.");
    }
    return dq->tail->data;
}

void print_deque(const DequeType *dq)
{
    const DlistNode *p = dq->head;
    printf("front [ ");
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->rlink;
    }
    printf("] rear\n");
}

void destroy(DequeType *dq)
{
    while (!is_empty(dq)) {
        (void)delete_front(dq);
    }
}

int main(void)
{
    DequeType dq;
    init(&dq);

    add_front(&dq, 10); // A
    add_rear(&dq, 20);  // B
    add_front(&dq, 30); // C
    add_rear(&dq, 40);  // D
    print_deque(&dq);  // [30, 10, 20, 40]

    printf("delete_front: %d\n", delete_front(&dq)); // 30
    printf("delete_rear: %d\n", delete_rear(&dq));   // 40
    print_deque(&dq);
    printf("get_front: %d, get_rear: %d\n", get_front(&dq), get_rear(&dq));

    destroy(&dq);
    return 0;
}