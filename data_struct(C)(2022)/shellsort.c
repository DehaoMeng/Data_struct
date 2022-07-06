#include <stdio.h>
int shellsort(int a[], int n,int gap)
{
    int i,j;
    for (i = 0; i < gap; i++) {
            for (j =i+gap; j < n; j += gap) {
                if(a[j] < a[j-gap]){
                    int temp = a[j];
                    int k = j - gap;
                    while (k >= 0 && a[k] >temp){
                        a[k+gap] = a[k];
                        k-=gap;
                    }
                    a[k+gap] = temp;
                }
            }
        }
    for(i=0;i<9;i++)
    	printf("%5d",a[i]);
    printf("\n");
	return 0;
}

int main()
{
    int a[9],i;
    for(i=0;i<9;i++)
    	scanf("%d",&a[i]);
    int b[3];
    for(i=0;i<3;i++)
		scanf("%d",&b[i]);
	for(i=0;i<3;i++)
	    shellsort(a, 9,b[i]); 
    return 0;
}
