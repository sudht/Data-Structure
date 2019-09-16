#include<stdio.h>

typedef struct { // 행렬 원소를 저장하기 위한 구조체 term 정의
	int row;
	int col;
	int value;
} term;

void smPrint(term []);
void smTranspose(term [], term []);

void main() {
	term a[20] = {{6, 6, 4}, {1, 3, 4}, {3, 5, 9}, {4, 2, 8}};
	term b[20];

	printf("a = \n");
	smPrint(a);

	smTranspose(a, b);
	printf("TransPose a = \n");
	smPrint(b);
}

void smTranspose(term a[], term b[]) {
	int m, n, v, i, j, p;
	m = a[0].row;	// 희소 행렬 a의 행 수
	n = a[0].col;	// 희소 행렬 a의 열 수
	v = a[0].value; // 희소 행렬 a에서 0이 아닌 원소 수
	b[0].row = n;	// 전치 행렬 b의 행 수
	b[0].col = m;	// 전치 행렬 b의 열 수
	b[0].value = v;	// 전치 행렬 b의 원소 수
	if (v > 0) {	// 0이 아닌 원소가 있는 경우에만 전치 연산 수행
		p = 1;
		for (i = 0; i < n; i++)			// 희소 행렬 a의 열별로 전치 반복 수행
			for (j = 1; j <= v; j++)	// 0이 아닌 원소 수에 대해서만 반복 수행
				if (a[j].col == i) {	// 현재의 열에 속하는 원소가 있으면 b[]에 삽입
					b[p].row = a[j].col;
					b[p].col = a[j].row;
					b[p].value = a[j].value;
					p++;
				}
	}
}

void smPrint(term a[]) {
	int i, j;
	int count = 1;	// term a 왼쪽 행 인덱스를 표시

	for(i = 0; i < a[0].row; i++) {
		for(j = 0; j < a[0].col; j++) {
			if (a[count].col == j && a[count].row == i) {
				printf("%d ", a[count].value);
				count++;
			}
			else
				printf("0 ");
		}
		printf("\n");
	}
	printf("\n\n");
}