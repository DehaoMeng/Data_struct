#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef int Elemtype;
#define MAXSIZE 100
typedef struct
{
	Elemtype *data;
	int length;
	int listsize;
}sqlist;
int initlist(sqlist* L) {
	L->data = (Elemtype*)malloc(sizeof(Elemtype) * MAXSIZE);
	L->length = 0;
	L->listsize = MAXSIZE;
}
int FIND_min(sqlist* L) {
	int pos=0;
	int min;
	min = L->data[0];
	for (int i = 0; i < L->length; i++) 
	{
		if (L->data[i] < min){
			min = L->data[i];
		    pos = i;}
	}
	for (int j = pos; j < L->length; j++) 
	{
		L->data[j] = L->data[j+1];
	}
	L->length--;
	return min;
}
int delete(sqlist *L,Elemtype n) {
	int k = 0, i = 0,j=0;
	while (i < L->length) {
		if (L->data[i] == n)
			k++;
		else
			L->data[i - k] = L->data[i];
		i++;
	}
	L->length = L->length - k;
	if (k == 0)
		printf("\nerror");
	else {
		printf("\n");
		for (int i = 0; i < L->length; i++) {
			printf("%d ", L->data[i]);
		}
	}
}
int main() {
	sqlist L;
	initlist(&L);
	scanf("%d", &L.data[0]);
	int i = 0;
	while(L.data[i]!=-1){
		i++;
		scanf("%d", &L.data[i]);
		L.length++;
	}
	int e;
	scanf("%d", &e);
	for (int i = 0; i < L.length; i++) {
		printf("%d ", L.data[i]);
	}
	int min=0;
	min=FIND_min(&L);
	printf("\n%d", min);
	printf("\n");
	for (int i = 0; i < L.length; i++) {
		printf("%d ", L.data[i]);
	}
	delete(&L, e);
	printf("\n");
	system("pause");
	return 0;
}
