/*
 * 顺序队列的c++实现
 * 队头指向数组头，数组头不存储数据，即队列只能存储MaxSize-1的数据
 */
#include <iostream>
#define OK 1
#define Error 0
const int MaxSize = 100;
using namespace std;

template <class DataType>
class Queue
{
private:
    DataType data[MaxSize];
    int front, rear;
public:
    Queue(){front = rear = 0;}
    ~Queue(){};
    int Length(){return rear;}
    int Insert(DataType x);
    DataType Get();
    int IsEmpty(){if(rear==front) return OK;else return Error;}
};

template<class DataType>
int Queue<DataType>::Insert(DataType x)
{
    if(rear == MaxSize - 1)
        rear = front;
    rear++;
    for (int j = rear; j > 1; j--) {
        data[j] = data[j-1];
    }
    data[1] = x;
    return OK;
}

template <class DataType>
DataType Queue<DataType>::Get()
{
    if(rear == front)
        throw "Error";
    int i = rear;
    rear--;
    return data[i];
}

int main()
{
    Queue<int> *L,p;
    L = &p;
    cout << L->IsEmpty()<<endl;
    cout << L->Length() << endl;
    cout << "-----" << endl;
    L->Insert(1);
    L->Insert(2);
    cout << "The Length of L：" << L->Length() << endl;
    cout << "The Value of L:" << L->Get() << endl;
    cout << "-----" << endl;
    cout <<"The Length of L：" << L->Length() << endl;
    cout << "The Value of L:" << L->Get() << endl;
    cout << "-----" << endl;
    cout << L->IsEmpty()<<endl;
    return OK;
}