#include<stdio.h>

typedef struct { // ��� ���Ҹ� �����ϱ� ���� ����ü term ����
	int row;
	int col;
	int value;
} term;

void mtxToSparse(int mtx[5][15], term sn[]);		// ��� ����� 2���� �迭�� ǥ��.
void smAdd(term a[], term b[], term c[]);			// �� ��� ����� ��.
void printMtx(int a[5][15]);						// ��� ��� ���.
void smPrint(term a[]);								// ��� ����� 2���� �迭 ǥ���� ���.

int main(void)
{
	term sma[50], smb[50], smc[50];
	int amtx[5][15] = {0,},bmtx[5][15] = {0,},cmtx[5][15];
	int i,j;

	// ��� �ʱ�ȭ
	amtx[1][4] = 3; amtx[2][6] = 4; amtx[3][8] = 5;
	bmtx[1][5] = 6; bmtx[2][6] = 7; bmtx[4][9] = 8;

	// ����� 2���� �迭�� ���
	printf("amtx:\n"); printMtx(amtx);
	printf("bmtx:\n"); printMtx(bmtx);

	// �����ķ� ��ȯ�ϰ� ���
	mtxToSparse(amtx, sma); printf("������ sma : \n"); smPrint(sma);
	mtxToSparse(bmtx, smb); printf("������ smb : \n"); smPrint(smb);

	// ������ ������ ���
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
			// (i,j) ��° ���Ҹ� ã�Ƽ� ���
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
	sn[0].row = row;					// �����Ŀ� ���� ����(row, col)�� ù��° �࿡ ����.
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
	sn[0].value = snRowIndex - 1;		// �������� ������ ����(value)�� ù��° �࿡ ����.
}

void smAdd(term a[], term b[], term c[]) {					// �� ������ a, b�� ���Ͽ� c�� ������.

	int aCount = 1;
	int bCount = 1;
	int cCount = 1;

	if (a[0].row == b[0].row && a[0].col == b[0].col) {		// ��� ���� ���̰� ���ƾ� ���ϱ� ������ �����ϴ�. (��������)
		c[0].row = a[0].row;
		c[0].col = a[0].col;
		while(aCount <= a[0].value && bCount <= b[0].value) {	// ���� �� ����� ���Ұ� ���Ҷ����� �ݺ����� �ݺ��Ѵ�.
			if(a[aCount].row < b[bCount].row) {				// row�� a < b, a�� row�� �� ������ a�� ���Ҹ� ����ִ´�.
				c[cCount++] = a[aCount++];
			}
			else if(a[aCount].row > b[bCount].row) {		// row�� a > b, b�� row�� �� ������ b�� ���Ҹ� ����ִ´�.
				c[cCount++] = b[bCount++];
			}
			else if(a[aCount].row = b[bCount].row) {		// row�� a = b, �� row�� ���ٸ� col�� ���غ���.

				if(a[aCount].col < b[bCount].col) {			// col�� a < b, a�� col�� �� ������ a�� ���Ҹ� ����ִ´�.
					c[cCount++] = a[aCount++];
				}
				else if(a[aCount].col > b[bCount].col) {	// col�� a > b, b�� col�� �� ������ b�� ���Ҹ� ����ִ´�.
					c[cCount++] = b[bCount++];
				}
				else if(a[aCount].col == b[bCount].col) {	// col�� a = b, �� ������ ���̸� row�� col�� ��� �����Ƿ� ���ؼ� ����ִ´�,
					c[cCount] = b[bCount];					// row�� col�� ������ a�� b�� �ƹ��ų� �����ؼ� ����ִ´�.
					c[cCount++].value = b[bCount++].value + a[aCount++].value;	// value�� ���� ������ �ٽ� ����ִ´�.
				}
			}
		}

		while(aCount <= a[0].value) {						// a�� �����߿��� �������� ���� ���� ���ҵ��� ��� ����ִ´�.
			c[cCount++] = a[aCount++];
		}
		while(bCount <= b[0].value) {						// b�� �����߿��� �������� ���� ���� ���ҵ��� ��� ����ִ´�.
			c[cCount++] = b[bCount++];
		}
		c[0].value = cCount - 1;							// c�� ������ ������ cCount - 1�� ���ؼ� ����.
	}
	else 
		printf("��� ���� ������ ���ƾ� �մϴ�,\n");		// ���� ����.
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