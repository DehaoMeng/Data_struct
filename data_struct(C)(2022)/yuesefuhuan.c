/*
 * 约瑟夫环的实现
 * */

#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int number;
    struct node * next;
}person;
person * initLink() {
    int i;
    person * head = NULL, *cyclic = NULL;
    head = (person*)malloc(sizeof(person));
    scanf("%d",&i);
    if(i != -1 && i > 0){
   	 head->number = i;
   	 head->next = NULL;
    }
    cyclic = head;
    scanf("%d",&i);
    while(i != -1 && i > 0)
    {
	    person * body = (person*)malloc(sizeof(person));
	    body->number = i;
	    body->next = NULL;
	    cyclic->next = body;
	    cyclic = cyclic->next;
	    scanf("%d",&i);
    }
    cyclic->next = head;//首尾相连
    return head;
}
void printlist(person *head)
{
	person * p = head;
	while(p->next != head)
	{
		printf("%d",p->number);
		p = p->next;
	}
	printf("%d",p->number);
}
void findAndKillK(person * head, int k, int m) {
    if(k < 1 || m < 1)
    {
	printf("error");
	return;
    }
    person * p = head;
    person * tail = head;
    while(tail->next != head)
    {
	    tail = tail->next;
    }
    int i;
    for(i=1;i < k;i++)
        {
                p = p->next;
                tail = tail->next;
        }

    while(p->next != p)
    {
	for(i=1;i < m;i++)
	{
		p = p->next;
		tail = tail->next;
	}
	printf("%d ",p->number);
	tail->next = p->next;
	p = p->next;
    }
    printf("%d\n",p->number);
}

int main() {
    int n = 0, k = 0, m = 0;
    person * head = NULL;
    head = initLink(n);
    scanf("%d", &k);
    scanf("%d", &m);
    findAndKillK(head, k, m);
    return 0;
}
