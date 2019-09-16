#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#define MAX_VERTEX 10
#define FALSE 0
#define TRUE 1

// �׷����� ���� ���� ����Ʈ�� ��� ���� ����
typedef struct graphNode {
	int vertex;
	struct graphNode* link;
} graphNode;

typedef struct graphType {
	int n;								// ���� ����
	graphNode* adjList_H[MAX_VERTEX];	// ������ ���� ���� ����Ʈ�� ��� ��� �迭
	int visited[MAX_VERTEX];			// ������ ���� �湮 ǥ�ø� ���� �迭
} graphType;

// << ���� (5�忡�� ������ ���� ����Ʈ�� �̿��� ���� ���� ����:[���� 5-2]�� 05~43��� ����)
typedef int element;

typedef struct stackNode {
	int data;
	struct stackNode *link;
} stackNode;

stackNode* top;

// ������ �������� Ȯ���ϴ� ����
int isEmpty() {
	if (top == NULL) return 1;
	else return 0;
}

void push(int item) {
	stackNode* temp = (stackNode *)malloc(sizeof(stackNode));
	temp->data = item;
	temp->link = top;
	top = temp;
}

int pop() {
	int item;
	stackNode* temp = top;

	if (isEmpty()) {
		printf("\n\n Stack is empty !\n");
		return 0;
	}
	else {
		item = temp->data;
		top = temp->link;
		free(temp);
		return item;
	}
} // ���� >>

// ���� �켱 Ž���� ���� �ʱ� ���� �׷����� �����ϴ� ����
void createGraph(graphType* g) {
	int v;
	g->n = 0;							// �׷����� ���� ������ 0���� �ʱ�ȭ
	for (v = 0; v<MAX_VERTEX; v++) {
		g->visited[v] = FALSE;			// �׷����� ������ ���� �迭 visited�� FALSE�� �ʱ�ȭ
		g->adjList_H[v] = NULL;			// ���� ����Ʈ�� ���� ��� ��� �迭�� NULL�� �ʱ�ȭ
	}
}

// �׷��� g�� ���� v�� �����ϴ� ���� : [���� 8-2]�� 26~32��� ����
void insertVertex(graphType* g, int v) {
	if (((g->n) + 1)>MAX_VERTEX) {
		printf("\n �׷��� ������ ������ �ʰ��Ͽ����ϴ�!");
		return;
	}
	g->n++;
}

// �׷��� g�� ���� (u, v)�� �����ϴ� ���� : [���� 8-2]�� 35~47��� ����
void insertEdge(graphType* g, int u, int v) {
	graphNode* node;
	if (u >= g->n || v >= g->n) {
		printf("\n �׷����� ���� �����Դϴ�!");
		return;
	}
	node = (graphNode *)malloc(sizeof(graphNode));
	node->vertex = v;
	node->link = g->adjList_H[u];
	g->adjList_H[u] = node;
}

// �׷��� g�� �� ������ ���� ���� ����Ʈ�� ����ϴ� ���� : [���� 8-2]�� 50~61��� ����
void print_adjList(graphType* g) {
	int i;
	graphNode* p;
	for (i = 0; i<g->n; i++) {
		printf("\n\t\t����%c�� ���� ����Ʈ", i + 65);
		p = g->adjList_H[i];
		while (p) {
			printf(" -> %c", p->vertex + 65);
			p = p->link;
		}
	}
}

// �׷��� g���� ���� v�� ���� ���� �켱 Ž�� ����
void DFS_adjList(graphType* g, int v) {	
	graphNode* w;
	top = NULL;					// ������ top ����
	push(v); 				// ���� �켱 Ž���� �����ϴ� ���� v�� ���ÿ� push
	g->visited[v] = TRUE;		// ���� v�� �湮�����Ƿ� �ش� �迭 ���� TRUE�� ���� 
	printf(" %c", v + 65);

	// ������ ������ �ƴ� ���� ���� �켱 Ž�� �ݺ�
	while (!isEmpty()) {
		v = pop();
		w = g->adjList_H[v];
		// ���� ������ �ִ� ���� ����
		while (w) {
			// ���� ���� w�� �湮���� ���� ��� 
			if (!g->visited[w->vertex]) { 
				if(isEmpty())  push(v); //** ����v�� ���ƿ� ��츦 ���� �ٽ� push�Ͽ� ����
				push(w->vertex); 				// ���� ���� w�� ���ÿ� push
				g->visited[w->vertex] = TRUE;	// ���� w�� ���� �迭 ���� TRUE�� ����
				printf(" %c", w->vertex + 65);	// ���� 0~6�� A~G�� �ٲپ ���		
				v = w->vertex;
				w = g->adjList_H[v];
			}
			// ���� ���� w�� �̹� �湮�� ���
			else w = w->link;
		}//while(w)		
	} //������ �����̸� ���� �켱 Ž�� ����
}

void main() {
	int i;
	graphType *G9;
	G9 = (graphType *)malloc(sizeof(graphType));
	createGraph(G9);

	// �׷��� G9 ����
	for (i = 0; i<7; i++)
		insertVertex(G9, i);
	insertEdge(G9, 0, 2);
	insertEdge(G9, 0, 1);
	insertEdge(G9, 1, 4);
	insertEdge(G9, 1, 3);
	insertEdge(G9, 1, 0);
	insertEdge(G9, 2, 4);
	insertEdge(G9, 2, 0);
	insertEdge(G9, 3, 6);
	insertEdge(G9, 3, 1);
	insertEdge(G9, 4, 6);
	insertEdge(G9, 4, 2);
	insertEdge(G9, 4, 1);
	insertEdge(G9, 5, 6);
	insertEdge(G9, 6, 5);
	insertEdge(G9, 6, 4);
	insertEdge(G9, 6, 3);      
	printf("\n G9�� ���� ����Ʈ ");
	print_adjList(G9);

	printf("\n\n///////////////\n\n���� �켱 Ž�� >> ");
	DFS_adjList(G9, 0);	// 0�� ������ ���� A���� ���� �켱 Ž�� ����

	getchar();
}