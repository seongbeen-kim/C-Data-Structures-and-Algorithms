//////////////////////////////////////////////////////////////////////////

// maxhip 코드구현, 올림차순
// level3이면 코드 작성이고 level2이면 스토코드만 작성하면 된다.(중요중요)

// 최대 힙(Max Heap) 구현
// 삽입 연산: Upheap, O(log N)
// 삭제 연산: Downheap, O(log N)
// 힙 정렬: O(N log N), 최대 힙을 이용하면 오름차순 정렬 가능
// 힙 정렬은 최대힙을 이용하여 정렬하는 방법이다

#include <stdio.h>
#define MAX 100

typedef struct {
    int heap[MAX];
    int size;
} HeapType;

void insert_maxheap(HeapType* A, int key) {
    A->size++;
    int i = A->size;
    A->heap[i] = key;

    while (i != 1 && A->heap[i] > A->heap[i / 2]) {
        int tmp = A->heap[i];
        A->heap[i] = A->heap[i / 2];
        A->heap[i / 2] = tmp;

        i = i / 2;
    }

}

int delete_maxheap(HeapType* A) {

    int item = A->heap[1];
    A->heap[1] = A->heap[A->size--];
    int i = 2;
    int largest;

    while (i <= A->size) {
        if (i < A->size && A->heap[i] < A->heap[i + 1])
            largest = i + 1;  // 오른쪽 자식이 더 큼
        else
            largest = i;      // 왼쪽 자식 선택

        if (A->heap[largest / 2] >= A->heap[largest])
            break;

        int tmp = A->heap[largest / 2];
        A->heap[largest / 2] = A->heap[largest];
        A->heap[largest] = tmp;

        i = largest * 2;
    }

    return item;
}


int main()
{
    int i;
    HeapType A = { 0 };
    int data[] = { 10, 30, 20, 50, 40 };

    for (i = 0; i < 5; i++) {
        insert_maxheap(&A, data[i]);
    }

    for (i = 1; i <= A.size; i++) {
        printf("%d ", A.heap[i]);
    }

    printf("\n %d \n", delete_maxheap(&A));

    for (i = 1; i <= A.size; i++) {
        printf("%d ", A.heap[i]);
    }

    return 0;
}