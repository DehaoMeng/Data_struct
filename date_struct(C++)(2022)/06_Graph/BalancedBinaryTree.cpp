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
    //*T��û�����ӣ���û���Һ��ӣ�ΪҶ�ӽ��
    if (!(*T)->lchild && !(*T)->rchild)
        *T = nullptr;
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
BiTree* SearchBST1(BiTree *T, int key){
    if (!T)                        //����������ʧ��
        return nullptr;
    else if (key == T->data)    //���ҳɹ�
        return T;
    else if (key < T->data)        //���������м�������
        return SearchBST1(T->lchild, key);
    else                        //���������м�������
        return SearchBST1(T->rchild, key);
}

bool SearchBST2(BiTree *T, BiTree *F, int key, BiTree **p){
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
bool DeleteBST(BiTree **T, int key)
{
    if (!*T)        //���������޴˽�㡣
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
 * �������
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
 * ����ݹ����
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
 * ��������
 */
bool PrintElement(int e)
{
    cout << e << " ";
    return true;
}
int main()
{
    BiTree *T = nullptr;//ע��һ��Ҫ�Ƚ�T��ʼ��Ϊ����
    int i, num;

    //ʹ�ò����������������������(����������Ѽ�����Һ���SearchBST2())
    cin >> num;
    while(num != -1){
        InsertBST(&T, num);
        cin >> num;
    }

    //�������Ч����������������������Ϊ��С���󣬱�������ɹ���
    InOrderTraverse_Recursive(T, PrintElement);
    putchar('\n');

    //ɾ������
    cin >> num;
    DeleteBST(&T, num);

    //����ɾ������
    InOrderTraverse_Recursive(T, PrintElement);
    putchar('\n');
    cin >> num;
    InOrder(T, PrintElement,num);

    return 0;
}
