/*
 * 哈夫曼树（最优二叉树）的实现
 */
#include <iostream>
using namespace std;
const int MAXSIZE = 100;
/*哈夫曼树的节点定义*/
template <typename T>
struct HuffmanNode
{
    //初始化
    HuffmanNode(T k,HuffmanNode<T>* l,HuffmanNode<T>* r):key(k),lchild(l),rchild(r),flag(0) {}

    T key;                  //节点权值
    HuffmanNode<T>* lchild; //节点左孩
    HuffmanNode<T>* rchild; //节点右孩
    int flag;               //标志　判断是否从森林中删除
};
template <typename T>
class Huffman
{
public:
    void preOrder();        //前序遍历哈夫曼树
    void inOrder();         //中序遍历哈夫曼树
    void postOrder();       //后序遍历哈夫曼树

    void creat(T a[],int size); //创建哈夫曼树
    void destory();             //销毁哈夫曼树
    void print();               //打印哈夫曼树

    void my_sort(int size);
    Huffman():root(NULL) {}
    ~Huffman(){
        destory(root);
    }
private:
    void preOrder(HuffmanNode<T>* pnode);   //前序遍历二叉树
    void inOrder(HuffmanNode<T>* pnode);    //中序遍历二叉树
    void postOrder(HuffmanNode<T>* pnode);  //后序遍历二叉树
    void print(HuffmanNode<T>* pnode);      //打印二叉树
    void destory(HuffmanNode<T>* pnode);    //销毁二叉树

    HuffmanNode<T>* root;            //哈夫曼树根节点
    HuffmanNode<T>* forest[MAXSIZE]; //用数组来存储森林中树的根节点
};
/*自写排序*/
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

/*创建哈夫曼树*/
template <typename T>
void Huffman<T>::creat(T a[],int size)
{
    int j,k=0;
    /*每个节点都作为一个森林*/
    for(int i=0; i<size; i++)
    {
        HuffmanNode<T>* ptr = new HuffmanNode<T>(a[i],NULL,NULL);
        forest[i] = ptr; //双向队列尾部加入一个元素
    }
    for(int i=0; i<size-1; i++)
    {
        /*排序　选出根节点权值最小的两棵树*/
        my_sort(size+k);
        for(j=0; ; j++)
        {
            if(forest[j]->flag!=1 && forest[j+1]->flag != 1)
            {
                /*构建新节点*/
                HuffmanNode<T>* node = new HuffmanNode<T>(forest[j]->key + forest[j+1]->key,forest[j],forest[j+1]);
                /*新节点加入森林中*/
                forest[size+k] = node;
                k++;
                /*删除两棵权值最小的树*/
                forest[j]->flag = 1;
                forest[j+1]->flag = 1;
                break;
            }
            else
                continue;
        }
    }
    root  = forest[size+k-1]; // 根节点即为最大数值
};

/*递归法前序遍历哈夫曼树*/
template <typename T>
void Huffman<T>::preOrder(HuffmanNode<T>* pnode)
{
    if(pnode != NULL)
    {
        cout << pnode -> key << " ";    // 打印根节点
        preOrder(pnode->lchild); // 打印左子树
        preOrder(pnode->rchild); // 打印右子树
    }
};
/* 外部可调用函数 */
template <typename T>
void Huffman<T>::preOrder()
{
    preOrder(root); // 调用类中的前序遍历函数
};

/*中序遍历哈夫曼树*/
template <typename T>
void Huffman<T>::inOrder(HuffmanNode<T>* pnode)
{
    if(pnode != NULL)
    {
        inOrder(pnode->lchild); // 先打印左子树
        cout << pnode -> key << " ";   // 打印根节点
        inOrder(pnode->rchild); // 打印右子树
    }
};
template <typename T>
void Huffman<T>::inOrder()
{
    inOrder(root);
};

/*后序遍历哈夫曼树*/
template <typename T>
void Huffman<T>::postOrder(HuffmanNode<T>* pnode)
{
    if(pnode != NULL)
    {
        postOrder(pnode->lchild); // 打印左子树
        postOrder(pnode->rchild); // 打印右子树
        cout << pnode -> key << " ";     // 打印根节点
    }
};
template <typename T>
void Huffman<T>::postOrder()
{
    postOrder(root);
};

/*打印哈夫曼树*/
template <typename T>
void Huffman<T>::print(HuffmanNode<T>* pnode)
{
    if(pnode != NULL)
    {
        cout << "当前结点：" << pnode -> key << ".";
        if(pnode -> lchild != NULL)
            cout << "它的左孩子结点为：" << pnode->lchild->key << ".";
        else
            cout << "它没有左孩子.";
        if(pnode -> rchild != NULL)
            cout << "它的右孩子结点为：" << pnode->rchild->key << ".";
        else
            cout << "它没有右孩子.";
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

/*销毁哈夫曼树*/
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