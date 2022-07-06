/*
 * 链式栈实现 == 头插法创建链表 只能从头节点取出
 */
#include <iostream>

#define OK 1
#define Error 0
using namespace std;

template <class DataType>
class LinkStack
{
public:
    typedef struct node{
        DataType data;
        node *next;
    }Node;
    LinkStack(){top = NULL;}
    ~LinkStack();
    int Length(){if (top != NULL)return length;else return Error;}
    int Push(DataType x);
    DataType Pop();
    DataType GetTop(){if(top != NULL) return top->data; else throw "Error";}
    int IsEmpty(){if(top == NULL) return OK;else return Error;}
private:
    Node *top;
    int length=0;
};

template <class DataType>
LinkStack<DataType>::~LinkStack()
{
    while (top != NULL)
    {
        Node* p = top;
        top = top->next;
        delete p;
    }
}

template <class DataType>
int LinkStack<DataType>::Push(DataType x)
{
    Node *s =new Node;
    s->next = top;
    s->data = x;
    top = s;
    length++;
    return OK;
}

template <class DataType>
DataType LinkStack<DataType>::Pop()
{
    if(top == NULL) throw "Error";
    Node *s = top;
    DataType x = top->data;
    top = top->next;
    delete s;
    return x;

}

int main()
{
    LinkStack<int> s,*L;
    L = &s;
    cout<<L->IsEmpty()<<endl;
    cout << "-------" <<endl;
    cout << L->Length() << endl;
    L->Push(3);
    L->Push(8);
    cout <<L->Length()<<endl;
    cout << "-------" <<endl;
    cout<<L->GetTop()<<endl;
    cout << L->Pop() << endl;
    cout<<L->GetTop( )<<endl;
    cout << L->Pop() <<endl;
    cout << "-------" <<endl;
    cout<<L->IsEmpty()<<endl;
    return OK;
}