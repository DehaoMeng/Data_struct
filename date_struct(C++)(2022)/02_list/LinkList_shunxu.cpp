/*
 * 顺序表的实现
 * */


#include<iostream>
using namespace std;

const int MaxSize = 100;
template <class DataType>
class SeqList
{
public:
    SeqList(){length=0;} // 初始化长度为0
    SeqList(DataType a[],int n); // 初始化顺序表
    ~SeqList(){} // 析构函数
    int Length(){return length;} // 获取顺序表长度
    DataType Get(int i); // 查找顺序表中位置i的元素
    int Locate(DataType x); // 查找顺序表中元素x的位置
    bool Insert(int i,DataType x); // 向顺序表位置i插入元素x
    DataType Delete(DataType e); // 删除位置i的元素并返回元素值
    void DeleteMin();
    bool PrintList(); // 打印顺序表
private:
    DataType* data;
    int length;
};
// 初始化顺序表
template <class DataType>
SeqList<DataType>::SeqList(DataType a[],int n)
{
    if(n>MaxSize) throw "wrong parameter";
    for(int i=0;i<n;i++)
        data[i]=a[i];
    length=n;
}
// 查找顺序表中位置i的元素
template <class DataType>
DataType SeqList<DataType>::Get(int i)
{
    if(i<1 && i>length) throw "wrong Location";
    else return data[i-1];
}
// 查找顺序表中元素x的位置
template <class DataType>
int SeqList<DataType>::Locate(DataType x)
{
    for(int i=0;i<length;i++)
        if(data[i]==x) return i+1;
    return 0;
}
// 向顺序表位置i插入元素x
template <class DataType>
bool SeqList<DataType>::Insert(int i,DataType x)
{
    if(length>=MaxSize) return false;
    if(i<1 || i>length+1) return false;
    for(int j=length;j>=i;j--)
        data[j]=data[j-1];
    data[i-1]=x;
    length++;
    return true;
}
//删除位置i的元素并返回元素值
template <class DataType>
DataType SeqList<DataType>::Delete(DataType e)
{
    DataType x;
    if(length==0) throw "Underflow";
    int i;
    for (i = 1; i < length; i++) {
        x = data[i-1];
        if (x == e) break;
    }
    if(i < length){
        for(int j=i;j<length;j++)
            data[j-1] = data[j];
        length--;
        return x;
    } else cout << "error" << endl;
    return 0;
}
// 删除顺序表中最小值
template <class DataType>
void SeqList<DataType>::DeleteMin() {
    if(length == 0) throw "error";
    int min = data[0];
    for (int i = 0; i < length-1; i++) {
        if (data[i] < min) {
            min = data[i];
        }
    }
    Delete(min);
    cout << min << endl;
}
// 打印顺序表
template <class DataType>
bool SeqList<DataType>::PrintList()
{
    if(length == 0){
        cout << "此表为空表" << endl;
        return true;
    }
    for(int i=0;i<length;i++)
        cout << data[i] << " ";
    cout << endl;
    return true;
}


int main()
{
    SeqList<int> *p,head; // 创建顺序表p
    p = &head;
    int e[MaxSize],i;
    i = 1;
    while(cin >> e[i])
    {
        if(e[i] == -1) break;
        i++;
    }
    int n = 1;
    while (n < i)
    {
        p->Insert(n,e[n]);
        n++;
    }
    p->PrintList();
    p->DeleteMin();
    p->PrintList();
    int s;
    cin >> s;
    p->Delete(s);
    p->PrintList();
    return 0;
}