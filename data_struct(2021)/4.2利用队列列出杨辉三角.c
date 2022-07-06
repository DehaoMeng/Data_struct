#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 10
typedef int Elemtype;
typedef struct
{
	Elemtype* base;
	int front;
	int rear;
	int length;
}cqueue;
void initial(cqueue* cq)
{
	cq->base = (Elemtype*)malloc(sizeof(Elemtype) * MAXSIZE);
	cq->front = cq->rear=0;
	cq->length = 0;
}
int push(cqueue* cq, Elemtype x)
{
	if (cq->length >= MAXSIZE)
		return 0;
	cq->base[cq->rear] = x;
	cq->rear = (cq->rear + 1) % MAXSIZE;
	cq->length++;
	return 1;
}
int pop(cqueue* cq, Elemtype* e)
{
	if (cq->length == 0)
		return 0;
	*e = cq->base[cq->front];
	cq->front = (cq->front + 1) % MAXSIZE;
	cq->length--;
	return 1;
}
int list(cqueue* cq) 
{
	int i;
	i = cq->front;
	while (i != cq->rear)
	{
		printf("%d ", cq->base[i]);
		i = (i + 1) % MAXSIZE;
	}
	printf("\n");
}
int main()
{
	cqueue* cq;
	int n, i,j;
	cq = (cqueue*)malloc(sizeof(cqueue));
	initial(cq);
	scanf("%d", &n);
	Elemtype e;
	for (i = 0; i < n; i++)             //¿ØÖÆÐÐÊýn
	{
		push(cq, 1);
		for (j = 1; j < i; j++)                 //    1
		{                                      //     1 1  
			pop(cq, &e);                        //     1 1 2    //  1 2 // 1 2 1////    2 1 1 3//  1 1 3 3//  1 3 3 1//
			push(cq, e + cq->base[cq->front]);
		}
		pop(cq, &e);
		push(cq, e);
		if (cq->length == MAXSIZE)
		{
			printf("FULL\n");
			break;
		}
		list(cq);
	}
	system("pause");
	return 0;
}