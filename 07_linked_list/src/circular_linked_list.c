// PDF 21~22쪽: 단일 원형 연결 리스트
// 중요: 이 예제에서 head 포인터는 '첫 노드'가 아니라 '마지막 노드'를 가리킵니다.
// 마지막 노드(head)->link == 첫 번째 노드
#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int data;
    struct ListNode *link;
} ListNode;

ListNode *create_node(int data) {
    ListNode *node = malloc(sizeof(ListNode));
    if (node == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->link = NULL;
    return node;
}

// 처음에 삽입: tail(head) 포인터는 변경하지 않습니다(공백 리스트는 예외).
void insert_first(ListNode **phead, ListNode *node) {
    if (*phead == NULL) {
        *phead = node;
        node->link = node;
    } else {
        node->link = (*phead)->link; // 새 노드 -> 기존 첫 노드
        (*phead)->link = node;       // 기존 마지막 -> 새 첫 노드
    }
}

// 끝에 삽입: 연결 후 tail(head)를 새 노드로 바꿉니다.
void insert_last(ListNode **phead, ListNode *node) {
    if (*phead == NULL) {
        *phead = node;
        node->link = node;
    } else {
        node->link = (*phead)->link; // 새 노드 -> 기존 첫 노드
        (*phead)->link = node;       // 기존 마지막 -> 새 노드
        *phead = node;              // 새 노드가 마지막 노드!
    }
}

// 추가 실습(PDF 22쪽에는 삽입만 제시): 첫 노드 삭제
// 삭제할 노드가 없으면 0, 삭제에 성공하면 1 반환
int remove_first(ListNode **phead) {
    if (*phead == NULL) return 0;

    ListNode *first = (*phead)->link;
    if (first == *phead) { // 노드가 하나뿐인 경우
        *phead = NULL;
    } else {
        (*phead)->link = first->link; // 마지막 -> 새로운 첫 노드
    }
    free(first);
    return 1;
}

// 추가 실습: 마지막 노드 삭제
// 단일 원형 리스트라 이전 노드를 찾기 위해 순회: O(n)
int remove_last(ListNode **phead) {
    if (*phead == NULL) return 0;

    ListNode *last = *phead;
    if (last->link == last) { // 노드가 하나뿐인 경우
        *phead = NULL;
    } else {
        ListNode *prev = last->link; // 첫 노드부터 출발
        while (prev->link != last) prev = prev->link;
        prev->link = last->link;
        *phead = prev; // 마지막 노드를 앞 노드로 변경
    }
    free(last);
    return 1;
}

// 추가 실습: 원형 리스트에서는 NULL이 아니라 시작 노드로 돌아오는지 확인
ListNode *search(ListNode *head, int target) {
    if (head == NULL) return NULL;
    ListNode *p = head->link;
    do {
        if (p->data == target) return p;
        p = p->link;
    } while (p != head->link);
    return NULL;
}

void display(ListNode *head) {
    if (head == NULL) {
        printf("(빈 원형 리스트)\n");
        return;
    }
    ListNode *first = head->link;
    ListNode *p = first;
    do {
        printf("%d", p->data);
        p = p->link;
        if (p != first) printf(" -> ");
    } while (p != first);
    printf(" -> (첫 노드로 돌아감)\n");
}

// 모든 노드의 순환 연결을 끊고 안전하게 해제합니다.
void destroy_list(ListNode **phead) {
    if (*phead == NULL) return;
    ListNode *p = (*phead)->link;
    (*phead)->link = NULL; // 고리를 끊으면 일반 단일 리스트처럼 해제 가능
    while (p != NULL) {
        ListNode *next = p->link;
        free(p);
        p = next;
    }
    *phead = NULL;
}

int main(void) {
    ListNode *head = NULL; // 실제 의미는 마지막 노드를 가리키는 tail

    insert_first(&head, create_node(20));
    insert_first(&head, create_node(10));
    printf("처음에 20, 10 삽입: ");
    display(head); // 10 -> 20
    printf("현재 마지막 노드(head)의 데이터: %d\n", head->data);

    insert_last(&head, create_node(30));
    insert_last(&head, create_node(40));
    printf("끝에 30, 40 삽입: ");
    display(head); // 10 -> 20 -> 30 -> 40
    printf("마지막 노드: %d, 첫 노드: %d\n", head->data, head->link->data);
    printf("30 탐색: %s\n", search(head, 30) ? "찾음" : "없음");

    remove_first(&head);
    printf("처음 삭제 후: ");
    display(head); // 20 -> 30 -> 40

    remove_last(&head);
    printf("끝 삭제 후: ");
    display(head); // 20 -> 30

    destroy_list(&head);
    return 0;
}
