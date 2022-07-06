    /*
    * ����������ʽ�洢
    */
#include <malloc.h>
#include <iostream>
using namespace std;
int num = 0;
typedef char ElemType;//��������������
#define MaxSize 20
//����������ʽ�洢�ṹ
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//��ָ��Ķ���
typedef struct {
    BiTree data[MaxSize];
    int front, rear;
} SqQueue;

//����������
//ab c  d  ;
//120300400;
bool CreateBiTree(BiTree &T) {
    ElemType s;
    cin >> s;
    if(s=='#') {
        T = nullptr;
    } else {
        //�������
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

//ǰ�����
bool PreOrder(BiTree &T) {
    if(T == nullptr) {
        return false;
    }
    cout << T->data << "  ";
    PreOrder(T->lchild);
    PreOrder(T->rchild);
    return true;
}


//�������
bool InOrder(BiTree &T) {
    if(T == nullptr) {
        return false;
    }
    InOrder(T->lchild);
    cout <<T->data;
    InOrder(T->rchild);
    return true;
}

//�������
bool PostOrder(BiTree &T) {
    if(T == nullptr) {
        return false;
    }
    PostOrder(T->lchild);
    PostOrder(T->rchild);
    cout << T->data << "  ";
    return true;
}

//��ʼ��ѭ������
void InitQueue(SqQueue &Q){
    Q.front = Q.rear = 0;
}

//�ж϶ӿ�
bool IsEmpty(SqQueue &Q){
    if(Q.front==Q.rear){
        return true;
    }else {
        return false;
    }
}

//���һ��Ԫ��
bool EnQueue(SqQueue &Q, BiTree x){
    //�ж϶��Ƿ���
    if(Q.front==(Q.rear+1)%MaxSize){
        return false;
    }
    Q.data[Q.rear] = x;
    Q.rear = (Q.rear+1)%MaxSize;
    return true;
}

//����һ��Ԫ��
bool DeQueue(SqQueue &Q, BiTree &x){
    //�ж϶����Ƿ�Ϊ��
    if(Q.front==Q.rear){
        return false;
    }
    x = Q.data[Q.front];
    Q.front = (Q.front+1)%MaxSize;
    return true;
}

//��α���
bool LeverOrder(BiTree &T) {
    if(EmptyBiTree(T)) return false;
    SqQueue Q;
    InitQueue(Q);
    BiTree p;
    EnQueue(Q, T);
    //����������
    while(!IsEmpty(Q)) {
        DeQueue(Q, p);
        cout << p->data;
        //������ӽ�����Ӳ��գ�����
        if(p->lchild) {
            EnQueue(Q, p->lchild);
        }
        //������ӽ���Һ��Ӳ��գ�����
        if(p->rchild) {
            EnQueue(Q, p->rchild);
        }
    }
    return true;
}

bool change_child(BiTree &T){
    if(EmptyBiTree(T)){
        return false;
    } else{
        if (T->rchild && T->lchild){
            BiTNode *p = (BiTNode*)malloc(sizeof(BiTNode));
            p = T->lchild;
            T->lchild = T->rchild;
            T->rchild = p;
        }
        change_child(T->lchild);
        change_child(T->rchild);
    }
    return true;
}

int Tree_depth(BiTree T){
    if (T == nullptr)
        return 0;
    int lDepth = Tree_depth(T->lchild);
    int rDepth = Tree_depth(T->rchild);

    return (((lDepth > rDepth)? lDepth:rDepth)+1);
}

bool Get_num(BiTree T){
    if(T == nullptr) return false;
    int l = Tree_depth(T->lchild);
    int r = Tree_depth(T->rchild);
    if (r == l) num++;
    Get_num(T->lchild);
    Get_num(T->rchild);
    return true;
}

int main() {
    BiTree T;
    CreateBiTree(T);
//    cout << "ǰ��������";
//    PreOrder(T); //ǰ�������abcd(1234)
//    cout << endl << "����������";

    if (EmptyBiTree(T))
        cout << "NULL";
    else {
        change_child(T);
        InOrder(T);  //���������bcad(2314)
    }
    cout << endl;
    Get_num(T);
    cout << num;
//    cout << endl <<"����������";
//    PostOrder(T);//���������cbda(3241)
//    cout << endl <<"����������";
//    if (!LeverOrder(T)) //��α���:abdc(1243)
//    {
//        cout << "NULL" << endl;
//    }
    return 0;
}