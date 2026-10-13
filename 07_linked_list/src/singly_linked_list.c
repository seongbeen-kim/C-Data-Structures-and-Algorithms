// PDF 15~20쪽: 단일 연결 리스트
// 노드 생성, 삽입, 삭제, 방문(반복/재귀), 탐색, 합병, 역순
#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode *link; // 다음 노드의 주소
} ListNode;

ListNode *create_node(element data) {
    ListNode *node = malloc(sizeof(ListNode));
    if (node == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->link = NULL;
    return node;
}

// phead: head 변수의 주소, p: 삽입 위치의 선행 노드
// p == NULL이면 맨 앞에 삽입합니다.
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node) {
    if (*phead == NULL) {           // ① 공백 리스트
        new_node->link = NULL;
        *phead = new_node;
    } else if (p == NULL) {        // ② 맨 앞 삽입
        new_node->link = *phead;
        *phead = new_node;
    } else {                       // ③ p 다음에 삽입
        new_node->link = p->link;
        p->link = new_node;
    }
}

// p가 NULL이면 첫 노드를 삭제합니다.
// 제거할 노드(removed)는 반드시 해당 리스트에 속해야 합니다.
void remove_node(ListNode **phead, ListNode *p, ListNode *removed) {
    if (removed == NULL) return;
    if (p == NULL) {
        if (*phead != removed) return; // 잘못된 전달 방어
        *phead = (*phead)->link;
    } else {
        if (p->link != removed) return; // 잘못된 전달 방어
        p->link = removed->link;
    }
    free(removed);
}

void display(ListNode *head) {
    ListNode *p = head;
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->link;
    }
    printf("NULL\n");
}

void display_recur(ListNode *head) {
    if (head != NULL) {
        printf("%d -> ", head->data);
        display_recur(head->link);
    } else {
        printf("NULL\n");
    }
}

ListNode *search(ListNode *head, int x) {
    for (ListNode *p = head; p != NULL; p = p->link) {
        if (p->data == x) return p;
    }
    return NULL;
}

// 두 리스트를 이어 붙입니다. head2의 노드는 복사되지 않습니다!
// 반환된 리스트를 해제한 뒤 head2를 따로 해제하면 이중 해제가 됩니다.
ListNode *concat(ListNode *head1, ListNode *head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    ListNode *p = head1;
    while (p->link != NULL) p = p->link;
    p->link = head2;
    return head1;
}

// PDF 20쪽의 p, q, r 사용 방식을 그대로 따릅니다.
ListNode *reverse(ListNode *head) {
    ListNode *p = head; // 아직 뒤집지 않은 부분의 현재 노드
    ListNode *q = NULL; // 이번에 링크를 뒤집을 노드
    ListNode *r = NULL; // 이미 뒤집은 부분의 첫 노드

    while (p != NULL) {
        r = q;
        q = p;
        p = p->link; // 다음 노드의 주소를 먼저 보관
        q->link = r; // 링크 방향을 반대로 변경
    }
    return q; // 새 첫 노드
}

void destroy_list(ListNode *head) {
    while (head != NULL) {
        ListNode *next = head->link;
        free(head);
        head = next;
    }
}

int main(void) {
    ListNode *head1 = NULL;
    ListNode *head2 = NULL;

    insert_node(&head1, NULL, create_node(10));
    insert_node(&head1, head1, create_node(30));
    insert_node(&head1, head1, create_node(20));
    insert_node(&head1, NULL, create_node(5));

    printf("삽입 후: ");
    display(head1); // 5 -> 10 -> 20 -> 30 -> NULL
    printf("재귀 출력: ");
    display_recur(head1);

    ListNode *found = search(head1, 20);
    printf("20 탐색: %s\n", found ? "찾음" : "없음");

    // 10 다음의 20을 삭제
    ListNode *before = head1->link;
    remove_node(&head1, before, before->link);
    printf("20 삭제 후: ");
    display(head1);

    head1 = reverse(head1);
    printf("역순 결과: ");
    display(head1);

    insert_node(&head2, NULL, create_node(40));
    insert_node(&head2, head2, create_node(50));
    head1 = concat(head1, head2);
    head2 = NULL; // 소유권을 head1로 넘겼으므로 별도 해제 X
    printf("두 리스트 합병: ");
    display(head1);

    destroy_list(head1);
    return 0;
}

