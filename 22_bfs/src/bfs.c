
/*
// 미로의 최단 경로 찾기(BFS)
// bfs, dsf함수 구현하는게 level3문제 정도로 나온다.
#include<stdio.h>
#define MAX 100


int adj_mat[MAX][MAX] = {0}; //그래프 데이터 저장하는 배열
int dist[MAX][MAX] = {0}; // 방문한 정점 표시하는 배열
int n, m;

int dx[4] = {-1, 1, 0, 0}; 
int dy[4] = {0, 0, -1, 1}; 

typedef struct{
    int x, y;
} Point;

typedef struct{
    Point data[MAX*MAX];
    int front, rear;
} QueueType;

void init(QueueType *q)
{
    q->front = q->rear = 0; // 큐 초기화
}

void enqueue(QueueType *q, int x, int y)
{
    q->data[q->rear].x = x;
    q->data[q->rear].y = y;
    q->rear++;
}

Point dequeue(QueueType *q)
{
    return q->data[q->front++];
}

int is_empty(QueueType *q)
{
    return q->front == q->rear; // 큐가 비어있는지 확인
}  

int bfs()
{
    QueueType q;
    init(&q);
    enqueue(&q, 0, 0); // 시작점 (0,0) 큐에 추가
    dist[0][0] = 1; // 시작점 거리 초기화

    while(!is_empty(&q))
    {
        Point p = dequeue(&q);
        int x = p.x;
        int y = p.y;

        if(x == n-1 && y == m-1) // 도착점에 도달하면 종료
        {
            return dist[x][y]-1; // 도착점 거리 반환
        }

        for(int i=0; i<4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx >= 0 && nx < n && ny >= 0 && ny < m) // 범위 체크
            {
                if(adj_mat[nx][ny] == 1 && dist[nx][ny] == 0) // 이동 가능하고 방문하지 않은 경우
                {
                    enqueue(&q, nx, ny); // 큐에 추가
                    dist[nx][ny] = dist[x][y] + 1; // 거리 갱신
                }
            }
        }
    }

    return -1; // 도착점에 도달하지 못하면 -1 반환 
}

int main()
{
    scanf("%d %d", &n, &m); // 정점의 수와 간선의 수 입력
     
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            scanf("%d", &adj_mat[i][j]); // 간선의 양 끝점 입력
        }
        
    }

    printf("min_distance: %d \n", bfs()); 

    return 0;
}
*/


#include<stdio.h>
#define MAX 100

typedef struct{
    int adj_mat[MAX][MAX]; //그래프 데이터 저장하는 배열
    int n; // 정점의 수
} GraphType;

int visited[MAX] = {0}; // 방문한 정점 표시하는 배열

typedef struct{
    int data[MAX];
    int front, rear;
} QueueType;

void init(QueueType *q)
{
    q->front = q->rear = 0; // 큐 초기화
}

int is_empty(QueueType *q)
{
    return q->front == q->rear; // 큐가 비어있는지 확인, 1차원 큐임(원형 큐 구현은 코드 구현이 다르다)
}

void enqueue(QueueType *q, int item)
{
    q->data[q->rear++] = item; // 큐에 데이터 추가
}

int dequeue(QueueType *q)
{
    return q ->data[q->front++]; // 큐에서 데이터 제거
}

void bfs_mat(GraphType *g, int v)
{
    QueueType q = {0}; // 큐 초기화
    init(&q); // 큐 초기화
    visited[v]=1;
    printf(" %d", v); // 방문한 정점 출력
    enqueue(&q, v); // 큐에 시작 정점 추가

    while(!is_empty(&q))
    {
        v = dequeue(&q); // 큐에서 정점 제거, v는 0이다
        for(int w=0; w<g->n; w++) //정점의 수만큼 반복
        {
            if(g->adj_mat[v][w]==1 && visited[w]==0) // 간선이 존재하고 방문하지 않은 곳이어야 함
            {
                // 방문한 곳 표시하고, enqueue작업
                visited[w]=1; // 방문한 정점 표시
                printf(" %d", w); // 방문한 정점 출력
                enqueue(&q, w); // 큐에 정점 추가
            }
        }
    }
}

int main()
{
    GraphType g = {0}; // 구조체 초기화
    int m; // 간선의 수
    int a, b; // 간선의 양 끝점
    scanf("%d %d", &g.n, &m); // 정점의 수와 간선의 수 입력
    for(int i=0; i<m; i++)
    {
        scanf("%d %d", &a, &b); // 간선의 양 끝점 입력
        g.adj_mat[a][b] = 1; // 간선 연결
        g.adj_mat[b][a] = 1; // 무방향 그래프이므로 반대 방향도 연결s
    }

    bfs_mat(&g, 0); // 주소값을 던져야 하고, 0(시작값 세팅)부터 시작하는 상황이어서

    return 0;
}

// 중요중요한데, dfs, bfs를 함수를 연속적으로 돌리려면 중간에 visied함수를 초기화 해야 한다.
// dfs, bfs 기본 코드중 기본코드

