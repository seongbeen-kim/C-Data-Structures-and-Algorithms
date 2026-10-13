
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define SIZE 5
#define MAX 100

// 위치 구조체
typedef struct {
    int x;
    int y;
} Position;

// 스택 구조체
typedef struct {
    Position data[MAX];
    int top;
} StackType;

// 미로 배열 (0: 이동 가능, 1: 벽)
int maze[SIZE][SIZE] = {
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {1, 1, 0, 1, 0},
    {0, 0, 0, 0, 0}
};

// 방문 여부 저장 배열
int visited[SIZE][SIZE] = { 0 };

// 스택 초기화
void init(StackType* s)
{
    s->top = -1;
}

// 스택 공백 검사
int is_empty(StackType* s)
{
    return s->top == -1;
}

// 스택 삽입
void push(StackType* s, int x, int y)
{
    if (s->top == MAX - 1) {
        printf("스택 포화 에러\n");
        exit(1);
    }

    s->top++;
    s->data[s->top].x = x;
    s->data[s->top].y = y;
}

// 스택 삭제
Position pop(StackType* s)
{
    if (is_empty(s)) {
        printf("스택 공백 에러\n");
        exit(1);
    }

    return s->data[(s->top)--];
}

int main(void)
{
    StackType s;
    Position current;

    int exit_x = 4;
    int exit_y = 4;

    // 상, 하, 좌, 우
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    init(&s);

    // 시작 위치
    current.x = 0;
    current.y = 0;

    // 출구에 도착할 때까지 반복
    while (current.x != exit_x || current.y != exit_y) {

        visited[current.x][current.y] = 1;

        printf("방문: (%d, %d)\n",
            current.x, current.y);

        // 상하좌우 탐색
        for (int i = 0; i < 4; i++) {

            int x = current.x + dx[i];
            int y = current.y + dy[i];

            // 이동할 수 있는 위치인지 검사
            if (x >= 0 && x < SIZE &&
                y >= 0 && y < SIZE &&
                maze[x][y] == 0 &&
                visited[x][y] == 0) {

                push(&s, x, y);
            }
        }

        // 더 이상 이동할 수 없는 경우
        if (is_empty(&s)) {
            printf("미로 탐색 실패\n");
            return 0;
        }

        // 다음 탐색 위치 가져오기
        current = pop(&s);
    }

    printf("출구 발견: (%d, %d)\n",
        current.x, current.y);

    printf("미로 탐색 성공\n");

    return 0;
}
