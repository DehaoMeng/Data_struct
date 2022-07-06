#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef int keytype;
#define MAXSIZE 100
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
//找出比x大的数字，并且从大到小排序
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
//改进版的冒泡排序(双向冒泡)  
void BidBubbleSort(int array[], int n)
{
	int low, high, flag, i;
	low = 0;
	high = n - 1;
	while (low < high)
	{
		flag = 0;
		for (i = low; i < high; i++)  //正向冒泡  
		{
			if (array[i] > array[i + 1]) //找到剩下中最大的  
			{
				Swap(&array[i], &array[i + 1]);
				flag = 1;    //标志， 有数据交换  
			}
		}
		if (!flag)
			break;
		high--;
		for (i = high; i > low; i--) //反向冒泡  
		{
			if (array[i] < array[i - 1])   //找到剩下中最小的  
				Swap(&array[i], &array[i - 1]);
		}
		low++;
	}
}
//快速排序
void HoareSort(int array[], int low, int high) {
	int i, j;
	if (low < high) 
	{
		i = low; j = high;     //指定排序记录上界和下界
		array[0] = array[i];   //暂存枢纽记录
		while (i < j) {
			while (i < j && array[j] >= array[0])   //反向定位移动的记录位置
				j--;
			array[i] = array[j];
			while (i < j && array[i] < array[0])    //正向定位移动的记录位置
				i++;
			array[j] = array[i];
		}
		array[i] = array[0];               //将枢轴记录存入指定的位置
		HoareSort(array, low, i - 1);      //对排在枢轴记录前面的记录快速排序
		HoareSort(array, i + 1, high);     //对排在枢轴记录后面的记录快速排序
	}
}
//寻找众数
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
	printf("\n众数为：%d", e);

}
int main()
{
	keytype key, x, a[10],i,b[11],c[MAXSIZE],length;
	Bitree* T = NULL;
	T = creatbst();						//创建二叉树
	printf("中序遍历为:");			//中序遍历，若空则输出空
	if (T == NULL)
		printf("空");
	else
		InOrder(T);
	printf("\n输入需要比较的数字：");
	scanf("%d", &x);
	printf("从大到小输出二叉排序树中不小于 %d 的数字序列：",x);
	Sort_x(T, x);
	printf("\n");
	printf("输入需要删除的数字，若退出则输入-1:");
	while (1)
	{
		scanf("%d", &key);
		if (key == -1)break;			//输入-1则退出
		F = NULL;
		T = deletebst(T, key);			//删除输入的元素
		printf("中序遍历为:");		//中序遍历
		if (T == NULL)
		{
			printf("二叉树为空");
			break;
		}
		else
			InOrder(T);
		printf("\n");
		printf("继续删除请输入数字，若退出则输入-1:");
	}
	printf("\n\n双向冒泡排序：\n输入需要排序的10个数：");
	for (i = 0; i < 10; i++) {
		scanf("%d", &a[i]);
	}
	BidBubbleSort(a, 10);
	printf("升序排序为：");
	for (i = 0; i < 10; i++)
		printf("%d ", a[i]);
	printf("\n\n快速排序：\n输入需要排序的10个数：");
	b[0] = -1;
	for (i = 1; i < 11; i++) {
		scanf("%d", &b[i]);
	}
	HoareSort(b, 1, 10);
	printf("升序排序为：");
	for (i = 1; i < 11; i++)
		printf("%d ", b[i]);
	printf("输入该递增序列的个数：");
	scanf("%d", &length);
	printf("输入%d个递增有序数列：",length);
	find_zhongshu(c,length);
	system("pause");
	return 0;
}