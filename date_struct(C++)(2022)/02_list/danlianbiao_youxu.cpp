/*
 * 有序单链表的实现
 * */

#include<iostream>
using namespace std;
const int MaxSize = 100;
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
    ~LinkList(){}// 析构函数
    void Insert(DataType x);
    void Delete(DataType e);
    void Printlist();
private:
    Node<DataType> *head;  // 创建
};
template<class DataType>
LinkList<DataType>::LinkList() {
    head = new Node<DataType>;
    head->next = nullptr;
    DataType data;
    cin >> data;
    while (data != -1){
        Insert(data);
        cin >> data;
    }
}
template<class DataType>
void LinkList<DataType>::Printlist(){
    auto p = head;
    while(p->next != nullptr)
    {
        p = p->next;
        cout << p->data << " ";
    }
    cout << endl;
}
template<class DataType>
void LinkList<DataType>::Insert(DataType x) {
    Node<DataType> *p = head;
    if(p == head) {
        if (p->next == nullptr) {
            Node<DataType> *r = new Node<DataType>;
            r->data = x;
            r->next = nullptr;
            p->next = r;
            return;
        } else if (p->next->data >= x) {
            Node<DataType> *r = new Node<DataType>;
            r->data = x;
            r->next = p->next;
            p->next = r;
            return;
        }
    }
    p = p->next;
    while (p->next != nullptr)
    {
        if(p->data <= x && p->next->data >= x){
            Node<DataType> *r = new Node<DataType>;
            r->data = x;
            r->next = p->next;
            p->next = r;
            break;
        }
        p = p->next;
    }
    if (p->next == nullptr)
    {
        Node<DataType> *r = new Node<DataType>;
        r->data = x;
        r->next = nullptr;
        p->next = r;
    }
}
template<class DataType>
void LinkList<DataType>::Delete(DataType e) {
    Node<DataType> *p = head;
    while (p->next != nullptr)
    {
        if(p->next->data == e){
            p->next = p->next->next;
        }
        p = p->next;
    }
}
int main() {
    LinkList<int> a;
    a.Printlist();
    int n;
    cin >> n;
    a.Insert(n);
    a.Printlist();
    cin >> n;
    a.Delete(n);
    a.Printlist();
    return 0;
}
