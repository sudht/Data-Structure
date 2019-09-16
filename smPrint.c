#include<stdio.h>

typedef struct { // ��� ���Ҹ� �����ϱ� ���� ����ü term ����
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
	m = a[0].row;	// ��� ��� a�� �� ��
	n = a[0].col;	// ��� ��� a�� �� ��
	v = a[0].value; // ��� ��� a���� 0�� �ƴ� ���� ��
	b[0].row = n;	// ��ġ ��� b�� �� ��
	b[0].col = m;	// ��ġ ��� b�� �� ��
	b[0].value = v;	// ��ġ ��� b�� ���� ��
	if (v > 0) {	// 0�� �ƴ� ���Ұ� �ִ� ��쿡�� ��ġ ���� ����
		p = 1;
		for (i = 0; i < n; i++)			// ��� ��� a�� ������ ��ġ �ݺ� ����
			for (j = 1; j <= v; j++)	// 0�� �ƴ� ���� ���� ���ؼ��� �ݺ� ����
				if (a[j].col == i) {	// ������ ���� ���ϴ� ���Ұ� ������ b[]�� ����
					b[p].row = a[j].col;
					b[p].col = a[j].row;
					b[p].value = a[j].value;
					p++;
				}
	}
}

void smPrint(term a[]) {
	int i, j;
	int count = 1;	// term a ���� �� �ε����� ǥ��

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