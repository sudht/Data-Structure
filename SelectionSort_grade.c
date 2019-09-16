#include <stdio.h>
int size;

struct Student {
	char name[20];
	int grade;
};

// ���� �����ϴ� ����
void SelectionSort(struct Student a[], int size) {
	int i, j, t, min;
	struct Student temp;
	printf("\n������ ���� : ");
	for (t = 0; t<size; t++)  printf("[%s %d] ", a[t].name, a[t].grade);	// ���� ���� ���� ���
	printf("\n\n<<<<<<<<<< ���� ���� ���� >>>>>>>>>>\n");
	for (i = 0; i<size - 1; i++) {
		min = i;
		for (j = i + 1; j<size; j++) {
			if (a[j].grade<a[min].grade) min = j;
		}
		temp = a[i];
		a[i] = a[min];
		a[min] = temp;
		printf("\n%d�ܰ� : ", i + 1);
		for (t = 0; t<size; t++)  printf("[%s %d] ", a[t].name, a[t].grade);
	}
}

void main() {
	struct Student list[5] = {{"A", 43}, {"B", 75}, {"C", 90}, {"D", 13}, {"E", 82}};	// ������ �ʱ� ���� �迭
	size = 5;
	SelectionSort(list, size);							// ���� ���� ���� ȣ��

	getchar();
}