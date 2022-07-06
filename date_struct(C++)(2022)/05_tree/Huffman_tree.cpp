/*
 * �������������Ŷ���������ʵ��
 */
#include <iostream>
using namespace std;
const int MAXSIZE = 100;
/*���������Ľڵ㶨��*/
template <typename T>
struct HuffmanNode
{
    //��ʼ��
    HuffmanNode(T k,HuffmanNode<T>* l,HuffmanNode<T>* r):key(k),lchild(l),rchild(r),flag(0) {}

    T key;                  //�ڵ�Ȩֵ
    HuffmanNode<T>* lchild; //�ڵ���
    HuffmanNode<T>* rchild; //�ڵ��Һ�
    int flag;               //��־���ж��Ƿ��ɭ����ɾ��
};
template <typename T>
class Huffman
{
public:
    void preOrder();        //ǰ�������������
    void inOrder();         //���������������
    void postOrder();       //���������������

    void creat(T a[],int size); //������������
    void destory();             //���ٹ�������
    void print();               //��ӡ��������

    void my_sort(int size);
    Huffman():root(NULL) {}
    ~Huffman(){
        destory(root);
    }
private:
    void preOrder(HuffmanNode<T>* pnode);   //ǰ�����������
    void inOrder(HuffmanNode<T>* pnode);    //�������������
    void postOrder(HuffmanNode<T>* pnode);  //�������������
    void print(HuffmanNode<T>* pnode);      //��ӡ������
    void destory(HuffmanNode<T>* pnode);    //���ٶ�����

    HuffmanNode<T>* root;            //�����������ڵ�
    HuffmanNode<T>* forest[MAXSIZE]; //���������洢ɭ�������ĸ��ڵ�
};
/*��д����*/
template <typename T>
void Huffman<T>::my_sort(int size)
{
    for(int i=0;i<size-1;i++)
    {
        for(int j=i+1;j<size;j++)
        {
            if(forest[i]->key > forest[j]->key)
            {
                swap(forest[i],forest[j]);
            }
            else
                continue;
        }
    }
};

/*������������*/
template <typename T>
void Huffman<T>::creat(T a[],int size)
{
    int j,k=0;
    /*ÿ���ڵ㶼��Ϊһ��ɭ��*/
    for(int i=0; i<size; i++)
    {
        HuffmanNode<T>* ptr = new HuffmanNode<T>(a[i],NULL,NULL);
        forest[i] = ptr; //˫�����β������һ��Ԫ��
    }
    for(int i=0; i<size-1; i++)
    {
        /*����ѡ�����ڵ�Ȩֵ��С��������*/
        my_sort(size+k);
        for(j=0; ; j++)
        {
            if(forest[j]->flag!=1 && forest[j+1]->flag != 1)
            {
                /*�����½ڵ�*/
                HuffmanNode<T>* node = new HuffmanNode<T>(forest[j]->key + forest[j+1]->key,forest[j],forest[j+1]);
                /*�½ڵ����ɭ����*/
                forest[size+k] = node;
                k++;
                /*ɾ������Ȩֵ��С����*/
                forest[j]->flag = 1;
                forest[j+1]->flag = 1;
                break;
            }
            else
                continue;
        }
    }
    root  = forest[size+k-1]; // ���ڵ㼴Ϊ�����ֵ
};

/*�ݹ鷨ǰ�������������*/
template <typename T>
void Huffman<T>::preOrder(HuffmanNode<T>* pnode)
{
    if(pnode != NULL)
    {
        cout << pnode -> key << " ";    // ��ӡ���ڵ�
        preOrder(pnode->lchild); // ��ӡ������
        preOrder(pnode->rchild); // ��ӡ������
    }
};
/* �ⲿ�ɵ��ú��� */
template <typename T>
void Huffman<T>::preOrder()
{
    preOrder(root); // �������е�ǰ���������
};

/*���������������*/
template <typename T>
void Huffman<T>::inOrder(HuffmanNode<T>* pnode)
{
    if(pnode != NULL)
    {
        inOrder(pnode->lchild); // �ȴ�ӡ������
        cout << pnode -> key << " ";   // ��ӡ���ڵ�
        inOrder(pnode->rchild); // ��ӡ������
    }
};
template <typename T>
void Huffman<T>::inOrder()
{
    inOrder(root);
};

/*���������������*/
template <typename T>
void Huffman<T>::postOrder(HuffmanNode<T>* pnode)
{
    if(pnode != NULL)
    {
        postOrder(pnode->lchild); // ��ӡ������
        postOrder(pnode->rchild); // ��ӡ������
        cout << pnode -> key << " ";     // ��ӡ���ڵ�
    }
};
template <typename T>
void Huffman<T>::postOrder()
{
    postOrder(root);
};

/*��ӡ��������*/
template <typename T>
void Huffman<T>::print(HuffmanNode<T>* pnode)
{
    if(pnode != NULL)
    {
        cout << "��ǰ��㣺" << pnode -> key << ".";
        if(pnode -> lchild != NULL)
            cout << "�������ӽ��Ϊ��" << pnode->lchild->key << ".";
        else
            cout << "��û������.";
        if(pnode -> rchild != NULL)
            cout << "�����Һ��ӽ��Ϊ��" << pnode->rchild->key << ".";
        else
            cout << "��û���Һ���.";
        cout << endl;
        if(pnode -> lchild != NULL)
                print(pnode->lchild);
        if(pnode -> rchild != NULL)
                print(pnode->rchild);
    }
};
template <typename T>
void Huffman<T>::print()
{
    print(root);
};

/*���ٹ�������*/
template <typename T>
void Huffman<T>::destory(HuffmanNode<T>* pnode)
{
    if( pnode!= NULL)
    {
        destory(pnode->lchild);
        destory(pnode->rchild);
        delete pnode;
        pnode = NULL;
    }
};
template <typename T>
void Huffman<T>::destory()
{
    destory(root);
};
int main()
{
    Huffman<int> huff,*huf;
    int a[] = {10,20,30,40};
    huff.creat(a,4);
    huf = &huff;
    huf->preOrder();
    cout << endl;
    huf->inOrder();
    cout << endl;
    huf->postOrder();
    cout << endl;
    huf->print();
    return 0;
}