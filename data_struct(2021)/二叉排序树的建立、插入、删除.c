#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef int keytype;
typedef struct node {
	keytype data;
	struct node* left, * right;
}Bitree;
Bitree* F = NULL;
//二叉树的递归查找算法
Bitree* find(Bitree* T, keytype x) {
	if (T == NULL)
		return NULL;
	if (T->data == x)
		return T;
	else
	{
		F = T;
		if (T->data > x)
			find(T->left, x);
		else
			find(T->right, x);
	}
}
//调用find函数插入节点
Bitree* insertbst(Bitree* T, keytype key) {
	Bitree* C, * s;
	C = find(T, key);
	if (C == NULL)
	{
		s = (Bitree*)malloc(sizeof(Bitree));
		s->data = key;
		s->left = s->right = NULL;
		if (F == NULL)
			T = s;
		else if (key < F->data)
			F->left = s;
		else
			F->right = s;
	}
	return T;
}
//调用函数insertbst进行二叉树的创建
Bitree* creatbst() {
	keytype key;
	Bitree* T = NULL;
	scanf("%d", &key);
	while (key != -1) {
		T = insertbst(T, key);
		scanf("%d", &key);
	}
	return T;
}
//中序遍历二叉树 看是否有序
void InOrder(Bitree* bt) {
	if (bt != NULL)
	{
		InOrder(bt->left);
		printf("%d ", bt->data);
		InOrder(bt->right);
	}
}
//调用函数find删除结点
int deletebst(Bitree* T, keytype key) {
	Bitree* p, * s, * q;
	s = NULL;
	p = find(T, key);
	if (!p) {
		printf("不存在\n");
		return 0;
	}
	if (p->left == NULL) {
		q = p;
		p = p->right;
	}
	else if (p->right == NULL) {
		q = p;
		p = p->left;
	}
	else
	{
		q = p;
		s = p->left;
		while (s->right != NULL) {
			q = s;
			s = s->right;
		}
		if (q != p)
			q->right = s->left;
		else
			q->left = s->left;
		q = s;
		p->data = s->data;
	}
	if (F == NULL) T = p;
	else if (q != s)
		if (key < F->data)
			F->left = p;
		else F->right = p;
	free(q);
	return 1;
}
int main() {
	Bitree* T;
	int x;
	T = (Bitree*)malloc(sizeof(Bitree));
	printf("输入序列：");
	T = creatbst();
	printf("输出的中序遍历序列应为：");
	InOrder(T);
	printf("\n输入要删除的整数：");
	scanf("%d", &x);
	while (1) {
		if (x == -1) break;
		if (T ->left== NULL) 
		{ printf("二叉树为空"); break; }
		deletebst(T, x);
		printf("输出删除后的中序遍历序列为：");
		InOrder(T); 
		printf("\n输入要删除的整数：");
		scanf("%d", &x);
	}
	system("pause");
	return 0;
}