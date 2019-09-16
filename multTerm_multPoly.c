#include <stdio.h>
#define MAX(a,b) ((a>b)?a:b)
#define MAX_DEGREE 50

typedef struct {             // ����ü polynomial ����
	int degree;              // ���׽��� ������ ������ ����
	float coef[MAX_DEGREE];  // ���׽��� �� ���� ����� ������ 1���� �迭
} polynomial;

polynomial zeroP();
polynomial addPoly(polynomial, polynomial);
polynomial multTerm(polynomial, float, int);
polynomial multPoly(polynomial , polynomial );
void printPoly(polynomial);

void main() {
	int i, deg;				// ���� degree �Է¿�
	polynomial A; //= { 3,{ 4,3,5,0 } };    // ���׽� A�� �ʱ�ȭ
	polynomial B; //= { 4,{ 3,1,0,2,1 } };  // ���׽� B�� �ʱ�ȭ
	polynomial C;

	printf("A ���׽� ����(int) �� �Է��ϼ��� : "); scanf("%d", &deg);
	A.degree = deg;
	printf("A ���׽� ���(float)�� ���� �������� ���ʷ� �Է��ϼ��� \n(��) 3.1 2.4 9.5 [enter] : ");
	for (i=0; i<deg+1; i++)					// ����� deg+1 ��
		scanf("%f", &A.coef[i]);
	printf("\n A(x) =");  printPoly(A);   // ���׽� A ���
	printf("\n");

	fflush(stdin);				// ���� ���� 
	printf("B ���׽� ����(int) �� �Է��ϼ��� : "); scanf("%d", &deg);
	B.degree = deg;
	printf("B ���׽� ���(float)�� ���� �������� ���ʷ� �Է��ϼ��� \n(��) 3.1 2.4 9.5 [enter] : ");
	for (i=0; i<deg+1; i++)					// ����� deg+1 ��
		scanf("%f", &B.coef[i]);
	printf("\n B(x) =");  printPoly(B);   // ���׽� B ���

	C = multPoly(A, B);   // ���׽� A, B�� ���� ������ �����ϱ� ���� multPoly �Լ� ȣ�� 

	printf("\n ****������****\n");
	printf("\n A(x) =");  printPoly(A);   // ���׽� A ���
	printf("\n B(x) =");  printPoly(B);   // ���׽� B ���
	printf("\n C(x) =");  printPoly(C);   // ���׽� C ���

	getchar();
}

polynomial zeroP() {
	polynomial emptyP = {0, {0,}};
	return emptyP;
}

polynomial addPoly(polynomial A, polynomial B) {
	polynomial C;   // ���׽� ������ ��� ���׽��� ������ polynomial ����ü ���� ����
	int A_index = 0, B_index = 0, C_index = 0;
	int A_degree = A.degree, B_degree = B.degree;
	C.degree = MAX(A.degree, B.degree);

	while (A_index <= A.degree && B_index <= B.degree) {
		if (A_degree > B_degree) {
			C.coef[C_index++] = A.coef[A_index++];
			A_degree--;
		}
		else if (A_degree == B_degree) {
			C.coef[C_index++] = A.coef[A_index++] + B.coef[B_index++];
			A_degree--;
			B_degree--;
		}
		else {
			C.coef[C_index++] = B.coef[B_index++];
			B_degree--;
		}
	}
	return C;    // ���׽� ������ ��� ���׽� C�� ��ȯ
}

polynomial multTerm(polynomial A, float b, int c) {
	int i;
	polynomial C;   // ���׽� ������ ��� ���׽��� ������ polynomial ����ü ���� ����

	for(i = 0; i<=A.degree; i++) {
		C.coef[i] = A.coef[i] * b;
	}

	for(i = A.degree + 1; i<=A.degree + c; i++) {
		C.coef[i] = 0;
	}

	C.degree = A.degree + c;

	return C;    // ���׽� ������ ��� ���׽� C�� ��ȯ
}

polynomial multPoly(polynomial A, polynomial B) {
	int i;
	int m = B.degree;
	polynomial p;	// �Ź� ������ �Ͼ�� ���� �ӽ������� ���׽��� ������ polynomial ����ü ���� ����
	polynomial C = zeroP();   // �� ���׽� ������ ����� ������ polynomial ����ü ���� ����
	
	for(i = 0; i <= m; i++) {
		p = multTerm(A, B.coef[i], m - i);
		C = addPoly(C, p);
	}

	return C;    // �� ���׽� ������ ��� ���׽� C�� ��ȯ
}

void printPoly(polynomial P) {
	int i, degree;
	degree = P.degree;

	for (i = 0; i <= P.degree; i++) {
		printf("%3.0fx^%d", P.coef[i], degree--);
		if (i < P.degree) printf(" +");
	}
	printf("\n");
}