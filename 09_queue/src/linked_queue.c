#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 교안 8쪽 / 16쪽 Review: 연결 리스트 기반 큐의 삽입 및 삭제
// front는 맨 앞 노드, rear는 맨 뒤 노드를 가리킨다.
typedef int element;

typedef struct QueueNode {
    element data;
    struct QueueNode *link;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
} LinkedQueueType;

void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

void init(LinkedQueueType *q)
{
    q->front = NULL;
    q->rear = NULL;
}

int is_empty(const LinkedQueueType *q)
{
    return q->front == NULL;
}

void enqueue(LinkedQueueType *q, element item)
{
    QueueNode *temp = malloc(sizeof(*temp));
    if (temp == NULL) {
        error("메모리 할당 실패");
    }

    temp->data = item;
    temp->link = NULL;

    if (is_empty(q)) {
        q->front = temp; // 첫 번째 노드는 front와 rear가 모두 가리킨다.
    } else {
        q->rear->link = temp; // 기존 마지막 노드 뒤에 연결
    }
    q->rear = temp; // 새로운 마지막 노드로 rear 이동
}

element dequeue(LinkedQueueType *q)
{
    if (is_empty(q)) {
        error("큐가 공백 상태입니다.");
    }

    QueueNode *temp = q->front;
    element item = temp->data;

    q->front = temp->link; // 다음 노드를 새 front로 설정
    if (q->front == NULL) {
        q->rear = NULL; // 마지막 노드를 삭제했으면 rear도 NULL
    }

    free(temp);
    return item;
}

element peek(const LinkedQueueType *q)
{
    if (is_empty(q)) {
        error("큐가 공백 상태입니다.");
    }
    return q->front->data;
}

void print_queue(const LinkedQueueType *q)
{
    const QueueNode *p = q->front;
    printf("front -> ");
    while (p != NULL) {
        printf("%d -> ", p->data);
        p = p->link;
    }
    printf("NULL (rear)\n");
}

void destroy(LinkedQueueType *q)
{
    while (!is_empty(q)) {
        (void)dequeue(q);
    }
}

int main(void)
{
    LinkedQueueType q;
    init(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    print_queue(&q);

    printf("dequeue: %d\n", dequeue(&q));
    print_queue(&q);
    printf("peek: %d\n", peek(&q));

    printf("dequeue: %d\n", dequeue(&q));
    printf("dequeue: %d\n", dequeue(&q));
    print_queue(&q); // 마지막 노드 삭제: front == rear == NULL

    enqueue(&q, 40); // 빈 큐에 다시 삽입해도 정상 동작
    print_queue(&q);
    destroy(&q);
    return 0;
}