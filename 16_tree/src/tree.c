
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
    cnt = 0;
    inorder(1);

    return 0;
}
*/