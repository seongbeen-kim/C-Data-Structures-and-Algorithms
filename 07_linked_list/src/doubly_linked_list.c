// PDF 23~25쪽: 헤드 노드(sentinel)를 가진 원형 이중 연결 리스트
// head_node는 실제 데이터를 보관하지 않는 '더미 노드'입니다.
// llink: 이전 노드, rlink: 다음 노드
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct DlistNode {
    element data;
    struct DlistNode *llink;
    struct DlistNode *rlink;
} DlistNode;

// 공백 상태: head_node <-> head_node (양방향 자기 자신)
void init(DlistNode *phead_node) {
    phead_node->llink = phead_node;
    phead_node->rlink = phead_node;
}

DlistNode *create_node(element data) {
    DlistNode *node = malloc(sizeof(DlistNode));
    if (node == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->llink = NULL;
    node->rlink = NULL;
    return node;
}

// PDF 25쪽 삽입 코드: before의 오른쪽에 new_node 삽입
void dinsert_node(DlistNode *before, DlistNode *new_node) {
    new_node->llink = before;                 // ① 새 노드의 이전 = before
    new_node->rlink = before->rlink;          // ② 새 노드의 다음 = 기존 다음 노드
    before->rlink->llink = new_node;          // ③ 기존 다음 노드의 이전 = 새 노드
    before->rlink = new_node;                 // ④ before의 다음 = 새 노드
}

// PDF 25쪽 삭제 코드: 헤드 노드 자체는 삭제하지 않습니다.
void dremove_node(DlistNode *phead_node, DlistNode *removed) {
    if (removed == phead_node) return;
    removed->llink->rlink = removed->rlink;   // 이전 노드 -> 다음 노드
    removed->rlink->llink = removed->llink;   // 다음 노드 -> 이전 노드
    free(removed);
}

void display_forward(const DlistNode *phead_node) {
    printf("정방향: HEAD <-> ");
    for (const DlistNode *p = phead_node->rlink; p != phead_node; p = p->rlink)
        printf("%d <-> ", p->data);
    printf("HEAD\n");
}

void display_backward(const DlistNode *phead_node) {
    printf("역방향: HEAD <-> ");
    for (const DlistNode *p = phead_node->llink; p != phead_node; p = p->llink)
        printf("%d <-> ", p->data);
    printf("HEAD\n");
}

// 추가 실습: 원하는 데이터를 가진 노드를 정방향으로 탐색
DlistNode *dsearch(DlistNode *phead_node, element target) {
    for (DlistNode *p = phead_node->rlink; p != phead_node; p = p->rlink) {
        if (p->data == target) return p;
    }
    return NULL;
}

void clear(DlistNode *phead_node) {
    while (phead_node->rlink != phead_node)
        dremove_node(phead_node, phead_node->rlink);
}

int main(void) {
    DlistNode head_node;
    init(&head_node);

    DlistNode *n10 = create_node(10);
    DlistNode *n20 = create_node(20);
    DlistNode *n30 = create_node(30);

    dinsert_node(&head_node, n10);
    dinsert_node(n10, n20);
    dinsert_node(n20, n30);
    display_forward(&head_node);   // 10, 20, 30

    dinsert_node(n10, create_node(15));
    printf("10 뒤에 15 삽입\n");
    display_forward(&head_node);   // 10, 15, 20, 30
    display_backward(&head_node);  // 30, 20, 15, 10

    dremove_node(&head_node, n20);
    printf("20 삭제 후\n");
    display_forward(&head_node);   // 10, 15, 30
    display_backward(&head_node);  // 30, 15, 10
    printf("15 탐색: %s\n", dsearch(&head_node, 15) ? "찾음" : "없음");

    clear(&head_node);
    return 0;
}