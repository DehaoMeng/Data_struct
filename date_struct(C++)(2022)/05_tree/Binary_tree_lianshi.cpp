    /*
    * 二叉树的链式存储
    */
#include <malloc.h>
#include <iostream>
using namespace std;

typedef char ElemType;//结点数据域的类型
#define MaxSize 20
//二叉树的链式存储结构
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//树指针的队列
typedef struct {
    BiTree data[MaxSize];
    int front, rear;
} SqQueue;

//创建二叉树
//ab c  d  ;
//120300400;
bool CreateBiTree(BiTree &T) {
    ElemType s;
    cin >> s;
    if(s=='#') {
        T = nullptr;
    } else {
        //创建结点
        T = (BiTNode *)malloc(sizeof(BiTNode));
        T->data = s;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
    return true;
}
bool EmptyBiTree(BiTree &T){
    if (T == nullptr) return true;
    else return false;
}

//前序遍历
bool PreOrder(BiTree &T) {
    if(T == nullptr) {
        return false;
    }
    cout << T->data << "  ";
    PreOrder(T->lchild);
    PreOrder(T->rchild);
    return true;
}


//中序遍历
bool InOrder(BiTree &T) {
    if(T == nullptr) {
        return false;
    }
    InOrder(T->lchild);

    cout <<T->data <<"  ";

    InOrder(T->rchild);
    return true;
}

//后序遍历
bool PostOrder(BiTree &T) {
    if(T == nullptr) {
        return false;
    }
    PostOrder(T->lchild);
    PostOrder(T->rchild);
    cout << T->data << "  ";
    return true;
}

//初始化循环队列
void InitQueue(SqQueue &Q){
    Q.front = Q.rear = 0;
}

//判断队空
bool IsEmpty(SqQueue &Q){
    if(Q.front==Q.rear){
        return true;
    }else {
        return false;
    }
}

//入队一个元素
bool EnQueue(SqQueue &Q, BiTree x){
    //判断队是否满
    if(Q.front==(Q.rear+1)%MaxSize){
        return false;
    }
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear+1)%MaxSize;
    return true;
}

//出队一个元素
bool DeQueue(SqQueue &Q, BiTree &x){
    //判断队列是否为空
    if(Q.front==Q.rear){
        return false;
    }
    x = Q.data[Q.front];
    Q.front = (Q.front+1)%MaxSize;
    return true;
}

//层次遍历
bool LeverOrder(BiTree &T) {
    if(EmptyBiTree(T)) return false;
    SqQueue Q;
    InitQueue(Q);
    BiTree p;
    EnQueue(Q, T);
    //将根结点入队
    while(!IsEmpty(Q)) {
        DeQueue(Q, p);
        cout << p->data;
        //如果出队结点左孩子不空，进队
        if(p->lchild) {
            EnQueue(Q, p->lchild);
        }
        //如果出队结点右孩子不空，进队
        if(p->rchild) {
            EnQueue(Q, p->rchild);
        }
    }
    return true;
}

int main() {
    BiTree T;
    CreateBiTree(T);
//    cout << "前序遍历结点";
//    PreOrder(T); //前序遍历：abcd(1234)
//    cout << endl << "中序遍历结点";
//    InOrder(T);  //中序遍历：bcad(2314)
//    cout << endl <<"后序遍历结点";
//    PostOrder(T);//后序遍历：cbda(3241)
//    cout << endl <<"层序遍历结点";
    if (!LeverOrder(T)) //层次遍历:abdc(1243)
    {
        cout << "NULL" << endl;
    }
    return 0;
}