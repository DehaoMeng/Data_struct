#include<stdio.h>
#include<stdlib.h>
typedef enum{false,true} bool;
typedef struct BBNode{
	struct BBNode *lchild,*rchild;
	int data;
}BBTree;
bool DeleteNode(BBTree **T){
    BBTree *L;
    //*T��û�����ӣ���û���Һ��ӣ�ΪҶ�ӽ��
    if (!(*T)->lchild && !(*T)->rchild)
        *T = NULL;
        //*Tֻ���Һ���
    else if (!(*T)->lchild)
        *T = (*T)->rchild;
        //*Tֻ������
    else if (!(*T)->rchild)
        *T = (*T)->lchild;
        //*T�������ӣ������Һ���
    else{
        L = (*T)->lchild;//Lָ��ɾ������������

        //Ѱ��L�����Һ���
        while (L->rchild)
            L = L->rchild;

        //��*T���������ӵ����������Һ��ӵ��������ϡ�
        L->rchild = (*T)->rchild;
        //*T��������ֱ����Ϊ*T����������
        *T = (*T)->lchild;
    }
    return true;
}
BBTree* SearchNode(BBTree *T, int key){
    if (!T)                        //����������ʧ��
        return NULL;
    else if (key == T->data)    //���ҳɹ�
        return T;
    else if (key < T->data)        //���������м�������
        return SearchNode(T->lchild, key);
    else                        //���������м�������
        return SearchNode(T->rchild, key);
}

bool SearchNodeandReturn(BBTree *T, BBTree *F, int key, BBTree **p){
    //�����У�ֻ�ܶ�*p�����޸ģ���������ͼ�޸�p��ֵ��
    //��ΪpΪ�βΣ��βεĸı䲢����Ӱ��ʵ�Ρ�
    if (!T){
        //TΪ��������ʱ�����F����ΪNULL������Ϊ����·���ϵ����һ����㡣
        //����ʧ��
        *p = F;
        return false;
    }
    else if (key == T->data) {   //���ҳɹ�
        *p = T;
        return true;
    }
    else if (key < T->data){
        return SearchNodeandReturn(T->lchild, T, key, p);
    }
    else{
        return SearchNodeandReturn(T->rchild, T, key, p);
    }
}
bool InsertNode(BBTree **T, int key){
    BBTree *p, *n;
    if (SearchNodeandReturn(*T, NULL, key, &p))
        return false;
    else{
        n = (BBTree *)malloc(sizeof(BBTree));
        n->data = key;
        n->lchild = NULL;
        n->rchild = NULL;

        //ע�ⲻҪ©��pΪNULL�������
        //��ʱ����*TΪ���������½��ֱ����Ϊ����㡣
        if (!p)
            *T = n;
            //key�Ȳ���·���ϵ����һ�����С����n��Ϊp����������
        else if (key < p->data){
            p->lchild = n;
        }
            //key�Ȳ���·���ϵ����һ��������n��Ϊp����������
        else{
            p->rchild = n;
        }
        return true;
    }
}
bool DeleteBST(BBTree **T, int x)
{
    if (!*T){        //���������޴˽�㡣
        printf("δ�ҵ��˽ڵ�\n");
		return false;
	}
    else if (x == (*T)->data){
        DeleteNode(T);
        return true;
    }
    else if (x < (*T)->data){
        return DeleteBST(&((*T)->lchild), x);
    }
    else{
        return DeleteBST(&((*T)->rchild), x);
    }
}

/*
 * ������� 
*/

void PreOrderTraverse(BBTree *T, bool(*Print)(int e)) {
    if (!T) {
        return;
    }
  	Print(T->data);
    PreOrderTraverse(T->lchild, Print);
    PreOrderTraverse(T->rchild, Print);
}
/*
 * ����ݹ����
 */
bool InOrderTree(BBTree *T, bool(*Print)(int e))
{
    if (T){
        if (InOrderTree(T->lchild, Print))
            if (Print(T->data))
                if (InOrderTree(T->rchild, Print));
    }
    return true;
}
void InOrder(BBTree *root,bool (*Print)(int k),int e){
    if(!root)
        return ;
    InOrder(root->rchild,Print,e);
    if(root->data>=e){
        Print(root->data);
    }
    InOrder(root->lchild,Print,e);
}
/*
 * ��������
 */
bool Printf(int e)
{
    printf("%d ",e);
    return true;
}
int main()
{
    BBTree *T = NULL;//ע��һ��Ҫ�Ƚ�T��ʼ��Ϊ����
    int i, num;	

    //ʹ�ò����������������������(����������Ѽ�����Һ���SearchBST2())
    scanf("%d",&num);
    while(num != -1){
        InsertNode(&T, num);
        scanf("%d",&num);
    }
	PreOrderTraverse(T,Printf);
//    //�������Ч����������������������Ϊ��С���󣬱�������ɹ���
    putchar('\n');
    InOrderTree(T, Printf);
    putchar('\n');
    //ɾ������
    scanf("%d",&num);
    DeleteBST(&T, num);

    //����ɾ������
    InOrderTree(T, Printf);
    putchar('\n');
    scanf("%d",&num);
    InOrder(T, Printf,num);
    return 0;
}

