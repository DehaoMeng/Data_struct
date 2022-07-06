/*
 *  有N个人围成一圈，从第i个人开始从1报数，数到m时，此人出列。下一个人重新从1开始报数，再数到m时，又一个人出列；以此类推，直到所有的人全部出列。
 *  请用循环链表为存储结构，按出列先后顺序得到一个新的序列，请输出出列的先后顺序。
 *  循环链表：将单链表中末尾结点的next指针值设为头指针
 *  请按照如下步骤进行主函数测试：
 *  输入若干个数（每个数代表圈中人的编号），以-1 作为结束->输入起始报数人的编号->输入m（数到m退出）->输出出列的顺序
 */
#include<iostream>
using namespace std;
#define OK 1
#define Error 0

template <class DataType>
struct DblNode{
    DataType data;
    DblNode<DataType> *next; // 前驱和后继
};
//类模板
template <class DataType>
class LinkList
{
public:
    LinkList();
    ~LinkList(){}
    void demo(int m,int n);
    void PrintList();
private:
    DblNode<DataType> *head; // 创建头指针
    DblNode<DataType> *tail; // 创建尾指针
};
// 构造函数
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
    DblNode<DataType> *out = head; // 要出队数据
    DblNode<DataType> *flag = tail; // 出对数据的前驱结点 将其next指针指向out->next
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