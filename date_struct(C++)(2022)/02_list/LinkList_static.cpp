/*
 静态链表的实现
 Created by 86176 on 2022/1/25 0025.
*/
#include <iostream>
using namespace std;
#define OK 1
#define Error 0
const int MaxSize = 100;

template <class DataType>
class StaticLinkList
{
public:
    typedef struct
    {
        DataType data;
        int next;
    }Node;
    StaticLinkList();
    StaticLinkList(DataType a[], int n);
    ~StaticLinkList(){};
    int Length(){return length;}
    DataType Get(int i);
    int Locate(DataType x);
    int Insert(int i, DataType x);
    DataType Delete(int i);
    int PrintList();
private:
    Node SList[MaxSize];
    int length;
    int cur;
};

template <class DataType>
StaticLinkList<DataType>::StaticLinkList()
{
    length = 0;
    for (int i = 1; i < MaxSize - 1; i++) {
        SList[i].next = i + 1;
    }
    SList[0].next = -1;
    SList[MaxSize - 1].next = -1;
    cur = 1;
}

template <class DataType>
StaticLinkList<DataType>::StaticLinkList(DataType a[], int n)
{
    length = 0;
    cur = 1;
    for (int i = 0; i < MaxSize - 1; ++i) {
        SList[i].next = i + 1;
    }
    SList[MaxSize - 1].next = -1;
    SList[0].next = cur;
    for (int j = cur; j <= n; j++) {
        SList[j].data = a[j - 1];
        SList[j].next = j + 1;
        length++;
    }
}


template <class DataType>
DataType StaticLinkList<DataType>::Get(int i)
{
    int m = 0;
    if(i > length || i < 1) throw "Error";
    else{
        for (int j = 0; j < i; j++) {
            m = SList[m].next;
        }
        return SList[m].data;
    }
}

template <class DataType>
int StaticLinkList<DataType>::Locate(DataType x)
{
    int m = 0;
    for (int i = 0; i < length; i++) {
        m = SList[m].next;
        if(SList[i].data == x) return i;
    }
    return Error;
}

template <class DataType>
int StaticLinkList<DataType>::Insert(int i, DataType x)
{
    if (i == MaxSize - 2) throw "FULL";
    else if(i<1 || i>length+1) throw "Location";
    else
    {
        int m = 0;
        for (int j = 0; j < i - 1; j++) {
            m = SList[m].next;
        }
        int t = cur;
        cur = SList[cur].next;
        int s = SList[m].next;
        SList[m].next = t;
        SList[t].data = x;
        SList[t].next = s;
        length++;
        return OK;
    }
}

template <class DataType>
DataType StaticLinkList<DataType>::Delete(int i) {
    if(i<1 || i>length) throw "Location";
    else {
        int m = 0;
        for (int j = 0; j < i - 1; j++) {
            m = SList[m].next;
        }
        DataType temp = SList[SList[m].next].data;
        int t = SList[m].next;
        SList[m].next = SList[SList[m].next].next;
        SList[t].next = cur;
        cur = t;
        length--;
        return temp;
    }
}

template <class DataType>
int StaticLinkList<DataType>::PrintList()
{
    int m = 0;
    if (length != 0)
        cout << "Location" << ":data" << endl;
    else
        cout << "静态链表为空" << endl;
    for(int i = 0;i<length;i++)
    {
        m = SList[m].next;
        cout<<m<<":";
        cout<<SList[m].data<<" "<<endl;
    }
    return OK;
}


int main()
{
    StaticLinkList<int> p,*L;
    L = &p;
    L->PrintList();
    L->Insert(1,3);
    L->Insert(2,6);
    L->PrintList();
    cout << "----" << endl;
    L->Insert(2,9);
    L->PrintList();
    cout << "----" << endl;
    cout<<L->Get(2)<<endl;
    cout<<L->Length()<<endl;
    cout<<L->Locate(6)<<endl;
    cout << "----" << endl;
    L->Delete(1);
    L->PrintList();
    return OK;
}