// DFS(인접 행렬로 구현) -recursive로 구현!!
// 시험에 나온다. dfs_mat(GraphType *g, int v)함수는 구현을 할 수 있어야 한다.
// 당연히 bfs도 구현할 수 있어야 한다. bfs함수도 구현하는게 문제가 나온다.

/*
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
        g.adj_mat[b][a] = 1; // 무방향 그래프이므로 반대 방향도 연결
    }

    dfs_mat(&g, 0); // 주소값을 던져야 하고, 0(시작값 세팅)부터 시작하는 상황이어서

    return 0;
}
*/

/*
// 그래프 응용_연결성분찾기(dfs) 
#include<stdio.h>
#define MAX 100

typedef struct{
    int adj_mat[MAX][MAX]; //그래프 데이터 저장하는 배열
    int n; // 정점의 수
} GraphType;

int visited[MAX] = {0}; // 방문한 정점 표시하는 배열
int count = 0; // 연결성분의 수를 저장하는 변수
GraphType g = {0}; // 구조체 초기화

void dfs_mat(int v) // 전역변수 g를 사용하므로 시작 정점만 전달
{
    visited[v] = count; // 방문한 정점 표시
    for(int w=0; w<g.n; w++) // w는 정점의 수만큼 반복
    {
        if(g.adj_mat[v][w]==1 && visited[w]==0) // 간선이 존재하고 방문하지 않은 곳이어야 함
        {
            dfs_mat(w); // 재귀 호출
        }
    }
}

int main()
{
    int m, a, b; // 간선의 수, 간선의 양 끝점 
    scanf("%d %d", &g.n, &m); // 정점의 수와 간선의 수 입력
    
    for(int i = 0; i < m; i++)
    {
        scanf("%d %d", &a, &b); // 간선의 양 끝점 입력
        g.adj_mat[a][b] = 1; // 간선 연결
        g.adj_mat[b][a] = 1; // 무방향 그래프이므로 반대 방향도 연결
    }
    
    for(int i=0; i<g.n; i++) //i는 정점의 수만큼 반복
    {
        if(visited[i]==0) // 방문하지 않은 경우에 dfs를 돌린다.
        {
            count++; // 연결성분의 수 증가
            dfs_mat(i);
        }    
    }

    printf("Count: %d \n", count); // 연결성분의 수 출력

    return 0;
}
*/

/*
// 섬의 개수 구하기(DFS)
// 상하좌우 움직임만 가능하다!
#include<stdio.h>
#define MAX 100

int adj_mat[MAX][MAX] = {0}; //그래프 데이터 저장하는 배열
int visited[MAX][MAX] = {0}; // 방문한 정점 표시하는 배열
int count = 0; // 연결성분의 수를 저장하는 변수
int n, m;
int dx[4] = {-1, 1, 0, 0}; 
int dy[4] = {0, 0, -1, 1}; 

void dfs_mat(int x, int y) // 현재 위치의 행과 열을 전달
{
    visited[x][y] = count; // 방문한 정점 표시

    for(int i=0; i<4; i++) 
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if(nx >= 0 && nx < n && ny >= 0 && ny < m) // 범위 체크
        {
            if(visited[nx][ny] == 0 && adj_mat[nx][ny] == 1) // 방문하지 않은 경우에 dfs를 돌린다.
            {
                dfs_mat(nx, ny);
            }
        }
    }
}

int main()
{
    scanf("%d %d", &n, &m); // 행과 열의 개수를 입력받음
     
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            scanf("%d", &adj_mat[i][j]); // 간선의 양 끝점 입력
        }
        
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            {
                if(visited[i][j]==0 && adj_mat[i][j]==1) 
                {
                    count++; // 연결성분의 수 증가
                    dfs_mat(i, j);
                }
            }
        }  
    }
    printf("Connected: %d \n", count); 

    return 0;
}
*/


