/*
 * 完全二叉树的顺序实现
 */
#include <iostream>
#include<cstring>
#include<queue>
using namespace std;
const int OK = 1;
const int MAXSIZE = 100;
const int Error = 0;
typedef int ElemType;
class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();
    int CreatTree();//创建一棵二叉树
    void Getelem(int i);//获取树中第i个结点
    void PreOrderTraversel(int i = 1);//前序遍历，如果传入i的值就用传入的，没传入默认i为1
    void InOrderTraversel(int i = 1);//中序遍历
    void PostOrderTraversel(int i = 1);//后序遍历
    void LevelTraversel();//层序遍历
    int Depth(int i=1);//获取二叉树的深度
    int NodeNum(int i=1);//获取所有结点数目
    int LeafNum(int i=1);//获取所有叶子节点数目
private:
    ElemType* ptr;//维护树中的每一个结点
    int length;//记录树中结点个数
};
//二叉树的顺序存储其实还是用数组来实现
BinaryTree::BinaryTree()
{
    ptr=new ElemType[MAXSIZE];//在堆区创建一块MAXSIZE这么大的内存，存放int类型数据，用ptr维护
    memset(ptr, 0, MAXSIZE);//对数组初始化：先用0来填充这些位置
}
BinaryTree::~BinaryTree()
{
    delete[] ptr;
}
int BinaryTree::CreatTree()//创建一棵二叉树
{
    int n;
    cout << "您想创建几个结点的二叉树：";
    cin >> n;
    if (n <= 0 || n > MAXSIZE)
    {
        cout << "您的输入有误，请重新输入！" << endl;
    }
    else
    {
        length = n;//**这里是最重要的，一定要先将树的长度指定好
        cout << "请分别输入各结点的值:";
        for (int i = 0; i < n; i++)
        {
            cin >> ptr[i];
        }
    }
    return OK;
}
void BinaryTree::Getelem(int i)//获取树中第i个结点
{
    if (ptr[i - 1] != 0)//树中的第i元素，下标为i-1，判断它是不是0
    {
        cout << ptr[i - 1] << " ";
    }
}
void BinaryTree::PreOrderTraversel(int i)//前序遍历
{
    //二叉树的前序遍历：根 左 右
    if (!length)
        return;//提高代码鲁棒性：判断二叉树是否为空，空返回false
    else
    {
        if (ptr[i-1]!=0)
        {
            Getelem(i);//先输出根节点的值
            PreOrderTraversel(2 * i);//递归左子树
            PreOrderTraversel(2 * i + 1);//递归右子树
        }
        else
            return;
    }
}
void BinaryTree::InOrderTraversel(int i)//中序遍历
{
    //二叉树的中序遍历：左 根 右
    if (!length)
        return;//提高代码鲁棒性：判断二叉树是否为空，空返回false
    else
    {
        if (ptr[i - 1] != 0)
        {
            InOrderTraversel(2 * i);//递归左子树
            Getelem(i);//先输出根节点的值
            InOrderTraversel(2 * i + 1);//递归右子树
        }
        else
            return;
    }
}
void BinaryTree::PostOrderTraversel(int i)//后序遍历
{
    //二叉树的后序遍历：左 右 根
    if (!length)
        return;//提高代码鲁棒性：判断二叉树是否为空，空返回false
    else
    {
        if (ptr[i - 1] != 0)
        {
            PostOrderTraversel(2 * i);//递归左子树
            PostOrderTraversel(2 * i + 1);//递归右子树
            Getelem(i);//先输出根节点的值
        }
        else
            return;
    }
}
void BinaryTree::LevelTraversel()//层序遍历
{
    //二叉树的层序遍历与上述三种遍历方式不同，要利用队列先进先出的特性来辅助实现
    if (!length)
        return ;
    else
    {
        queue<int>q;
        int i = 1;
        q.push(i);
        while (!q.empty())
        {
            if (ptr[q.front() - 1] != 0)
            {
                int i = q.front();
                q.push(i * 2);
                q.push(i * 2 + 1);
                Getelem(i);
                q.pop();
            }
            else return;
        }
    }
}
int BinaryTree::Depth(int i)//获取二叉树的深度
{
    //获取二叉树的深度先要判别左子树和右子树的深度哪个比较大，取大的再加root这一层就妥了
    if (!length)
        return Error;
    else
    {
        if (ptr[i - 1] != 0)//这里就是判断每一层的root是否存在
        {
            int m = Depth(i * 2);//递归左子树，获得左子树的深度
            int n = Depth(i * 2 + 1); //递归左子树，获得左子树的深度
            return m > n ? (m + 1) : (n + 1);//判断哪个深度大，取大的加一
        }
        else return Error;
    }
}
int BinaryTree::NodeNum(int i)//获取所有结点数目
{
    //左子树的所有节点加上右子树的所有节点加上root
    if (!length)
        return Error;
    else
    {
        if (ptr[i - 1] != 0)
        {
            return NodeNum(i * 2) + NodeNum(i * 2 + 1) + 1;
        }
        else
            return Error;
    }
}
int BinaryTree::LeafNum(int i)//获取所有叶子节点数目
{
    if (!length)
        return 0;
    else
    {
        if (ptr[i * 2] == 0 && ptr[2 * i + 1] == 0)
            return Error;//左右子树都不存在，就有个root
        else if (ptr[i * 2] != 0 && ptr[2 * i + 1] == 0)//左子树存在
            return LeafNum(i * 2);//递归左子树
        else if (ptr[i * 2] == 0 && ptr[2 * i + 1] != 0)//右子树存在
            return LeafNum(i * 2 + 1);//递归右子树
        else return LeafNum(i * 2) + LeafNum(i * 2 + 1);

    }
}
int main()
{
    BinaryTree bi;
    bi.CreatTree();
    cout << "先序递归遍历：";
    bi.PreOrderTraversel();
    cout << endl;
    cout << "中序递归遍历：";
    bi.InOrderTraversel();
    cout << endl;
    cout << "后序递归遍历：";
    bi.PostOrderTraversel();
    cout << endl;
    cout << "层次遍历：";
    bi.LevelTraversel();
    cout << endl;
    cout << "深度：" << bi.Depth();
    cout << endl;
    cout << "结点数：" << bi.NodeNum();
    cout << endl;
    cout << "叶子结点数：" << bi.LeafNum();
    cout << endl;
}