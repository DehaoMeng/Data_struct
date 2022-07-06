#include<stdio.h>
#include<stdlib.h>
typedef enum{false,true} bool;
typedef struct BBNode{
	struct BBNode *lchild,*rchild;
	int data;
}BBTree;
bool DeleteNode(BBTree **T){
    BBTree *L;
    //*T既没有左孩子，又没有右孩子，为叶子结点
    if (!(*T)->lchild && !(*T)->rchild)
        *T = NULL;
        //*T只有右孩子
    else if (!(*T)->lchild)
        *T = (*T)->rchild;
        //*T只有左孩子
    else if (!(*T)->rchild)
        *T = (*T)->lchild;
        //*T既有左孩子，又有右孩子
    else{
        L = (*T)->lchild;//L指向被删除结点的左子树

        //寻找L的最右孩子
        while (L->rchild)
            L = L->rchild;

        //把*T的右子树接到左子树最右孩子的右子树上。
        L->rchild = (*T)->rchild;
        //*T的左子树直接作为*T父结点的子树
        *T = (*T)->lchild;
    }
    return true;
}
BBTree* SearchNode(BBTree *T, int key){
    if (!T)                        //空树，查找失败
        return NULL;
    else if (key == T->data)    //查找成功
        return T;
    else if (key < T->data)        //在左子树中继续查找
        return SearchNode(T->lchild, key);
    else                        //在右子树中继续查找
        return SearchNode(T->rchild, key);
}

bool SearchNodeandReturn(BBTree *T, BBTree *F, int key, BBTree **p){
    //函数中，只能对*p进行修改，而不能试图修改p的值。
    //因为p为形参，形参的改变并不会影响实参。
    if (!T){
        //T为空树，此时父结点F或者为NULL，或者为查找路径上的最后一个结点。
        //查找失败
        *p = F;
        return false;
    }
    else if (key == T->data) {   //查找成功
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

        //注意不要漏掉p为NULL的情况，
        //此时表明*T为空树，将新结点直接作为根结点。
        if (!p)
            *T = n;
            //key比查找路径上的最后一个结点小，则将n作为p的左子树。
        else if (key < p->data){
            p->lchild = n;
        }
            //key比查找路径上的最后一个结点大，则将n作为p的右子树。
        else{
            p->rchild = n;
        }
        return true;
    }
}
bool DeleteBST(BBTree **T, int x)
{
    if (!*T){        //空树。查无此结点。
        printf("未找到此节点\n");
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
 * 先序遍历 
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
 * 中序递归遍历
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
 * 遍历函数
 */
bool Printf(int e)
{
    printf("%d ",e);
    return true;
}
int main()
{
    BBTree *T = NULL;//注意一定要先将T初始化为空树
    int i, num;	

    //使用插入操作构建二叉排序树。(插入过程中已检验查找函数SearchBST2())
    scanf("%d",&num);
    while(num != -1){
        InsertNode(&T, num);
        scanf("%d",&num);
    }
	PreOrderTraverse(T,Printf);
//    //检验插入效果。中序遍历该树，若结果为由小到大，表明插入成功。
    putchar('\n');
    InOrderTree(T, Printf);
    putchar('\n');
    //删除操作
    scanf("%d",&num);
    DeleteBST(&T, num);

    //检验删除操作
    InOrderTree(T, Printf);
    putchar('\n');
    scanf("%d",&num);
    InOrder(T, Printf,num);
    return 0;
}

