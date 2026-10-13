// PDF 9~11쪽: 배열을 이용한 리스트(ArrayListType)
// 슬라이드의 init, is_empty, is_full, add, delete를 포함합니다.
// display, get_length, get_entry, replace 등은 실행/복습용 추가 구현입니다.
#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 10

typedef int element;

typedef struct {
    element list[MAX_LIST_SIZE];
    int length;
} ArrayListType;

void error(const char *message) {
    fprintf(stderr, "오류: %s\n", message);
    exit(EXIT_FAILURE);
}

void init(ArrayListType *L) {
    L->length = 0;
}

int is_empty(const ArrayListType *L) {
    return L->length == 0;
}

int is_full(const ArrayListType *L) {
    return L->length == MAX_LIST_SIZE;
}

// position 위치에 item 삽입: 뒤쪽 요소를 한 칸씩 오른쪽으로 이동
void add(ArrayListType *L, int position, element item) {
    if (is_full(L)) error("배열 리스트가 가득 찼습니다.");
    if (position < 0 || position > L->length) error("삽입 위치 오류");

    for (int i = L->length - 1; i >= position; i--) {
        L->list[i + 1] = L->list[i];
    }
    L->list[position] = item;
    L->length++;
}

// position 위치의 요소 삭제: 뒤쪽 요소를 한 칸씩 왼쪽으로 이동
// 삭제한 값을 반환합니다.
element delete(ArrayListType *L, int position) {
    if (position < 0 || position >= L->length) error("삭제 위치 오류");

    element item = L->list[position];
    for (int i = position; i < L->length - 1; i++) {
        L->list[i] = L->list[i + 1];
    }
    L->length--;
    return item;
}

// 아래 함수들은 리스트 ADT를 복습하기 위한 추가 기능입니다.
int get_length(const ArrayListType *L) {
    return L->length;
}

element get_entry(const ArrayListType *L, int position) {
    if (position < 0 || position >= L->length) error("조회 위치 오류");
    return L->list[position];
}

void replace(ArrayListType *L, int position, element item) {
    if (position < 0 || position >= L->length) error("교체 위치 오류");
    L->list[position] = item;
}

// 추가 실습: 해당 값의 포함 여부 검사
int is_in_list(const ArrayListType *L, element item) {
    for (int i = 0; i < L->length; i++) {
        if (L->list[i] == item) return 1;
    }
    return 0;
}

// 추가 실습: 배열을 재할당하지 않고 논리적 길이만 0으로 변경
void clear(ArrayListType *L) {
    L->length = 0;
}

void display(const ArrayListType *L) {
    printf("[");
    for (int i = 0; i < L->length; i++) {
        printf("%d", L->list[i]);
        if (i < L->length - 1) printf(", ");
    }
    printf("]\n");
}

int main(void) {
    ArrayListType list1;
    init(&list1);

    printf("초기 상태: ");
    display(&list1);
    printf("비어 있나요? %s\n", is_empty(&list1) ? "예" : "아니오");

    add(&list1, 0, 10);
    add(&list1, 1, 20);
    add(&list1, 2, 30);
    printf("10, 20, 30 삽입: ");
    display(&list1);

    add(&list1, 1, 15); // 인덱스 1에 15 삽입
    printf("인덱스 1에 15 삽입: ");
    display(&list1);

    printf("삭제한 값: %d\n", delete(&list1, 2));
    printf("삭제 후: ");
    display(&list1);

    replace(&list1, 0, 99);
    printf("0번째 값 교체: ");
    display(&list1);
    printf("길이: %d, 1번째 값: %d\n", get_length(&list1), get_entry(&list1, 1));
    printf("15 포함? %s\n", is_in_list(&list1, 15) ? "예" : "아니오");
    clear(&list1);
    printf("모두 비운 후: ");
    display(&list1);
    return 0;
}
