
// 이 정도는 구현할 수 있어야 함
// 조직도에서 부하 직원 수 구하기(level 2), 이진트리 문제는 아니고 일반적인 트리 문제임

// 사장이 있기 때문에 입력받을 때 n-1개의 간선만 입력받으면 됨, 2차원 배열로 구현한다.
// 7명이면 2차원 배열은 8짜리로 선언하는 편이 좋다. 초기값을 0으로 세팅한다.
// 입력 받은 좌표에 대해 1로 세팅, 이게 2차원 배열 세팅(코드 이해가 필요함, 많이 어렵다)
// dfs의 기본

/*
#include <stdio.h>

int tree[101][101] = {0}; // 2차원 배열 초기화
int count[101] = {0}; // 각 직원의 부하 직원 수를 저장할 배열
int N;

int dfs(int x)
{
    int total = 0; // x의 부하 직원 수를 저장할 변수
    for(int i = 1; i <= N; i++) // 1번부터 N번까지 반복
    {
        if(tree[x][i] == 1) // x가 i의 상사라면
        {
            total += dfs(i) + 1; // x의 부하 직원 수에 i의 부하 직원 수 + 1을 더함
        }
    }
    count[x] = total; // x의 부하 직원 수를 count 배열에 저장
    return total; // x의 부하 직원 수 반환
}

int main()
{
    scanf("%d", &N); // 직원 수 입력;
    int a, b;
    for(int i = 0; i < N - 1; i++) // 간선 수는 n-1개, 부등호 실수하지마라(점수 못준다)
    {
        scanf("%d %d", &a, &b); // a가 b의 상사
        tree[a][b] = 1; // a가 b의 상사이므로 a행 b열에 1을 세팅
    }

    dfs(1); // 사장부터 시작, 사장은 1번이라고 가정

    for(int i = 1; i <= N; i++)
    {
            printf("%d : %d \n", i, count[i]); // 각 직원의 부하 직원 수 출력
    }


    return 0;
}
*/

//////////////////////////////////////////////////////////////////////////

// 이진 탐색 트리에서 K번째 작은 값 찾기(level 2.5)
// 0번째를 더미로 안두고 값을 저장하는 용으로 사용한다.
// value 0, left 1, right2
// 첫번째 값은 root로 사용, 해당 문제 시각화해서 이해하면 될 듯(별거 없음)
// 세번째 작은 값은 중위 순회로 3번째 방문한 노드의 값이 된다.
// 중위 순회로 해야지 오름차순
// 내용은 복잡한데 코드로 짜면 간단하다

/*
#include <stdio.h>
int bt[100][3] = {0};
int n, k, cnt;

void inorder(int root)
{
    if(root == 0)
    {
        return;
    }
    inorder(bt[root][1]); // 왼쪽 먼저 훑고
    cnt++;
    if(cnt==k)
    {
        printf("%d\n", bt[root][0]);
    }
    inorder(bt[root][2]);
}
void insert_bt(int cur, int root)
{
    int dir = (bt[cur][0] < bt[root][0]) ? 1 : 2;
    if(bt[root][dir] == 0)
    {
        bt[root][dir] = cur;
    }
    else
    {
        insert_bt(cur, bt[root][dir]);
    }
}

int main()
{   
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &bt[i][0]);
        if(i==1)
        {
            continue;
        }
        insert_bt(i, 1);
    }
    
    scanf("%d", &k);
    cnt = 1;
    inorder(1);

    return 0;
}
*/

//////////////////////////////////////////////////////////////////////////

// maxhip 코드구현, 올림차순

// level3이면 코드 작성이고 level2이면 스토코드만 작성하면 된다.(중요중요)

// 삽입연산

/*
#include<stdio.h>
#define MAX 100

typedef struct{
    int heap[MAX];
    int size;
}HeapType;

void insert_maxheap(HeapType *A, int key)
{
    A->size++;
    int i = A->size;
    A->heap[i]=key;

while(i!=1 && A->heap[i/2]<A->heap[i]) // 부모노드가 자식노드보다 작으면 교환
    {
        int temp = A->heap[i];
        A->heap[i] = A->heap[i/2];
        A->heap[i/2] = temp;
        i/=2;
    }
}

int main()
{
    HeapType A = {0}; 
    int data[] = {10,30,50,20,40};

    for(int i=0; i<5; i++)
    {
        insert_maxheap(&A, data[i]); //주소값을 던져야 함
    }

    for(int i=1; i<= A.size; i++) //포인터가 아니고 변수이므로 .으로 접근
    {
        printf("%d ", A.heap[i]);
    }

    return 0;
}
*/

// 삭제연산 + 삽입연산 병합
// 힙 정렬 시간복잡도는 nlog(n)이다. 힙 정렬은 최대힙을 이용하여 정렬하는 방법이다.

/*
#include<stdio.h>
#define MAX 100

typedef struct{
    int heap[MAX];
    int size;
}HeapType;

void insert_maxheap(HeapType *A, int key)
{
    A->size++;
    int i = A->size;
    A->heap[i]=key;

while(i!=1 && A->heap[i/2]<A->heap[i]) // 부모노드가 자식노드보다 작으면 교환
    {
        int temp = A->heap[i];
        A->heap[i] = A->heap[i/2];
        A->heap[i/2] = temp;
        i/=2;
    }
}

int delete_maxheap(HeapType *A) // 코드 정리 필요!!
{
    int item = A->heap[1]; // 삭제할 루트노드

    A->heap[1] = A->heap[A->size]; // 마지막 노드를 루트로 이동
    A->size--;
    int parent = 1;
    int child = 2; // 2번 자식(왼쪽 노드)
    
    while(child <= A->size) // 자식노드가 존재하면 반복
    {
        if(child < A->size && A->heap[child] < A->heap[child+1]) // 오른쪽 자식이 더 크면
        {
            parent = child+1; // 오른쪽 자식으로 이동 
        }
        else 
            parent = child; // 왼쪽 자식으로 이동


        if(A->heap[parent] >= A->heap[child]) // 부모가 자식보다 크면 종료
        {
            break;
        }
        else // 부모가 자식보다 작으면 교환
        {
            int temp = A->heap[parent];
            A->heap[parent] = A->heap[parent/2];
            A->heap[parent/2] = temp;
            child = parent * 2; // 왼쪽 자식으로 이동
        }
    }
    
    return item; // 삭제된 루트노드 반환
}

int main()
{
    HeapType A = {0}; 
    int data[] = {10,30,50,20,40};

    for(int i=0; i<5; i++)
    {
        insert_maxheap(&A, data[i]); //주소값을 던져야 함
    }

    for(int i=1; i<= A.size; i++) //포인터가 아니고 변수이므로 .으로 접근
    {
        printf("%d ", A.heap[i]);
    }

    printf("\n %d \n", delete_maxheap(&A)); //삭제연산 호출

    for(int i=1; i<= A.size; i++) //포인터가 아니고 변수이므로 .으로 접근
    {
        printf("%d ", A.heap[i]);
    }

    return 0;
}
*/

/*
// DFS(인접 행렬로 구현) -recursive로 구현!!
// 시험에 나온다. dfs_mat(GraphType *g, int v)함수는 구현을 할 수 있어야 한다.
// 당연히 bfs도 구현할 수 있어야 한다. bfs함수도 구현하는게 문제가 나온다.

#include<stdio.h>
#define MAX 100

typedef struct{
    int adj_mat[MAX][MAX]; //그래프 데이터 저장하는 배열
    int n; // 정점의 수
} GraphType;

int visited[MAX] = {0}; // 방문한 정점 표시하는 배열

void dfs_mat(GraphType *g, int v) // 주소값을 던져야 함
{
    visited[v] = 1; // 방문한 정점 표시
    printf(" %d", v); // 방문한 정점 출력
    for(int w=0; w<g->n; w++) // 정점의 수만큼 반복
    {
        if(g->adj_mat[v][w]==1 && visited[w]==0) // 간선이 존재하고 방문하지 않은 곳이어야 함
        {
            dfs_mat(g, w); // 재귀 호출
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

    dfs_mat(&g, 0); // 주소값을 던져야 하고, 0(시작값 세팅)부터 시작하는 상황이어서

    return 0;
}

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

*/

/*
c++구현(bfs)

#include<queue>
#include <iostream>
#define MAX 100

void bfs_mat(GraphType *g, int v)
{
    queue<int> q; // 큐 초기화
    q.init(); // 큐 초기화
    visited[v]=1;

    cout << v;
    q.push(v);


    /////////////////////////////////////////////////////

    // while문만 c에서 c++로 돌려보기
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
    ////////////////////////////////////////////
}


int main()
{
    GraphType g = {0}; // 구조체 초기화
    int m; // 간선의 수
    int a, b; // 간선의 양 끝점
    cin >> g.n >> m; // 정점의 수와 간선의 수 입력
    for(int i=0; i<m; i++)
    {
        cin >> a >> b; // 간선의 양 끝점 입력
        g.adj_mat[a][b] = 1; // 간선 연결
        g.adj_mat[b][a] = 1; // 무방향 그래프이므로 반대 방향도 연결s
    }

    bfs_mat(&g, 0); // 주소값을 던져야 하고, 0(시작값 세팅)부터 시작하는 상황이어서

    return 0;
}
*/

// 그래프 응용_연결성분찾기(dfs) 

#include<stdio.h>
#define MAX 100

typedef struct{
    int adj_mat[MAX][MAX]; //그래프 데이터 저장하는 배열
    int n; // 정점의 수
} GraphType;

int visited[MAX] = {0}; // 방문한 정점 표시하는 배열
int count = 0; // 연결성분의 수를 저장하는 변수

void dfs_mat(GraphType *g, int v) // 주소값을 던져야 함
{
    visited[v] = count; // 방문한 정점 표시
    for(int w=0; w<g->n; w++) // 정점의 수만큼 반복
    {
        if(g->adj_mat[v][w]==1 && visited[w]==0) // 간선이 존재하고 방문하지 않은 곳이어야 함
        {
            dfs_mat(g, w); // 재귀 호출
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
        g.adj_mat[b][a] = 1; // 무방향 그래프이므로 반대 방향도 연결
    }

    count = 0;
    for(int i=0; i<g.n; i++)
    {
        if(visited[i]==0) // 방문하지 않은 경우에 dfs를 돌린다.
        {
            count++; // 연결성분의 수 증가
            dfs_mat(&g, i);
        }    
    }
    printf("Count: %d", count); // 연결성분의 수 출력

    return 0;
}

