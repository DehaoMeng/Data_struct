//
// 单链表的实现
// Created by 86176 on 2022/1/23 0023.
//
#include<iostream>
using namespace std;

template<class DataType>
struct Node{
    DataType data;
    Node<DataType> *next;
};
template<class DataType>
class LinkList
{
public:
    LinkList();
    ~LinkList();// 析构函数
    void Insert(DataType x);
    DataType Get(int i); // 获取单链表位置i的元素
    int CutLink(LinkList<DataType> *P,int x);
    void PrintList(); // 打印输出单链表
    int GetCounts(DataType x);
    int GetLast();
private:
    Node<DataType> *head;  // 创建
};
// 构造函数 尾插法构造
template <class DataType>
LinkList<DataType>::LinkList()
{

    head = new Node<DataType>;
    head->next = nullptr;
    Node<DataType> *r = head;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        DataType m;
        cin >> m;
        auto s = new Node<DataType>;
        s->data = m;
        s->next = nullptr;
        r->next = s;
        r = s;
    }
    r->next = nullptr;
}

// 析构函数 删除单链表
template<class DataType>
LinkList<DataType>::~LinkList()
{
    while (head != nullptr)
    {
        Node<DataType>* q = head;
        head = head->next;
        delete q;
    }
}

//获取单链表位置i的元素
template <class DataType>
DataType LinkList<DataType>::Get(int i)
{
    Node<DataType> *p = head->next;
    int count=1;
    while(count < i && p != nullptr)
    {
        p = p->next;
        count++;
    }
    if(p == nullptr) {
        return 0;
    }
    else return p->data;
}

// 打印输出单链表
template <class DataType>
void LinkList<DataType>::PrintList()
{
    auto p = head;
    while(p->next != nullptr)
    {
        p = p->next;
        cout << p->data << " ";
    }
    cout << endl;
}

template<class DataType>
int LinkList<DataType>::CutLink(LinkList<DataType> *P,int x) {
    /*将本来的链表指向表为，将表尾的next指向P链表的头结点的next，将本身的结点存在P链表末尾。*/
    auto p = head;
    while (--x)
    {
        if(p->next == nullptr && x != 0)
            return 0;
        p = p->next;
    }
//    if(x!=0) { cout << "error" <<endl;
//        throw "error";
//    }
    Node<DataType> *s = p->next; // 保存结点
    int i = 1;
    while (P->GetLast() != P->Get(i))
    {
        Node<DataType> *r = new Node<DataType>;
        r->data = P->Get(i);
        r->next = nullptr;
        p->next = r;
        p =p->next;
        i++;
    }
    Node<DataType> *r = new Node<DataType>;
    r->data = P->GetLast();
    r->next = s;
    p->next = r;
    return 1;
}

template<class DataType>
int LinkList<DataType>::GetLast() {
    Node<DataType> *p = head;
    while (p->next != nullptr)
    {
        p = p->next;
    }
    return p->data;
}
template<class DataType>
void LinkList<DataType>::Insert(DataType x) {
    Node<DataType> *p = head;
    while (p->next != nullptr)
    {
        p = p->next;
    }
    Node<DataType> *r = new Node<DataType>;
    r->data = x;
    r->next = nullptr;
    p->next = r;
}

template<class DataType>
int LinkList<DataType>::GetCounts(DataType x) {
    auto q = head->next;
    int counts = 0;
    while(q != nullptr)
    {
        if(q->data == x) counts++;
        q = q->next;
    }
    return counts;
}


int main()
{
    int n;
    LinkList<int> head;
    head.PrintList();
    cin >> n;
    if(head.Get(n) == 0){
        cout << "error" << endl;
    } else {
        cout << head.Get(n) << endl;
    }
    LinkList<int> head1;
    head1.PrintList();
    cin >> n;
    if (head.CutLink(&head1,n)==0)
    {
        cout << "error" <<endl;
    }
    head.PrintList();
    cin >> n;
    cout << head.GetCounts(n) <<endl;
    return 0;
}