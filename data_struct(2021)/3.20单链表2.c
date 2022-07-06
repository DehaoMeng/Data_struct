#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct node
{
	ElemType data;
	struct node* next;
}slink;
int initlist(slink* L) 
{
	L = (slink*)malloc(sizeof(slink));
	L->next = NULL;
	return L;
}
int creslink(slink* head)
{
	initlist(head);
	slink* s;
	ElemType x;
	scanf("%d", &x);
	while (x != -1) {
		s = (slink*)malloc(sizeof(slink));
		s->data = x;
		s->next = head->next;
		head->next = s;
		scanf("%d", &x);
	}
	return head;
}
int list(slink* head)
{
	slink* p;
	p = head->next;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}


int insert(slink * head, int i, ElemType x) {
	slink* p, * q;
	int j;
	if (i < 1) return 0;
	p = head;
	j = 0;
	while (p != NULL && j < i - 1) {
		p = p->next;
		j++;
	}
	if (p == NULL) return 0;
	q = (slink*)malloc(sizeof(slink));
	q->data = x;
	q->next = p->next;
	p->next = q;
	return 1;
}

int getlen(slink * head) {
	slink* p;
	int n;
	p = head->next;
	n = 0;
	while (p != NULL) {
		n++;
		p = p->next;
	}
	return n-1;
}
int locate(slink* head,ElemType x) {
	int i= 1;
	slink* p=head->next;
	while (p && p->data!=x) 
	{
		p = p ->next;
		i++;
	}
	if (p) 
		return i;
	else 
		return 0;
}
int delete(slink* head, int i)
{
	ElemType* e=(slink*)malloc(sizeof(slink));
	slink* p, * q;
	int j=0;
	if (i<1 && i>getlen(head))
		return 0;
	p = head;
	while (p && j < i - 1) {
		p = p->next;
		j++;
	}
	if (p->next == NULL)
		return 0;
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return i;
}
int sort(slink* head) 
{
	int t = 0;
	for (slink* temp = head->next; temp != NULL; temp = temp->next) {
		for (slink* p = temp; p != NULL; p = p->next) {
			if (temp->data > p->data) {
				t = temp->data;
				temp->data = p->data;
				p->data = t;
			}
		}
	}
	return head;
}
slink* redelete(slink* head, int x) {

	slink* p = head;
	slink* q = NULL;
	slink* s = NULL;
	while (p)
	{
		if (p->data!= x)
		{
			q= p;
			p = p->next;
		}
		else if (p->data == x)
		{
			if (q == NULL)
			{
				s = p->next;
				head = s;
				free(p);
				p = NULL;
				p = s;
			}
			else
			{
				q->next = p->next;
				free(p);
				p = NULL;
				p = q->next;
			}
		}
	}
	return head;
}
int main() {
	slink* L;
	L = (slink*)malloc(sizeof(slink));
	L->data = 0;
	L->next = NULL;
	creslink(L);
	sort(L);
	list(L);
	int x;
	scanf("%d", &x);
	redelete(L, x);
	if (L->next==NULL)
		printf("empty!");
	else 
		list(L);
	system("pause");
	return 0;
}
