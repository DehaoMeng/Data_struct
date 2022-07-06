//
// �������ʵ��
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
    ~LinkList();// ��������
    void Insert(DataType x);
    DataType Get(int i); // ��ȡ������λ��i��Ԫ��
    int CutLink(LinkList<DataType> *P,int x);
    void PrintList(); // ��ӡ���������
    int GetCounts(DataType x);
    int GetLast();
private:
    Node<DataType> *head;  // ����
};
// ���캯�� β�巨����
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

// �������� ɾ��������
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

//��ȡ������λ��i��Ԫ��
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

// ��ӡ���������
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
    /*������������ָ���Ϊ������β��nextָ��P�����ͷ����next��������Ľ�����P����ĩβ��*/
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
    Node<DataType> *s = p->next; // ������
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