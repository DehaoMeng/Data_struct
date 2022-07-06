#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
#define M1 7
#define N1 7
typedef int Elemtype;
typedef struct
{
	int row;
	int col;
	Elemtype e;
}tupletype;
typedef struct
{
	int rownum;
	int colnum;
	int nznum;
	tupletype data[MAXSIZE];
}table;
int initial(table* M)
{
	M->rownum = M1;
	M->colnum = N1;
	M->nznum = 0;
}
int table_scanf(table* M)
{
	int i, j, data;
	int k = 0;
	scanf("%d %d %d", &i, &j, &data);
	while (i!=-1)
	{
		M->data[k].row = i-1;
		M->data[k].col = j-1;
		M->data[k].e = data;
		k++;
		M->nznum++;
		scanf("%d %d %d", &i, &j, &data);
	}
	return 1;
}
int trans1(table* M, table* T)
{
	int c, b, q = 0;
	T->rownum = M->colnum;
	T->colnum = M->rownum;
	T->nznum = M->nznum;
	if (T->nznum != 0)
	{
		for (c = 0; c < M->colnum; c++)
		{
			for (b = 0; b < M->nznum; b++) {
				if (M->data[b].col == c)
				{
					T->data[q].row = M->data[b].col;
					T->data[q].col = M->data[b].row;
					T->data[q].e = M->data[b].e;
					q++;
				}
			}
		}
	}
	return 1;
}
int trans2(table* M, table* T)
{
	int i, q, c, num[100], cpot[100];
	T->rownum = M->colnum;
	T->colnum = M->rownum;
	T->nznum = M->nznum;
	for (i = 0; i < M->colnum; i++)
		num[i] = 0;
	for (i = 0; i < M->nznum; i++)
		num[M->data[i].col]++;
	cpot[0] = 0;
	for (i = 1; i < M->colnum; i++)
		cpot[i] = cpot[i - 1] + num[i - 1];
	for (i = 0; i < M->nznum; i++)
	{
		c = M->data[i].col;
		q = cpot[c];
		T->data[q].row = M->data[i].col;
		T->data[q].col = M->data[i].row;
		T->data[q].e = M->data[i].e;
		cpot[c]++;
	}
	return 1;
}
int list(table* M)
{
	int i, j, k,e;
	for (i = 0; i < M->rownum; i++)
	{
		for (j = 0; j < M->colnum; j++)
		{
			e = 0;
			for (k = 0; k < M->nznum; k++)
			{
				if (i == M->data[k].row && j == M->data[k].col)
				{
					e = M->data[k].e;
					break;
				}
			}
			printf("%4d", e);
		}
		printf("\n");
	}
	return 1;
}
int main()
{
	table *M,  *T;
	M = (table*)malloc(sizeof(table));
	T = (table*)malloc(sizeof(table));
	initial(M);
	initial(T);
	table_scanf(M);
	printf("转置前\n");
	list(M);
	trans1(M, T);
	printf("转置后\n");
	list(T);
	system("pause");
	return 0;
}