#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 20				//����������󳤶�
void list(int* r,int length)	//�����������
{
	int i = 1;
	while (i <= length)
	{
		printf("%d ", r[i]);
		i++;
	}
	printf("\n");
}
void maopao(int* r,int length)	//˫��ð������
{
	int i, j, t, x=0;
	for (i = 1; i < length; i++)
	{
		if (i % 2 != 0)			
		{
			for (j = 1; j < length; j++)//������ʱ�������ҽ��бȽϺͽ���
				if (r[j] > r[j + 1])
				{
					t = r[j]; r[j] = r[j + 1]; r[j + 1] = t;
					x = 1;
				}
		}
		else
			for (j = length; j >= 2; j--)//ż����ʱ����������бȽϺͽ���
				if (r[j] < r[j - 1])
				{
					t = r[j]; r[j] = r[j - 1]; r[j - 1] = t;
					x = 1;
				}
		if (x == 1)
		{
			list(r, length);			//���ÿһ������Ľ��(������������Ļ�)
			x = 0;
		}				
	}
	

}
void quicksort(int* r, int low, int high,int length)	//��������
{
	if (low <= high) {
		int i, j, t, sum = 0, ave;
		for (i = low; i <= high; i++) {	//����ƽ��ֵ��Ϊ����
			sum += r[i];
		}
		i = low;						//��¼�Ͻ���½�
		j = high;
		ave = sum / (high - low + 1);
		while (i < j) {
			while (r[i] < ave && i <= j)  ++i;
			while (r[j] > ave && i <= j)  --j;
			if (i < j) {
				t = r[i];
				r[i] = r[j];
				r[j] = t;
				i++;
				j--;
				list(r,length);
			}
		}
		if (i<high && j>low) {
			quicksort(r, low, j,length);
			quicksort(r, i, high,length);
		}
		else return;
	}
}
void zhongshu(int* r, int length)			//Ѱ������
{
	int i, j, num1 = 1, maxnum = 0, x = 0;
	for (int i = 0; i < length; i++)		//�ҵ������ĸ���
	{
		num1 = 1;
		for (int j = 0; j <=length; j++)	
		{
			if (r[j] == r[i] && j != i) {
				num1++;
			}
		}
		if (num1 > maxnum)
		{
			maxnum = num1;
		}
	}
	printf("�⴮���е�������:");
	for (i = 1; i <= length; i++)			//�������
		if (r[i] != x)
		{
			x = r[i];
			if (r[i + maxnum - 1] == r[i])
				printf("%d ", x);
		}
	printf("\n");
}
int main() {
	int a[MAXSIZE] = { 0 };				//ð����������
	int b[MAXSIZE] = { 0 };				//������������
	int i,x;
	int length = 0;
	printf("������һ�����֣�����-1��β��:\n");
	for (i = 1; 1; i++)					//��������
	{
		scanf("%d", &x);
		if (x == -1)break;
		b[i] = a[i] = x;
		length++;						//��¼���еĳ���
	}
	printf("---------------------------------------------------\n");
	printf("˫��ð�������������:\n");
	maopao(a, length);					//ð���������
	printf("���ս��:");
	list(a, length);
	printf("---------------------------------------------------\n");
	printf("���������������:\n");
	quicksort(b, 1, length,length);		//�����������
	printf("���ս��:");
	list(a, length);
	printf("---------------------------------------------------\n");
	zhongshu(a, length);				//Ѱ����������
	system("pause");
	return 0;
}