#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef int Elemtype;
#define MAXSIZE 100

typedef struct 
{
	Elemtype* data;
	int length;
	int listsize;
}sqlist;

int initlist(sqlist* L) 
{
	L->data = (Elemtype*)malloc(sizeof(Elemtype) * MAXSIZE);
	L->length = 0;
	L->listsize = MAXSIZE;
}

int getlen(sqlist* L) {
	return L->length;
}

int insert(sqlist* L, int i, Elemtype x)
{
	int j;
	if (i<1 || i>L->length + 1)return 0;
	if (L->length == L->listsize)
	{
		(L->data = (Elemtype*)realloc(L->data, (L->listsize + 1) * sizeof(Elemtype)));
		L->listsize++;
	}
	for (j = L->length - 1; j >= i - 1; j--)
		L->data[j + 1] = L->data[j];
	L->data[i - 1] = x;
	L->length++;
	return 1;
}
int sort(sqlist* L){
	int temp;
	for (int i = 0; i < L->length - 1; i++) 
	{
		for (int j = 0; j < L->length - i - 1; j++) 
		{
			if (L->data[j] > L->data[j + 1]) 
			{
				temp = L->data[j];
				L->data[j] = L->data[j + 1];
				L->data[j + 1] = temp;
			}
		}
	}
	}
int delete(sqlist* L, Elemtype n) {
	int k = 0, i = 0, j = 0;
	while (i < L->length) {
		if (L->data[i] == n)
			k++;
		else
			L->data[i - k] = L->data[i];
		i++;
	}
	L->length = L->length - k;
	if (k == 0) return 0;
	else return 1;
}

int uniona(sqlist* la, sqlist* lb) {
	int a_len,b_len,x;
	b_len=getlen(lb);
	a_len = getlen(la);
	for (int i = 0; i < b_len; i++) {
		insert(la, ++a_len, lb->data[i]);
	}
}
int list(sqlist* L)
{
	int i;
	for (i = 0; i < L->length; i++)
		printf("%d ", L->data[i]);
	printf("\n");
}
int scan(sqlist* L) {
	int x, i = 0;
	for (i = 0; i<MAXSIZE; i++) {
		scanf("%d", &x);
		if (x == -1) break;
		insert(L, i+1, x);
	}
}
int locate(sqlist* L, Elemtype x)
{
	int i = 0;
	while (i < L->length)
		if (L->data[i] == x) return i + 1;
		else i++;
	return 0;
}
int main() {
	sqlist L;
	initlist(&L);
	scan(&L);
	int e;
	scanf("%d", &e);
	sort(&L);
	list(&L);
	int t = locate(&L, e);
	delete(&L, e);
	while (t == 0) {
		printf("error\n");
		scanf("%d", &e);
		t = locate(&L, e);
		delete(&L, e);
	}
	list(&L);
	sqlist M;
	initlist(&M);
	scan(&M);
	uniona(&L, &M);
	sort(&L);
	list(&L);
	system("pause"); 
	return 0;
}
