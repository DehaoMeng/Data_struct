/*
 *  C++ 自定义类模板实现顺序栈
 */

#include<iostream>
#define OK 1
#define Error 0
using namespace std;
const int MaxSize = 100;


template <class DataType>
class Stack
{
private:
    DataType data[MaxSize];
    int top;
public:
    Stack(){top = -1;}
    ~Stack(){}
    int Push(DataType x);
    DataType Pop();
    DataType GetTop(){if(top != -1) return data[top]; else throw "Error";}
    int Isempty(){if(top == - 1) return OK;else return Error;}
};

template <class DataType>
int Stack<DataType>::Push(DataType x)
{
    if(top == MaxSize - 1){
        cout << "超出栈的长度" << endl;
        return Error;
    }
    data[++top] = x;
    return OK;
}

template<class DataType>
DataType Stack<DataType>::Pop()
{
    if(top == -1){
        cout << "此时栈为空" << endl;
        throw "Error";
    }
    DataType x = data[top--];
    return x;
}

int main()
{
    Stack<int> p,*L;
    L = &p;
    L->Push(1);
    L->Push(3);
    L->Push(2);
    cout << "-----" << endl;
    cout << L->Isempty() << endl;
    cout << L->GetTop() << endl;
    cout << "依次出栈：" << endl;
    cout << L->Pop() << endl;
    cout << L->Pop() << endl;
    cout << L->Pop() << endl;
    cout << "-----" << endl;
    cout << L->Isempty() << endl;
    return OK;
}