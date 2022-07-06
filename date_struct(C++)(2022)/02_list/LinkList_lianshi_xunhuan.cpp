/*
 *  ��N����Χ��һȦ���ӵ�i���˿�ʼ��1����������mʱ�����˳��С���һ�������´�1��ʼ������������mʱ����һ���˳��У��Դ����ƣ�ֱ�����е���ȫ�����С�
 *  ����ѭ������Ϊ�洢�ṹ���������Ⱥ�˳��õ�һ���µ����У���������е��Ⱥ�˳��
 *  ѭ����������������ĩβ����nextָ��ֵ��Ϊͷָ��
 *  �밴�����²���������������ԣ�
 *  �������ɸ�����ÿ��������Ȧ���˵ı�ţ�����-1 ��Ϊ����->������ʼ�����˵ı��->����m������m�˳���->������е�˳��
 */
#include<iostream>
using namespace std;
#define OK 1
#define Error 0

template <class DataType>
struct DblNode{
    DataType data;
    DblNode<DataType> *next; // ǰ���ͺ��
};
//��ģ��
template <class DataType>
class LinkList
{
public:
    LinkList();
    ~LinkList(){}
    void demo(int m,int n);
    void PrintList();
private:
    DblNode<DataType> *head; // ����ͷָ��
    DblNode<DataType> *tail; // ����βָ��
};
// ���캯��
template <class DataType>
LinkList<DataType>::LinkList()
{
    head = new DblNode<DataType>;
    DblNode<DataType> *r = head;
    DataType x;
    cin >> x;
    while (x != -1){
        if (x <= 0)
        {
            cin >> x;
            continue;
        }
        DblNode<DataType> *s =new DblNode<DataType>;
        s->data = x;
        s->next = head;
        r->next = s;
        r = s;
        cin >> x;
    }
    head = r->next->next;
    tail = r;
    tail->next = head;
}
template <class DataType>
void LinkList<DataType>::demo(int m, int n) {
    if (m < 1 || n < 1) {
        cout << "error" << endl;
        return;
    }
    DblNode<DataType> *out = head; // Ҫ��������
    DblNode<DataType> *flag = tail; // �������ݵ�ǰ����� ����nextָ��ָ��out->next
    for (int i = 1; i < m; i++) {
        flag = flag->next;
        out = out->next;
    }
    while (out != flag) {
        for (int i = 1; i < n; i++) {
            flag = flag->next;
            out = out->next;
        }
        flag->next = out->next;
        cout << out->data << " ";
        out = flag->next;
    }
    cout << out->data <<endl;
}

template <class DataType>
void LinkList<DataType>::PrintList()
{
    DblNode<DataType>* p = head;
    while(p != tail)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << p->data << endl;
}

int main()
{
    LinkList<int> *L,head;
    L = &head;
    int m,n;
//    L->PrintList();
    cin >> m >> n;
    L->demo(m,n);
    return OK;
}