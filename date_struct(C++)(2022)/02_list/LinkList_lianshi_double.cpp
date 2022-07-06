//
// 双链表的实现
// Created by 86176 on 2022/1/24 0024.
//
#include <iostream>

using namespace std;
#define OK 1
#define Error 0
template <class DataType>
struct DLNode
{
    DataType data;
    DLNode<DataType> *prior,*next;
};

template <class DataType>
class LinkList
{
private:
    DLNode<DataType> *head;
public:
    LinkList();
    LinkList(DataType a[], int n);
    ~LinkList();
    int Length();
    DataType Get(int i);
    int Locate(DataType x);
    bool Insert(int i, DataType x);
    DataType Delete(int i);
    bool PrintList();
};

template <class DataType>
LinkList<DataType>::LinkList()
{
    head = new DLNode<DataType>;
    head->next = NULL;
    head->prior = NULL;
}

template <class DataType>
LinkList<DataType>::LinkList(DataType a[], int n)
{
    head = new DLNode<DataType>;
    head->next = NULL;
    head->prior = NULL;
    for (int i = 0; i < n; i++) {
        DLNode<DataType> *s = new DLNode<DataType>;
        s->data = a[i];
        s->prior = head;
        s->next = head->next;
        head->next = s;
    }
}

template<class DataType>
LinkList<DataType>::~LinkList()
{
    while(head->next!= NULL)
    {
        DLNode<DataType> *s = head;
        if(head->prior != NULL)
            head->prior->next = head->next;
        head = head->next;
        delete s;
    }
    delete head;
}

template <class DataType>
int LinkList<DataType>::Length()
{
    int count = 0;
    DLNode<DataType> *p = head->next;
    while(p != NULL)
    {
        p = p->next;
        count ++;
    }
    return count;
}

template<class DataType>
DataType LinkList<DataType>::Get(int i)
{
    DLNode<DataType> *p = head->next;
    int count = 1;
    while(count < i-1 && p != NULL)
    {
        p = p->next;
        count++;
    }
    if(p == head && count != 1) throw "Error";
    return p->data;
}

template <class DataType>
int LinkList<DataType>::Locate(DataType x)
{
    DLNode<DataType>* p=head->next;
    int count=1;
    while (p != NULL)
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
    int count = 0;
    DLNode<DataType>* p = head;
    while(p->next != NULL && count < i - 1)
    {
        p = p->next;
        count++;
    }
    if(count != 0 && p == NULL)
    {
        cout << "超出双链表长度" << endl;
        return false;
    }
    else
    {
        DLNode<DataType> *s = new DLNode<DataType>;
        s->data = x;
        // 在尾节点插入时
        if(p->next == NULL)
        {
            s->next = NULL;
            s->prior = p;
            p->next = s;

        } else
        {
            s->next = p->next;
            s->prior = p;
            p->next->prior = s;
            p->next = s;
        }
        return true;
    }
}

template <class DataType>
DataType LinkList<DataType>::Delete(int i)
{
    DLNode<DataType>* p = head;
    int count = 0;
    while (p != NULL && count < i - 1)
    {
        p = p->next;
        count++;
    }
    if(count != 0 && p == NULL)
    {
        cout << "超出链表长度" << endl;
        throw "Error";
    }
    else
    {
        DLNode<DataType>* s = p->next;
        DataType x = s->data;
        s->next->prior = s->prior;
        s->prior->next = s->next;
        return x;
    }
}

template <class DataType>
bool LinkList<DataType>::PrintList()
{
    DLNode<DataType>* p = head->next;
    while(p != NULL)
    {
        cout << p->data <<endl;
        p = p->next;
    }
    return true;
}

int main()
{
    LinkList<int> p, *L;
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