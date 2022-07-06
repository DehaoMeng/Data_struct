#include<stdio.h>
 
#define Max_ 10
 
// ��ӡ���
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
        for(i=low; i<high; i++)  //����ð��
        {
            if(array[i] > array[i+1]) //�ҵ�ʣ��������
            {
                Swap(&array[i], &array[i+1]);
                flag = 1;    //��־�� �����ݽ���
            }
        }
        Show(array,8);
        if( !flag )
            break;
        high--;
        for( i=high; i>low; i-- ) //����ð��
        {
            if(array[i] < array[i-1])   //�ҵ�ʣ������С��
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
