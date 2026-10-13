#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 교안 13쪽: 생산자-버퍼-소비자 구조를 순서대로 보여 주는 단일 스레드 예제
// 교안의 lock()/unlock()은 동시 실행을 전제로 하는 의사코드이다.
// 이 프로그램은 동시 실행이 아니므로 동기화 함수를 넣지 않았다.
#define BUFFER_SIZE 5 // 실제 저장 가능: 4개

typedef struct {
    int data[BUFFER_SIZE];
    int front;
    int rear;
} Buffer;

void init(Buffer *b)
{
    b->front = 0;
    b->rear = 0;
}

int is_empty(const Buffer *b)
{
    return b->front == b->rear;
}

int is_full(const Buffer *b)
{
    return (b->rear + 1) % BUFFER_SIZE == b->front;
}

// 생산자: 큐에 데이터를 넣는다.
int producer(Buffer *b, int item)
{
    if (is_full(b)) {
        printf("생산자: 버퍼 가득 참. %d 저장 불가\n", item);
        return 0;
    }
    b->rear = (b->rear + 1) % BUFFER_SIZE;
    b->data[b->rear] = item;
    printf("생산자: %d 저장\n", item);
    return 1;
}

// 소비자: 큐에서 가장 오래된 데이터를 꺼낸다.
int consumer(Buffer *b)
{
    if (is_empty(b)) {
        printf("소비자: 버퍼 비어 있음\n");
        return 0;
    }
    b->front = (b->front + 1) % BUFFER_SIZE;
    printf("소비자: %d 사용\n", b->data[b->front]);
    return 1;
}

int main(void)
{
    Buffer buffer;
    init(&buffer);

    producer(&buffer, 10);
    producer(&buffer, 20);
    producer(&buffer, 30);
    producer(&buffer, 40);
    producer(&buffer, 50); // 버퍼가 가득 차서 삽입 불가

    consumer(&buffer);     // 먼저 저장된 10 소비
    producer(&buffer, 50); // 빈 자리에 50 저장(원형 순환)

    while (consumer(&buffer)) {
        // 비워질 때까지 소비
    }
    return 0;
}
