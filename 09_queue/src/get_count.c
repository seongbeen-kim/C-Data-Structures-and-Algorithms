#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10

typedef int element;

typedef struct {
    element queue[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init(QueueType *q)
{
    q->front = 0;
    q->rear = 0;
}

int is_empty(QueueType *q)
{
    return q->front == q->rear;
}

int is_full(QueueType *q)
{
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void enqueue(QueueType *q, element item)
{
    if (is_full(q))
        error("Queue is Full");

    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

element dequeue(QueueType *q)
{
    if (is_empty(q))
        error("Queue is Empty");

    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

// 원형 큐에 저장된 요소 수를 반환 (슬라이드 핵심 함수)
int get_count(QueueType *q)
{
    return (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

int main(void)
{
    QueueType q;
    init(&q);

    printf("Initial count: %d\n", get_count(&q)); // 0

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    printf("After 3 enqueues: %d\n", get_count(&q)); // 3

    printf("dequeue(): %d\n", dequeue(&q)); // 10
    printf("After dequeue: %d\n", get_count(&q)); // 2

    return 0;
}
