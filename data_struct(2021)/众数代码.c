#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 20				//设置数组最大长度
void list(int* r,int length)	//数组输出函数
{
	int i = 1;
	while (i <= length)
	{
		printf("%d ", r[i]);
		i++;
	}
	printf("\n");
}
void maopao(int* r,int length)	//双向冒泡排序法
{
	int i, j, t, x=0;
	for (i = 1; i < length; i++)
	{
		if (i % 2 != 0)			
		{
			for (j = 1; j < length; j++)//奇数趟时从左向右进行比较和交换
				if (r[j] > r[j + 1])
				{
					t = r[j]; r[j] = r[j + 1]; r[j + 1] = t;
					x = 1;
				}
		}
		else
			for (j = length; j >= 2; j--)//偶数趟时从右向左进行比较和交换
				if (r[j] < r[j - 1])
				{
					t = r[j]; r[j] = r[j - 1]; r[j - 1] = t;
					x = 1;
				}
		if (x == 1)
		{
			list(r, length);			//输出每一趟排序的结果(如果发生交换的话)
			x = 0;
		}				
	}
	

}
void quicksort(int* r, int low, int high,int length)	//快速排序
{
	if (low <= high) {
		int i, j, t, sum = 0, ave;
		for (i = low; i <= high; i++) {	//计算平均值作为枢轴
			sum += r[i];
		}
		i = low;						//记录上界和下界
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
void zhongshu(int* r, int length)			//寻找众数
{
	int i, j, num1 = 1, maxnum = 0, x = 0;
	for (int i = 0; i < length; i++)		//找到众数的个数
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
	printf("这串序列的众数是:");
	for (i = 1; i <= length; i++)			//输出众数
		if (r[i] != x)
		{
			x = r[i];
			if (r[i + maxnum - 1] == r[i])
				printf("%d ", x);
		}
	printf("\n");
}
int main() {
	int a[MAXSIZE] = { 0 };				//冒泡排序数组
	int b[MAXSIZE] = { 0 };				//快速排序数组
	int i,x;
	int length = 0;
	printf("请输入一串数字（并以-1结尾）:\n");
	for (i = 1; 1; i++)					//输入序列
	{
		scanf("%d", &x);
		if (x == -1)break;
		b[i] = a[i] = x;
		length++;						//记录序列的长度
	}
	printf("---------------------------------------------------\n");
	printf("双向冒泡排序过程如下:\n");
	maopao(a, length);					//冒泡排序过程
	printf("最终结果:");
	list(a, length);
	printf("---------------------------------------------------\n");
	printf("快速排序过程如下:\n");
	quicksort(b, 1, length,length);		//快速排序过程
	printf("最终结果:");
	list(a, length);
	printf("---------------------------------------------------\n");
	zhongshu(a, length);				//寻找众数过程
	system("pause");
	return 0;
}