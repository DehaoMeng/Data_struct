/*
 * 利用队列列出杨辉三角
 */
#include<iostream>
#include <iomanip>
#define OK 1
#define Error 0
using namespace std;
const int MaxSize = 100;
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
    int IsEmpty(){if(front->next == nullptr) return OK; else return Error;}
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


int main()
{
    LinkQueue<int> p,*L;
    L = &p;
    int s,t;
    int n;
    cin >> n;
    if (n < 1)
    {
        cout << "error" << endl;
        return OK;
    }
    cout<<"1"<<endl;
    L->InQueue(0);
    L->InQueue(1);
    L->InQueue(1);
    for(int j = 1; j < n; j++)
    {
        L->InQueue(0);
        do
        {
            s = L->OutQueue();
            t = L->GetQueue();
            if(t)
                cout<<t << " ";
            else cout<<endl;
            L->InQueue(s + t);
        }while(t != 0);
    }
    return OK;
}