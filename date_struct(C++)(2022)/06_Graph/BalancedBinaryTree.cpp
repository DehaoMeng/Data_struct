//
// Created by 86176 on 2022/5/28 0028.
//
#include <iostream>
#include <stack>
using namespace std;
class BiTree{
public:
    BiTree *lchild,*rchild;
    int data;
    BiTree(){lchild = nullptr;rchild = nullptr;}
};
bool Delete(BiTree **T){
    BiTree *L;
    //*T既没有左孩子，又没有右孩子，为叶子结点
    if (!(*T)->lchild && !(*T)->rchild)
        *T = nullptr;
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
BiTree* SearchBST1(BiTree *T, int key){
    if (!T)                        //空树，查找失败
        return nullptr;
    else if (key == T->data)    //查找成功
        return T;
    else if (key < T->data)        //在左子树中继续查找
        return SearchBST1(T->lchild, key);
    else                        //在右子树中继续查找
        return SearchBST1(T->rchild, key);
}

bool SearchBST2(BiTree *T, BiTree *F, int key, BiTree **p){
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
        return SearchBST2(T->lchild, T, key, p);
    }
    else{
        return SearchBST2(T->rchild, T, key, p);
    }
}
bool InsertBST(BiTree **T, int key){
    BiTree *p, *n;
    if (SearchBST2(*T, nullptr, key, &p))
        return false;
    else{
        n = new BiTree();
        n->data = key;
        n->lchild = nullptr;
        n->rchild = nullptr;

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
bool DeleteBST(BiTree **T, int key)
{
    if (!*T)        //空树。查无此结点。
        return false;
    else if (key == (*T)->data){
        Delete(T);
        return true;
    }
    else if (key < (*T)->data){
        return DeleteBST(&((*T)->lchild), key);
    }
    else{
        return DeleteBST(&((*T)->rchild), key);
    }
}

/*
 * 先序遍历
 * */
bool PreOrderTraverse_Recursive(BiTree *T,bool (*Visit)(int e)){
    if (T){
        if (Visit(T->data))
            if (InOrderTraverse_Recursive(T->lchild, Visit))
                if (InOrderTraverse_Recursive(T->rchild, Visit));
    }
    return true;
}

/*
 * 中序递归遍历
 */
bool InOrderTraverse_Recursive(BiTree *T, bool(*Visit)(int e))
{
    if (T){
        if (InOrderTraverse_Recursive(T->lchild, Visit))
            if (Visit(T->data))
                if (InOrderTraverse_Recursive(T->rchild, Visit));
    }
    return true;
}
void InOrder(BiTree *root,bool (*Visit)(int k),int e){
    if(!root)
        return ;
    InOrder(root->rchild,Visit,e);
    if(root->data>=e){
        Visit(root->data);
    }
    InOrder(root->lchild,Visit,e);
}
/*
 * 遍历函数
 */
bool PrintElement(int e)
{
    cout << e << " ";
    return true;
}
int main()
{
    BiTree *T = nullptr;//注意一定要先将T初始化为空树
    int i, num;

    //使用插入操作构建二叉排序树。(插入过程中已检验查找函数SearchBST2())
    cin >> num;
    while(num != -1){
        InsertBST(&T, num);
        cin >> num;
    }

    //检验插入效果。中序遍历该树，若结果为由小到大，表明插入成功。
    InOrderTraverse_Recursive(T, PrintElement);
    putchar('\n');

    //删除操作
    cin >> num;
    DeleteBST(&T, num);

    //检验删除操作
    InOrderTraverse_Recursive(T, PrintElement);
    putchar('\n');
    cin >> num;
    InOrder(T, PrintElement,num);

    return 0;
}
