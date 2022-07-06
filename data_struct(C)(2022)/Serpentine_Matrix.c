/*
 * 蛇形矩阵实现 普通输出矩阵，按照蛇形输出矩阵
 * */


#include<stdio.h>
typedef int ElemType;
#define MaxSize 100
typedef struct Array{
	ElemType data[MaxSize];
	int length;
}Array;

// 初始化创建矩阵
void Init(Array *L,int n){
	int i;
	L->length=0;
	for(i=0;i<n*n;i++){
		ElemType s;
		scanf("%d",&s);
		L->data[L->length++]=s;
	}
}
// 普通输出矩阵
void Print(Array *L,int n){
	int i;
	for(i=0;i<L->length;i++){
		if(i!=0&&i%n==0) printf("\n");
		printf("%d ",L->data[i]);
	}
	printf("\n");
}
// 蛇形输出矩阵
void Serpentine_Print(Array *L,int n){
	int i,j=0;
    	for (i = 0; i < n; i++) {
        	if (j <= n) {
            		for (; j < n * n; ) {
                		printf("%d ",L->data[j]);
                		j += n;
            		}
            		j = j-n+1;
        	}
       		else if(j >= n*(n-1)) {
            		for (; j > 0; ) {
                		printf("%d ",L->data[j]);
                		j -= n;
           		}
            		j += n + 1;
        	}
        printf("\n");
    	}
}


int main(){
	Array L;
	int n;
	scanf("%d",&n);// 输入要输出的矩阵阶数
	Init(&L,n);// 初始化矩阵
	Print(&L,n);// 正常输出矩阵
	Serpentine_Print(&L,n); // 蛇形输出矩阵
	return 0;
}

