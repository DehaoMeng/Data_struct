#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef int keytype;
#define MAXSIZE 100
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
//�ҳ���x������֣����ҴӴ�С����
void Sort_x(Bitree* T, int x) {
	if (T != NULL) {
		Sort_x(T->right, x);
		if (T->data >= x)
			printf("%d ", T->data);
		Sort_x(T->left, x);
	}
	return 1;
}
void Swap(int* a, int* b)
{
	int temp = *b;
	*b = *a;
	*a = temp;
}
//�Ľ����ð������(˫��ð��)  
void BidBubbleSort(int array[], int n)
{
	int low, high, flag, i;
	low = 0;
	high = n - 1;
	while (low < high)
	{
		flag = 0;
		for (i = low; i < high; i++)  //����ð��  
		{
			if (array[i] > array[i + 1]) //�ҵ�ʣ��������  
			{
				Swap(&array[i], &array[i + 1]);
				flag = 1;    //��־�� �����ݽ���  
			}
		}
		if (!flag)
			break;
		high--;
		for (i = high; i > low; i--) //����ð��  
		{
			if (array[i] < array[i - 1])   //�ҵ�ʣ������С��  
				Swap(&array[i], &array[i - 1]);
		}
		low++;
	}
}
//��������
void HoareSort(int array[], int low, int high) {
	int i, j;
	if (low < high) 
	{
		i = low; j = high;     //ָ�������¼�Ͻ���½�
		array[0] = array[i];   //�ݴ���Ŧ��¼
		while (i < j) {
			while (i < j && array[j] >= array[0])   //����λ�ƶ��ļ�¼λ��
				j--;
			array[i] = array[j];
			while (i < j && array[i] < array[0])    //����λ�ƶ��ļ�¼λ��
				i++;
			array[j] = array[i];
		}
		array[i] = array[0];               //�������¼����ָ����λ��
		HoareSort(array, low, i - 1);      //�����������¼ǰ��ļ�¼��������
		HoareSort(array, i + 1, high);     //�����������¼����ļ�¼��������
	}
}
//Ѱ������
void find_zhongshu(int a[],int length) {
	int i, flag[100],num=0,e;
	for (i = 0; i < 100; i++)
		flag[i] = 0;
	for (i = 0; i < length; i++) {
		scanf("%d", &a[i]);
		flag[a[i]]++;
	}
	for (i = 0; i < length; i++) {
		if (flag[i] != 0 && num < flag[i]) {
			num = flag[i];
			e = i;
		}
	}
	printf("\n����Ϊ��%d", e);

}
int main()
{
	keytype key, x, a[10],i,b[11],c[MAXSIZE],length;
	Bitree* T = NULL;
	T = creatbst();						//����������
	printf("�������Ϊ:");			//��������������������
	if (T == NULL)
		printf("��");
	else
		InOrder(T);
	printf("\n������Ҫ�Ƚϵ����֣�");
	scanf("%d", &x);
	printf("�Ӵ�С��������������в�С�� %d ���������У�",x);
	Sort_x(T, x);
	printf("\n");
	printf("������Ҫɾ�������֣����˳�������-1:");
	while (1)
	{
		scanf("%d", &key);
		if (key == -1)break;			//����-1���˳�
		F = NULL;
		T = deletebst(T, key);			//ɾ�������Ԫ��
		printf("�������Ϊ:");		//�������
		if (T == NULL)
		{
			printf("������Ϊ��");
			break;
		}
		else
			InOrder(T);
		printf("\n");
		printf("����ɾ�����������֣����˳�������-1:");
	}
	printf("\n\n˫��ð������\n������Ҫ�����10������");
	for (i = 0; i < 10; i++) {
		scanf("%d", &a[i]);
	}
	BidBubbleSort(a, 10);
	printf("��������Ϊ��");
	for (i = 0; i < 10; i++)
		printf("%d ", a[i]);
	printf("\n\n��������\n������Ҫ�����10������");
	b[0] = -1;
	for (i = 1; i < 11; i++) {
		scanf("%d", &b[i]);
	}
	HoareSort(b, 1, 10);
	printf("��������Ϊ��");
	for (i = 1; i < 11; i++)
		printf("%d ", b[i]);
	printf("����õ������еĸ�����");
	scanf("%d", &length);
	printf("����%d�������������У�",length);
	find_zhongshu(c,length);
	system("pause");
	return 0;
}