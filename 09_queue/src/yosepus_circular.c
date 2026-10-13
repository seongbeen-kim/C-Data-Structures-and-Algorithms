#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 교안 16쪽 Review: 요세푸스 문제를 원형 큐로 해결
// n명 중 k번째를 제거하고, 1명이 남을 때까지 반복한다.
// 예: n=7, k=3 => 제거 3,6,2,7,5,1 / 생존 4

typedef struct {
    int *data;
    int size;   // n+1칸: 원형 큐는 한 칸 비운다.
    int front;
    int rear;
} QueueType;

void error(const char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

void init(QueueType *q, int n)
{
    q->size = n + 1;
    q->data = malloc(sizeof(int) * (size_t)q->size);
    if (q->data == NULL) {
        error("메모리 할당 실패");
    }
    q->front = 0;
    q->rear = 0;
}

int is_empty(const QueueType *q)
{
    return q->front == q->rear;
}

int is_full(const QueueType *q)
{
    return (q->rear + 1) % q->size == q->front;
}

void enqueue(QueueType *q, int item)
{
    if (is_full(q)) {
        error("큐 포화");
    }
    q->rear = (q->rear + 1) % q->size;
    q->data[q->rear] = item;
}

int dequeue(QueueType *q)
{
    if (is_empty(q)) {
        error("큐 공백");
    }
    q->front = (q->front + 1) % q->size;
    return q->data[q->front];
}

int main(void)
{
    int n, k;
    QueueType q;

    printf("전체 인원 n, 제거 간격 k 입력 (예: 7 3): ");
    if (scanf("%d %d", &n, &k) != 2 || n < 1 || n > 1000 || k < 1) {
        fprintf(stderr, "n은 1~1000, k는 1 이상의 정수여야 합니다.\n");
        return EXIT_FAILURE;
    }

    init(&q, n);
    for (int i = 1; i <= n; ++i) {
        enqueue(&q, i);
    }

    printf("제거 순서: ");
    for (int remaining = n; remaining > 1; --remaining) {
        // k-1명은 뒤로 보내어 생존시킨다.
        for (int step = 1; step < k; ++step) {
            enqueue(&q, dequeue(&q));
        }

        // k번째 사람을 실제로 제거한다.
        int removed = dequeue(&q);
        printf("%d%s", removed, remaining == 2 ? "" : ", ");
    }

    printf("\n마지막 생존자: %d\n", dequeue(&q));
    free(q.data);
    return 0;
}