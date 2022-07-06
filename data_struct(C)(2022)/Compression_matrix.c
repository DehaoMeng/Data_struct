/*
 * 压缩矩阵的实现，编写算法按列优先压缩存储n阶（即n行n列）下三角矩阵，并按照矩阵的样式输出
 * */

#include<stdio.h>
typedef int ElemType;
#define MaxSize 100
typedef struct table{
	ElemType data[MaxSize];
	int length;
}table;

void Init(table *L,int n){
	int i,j;
	ElemType s;
	L->length=0;
	for(i=0;i<n*(n+1)/2;i++){
		scanf("%d",&s);
		L->data[i]=s;
		L->length++;
		}
	scanf("%d",&s);
	L->data[n*(n+1)/2]=s;
	L->length++;
}

void Print(table *L,int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i>=j) printf("%d ",L->data[i*(i+1)/2+j]);
			else printf("%d ",L->data[L->length-1]);
		}
		printf("\n");
	}
}


int main(){
	table L;
	int n;
	scanf("%d",&n);
	Init(&L,n);
	Print(&L,n);
	return 0;
}
