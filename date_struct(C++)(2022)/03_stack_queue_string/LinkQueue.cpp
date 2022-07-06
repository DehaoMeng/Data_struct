/*
 * 链式队列的c++实现
 */
#include<iostream>
#define OK 1
#define Error 0
using namespace std;

template <class DataType>
class LinkQueue
{
public:
    typedef struct node
    {
        DataType data;
        node *next;
    }Node;
    LinkQueue();
    ~LinkQueue();
    int InQueue(DataType x);
    DataType OutQueue();
    DataType GetQueue(){if(rear == front) throw "Error"; else return front->next->data;}
    int IsEmpty(){if(front == rear) return OK; else return Error;}
private:
    Node *front,*rear; // 队头、队尾
};

template <class DataType>
LinkQueue<DataType>::LinkQueue()
{
    // 创建空队列 队头队尾同时指向头节点。
    Node *s = new Node;
    s->next = nullptr;
    front = rear = s;
}

template <class DataType>
LinkQueue<DataType>::~LinkQueue()
{
    while (front->next != nullptr)
    {
        Node *s = front->next;
        front->next = rear->next;
        delete s;
    }
}

template <class DataType>
int LinkQueue<DataType>::InQueue(DataType x)
{
    Node *s =new Node;
    if(!s) return Error;
    s->data = x;
    s->next = nullptr;
    rear->next = s;
    rear = s;
    return OK;
}

template <class DataType>
DataType LinkQueue<DataType>::OutQueue()
{
    if (rear == front) throw "Error";
    Node *p = front->next;
    DataType x = p->data;
    front->next = p->next;
    if(p->next == nullptr) rear = front;
    delete p;
    return x;
}

int main() {
    LinkQueue<int> *L, p;
    L = &p;
    L->InQueue(1);
    L->InQueue(2);
    L->InQueue(3);
    cout << L->IsEmpty() << endl;
    cout << "-------" << endl;
    cout << L->GetQueue() << endl;
    cout << "-------" << endl;
    cout << L->OutQueue() << endl;
    cout << L->OutQueue() << endl;
    cout << L->OutQueue() << endl;
    cout << "-------" << endl;
    cout << L->IsEmpty() << endl;
    return OK;
}
