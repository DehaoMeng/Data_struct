#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef char Elemtype;
typedef struct node
{
	Elemtype data;
	struct node* lchild, * rchild;
}BitTree;
BitTree* crebitree(void)
{
	BitTree* bt;
	Elemtype x;
	x = getchar();
	if (x == '#')
		bt = NULL;
	else 
	{
		bt = (BitTree*)malloc(sizeof(BitTree));
		bt->data = x;
		bt->lchild = crebitree();
		bt->rchild = crebitree();
	}
	return bt;
}
void InOrder(BitTree* bt)
{
	if (bt != NULL)
	{
		InOrder(bt->lchild);
		printf("%c", bt->data);
		InOrder(bt->rchild);
	}
}
void PostOrder(BitTree* bt)
{
	if (bt != NULL)
	{
		PostOrder(bt->lchild);
		PostOrder(bt->rchild);
		printf("%c", bt->data);
	}
}
int hightree(BitTree* bt)
{
	int h, h1, h2;
	if (bt == NULL)
		h = 0;
	else
	{
		h1 = hightree(bt->lchild);
		h2 = hightree(bt->rchild);
		h = (h1 > h2 ? h1 : h2) + 1;
	}
	return h;
}
int leafcount(BitTree* bt)
{
	static int n = 0;
	if (bt != NULL)
	{
		if (bt->lchild == NULL && bt->rchild == NULL)
		{
			n++;
			//printf("%c", bt->data);
		}
		leafcount(bt->lchild);
		leafcount(bt->rchild);
	}
	return n;
}
void exchangetree(BitTree* bt)
{
	BitTree* t;
	if (bt != NULL)
	{
		if (bt->lchild != NULL || bt->rchild != NULL)
		{
			t = bt->lchild;
			bt->lchild = bt->rchild;
			bt->rchild = t;
		}
		exchangetree(bt->lchild);
		exchangetree(bt->rchild);
	}
}
int levelwidth(BitTree* bt, int level)
{
	if (!bt) return 0;
	else
	{
		if (level == 1) return 1;
		level = levelwidth(bt->lchild, level - 1) + levelwidth(bt->rchild, level - 1);
	}
	return level;
}
int width(BitTree* bt)
{
	int wid=0, i;
	int w[100];
	for (i = 0; i < 100; i++)
		w[i] = 0;
	if (!bt) wid = 0;
	else
	{
		for (i = 0; i <= hightree(bt); i++)
			w[i] = levelwidth(bt, i + 1);
	}
	i = 0;
	while (w[i])
	{
		if (w[i] > wid)
			wid = w[i];
		i++;
	}
	return wid;
}
int main()
{
	BitTree* bt;
	bt = (BitTree*)malloc(sizeof(BitTree));
	int high,number,wid;
	printf("���������ַ�����������������");
	bt=crebitree();
	printf("�����������ӦΪ:");
	InOrder(bt);
	printf("\n�����������ӦΪ:");
	PostOrder(bt);
	high = hightree(bt);
	printf("\n�����������ӦΪ:%d",high);
	wid = width(bt);
	printf("\n�������Ŀ��ӦΪ��%d", wid);
	number = leafcount(bt);
	printf("\n��������Ҷ����ĿӦΪ:%d",number);
	exchangetree(bt);
	printf("\n������Ķ����������������:");
	InOrder(bt);
	printf("\n");
	system("pause");
	return 0;
}