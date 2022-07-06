#include<stdio.h>
 
#define Max_ 10
 
// 打印结果
void Show(int  arr[], int n)
{
    int i;
    for ( i=0; i<n; i++ )
        printf("%d ", arr[i]);
    printf("\n");
}
 

void Swap( int *num_a, int *num_b )
{
    int temp = *num_b;
    *num_b = *num_a;
    *num_a = temp;
}
 
void BidBubbleSort(int array[], int n)
{
    int low, high, flag, i;
    low = 0;
    high = n - 1;
    while(low < high)
    {
        flag=0;
        for(i=low; i<high; i++)  //正向冒泡
        {
            if(array[i] > array[i+1]) //找到剩下中最大的
            {
                Swap(&array[i], &array[i+1]);
                flag = 1;    //标志， 有数据交换
            }
        }
        Show(array,8);
        if( !flag )
            break;
        high--;
        for( i=high; i>low; i-- ) //反向冒泡
        {
            if(array[i] < array[i-1])   //找到剩下中最小的
                Swap(&array[i], &array[i-1]);
        }
        Show(array, 8);
        low++;
    }
}
 
int main()
{   
    int a[8],i;
    for(i=0;i<8;i++)
    	scanf("%d",&a[i]);

    BidBubbleSort(a, 8);
    return 0;
}
