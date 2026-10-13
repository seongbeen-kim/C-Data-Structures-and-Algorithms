#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct DlistNode {
    element data;
    struct DlistNode *llink;
    struct DlistNode *rlink;
} DlistNode;

typedef struct {
    DlistNode *head;
    DlistNode *tail;
} DequeType;

void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init(DequeType *dq)
{
    dq->head = NULL;
    dq->tail = NULL;
}

int is_empty(DequeType *dq)
{
    return dq->head == NULL;
}

// 덱의 뒤쪽에 노드 삽입
void add_rear(DequeType *dq, element item)
{
    DlistNode *new_node = (DlistNode *)malloc(sizeof(DlistNode));
    if (new_node == NULL)
        error("Memory allocation failed");

    new_node->data = item;
    new_node->llink = dq->tail;
    new_node->rlink = NULL;

    if (is_empty(dq))
        dq->head = new_node;
    else
        dq->tail->rlink = new_node;

    dq->tail = new_node;
}

// 덱의 뒤쪽 노드를 삭제하고 값을 반환 (슬라이드 핵심 함수)
element delete_rear(DequeType *dq)
{
    element item;
    DlistNode *removed_node;

    if (is_empty(dq))
        error("Empty Deque");

    removed_node = dq->tail;
    item = removed_node->data;
    dq->tail = dq->tail->llink;
    free(removed_node);

    if (dq->tail == NULL)
        dq->head = NULL;
    else
        dq->tail->rlink = NULL;

    return item;
}

void print_deque(DequeType *dq)
{
    DlistNode *p = dq->head;
    printf("Deque: ");
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->rlink;
    }
    printf("\n");
}

int main(void)
{
    DequeType dq;
    init(&dq);

    add_rear(&dq, 10);
    add_rear(&dq, 20);
    add_rear(&dq, 30);
    print_deque(&dq);  // 10 20 30

    printf("delete_rear(): %d\n", delete_rear(&dq)); // 30
    print_deque(&dq);  // 10 20

    // 남아 있는 노드 정리
    while (!is_empty(&dq))
        delete_rear(&dq);

    return 0;
}
