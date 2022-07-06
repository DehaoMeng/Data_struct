#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef int keytype;
typedef struct node
{
	keytype data;
	struct node* left, * right;
}Bitree;				//�������������Ͷ���
Bitree* F = NULL;			//���˫�׽ڵ�ָ�룬���ڲ����ɾ��
Bitree* searchbst(Bitree* T, keytype key)
{
	Bitree* C = NULL;		//����ҵ�����ָ��
	while (T != NULL)
		if (T->data == key)	//�ҵ�
		{
			C = T; break;
		}
		else if (key < T->data)
		{
			F = T; T = T->left;		//���������ϲ���
		}
		else
		{
			F = T; T = T->right;	//���������ϲ���
		}
	return C;
}
Bitree* insertbst(Bitree* T, keytype key)
{
	Bitree* C, * s;
	C = searchbst(T, key);	//����Ԫ���Ƿ����
	if (C == NULL)		//�����ڣ������
	{
		s = (Bitree*)malloc(sizeof(Bitree));
		s->data = key;
		s->left = s->right = NULL;
		if (F == NULL)		//������ڵ�
			T = s;
		else if (key < F->data)		//����Ҷ�ӽ��
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
	Bitree* T = NULL;	    //�����յĸ��ڵ�
	printf("����������,����-1��β:");
	scanf("%d", &key);	    //����Ԫ�ز���-1��β
	while (key != -1)
	{
		T = insertbst(T, key);	//������Ԫ��
		scanf("%d", &key);
	}
	return T;
}
Bitree* deletebst(Bitree* T, keytype key)
{
	Bitree* p, * s, * q;
	s = NULL;
	p = searchbst(T, key);	//Ѱ��Ҫɾ���Ľ��
	if (!p)
	{ 
		printf("û���ҵ�������\n");
	    return T; 
	}
	if (p->left == NULL)	//���ýڵ�������Ϊ�գ��ؽ�������
	{
		q = p; 
		p = p->right;
	}
	else if (p->right == NULL)	//���ýڵ�������Ϊ�գ��ؽ�������
	{
		q = p; 
		p = p->left;
	}
	else						//����������������Ϊ��
	{
		q = p; 
		s = p->left;		//�ҵ�p�������������½��s
		while (s->right != NULL)
		{
			q = s; 
			s = s->right;
		}
		if (q != p)
			q->right = s->left;	//�ؽ�q��������
		else 
			q->left = s->left;			//�ؽ�q��������
		q = s; 
		p->data = s->data;		//��s����ֵ�滻q����ֵ
	}
	if (F == NULL)
		T = p;				//��ɾ�����Ǹ��ڵ㣬��p������ڵ�
	else if (q != s)					//��������������Ϊ�յĽ�㣬p��������
		if (key < F->data)
			F->left = p;
		else
			F->right = p;
	free(q);							//�ͷŲ��õĽ��
	return T;							//���ظ��ڵ�
}
void InOrder(Bitree* T)					//�������
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
	A = creatbst();						//����������
	printf("�������Ϊ:\n");			//��������������������
	if (A == NULL)
		printf("��");
	else
		InOrder(A);
	printf("\n");
	printf("������Ҫɾ�������֣��˳�����-1:\n");
	while (1)
	{
		scanf("%d", &key);
		if (key == -1)break;			//����-1���˳�
		F = NULL;
		A = deletebst(A, key);			//ɾ�������Ԫ��
		printf("�������Ϊ:\n");		//�������
		if (A == NULL)
		{
			printf("��");
			break;
		}
		else
			InOrder(A);
		printf("\n");
		printf("����ɾ�����������֣��˳�����-1:\n");
	}
	printf("\n");
	system("pause");
	return 0;
}