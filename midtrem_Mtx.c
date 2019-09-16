#include<stdio.h>

typedef struct { // 행렬 원소를 저장하기 위한 구조체 term 정의
	int row;
	int col;
	int value;
} term;

void mtxToSparse(int mtx[5][15], term sn[]);		// 희소 행렬을 2차원 배열로 표현.
void smAdd(term a[], term b[], term c[]);			// 두 희소 행렬의 합.
void printMtx(int a[5][15]);						// 희소 행렬 출력.
void smPrint(term a[]);								// 희소 행렬의 2차원 배열 표현을 출력.

int main(void)
{
	term sma[50], smb[50], smc[50];
	int amtx[5][15] = {0,},bmtx[5][15] = {0,},cmtx[5][15];
	int i,j;

	// 행렬 초기화
	amtx[1][4] = 3; amtx[2][6] = 4; amtx[3][8] = 5;
	bmtx[1][5] = 6; bmtx[2][6] = 7; bmtx[4][9] = 8;

	// 행렬을 2차원 배열로 출력
	printf("amtx:\n"); printMtx(amtx);
	printf("bmtx:\n"); printMtx(bmtx);

	// 희소행렬로 변환하고 출력
	mtxToSparse(amtx, sma); printf("희소행렬 sma : \n"); smPrint(sma);
	mtxToSparse(bmtx, smb); printf("희소행렬 smb : \n"); smPrint(smb);

	// 희소행렬 덧셈후 출력
	smAdd(sma, smb, smc);
	printf("smc = sma + smb : \n");
	smPrint(smc);

	return 0;
}

void smPrint(term a[])
{
	int row, col, val, i,j,k, ijvalue;
	row = a[0].row;
	col = a[0].col;
	val = a[0].value;

	for (i=0; i<row; i++) {
		for (j=0; j<col; j++) {
			// (i,j) 번째 원소를 찾아서 출력
			ijvalue = 0;
			for (k=1; k<=val; k++) {
				if (a[k].row==i && a[k].col==j ) {
					ijvalue = a[k].value;
					break;
				}
			}
			printf("%5d", ijvalue);
		}
		printf("\n");
	}
	printf("\n\n");
}

void mtxToSparse(int mtx[5][15], term sn[])
{
	int row = 5;
	int col = 15;
	int i, j, snRowIndex = 1;
	int rowCount = 0, colCount = 0;
	sn[0].row = row;					// 희소행렬에 대한 정보(row, col)를 첫번째 행에 저장.
	sn[0].col = col;

	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			if(mtx[i][j]) {
				sn[snRowIndex].row = i;
				sn[snRowIndex].col = j;
				sn[snRowIndex].value = mtx[i][j];
				snRowIndex++;
			}
		}
	}
	sn[0].value = snRowIndex - 1;		// 희소행렬의 원소의 개수(value)를 첫번째 행에 저장.
}

void smAdd(term a[], term b[], term c[]) {					// 두 희소행렬 a, b를 합하여 c를 만들자.

	int aCount = 1;
	int bCount = 1;
	int cCount = 1;

	if (a[0].row == b[0].row && a[0].col == b[0].col) {		// 행과 열의 길이가 같아야 더하기 연산이 가능하다. (오류검출)
		c[0].row = a[0].row;
		c[0].col = a[0].col;
		while(aCount <= a[0].value && bCount <= b[0].value) {	// 둘중 한 행렬의 원소가 다할때까지 반복문을 반복한다.
			if(a[aCount].row < b[bCount].row) {				// row비교 a < b, a의 row가 더 작으면 a의 원소를 집어넣는다.
				c[cCount++] = a[aCount++];
			}
			else if(a[aCount].row > b[bCount].row) {		// row비교 a > b, b의 row가 더 작으면 b의 원소를 집어넣는다.
				c[cCount++] = b[bCount++];
			}
			else if(a[aCount].row = b[bCount].row) {		// row비교 a = b, 두 row가 같다면 col을 비교해보자.

				if(a[aCount].col < b[bCount].col) {			// col비교 a < b, a의 col이 더 작으면 a의 원소를 집어넣는다.
					c[cCount++] = a[aCount++];
				}
				else if(a[aCount].col > b[bCount].col) {	// col비교 a > b, b의 col이 더 작으면 b의 원소를 집어넣는다.
					c[cCount++] = b[bCount++];
				}
				else if(a[aCount].col == b[bCount].col) {	// col비교 a = b, 이 조건이 참이면 row와 col이 모두 같으므로 더해서 집어넣는다,
					c[cCount] = b[bCount];					// row와 col의 대입은 a와 b중 아무거나 복사해서 집어넣는다.
					c[cCount++].value = b[bCount++].value + a[aCount++].value;	// value는 더한 값으로 다시 집어넣는다.
				}
			}
		}

		while(aCount <= a[0].value) {						// a의 원소중에서 아직까지 들어가지 못한 원소들을 모두 집어넣는다.
			c[cCount++] = a[aCount++];
		}
		while(bCount <= b[0].value) {						// b의 원소중에서 아직까지 들어가지 못한 원소들을 모두 집어넣는다.
			c[cCount++] = b[bCount++];
		}
		c[0].value = cCount - 1;							// c의 원소의 갯수는 cCount - 1로 구해서 삽입.
	}
	else 
		printf("행과 열의 갯수가 같아야 합니다,\n");		// 오류 검출.
}

void printMtx(int a[5][15])
{
	int i, j;
	int row = 5;
	int col = 15;

	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			printf("%5d", a[i][j]);
		}
		printf("\n");
	}
}