#include <stdio.h>
struct Student {
	char name[20];
	int grade;
};
int size;

// ���� �����ϴ� ����
void bubbleSort(struct Student a[], int size) {
	int i, j, t;
	struct Student temp;
	printf("\n������ ���� : ");
	for (t = 0; t<size; t++) printf("[%s %d] ", a[t].name, a[t].grade);
	printf("\n<<<<<<<<<< ���� ���� ���� >>>>>>>>>>");
	for (i = size - 1; i>0; i--) {
		printf("\n %d�ܰ�>>", size - i);
		for (j = 0; j < i; j++) {
			if (a[j].grade>a[j+1].grade) {
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
			printf("\n\t");
			for (t = 0; t<size; t++) printf("[%s %d] ", a[t].name, a[t].grade);
		}
	}
}

void main() {
	struct Student list[5] = {{"A", 43}, {"B", 75}, {"C", 90}, {"D", 13}, {"E", 82}};	// ������ �ʱ� ���� �迭
	size = 5;
	bubbleSort(list, size);
	getchar();
}