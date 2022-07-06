#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef char elemtype;
typedef struct node
{
	elemtype data;
	struct node* next;
}slink;
slink* creslink(int n)
{
	slink* head, * p, * s;
	int i;
	p = head = (slink*)malloc(sizeof(slink));
	for (i = 0; i < n; i++)
	{
		s = (slink*)malloc(sizeof(slink));
		scanf("%c ", &s->data);
		p->next = s;
		p = s;
	}
	p->next = NULL;//!
	return head;
}
int getlen(slink* l)
{
	slink* p;
	int n;
	p = l->next;
	n = 0;
	while (p != NULL)
	{
		p = p->next;
		n++;
	}
	return n;
}
int find(slink* l, elemtype x)
{
	slink* p;
	int count = 0;
	p = l->next;
	while (p != NULL)
	{
		if (p->data == x)
			count++;
		p = p->next;
	}
	return count;
}
slink* locate(slink* head, int i)
{
	slink* p;
	p = head->next;
	int j = 1;
	if (i < 1) {
		printf("error\n");
		return NULL;
	}
	while (p != NULL && j < i)
	{
		p = p->next;
		j++;
	}
	if (p == NULL) {
		printf("error\n");
		return NULL;
	}
	return p;
}
int insert(slink* head1, slink* head2, int i)
{
	slink* p1, * p2;
	int j = 1;
	if (i < 1) return 0;
	p1 = head1->next;
	p2 = head2->next;
	while (p1->next != NULL && j < i - 1)
	{
		p1 = p1->next;
		j++;
	}
	if (p1->next == NULL) return 0;
	while (p2->next != NULL)
	{
		p2 = p2->next;
	}
	p2->next = p1->next;
	p1->next = head2->next;
	return 1;

}
void list(slink* head)
{
	slink* p;
	p = head->next;
	while (p != NULL)
	{
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
}
int main()
{
	int n,m;
	char x;
	slink* head1, * head2;
	slink* temp;
	scanf("%d", &n);
	getchar();
	head1 = creslink(n);
	scanf("%d", &n);
	temp = locate(head1, n);
	while (temp == 0)
	{
		scanf("%d", &n);
		temp = locate(head1, n);
	}
	printf("%c\n", temp->data);
	scanf("%d", &n);
	getchar();
	if (n != 0) 
	{
		head2 = creslink(n);
		scanf("%d", &m);
		insert(head1, head2, m);
	}
	list(head1);
	getchar();
	scanf("%c", &x);
	printf("%d", find(head1, x));
	return 0;
}


