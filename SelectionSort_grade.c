#include <stdio.h>
int size;

struct Student {
	char name[20];
	int grade;
};

// 선택 정렬하는 연산
void SelectionSort(struct Student a[], int size) {
	int i, j, t, min;
	struct Student temp;
	printf("\n정렬할 원소 : ");
	for (t = 0; t<size; t++)  printf("[%s %d] ", a[t].name, a[t].grade);	// 정렬 전의 원소 출력
	printf("\n\n<<<<<<<<<< 선택 정렬 수행 >>>>>>>>>>\n");
	for (i = 0; i<size - 1; i++) {
		min = i;
		for (j = i + 1; j<size; j++) {
			if (a[j].grade<a[min].grade) min = j;
		}
		temp = a[i];
		a[i] = a[min];
		a[min] = temp;
		printf("\n%d단계 : ", i + 1);
		for (t = 0; t<size; t++)  printf("[%s %d] ", a[t].name, a[t].grade);
	}
}

void main() {
	struct Student list[5] = {{"A", 43}, {"B", 75}, {"C", 90}, {"D", 13}, {"E", 82}};	// 정렬할 초기 원소 배열
	size = 5;
	SelectionSort(list, size);							// 선택 정렬 연산 호출

	getchar();
}