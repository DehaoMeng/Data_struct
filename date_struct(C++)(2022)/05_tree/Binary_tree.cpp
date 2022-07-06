/*
 * ��ȫ��������˳��ʵ��
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
    int CreatTree();//����һ�ö�����
    void Getelem(int i);//��ȡ���е�i�����
    void PreOrderTraversel(int i = 1);//ǰ��������������i��ֵ���ô���ģ�û����Ĭ��iΪ1
    void InOrderTraversel(int i = 1);//�������
    void PostOrderTraversel(int i = 1);//�������
    void LevelTraversel();//�������
    int Depth(int i=1);//��ȡ�����������
    int NodeNum(int i=1);//��ȡ���н����Ŀ
    int LeafNum(int i=1);//��ȡ����Ҷ�ӽڵ���Ŀ
private:
    ElemType* ptr;//ά�����е�ÿһ�����
    int length;//��¼���н�����
};
//��������˳��洢��ʵ������������ʵ��
BinaryTree::BinaryTree()
{
    ptr=new ElemType[MAXSIZE];//�ڶ�������һ��MAXSIZE��ô����ڴ棬���int�������ݣ���ptrά��
    memset(ptr, 0, MAXSIZE);//�������ʼ��������0�������Щλ��
}
BinaryTree::~BinaryTree()
{
    delete[] ptr;
}
int BinaryTree::CreatTree()//����һ�ö�����
{
    int n;
    cout << "���봴���������Ķ�������";
    cin >> n;
    if (n <= 0 || n > MAXSIZE)
    {
        cout << "���������������������룡" << endl;
    }
    else
    {
        length = n;//**����������Ҫ�ģ�һ��Ҫ�Ƚ����ĳ���ָ����
        cout << "��ֱ����������ֵ:";
        for (int i = 0; i < n; i++)
        {
            cin >> ptr[i];
        }
    }
    return OK;
}
void BinaryTree::Getelem(int i)//��ȡ���е�i�����
{
    if (ptr[i - 1] != 0)//���еĵ�iԪ�أ��±�Ϊi-1���ж����ǲ���0
    {
        cout << ptr[i - 1] << " ";
    }
}
void BinaryTree::PreOrderTraversel(int i)//ǰ�����
{
    //��������ǰ��������� �� ��
    if (!length)
        return;//��ߴ���³���ԣ��ж϶������Ƿ�Ϊ�գ��շ���false
    else
    {
        if (ptr[i-1]!=0)
        {
            Getelem(i);//��������ڵ��ֵ
            PreOrderTraversel(2 * i);//�ݹ�������
            PreOrderTraversel(2 * i + 1);//�ݹ�������
        }
        else
            return;
    }
}
void BinaryTree::InOrderTraversel(int i)//�������
{
    //������������������� �� ��
    if (!length)
        return;//��ߴ���³���ԣ��ж϶������Ƿ�Ϊ�գ��շ���false
    else
    {
        if (ptr[i - 1] != 0)
        {
            InOrderTraversel(2 * i);//�ݹ�������
            Getelem(i);//��������ڵ��ֵ
            InOrderTraversel(2 * i + 1);//�ݹ�������
        }
        else
            return;
    }
}
void BinaryTree::PostOrderTraversel(int i)//�������
{
    //�������ĺ���������� �� ��
    if (!length)
        return;//��ߴ���³���ԣ��ж϶������Ƿ�Ϊ�գ��շ���false
    else
    {
        if (ptr[i - 1] != 0)
        {
            PostOrderTraversel(2 * i);//�ݹ�������
            PostOrderTraversel(2 * i + 1);//�ݹ�������
            Getelem(i);//��������ڵ��ֵ
        }
        else
            return;
    }
}
void BinaryTree::LevelTraversel()//�������
{
    //�������Ĳ���������������ֱ�����ʽ��ͬ��Ҫ���ö����Ƚ��ȳ�������������ʵ��
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
int BinaryTree::Depth(int i)//��ȡ�����������
{
    //��ȡ�������������Ҫ�б���������������������ĸ��Ƚϴ�ȡ����ټ�root��һ�������
    if (!length)
        return Error;
    else
    {
        if (ptr[i - 1] != 0)//��������ж�ÿһ���root�Ƿ����
        {
            int m = Depth(i * 2);//�ݹ�����������������������
            int n = Depth(i * 2 + 1); //�ݹ�����������������������
            return m > n ? (m + 1) : (n + 1);//�ж��ĸ���ȴ�ȡ��ļ�һ
        }
        else return Error;
    }
}
int BinaryTree::NodeNum(int i)//��ȡ���н����Ŀ
{
    //�����������нڵ���������������нڵ����root
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
int BinaryTree::LeafNum(int i)//��ȡ����Ҷ�ӽڵ���Ŀ
{
    if (!length)
        return 0;
    else
    {
        if (ptr[i * 2] == 0 && ptr[2 * i + 1] == 0)
            return Error;//���������������ڣ����и�root
        else if (ptr[i * 2] != 0 && ptr[2 * i + 1] == 0)//����������
            return LeafNum(i * 2);//�ݹ�������
        else if (ptr[i * 2] == 0 && ptr[2 * i + 1] != 0)//����������
            return LeafNum(i * 2 + 1);//�ݹ�������
        else return LeafNum(i * 2) + LeafNum(i * 2 + 1);

    }
}
int main()
{
    BinaryTree bi;
    bi.CreatTree();
    cout << "����ݹ������";
    bi.PreOrderTraversel();
    cout << endl;
    cout << "����ݹ������";
    bi.InOrderTraversel();
    cout << endl;
    cout << "����ݹ������";
    bi.PostOrderTraversel();
    cout << endl;
    cout << "��α�����";
    bi.LevelTraversel();
    cout << endl;
    cout << "��ȣ�" << bi.Depth();
    cout << endl;
    cout << "�������" << bi.NodeNum();
    cout << endl;
    cout << "Ҷ�ӽ������" << bi.LeafNum();
    cout << endl;
}