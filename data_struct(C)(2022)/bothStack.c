/*
 * 双栈的实现
 * */

#include<stdio.h>
typedef int ElemType;
#define MaxSize 12 // 设置栈的最大值
typedef struct Stack{
	ElemType data[MaxSize]; // 数据存储单元
	int top1,top2; // 两个栈顶共用一个数组区域
}Stack;
void InitStack(Stack *L)
{
	// 设置两个空栈;一个为-1一个为最大长度值；
	L->top1 = -1; 
	L->top2 = MaxSize;
}
void Push(Stack *L,int i)
{
	int m;
	for(m = 1;m < i;m++)
	{
		if(m % 2 != 0)
		{
			L->data[++L->top1] = m;
		}
		if(L->top1 == L->top2 - 1)
		{
			printf("full\n");
			return;
		}
	}
	for(m=1;m<i;m++)
	{
		if(m % 2 == 0)
		{
			L->data[--L->top2] = m;
		}
		if(L->top1 == L->top2 - 1)
		{
			printf("full\n");
			return;
		}
	}
}
void Pop(Stack *L,int i)
{
	if(L->top1 == -1 && i == 1)
	{
		printf("stack1:empty\n");
		return;
	}
	else if(L->top2 == MaxSize && i == 2)
	{
		printf("stack2:empty\n");
		return;
	}
	if(i == 1)
		printf("%d\n",L->data[L->top1--]);
	else printf("%d\n",L->data[L->top2++]);
}
void OutStack(Stack *L ,int i)
{
	if(i == 1)
	{
		printf("stack1:");
		while(L->top1 != -1)
		{
			printf("%d ",L->data[L->top1--]);
		}
		printf("\n");
	}
	else{
		printf("stack2:");
		while(L->top2 != MaxSize)
			printf("%d ",L->data[L->top2++]);
		printf("\n");
	}
}

int main()
{
	Stack p;
	InitStack(&p);
	Pop(&p,1);
	Pop(&p,2);
	int i;
	scanf("%d",&i);
	if(i<=1)
	{
		printf("error\n");
		printf("stack1:empty\n");
		printf("stack2:empty\n");
		return 0;
	}
	Push(&p,i);
	Pop(&p,1);
	Pop(&p,2);
	OutStack(&p,1);
	OutStack(&p,2);
	return 0;
}
