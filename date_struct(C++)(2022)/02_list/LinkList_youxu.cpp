#include <iostream>
using namespace std;

const int MaxSize = 100;
template <class DataType>
class SeqList
{
public:
    SeqList(){length=0;} // 初始化长度为0
    SeqList(DataType a[],int n); // 初始化有序表
    ~SeqList(){} // 析构函数
    DataType Get(int i){return data[i];} // 返回索引位置的元素
    int Length(){return length;} // 获取顺序表长度
    bool Insert(DataType x); // 向有序表中插入元素x
    DataType Delete(DataType e); // 删除元素值
    DataType Delete(DataType s, DataType t); // 删除给定范围内的所有元素值
    bool PrintList(); // 打印顺序表
private:
    DataType data[MaxSize];
    int length;
};
template<class DataType>
SeqList<DataType>::SeqList(DataType a[], int n) {
    int temp, pos;
    for (int i = 0; i < n; i++)         /*10个数排序，则只需执行9次*/
    {
        temp = a[i];         /*记录此时的值为最小值*/
        pos = i;               /*记录该元素的位置*/
        for (int j = i + 1; j < n; j++)  /*与后面的元素逐个比较*/
        {
            if (a[j] < temp)  /*若temp中的数大于下一位，则temp赋值为下一位*/
            {
                temp = a[j];
                pos = j;
            }
        }
        a[pos] = a[i];      /*交换两个元素的值*/
        a[i] = temp;
    }
    for(int i=0;i<n;i++)
        data[i] = a[i + 1];
    length=n-1;
}
template <class DataType>
DataType SeqList<DataType>::Delete(DataType e)
{
    DataType x;
    if(length==0) throw "Underflow";
    int i,pos=0;
    for (i = 1; i < length; i++) {
        x = data[i-1];
        if (x == e)
        {
            for(int j=i;j<length;j++)
                data[j-1] = data[j];
            length--;
            pos = 1;
            i--;
        }
    }
    if(pos == 1)
        return x;
    else if(pos == 0)
        cout << "error" << endl;
    return 0;
}
template <class DataType>
bool SeqList<DataType>::PrintList()
{
    if(length == 0){
        cout << "empty list" << endl;
        return true;
    }
    for(int i=0;i<length;i++)
        cout << data[i] << " ";
    cout << endl;
    return true;
}
template<class DataType>
bool SeqList<DataType>::Insert(DataType x)
{
    if(length>=MaxSize) return false;
    for (int i = 0; i < length; i++) {
        if(x >= data[i] && x <= data[i+1])
        {
            for (int j = length; j >= i+1; j--) {
                data[j] = data[j-1];
            }
            data[i+1] = x;
            length++;
            break;
        }
    }
    return true;
}
template<class DataType>
DataType SeqList<DataType>::Delete(DataType s, DataType t)
{
    if(s >= t|| length == 0) {
        cout << "error" << endl;
        return false;
    }
    int pos=0;
    for (int i = 0; i < length; i++) {
        if(data[i] >= s && data[i] <= t)
        {
            for(int j=i;j<length;j++)
                data[j-1] = data[j];
            length--;
            i--;
            pos = 1;
            }
    }
    if(pos == 1) {
        PrintList();
        return true;
    }else cout << "error" << endl;
    return false;
}
int main()
{
    int a[MaxSize],i;
    i = 1;
    while(cin >> a[i-1])
    {
        if(a[i-1] == -1 || i >= MaxSize) break;
        else i++;
    }
    SeqList<int> *p,head(a,i);
    p = &head;
    p->PrintList();
    int e;
    cin >> e;
    p->Delete(e);

    i = 1;
    while(cin >> a[i-1])
    {
        if(a[i-1] == -1 || i >= MaxSize) break;
        else i++;
    }
    SeqList<int> *L,h(a,i);
    L = &h;

    for (int j = 0; j < L->Length(); j++) {
        p->Insert(L->Get(j));
    }
    p->PrintList();
    int t,s;
    cin >> s;
    cin >> t;
    p->Delete(s,t);
}