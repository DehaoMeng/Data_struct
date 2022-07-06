/*
 * 双栈c++实现
 */
#include<iostream>
using namespace std;
#define OK 1
#define Error 0
const int MaxSize = 12;
template<class DataType>
class BothStack
{
public:
    BothStack(){top1 = -1;top2 = MaxSize;}
    ~BothStack(){}
    int Push(int i);
    DataType Pop(int i);
    DataType OutStack(int i);
    int IsEmpty(int i);
private:
    DataType data[MaxSize];
    int top1=-1,top2=MaxSize;
};

template<class DataType>
int BothStack<DataType>::Push(int i)
{
    if (i <= 1)
    {
        cout << "error" << endl;
        return Error;
    }
    if(top1 == top2-1) {
        cout << "full" << endl;
        return Error;
    }
    for (int j = 1; j < i; j++) {
        if (j % 2 != 0){
            data[++top1] = j;
        }
        if(top1 == top2-1) {
            cout << "full" << endl;
            return Error;
        }
    }
    for (int j = 1; j < i; j++) {
        if (j % 2 == 0)
        {
            data[--top2] = j;
        }
        if(top1 == top2-1) {
            cout << "full" << endl;
            return Error;
        }
    }
    return OK;
}

template<class DataType>
DataType BothStack<DataType>::Pop(int i)
{
    if(i == 1){
        if(top1 == -1) {
            cout << "stack1:empty" << endl;
            return -1;
        }
        cout << data[top1--] << endl;
        return data[top1];
    }
    if(i == 2){
        if(top2 == MaxSize) {
            cout << "stack2:empty" << endl;
            return -1;
        }
        cout << data[top2++] << endl;
        return data[top2];
    }
    throw "Error";
}

template<class DataType>
DataType BothStack<DataType>::OutStack(int i)
{
    if (i == 1 && top1 != -1)
    {
        cout << "stack1:";
        while (top1 != -1)
            cout << data[top1--] << " ";
    }
    if (i == 2 && top2 != MaxSize)
    {
        cout << "stack2:";
        while (top2 != MaxSize)
            cout << data[top2++] << " ";
    }
    cout << endl;
    return OK;
}

template<class DataType>
int BothStack<DataType>::IsEmpty(int i)
{
    if((i == 1 && top1 == -1) || (i == 2 && top2 == MaxSize)) return OK;
    else return Error;
}

int main()
{
    BothStack<int> p,*L;
    L = &p;
    L->Pop(1);
    L->Pop(2);
    int m;
    cin >> m;
    L->Push(m);
    L->Pop(1);L->Pop(2);
    L->OutStack(1);
    L->OutStack(2);
    return OK;
}