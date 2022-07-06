#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef int keytype;
typedef struct node
{
	keytype data;
	struct node* left, * right;
}Bitree;				//二叉排序树类型定义
Bitree* F = NULL;			//存放双亲节点指针，用于插入和删除
Bitree* searchbst(Bitree* T, keytype key)
{
	Bitree* C = NULL;		//存放找到结点的指针
	while (T != NULL)
		if (T->data == key)	//找到
		{
			C = T; break;
		}
		else if (key < T->data)
		{
			F = T; T = T->left;		//到左子树上查找
		}
		else
		{
			F = T; T = T->right;	//到右子树上查找
		}
	return C;
}
Bitree* insertbst(Bitree* T, keytype key)
{
	Bitree* C, * s;
	C = searchbst(T, key);	//查找元素是否存在
	if (C == NULL)		//不存在，则插入
	{
		s = (Bitree*)malloc(sizeof(Bitree));
		s->data = key;
		s->left = s->right = NULL;
		if (F == NULL)		//插入根节点
			T = s;
		else if (key < F->data)		//插入叶子结点
		{
			F->left = s;
		}
		else
		{
			F->right = s;
		}
	}
	return T;
}
Bitree* creatbst()
{
	keytype key;
	Bitree* T = NULL;	    //创建空的根节点
	printf("请输入序列,并以-1结尾:");
	scanf("%d", &key);	    //输入元素并以-1结尾
	while (key != -1)
	{
		T = insertbst(T, key);	//插入新元素
		scanf("%d", &key);
	}
	return T;
}
Bitree* deletebst(Bitree* T, keytype key)
{
	Bitree* p, * s, * q;
	s = NULL;
	p = searchbst(T, key);	//寻找要删除的结点
	if (!p)
	{ 
		printf("没有找到此数字\n");
	    return T; 
	}
	if (p->left == NULL)	//若该节点左子树为空，重接右子树
	{
		q = p; 
		p = p->right;
	}
	else if (p->right == NULL)	//若该节点右子树为空，重接左子树
	{
		q = p; 
		p = p->left;
	}
	else						//或者左右子树都不为空
	{
		q = p; 
		s = p->left;		//找到p左子树的最右下结点s
		while (s->right != NULL)
		{
			q = s; 
			s = s->right;
		}
		if (q != p)
			q->right = s->left;	//重接q的左子树
		else 
			q->left = s->left;			//重接q的右子树
		q = s; 
		p->data = s->data;		//用s结点的值替换q结点的值
	}
	if (F == NULL)
		T = p;				//若删除的是根节点，用p代替根节点
	else if (q != s)					//左子树或右子树为空的结点，p重新连接
		if (key < F->data)
			F->left = p;
		else
			F->right = p;
	free(q);							//释放不用的结点
	return T;							//返回根节点
}
void InOrder(Bitree* T)					//中序遍历
{
	if (T != NULL)
	{
		InOrder(T->left);
		printf("%d ", T->data);
		InOrder(T->right);
	}
}
int main()
{
	keytype key;
	Bitree* A = NULL;
	A = creatbst();						//创建二叉树
	printf("中序遍历为:\n");			//中序遍历，若空则输出空
	if (A == NULL)
		printf("空");
	else
		InOrder(A);
	printf("\n");
	printf("输入需要删除的数字，退出输入-1:\n");
	while (1)
	{
		scanf("%d", &key);
		if (key == -1)break;			//输入-1则退出
		F = NULL;
		A = deletebst(A, key);			//删除输入的元素
		printf("中序遍历为:\n");		//中序遍历
		if (A == NULL)
		{
			printf("空");
			break;
		}
		else
			InOrder(A);
		printf("\n");
		printf("继续删除请输入数字，退出输入-1:\n");
	}
	printf("\n");
	system("pause");
	return 0;
}