#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 교안 5~7쪽: 배열 기반 원형 큐
// 추가 슬라이드: get_count() 구현
// 배열이 6칸이면 실제 저장 가능한 데이터는 최대 5개이다.
#define MAX_QUEUE_SIZE 6

typedef int element;

typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front; // 첫 번째 데이터 바로 앞의 인덱스
    int rear;  // 마지막 데이터의 인덱스
} QueueType;

void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

void init(QueueType *q)
{
    q->front = 0;
    q->rear = 0;
}

int is_empty(const QueueType *q)
{
    return q->front == q->rear;
}

int is_full(const QueueType *q)
{
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

int get_count(const QueueType *q)
{
    return (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

void enqueue(QueueType *q, element item)
{
    if (is_full(q)) {
        error("큐가 포화 상태입니다.");
    }

    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

element dequeue(QueueType *q)
{
    if (is_empty(q)) {
        error("큐가 공백 상태입니다.");
    }

    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

element peek(const QueueType *q)
{
    if (is_empty(q)) {
        error("빈 큐는 확인할 수 없습니다.");
    }

    return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
}

void print_queue(const QueueType *q)
{
    int count = get_count(q);
    printf("front=%d, rear=%d, count=%d, queue=[", q->front, q->rear, count);
    for (int i = 0; i < count; ++i) {
        int index = (q->front + 1 + i) % MAX_QUEUE_SIZE;
        printf("%d%s", q->queue[index], i == count - 1 ? "" : ", ");
    }
    printf("]\n");
}

int main(void)
{
    QueueType q;
    init(&q);
    print_queue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);
    print_queue(&q); // count=5, 포화 상태

    printf("dequeue: %d\n", dequeue(&q));
    printf("dequeue: %d\n", dequeue(&q));
    print_queue(&q);

    enqueue(&q, 60);
    enqueue(&q, 70); // rear가 배열 끝에서 처음으로 순환
    print_queue(&q);
    printf("peek: %d\n", peek(&q));
    printf("is_full: %d\n", is_full(&q));

    return 0;
}