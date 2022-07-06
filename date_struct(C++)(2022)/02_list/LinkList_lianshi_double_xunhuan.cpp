/*
 *           循环双链表的实现
 * Created by 86176 on 2022/1/23 0023.
 */
#include<iostream>
using namespace std;
#define OK 1
#define Error 0

template <class DataType>
struct DblNode{
    DataType data;
    DblNode<DataType> *prior, *next; // 前驱和后继
};
//类模板
template <class DataType>
class LinkList
{
public:
    LinkList();
    LinkList(DataType a[],int n);
    ~LinkList();
    int Length();
    DataType Get(int i);
    int Locate(DataType x);
    bool Insert(int i, DataType x);
    DataType Delete(int i);
    void PrintList();
private:
    DblNode<DataType> *head; // 创建头指针
};
// 构造函数
template <class DataType>
LinkList<DataType>::LinkList()
{
    head = new DblNode<DataType>;
    head->next = head;
    head->prior = head;
}

template <class DataType>
LinkList<DataType>::LinkList(DataType a[], int n)
{
    head = new DblNode<DataType>;
    head->next = NULL;
    for (int i = 0; i < n; i++) {
        DblNode<DataType> *s = new DblNode<DataType>;
        s->data = a[i];
        s->prior = head;
        s->next = head->next;
        head->next->prior = s;
        head->next = s;
    }
}
// 析构函数
template <class DataType>
LinkList<DataType>::~LinkList()
{
    while(head->next != head)
    {
        DblNode<DataType> *s = head;
        head->prior->next = head->next;
        head = head->next;
        delete s;
    }
}

template <class DataType>
int LinkList<DataType>::Length()
{
    DblNode<DataType> *s = head->next;
    int count = 0;
    while(s != head)
    {
        s = s->next;
        count ++;
    }
    return count;
}

template <class DataType>
DataType LinkList<DataType>::Get(int i)
{
    DblNode<DataType> *p = head->next;
    int count=1;
    while(p != head && count < i)
    {
        p = p->next;
        count++;
    }
    if(p == head && count != 1) throw "Error";
    else return p->data;
}

template <class DataType>
int LinkList<DataType>::Locate(DataType x)
{
    DblNode<DataType> *p = head->next;
    int count=1;
    while(p != head)
    {
        if(p->data == x) return count;
        p = p->next;
        count++;
    }
    return Error;
}

template <class DataType>
bool LinkList<DataType>::Insert(int i, DataType x)
{
    DblNode<DataType> *p = head;
    int count = 0;
    while (p->next != head && count < i - 1)
    {
        p = p->next;
        count++;
    }
    if (count!=0 && p == head)
    {
        throw "Location";
    }
    else {
        DblNode<DataType> *s = new DblNode<DataType>;
        s->data = x;
        s->prior = p;
        s->next = p->next;
        p->next->prior = s;
        p->next = s;
        return true;
    }
}

template <class DataType>
DataType LinkList<DataType>::Delete(int i)
{
    DblNode<DataType>* p = head;
    int count=0;
    while(p->next != head && count < i-1)
    {
        p = p->next;
        count++;
    }
    if(p == head && count != 0)
    {
        cout << "删除的位置超出链表长度" << endl;
        throw "Error";
    }
    else{
        DblNode<DataType>* s = p->next;
        DataType x = s->data;
        s->next->prior = s->prior;
        s->prior->next = s->next;
        return x;
    }
}

template <class DataType>
void LinkList<DataType>::PrintList()
{
    DblNode<DataType>* p = head->next;
    while(p != head)
    {
        cout << p->data <<endl;
        p = p->next;
    }
}

int main()
{
    LinkList<int> p,*L;
    L = &p;
    L->Insert(1,6);
    L->Insert(2, 9);
    L->PrintList();
    cout << "-------" << endl;
    L->Insert(2, 3);
    L->PrintList();
    cout << "-------" << endl;
    cout << L->Get(1) << endl;
    cout << L->Locate(6) << endl;
    cout << L->Length() << endl;
    cout << "-------" << endl;
    L->Delete(1);
    L->PrintList();
    return OK;
}