#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// 교안 14~15쪽: 은행 고객 대기열 시뮬레이션
// 슬라이드에는 핵심 반복문만 실려 있어, 빠진 도착 판정/고객 생성/
// 통계 함수를 보충해 독립 실행되도록 완성한 학습용 예제이다.
#define MAX_QUEUE_SIZE 101 // 최대 대기 고객 100명
#define DURATION 30        // 30분 시뮬레이션
#define ARRIVAL_PERCENT 45 // 매 분 45% 확률로 고객 도착

typedef struct {
    int id;
    int arrival_time;
    int service_time;
} Customer;

typedef struct {
    Customer data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} CustomerQueue;

static CustomerQueue waiting;
static int next_customer_id = 1;
static int arrived_count = 0;
static int started_count = 0;
static int finished_count = 0;
static int total_wait_time = 0;

void init(CustomerQueue *q)
{
    q->front = 0;
    q->rear = 0;
}

int is_empty(const CustomerQueue *q)
{
    return q->front == q->rear;
}

int is_full(const CustomerQueue *q)
{
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

int get_count(const CustomerQueue *q)
{
    return (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

void enqueue(CustomerQueue *q, Customer c)
{
    if (is_full(q)) {
        fprintf(stderr, "대기열이 가득 찼습니다.\n");
        exit(EXIT_FAILURE);
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = c;
}

Customer dequeue(CustomerQueue *q)
{
    if (is_empty(q)) {
        fprintf(stderr, "대기열이 비어 있습니다.\n");
        exit(EXIT_FAILURE);
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

int is_customer_arrived(void)
{
    return rand() % 100 < ARRIVAL_PERCENT;
}

void insert_customer(int current_time)
{
    Customer c;
    c.id = next_customer_id++;
    c.arrival_time = current_time;
    c.service_time = rand() % 4 + 1; // 1~4분

    enqueue(&waiting, c);
    arrived_count++;
    printf("  고객 %d 도착 (서비스 %d분, 대기 %d명)\n",
           c.id, c.service_time, get_count(&waiting));
}

Customer remove_customer(int current_time)
{
    Customer c = dequeue(&waiting);
    int wait = current_time - c.arrival_time;
    total_wait_time += wait;
    started_count++;
    printf("  고객 %d 서비스 시작 (대기 시간 %d분)\n", c.id, wait);
    return c;
}

void print_stat(int service_time)
{
    printf("\n--- 최종 통계 ---\n");
    printf("도착한 고객: %d명\n", arrived_count);
    printf("서비스 시작: %d명\n", started_count);
    printf("서비스 완료: %d명\n", finished_count);
    printf("아직 대기 중: %d명\n", get_count(&waiting));
    printf("현재 서비스 중: %s\n", service_time > 0 ? "예" : "아니요");
    printf("평균 대기 시간(서비스를 시작한 고객 기준): %.2f분\n",
           started_count > 0 ? (double)total_wait_time / started_count : 0.0);
}

int main(void)
{
    int current_time = 0;
    int service_time = 0;
    int current_customer_id = -1;

    srand(42); // 실행할 때마다 비슷한 결과가 나오도록 시드 고정
    init(&waiting);

    while (current_time < DURATION) {
        current_time++;
        printf("[%2d분]\n", current_time);

        if (is_customer_arrived()) {
            insert_customer(current_time);
        }

        // 기존 고객의 서비스 시간을 1분 줄인다.
        if (service_time > 0) {
            service_time--;
            if (service_time == 0) {
                finished_count++;
                printf("  고객 %d 서비스 완료\n", current_customer_id);
                current_customer_id = -1;
            }
        }

        // 창구가 비어 있으면 가장 먼저 온 고객을 꺼내 서비스한다.
        if (service_time == 0 && !is_empty(&waiting)) {
            Customer c = remove_customer(current_time);
            current_customer_id = c.id;
            service_time = c.service_time;
        }
    }

    print_stat(service_time);
    return 0;
}