/*
 * 线索二叉树的实现
 */

#include <iostream
const int OK = 1;
const int Error = 0;
typedef char ElemType;
typedef struct node
{
    ElemType data;          /*数据域*/
    struct node *lchild;    /*左链域*/
    struct node *rchild;    /*右链域*/
    int ltag;               /*左链域信息标记*/
    int rtag;               /*右链域信息标记*/
}BiThrTree;
/*
 * ltag=0 lchild指针指向该结点的左孩子结点 ltag=1 lchild指针指向该结点的直接前驱结点
 * rtag=0 rchild指针指向该结点的左孩子结点 rtag=1 rchild指针指向该结点的直接前驱结点
 */


/*先序线索化处理算法*/
BiThrTree *pre;             /*指向遍历结点的前驱结点*/
int PreThreading(BiThrTree *p)
{
    if(p)                   /*若当前结点左指针为空，则处理前驱线索*/
    {
        p->ltag = 1;
        p->lchild = pre;
    }
    else
    {
        p->ltag = 0;
    }
    if(!pre->rchild)         /*若前驱结点右指针为空，则处理后继线索*/
    {
        pre->rtag = 1;
        pre->rchild = p;
    }
    else pre->rtag = 0;
    pre = p;                 /*前驱结点指针后移*/
    if(p->ltag == 0)
    {
        PreThreading(p->lchild);    /*左子树线索化处理*/
    }
    if(p->rtag == 0)
        PreThreading(p->rchild);    /*右子树线索化处理*/
    return OK;
}
BiThrTree * PreOrderThreading(BiThrTree *T)
{
    BiThrTree *Thrt;
    Thrt = (BiThrTree*)new BiThrTree;           /*创建头结点*/
    Thrt->ltag = 0;
    Thrt->rtag = 1;
    Thrt->rchild = Thrt;
    if(!T) Thrt->lchild = Thrt;                 /*若二叉树为空，则头结点自身构成一个循环链表*/
    else
    {
        Thrt->lchild = T;                       /*头结点的左指针指向根节点，pre指向头结点*/
        pre = Thrt;
        PreThreading(T);                        /*对二叉树进行先序线索化处理*/
        pre->rchild = Thrt;
        pre->rtag = 1;
        Thrt->rchild = pre;                     /*序列中最后一个结点与头结点相互连接*/
    }
    return Thrt;
}

