#include <stdio.h>
#define MAX(a,b) ((a>b)?a:b)
#define MAX_DEGREE 50

typedef struct {             // 구조체 polynomial 정의
	int degree;              // 다항식의 차수를 저장할 변수
	float coef[MAX_DEGREE];  // 다항식의 각 항의 계수를 저장할 1차원 배열
} polynomial;

polynomial zeroP();
polynomial addPoly(polynomial, polynomial);
polynomial multTerm(polynomial, float, int);
polynomial multPoly(polynomial , polynomial );
void printPoly(polynomial);

void main() {
	int i, deg;				// 차수 degree 입력용
	polynomial A; //= { 3,{ 4,3,5,0 } };    // 다항식 A의 초기화
	polynomial B; //= { 4,{ 3,1,0,2,1 } };  // 다항식 B의 초기화
	polynomial C;

	printf("A 다항식 차수(int) 를 입력하세요 : "); scanf("%d", &deg);
	A.degree = deg;
	printf("A 다항식 계수(float)를 높은 차수부터 차례로 입력하세요 \n(예) 3.1 2.4 9.5 [enter] : ");
	for (i=0; i<deg+1; i++)					// 계수는 deg+1 개
		scanf("%f", &A.coef[i]);
	printf("\n A(x) =");  printPoly(A);   // 다항식 A 출력
	printf("\n");

	fflush(stdin);				// 버퍼 비우기 
	printf("B 다항식 차수(int) 를 입력하세요 : "); scanf("%d", &deg);
	B.degree = deg;
	printf("B 다항식 계수(float)를 높은 차수부터 차례로 입력하세요 \n(예) 3.1 2.4 9.5 [enter] : ");
	for (i=0; i<deg+1; i++)					// 계수는 deg+1 개
		scanf("%f", &B.coef[i]);
	printf("\n B(x) =");  printPoly(B);   // 다항식 B 출력

	C = multPoly(A, B);   // 다항식 A, B에 대한 곱셈을 수행하기 위해 multPoly 함수 호출 

	printf("\n ****결과출력****\n");
	printf("\n A(x) =");  printPoly(A);   // 다항식 A 출력
	printf("\n B(x) =");  printPoly(B);   // 다항식 B 출력
	printf("\n C(x) =");  printPoly(C);   // 다항식 C 출력

	getchar();
}

polynomial zeroP() {
	polynomial emptyP = {0, {0,}};
	return emptyP;
}

polynomial addPoly(polynomial A, polynomial B) {
	polynomial C;   // 다항식 덧셈의 결과 다항식을 저장할 polynomial 구조체 변수 선언
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
	return C;    // 다항식 덧셈의 결과 다항식 C를 반환
}

polynomial multTerm(polynomial A, float b, int c) {
	int i;
	polynomial C;   // 다항식 곱셈의 결과 다항식을 저장할 polynomial 구조체 변수 선언

	for(i = 0; i<=A.degree; i++) {
		C.coef[i] = A.coef[i] * b;
	}

	for(i = A.degree + 1; i<=A.degree + c; i++) {
		C.coef[i] = 0;
	}

	C.degree = A.degree + c;

	return C;    // 다항식 곱셈의 결과 다항식 C를 반환
}

polynomial multPoly(polynomial A, polynomial B) {
	int i;
	int m = B.degree;
	polynomial p;	// 매번 곱셈이 일어날때 마다 임시적으로 단항식을 저장할 polynomial 구조체 변수 선언
	polynomial C = zeroP();   // 두 다항식 곱셈의 결과를 저장할 polynomial 구조체 변수 선언
	
	for(i = 0; i <= m; i++) {
		p = multTerm(A, B.coef[i], m - i);
		C = addPoly(C, p);
	}

	return C;    // 두 다항식 곱셈의 결과 다항식 C를 반환
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