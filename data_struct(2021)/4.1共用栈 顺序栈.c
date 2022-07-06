#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 12
typedef int ElemType;
typedef struct
{
	int top[2];
	int size;
	ElemType* base;
}sqstack;
void initial(sqstack* head)
{
	head->base = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
	head->top[0] = 0;
	head->top[1] = MAXSIZE - 1;
	head->size = MAXSIZE;
}
int emptysq(sqstack* sq,int n)
{
	if (n == 1)
	{
		if (sq->top[0] == 0)
			return 0;
		else
			return 1;
	}
	else if (n == 2)
	{
		if (sq->top[1] == MAXSIZE - 1)
			return 0;
		else
			return 1;
	}
}
int push(sqstack* sq,int n,ElemType x)
{
	if (sq->top[0] > sq->top[1]) {
		printf("full\n");
		return 0;
	}
	sq->base[sq->top[n - 1]] = x;
	if (n == 1)
		sq->top[0]++;
	else
		sq->top[1]--;
	return 1;
}
int list(sqstack* sq)
{
	int i;
	printf("stack1: ");
	if (!emptysq(sq,1)) {
		printf("empty");
	}
	for (i = sq->top[0] - 1; i >= 0; i--)
	{
		printf("%d ", sq->base[i]);
	}
	printf("\nstack2: ");
	if (!emptysq(sq,2))
	{
		printf("empty");
	}
	for (i = sq->top[1] + 1; i <MAXSIZE; i++)
	{
		printf("%d ", sq->base[i]);
     }
	printf("\n");
	return 1;
}
int pop(sqstack* sq, int n, ElemType* e)      //n为栈1 和栈2 的表示 
{
	if (!emptysq(sq,n))
	{
		printf("stack%d: empty\n", n);
		return 0;
    }
	if (n == 1)
		sq->top[0]--;
	else
		sq->top[1]++;                  //栈顶指针向前移或向后移
	*e = sq->base[sq->top[n - 1]];
	return 1;
}
int main()
{
	int n, i;
	ElemType e;
	sqstack* sq;
	sq = (sqstack*)malloc(sizeof(sqstack));
	initial(sq);
	scanf("%d", &n);
	if (n < 0)
		n = -n;
	list(sq);
	for (i = 1; i < n; i++)
	{
		if (i % 2 != 0)
		 if (!push(sq, 1, i))
			break;
	}
	for (i = 1; i < n; i++)
	{
		if (i % 2 == 0)
		if (!push(sq, 2, i))
			break;
	}
	if (pop(sq, 1, &e))
		printf("%d\n", e);
	if (pop(sq, 2, &e))
		printf("%d\n", e);
	list(sq);
	system("pause");
	return 0;
}