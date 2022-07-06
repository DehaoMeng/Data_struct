/*
 * ˳����ʵ��
 * */


#include<iostream>
using namespace std;

const int MaxSize = 100;
template <class DataType>
class SeqList
{
public:
    SeqList(){length=0;} // ��ʼ������Ϊ0
    SeqList(DataType a[],int n); // ��ʼ��˳���
    ~SeqList(){} // ��������
    int Length(){return length;} // ��ȡ˳�����
    DataType Get(int i); // ����˳�����λ��i��Ԫ��
    int Locate(DataType x); // ����˳�����Ԫ��x��λ��
    bool Insert(int i,DataType x); // ��˳���λ��i����Ԫ��x
    DataType Delete(DataType e); // ɾ��λ��i��Ԫ�ز�����Ԫ��ֵ
    void DeleteMin();
    bool PrintList(); // ��ӡ˳���
private:
    DataType* data;
    int length;
};
// ��ʼ��˳���
template <class DataType>
SeqList<DataType>::SeqList(DataType a[],int n)
{
    if(n>MaxSize) throw "wrong parameter";
    for(int i=0;i<n;i++)
        data[i]=a[i];
    length=n;
}
// ����˳�����λ��i��Ԫ��
template <class DataType>
DataType SeqList<DataType>::Get(int i)
{
    if(i<1 && i>length) throw "wrong Location";
    else return data[i-1];
}
// ����˳�����Ԫ��x��λ��
template <class DataType>
int SeqList<DataType>::Locate(DataType x)
{
    for(int i=0;i<length;i++)
        if(data[i]==x) return i+1;
    return 0;
}
// ��˳���λ��i����Ԫ��x
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
//ɾ��λ��i��Ԫ�ز�����Ԫ��ֵ
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
// ɾ��˳�������Сֵ
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
// ��ӡ˳���
template <class DataType>
bool SeqList<DataType>::PrintList()
{
    if(length == 0){
        cout << "�˱�Ϊ�ձ�" << endl;
        return true;
    }
    for(int i=0;i<length;i++)
        cout << data[i] << " ";
    cout << endl;
    return true;
}


int main()
{
    SeqList<int> *p,head; // ����˳���p
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