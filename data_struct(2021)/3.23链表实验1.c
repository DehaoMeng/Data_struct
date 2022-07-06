#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef int Elemtype;
typedef struct node
{
	int coef;
	int exp;
	struct node* next;
}slink;
slink* creslink()
{
	slink* head, * p, * q;
	p = head = (slink*)malloc(sizeof(slink));
	while (1)
	{
		q = (slink*)malloc(sizeof(slink));
		scanf("%d", &q->coef);
		scanf("%d", &q->exp);
		if (q->coef == 0)break;
		p->next = q;
		p = q;
	}
	p->next = NULL;
	return head;
}
void add(slink* head1, slink* head2)
{
	slink* h, * p1, * p2, * q;
	h = head1;
	p1 = head1->next;
	p2 = head2->next;
	while (p1&& p2)
	{
		if (p1->exp < p2->exp)
		{
			h->next = p1;
			h = p1;
			p1 = p1->next;
		}
		else if (p1->exp > p2->exp)
		{
			h->next = p2;
			h = p2;
			p2 = p2->next;
		}
		else if (p1->coef + p2->coef != 0)
		{
			p1->coef += p2->coef;
			h->next = p1;
			h = p1;
			p1 = p1->next;
			q = p2;
			p2 = p2->next;
			free(q);
		}
		else
		{
			q = p1; 
			p1 = p1->next;
			free(q);
			q = p2; 
			p2 = p2->next;
			free(q);
		}


	}
	if (p1 != NULL)
		h->next = p1;
	else
		h->next = p2;
	free(head2);
}
int list(slink* head)
{
	printf("result:\n");
	slink* p = head->next;
	if (p == NULL)
	{
		printf("empty\n0\n");
		return 0;
	}
	while (p)
	{
		printf("%d %d", p->coef, p->exp);
		p = p->next;
		printf("\n");
	}
	p = head->next;
	int i;
	for (i = 1; p != NULL; i++)
	{
		if (i != 1 && p->coef > 0)
			printf("+");
		//if (p->coef == 1)
			//printf("(x,%d)", p->exp);
		//else if (p->coef == -1)
			//printf("-(x,%d)", p->exp);
		//else
			printf("%d(x,%d)", p->coef, p->exp);
		p = p->next;
	}
	printf("\n");
	return 1;
}
int main()
{
	slink* p1, * p2;
	p1 = creslink();
	p2 = creslink();
	add(p1, p2);
	list(p1);
	system("pause");
	return 0;
}