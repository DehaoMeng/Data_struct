/*
 *  C++广义表实现
 */

#include<iostream>
#include<assert.h>
using namespace std;
enum Type{
    HEAD,
    SUB,
    VALUE
};
struct GeneralListNode{
    Type type;
    union{
        char value;
        GeneralListNode *sublink;
    };
    GeneralListNode *next;
    GeneralListNode(Type t,const char v = 0)
            :type(t)
            ,next(0){
        if(t == HEAD || t ==VALUE){
            value = v;
        }else if(t == SUB){
            sublink = 0;
        }else {
            assert(false);
        }
    }
};

class GeneralList{
    typedef GeneralListNode Node;
public:
    //构造函数
    GeneralList(const char *s){
        _head = _CreateList(s);
    }
    //拷贝构造
    GeneralList(const GeneralList &g){
        _head = _Copy(g._head);
    }
    //赋值运算符重载
    GeneralList &operator=(const GeneralList &g){
        if(_head!=g._head){     //不是自己给自己赋值
            GeneralList temp(g);
            swap(_head,temp._head);
        }
        return *this;
    }
    //析构函数
    ~GeneralList(){
        if(_head!=NULL){
            _Destory(_head);
            _head = NULL;
        }
    }
public:
    //打印广义表
    void Print(){
        _Print(_head);
        cout<<endl;
    }
    //广义表数据个数
    size_t Size(){
        return _Size(_head);
    }
    //广义表深度
    size_t Depth(){
        return _Depth(_head);
    }
protected:
    //拷贝广义表
    Node * _Copy(Node* head){
        Node *NewHead = new Node(HEAD);
        Node *Tail = NewHead;
        Node *cur = head;
        while(cur){
            if(cur->type == VALUE){                          //数据节点
                Tail->next = new Node(VALUE,cur->value);  //创建新节点,添加至尾节点
                Tail = Tail->next;                           //尾节点后移
                cur = cur->next;                         //被拷贝节点后移
            }else if(cur->type == SUB){                      //子表节点
                Node *NewSub = new Node(SUB);               //创建新子表节点
                Tail->next = NewSub;                     //添加至尾节点
                Tail = Tail->next;                           //尾节点后移
                NewSub->sublink = _Copy(cur->sublink);        //递归拷贝子节点
                cur = cur->next;                         //被拷贝节点后移
            }else if(cur->type == HEAD){                 //头节点
                cur = cur->next;                         //被拷贝节点后移
            }else{
                assert(false);          //出错!
            }
        }
        return NewHead;
    }
    //交换
    void _Swap(Node* &l,Node *&r){
        Node *tmp = l;
        l = r;
        r = tmp;
    }
    //销毁
    void _Destory(Node *head){
        Node *cur = head;
        while(cur){
            if((cur->type == VALUE)
               ||(cur->type == HEAD)){      //当前节点为头节点或数据节点
                Node *del = cur;            //保存当前节点
                cur = cur->next;         //当前节点后移
                delete del;                 //删除节点
            }else if(cur->type == SUB){      //当前节点为子表
                Node * del = cur;           //保存当前节点
                cur = cur->next;         //当前节点后移
                _Destory(del->sublink);      //递归销毁子表里的数据
                delete del;                 //销毁子表
            }else{
                assert(false);              //程序运行出错!
            }

        }
    }
    //判断是否为数据
    bool _IsValue(const char s){
        if((s>='0'&&s<='9')
           ||(s>='a'&&s<='z')
           ||(s>='A'&&s<='Z')){
            return true;
        }
        return false;
    }
    //递归创建广义表
    Node *_CreateList(const char * &s){
        assert(*s=='(');                        //断言字符串s第一个字符是(
        ++s;                                    //跳过(进入数据部分
        Node *head = new Node(HEAD);            //创建头节点
        Node *Tail = head;                      //作为尾节点,来插入新数据
        while(*s){
            if(_IsValue(*s)){                       //数据项
                Tail->next = new Node(VALUE,*s); //创建数据节点
                Tail = Tail->next;                   //尾节点后移
                ++s;
            }else if(*s == '('){                //子表项
                Node *NewNode = new Node(SUB);  //创建子表节点
                Tail->next = NewNode;            //插入尾部
                Tail = Tail->next;               //尾部后移
                NewNode->sublink = _CreateList(s);   //递归创建子表数据节点
            }else if(*s ==')'){                     //数据结束
                ++s;
                return head;                        //返回头节点
            }else{
                ++s;                                //遇到逗号跳过
            }
        }
        return head;
    }
    //递归打印广义表
    void _Print(Node *head){
        Node * cur = head;
        while(cur){
            if(cur->type == HEAD){           //头节点
                cout<<"(";
            }else if(cur->type == VALUE){    //值节点
                cout<<cur->value;
                if(cur->next!=NULL){     //不是最后一个元素
                    cout<<",";                //以逗号分隔
                }
            }else if(cur->type == SUB){      //子表项
                _Print(cur->sublink);        //递归打印子表
                if(cur->next!=NULL){     //不是最后一项数据
                    cout<<",";                //以逗号分隔
                }
            }else{
                assert(false);
            }
            cur = cur->next;
        }
        cout<<")";
    }
    //递归获取广义表数据个数
    size_t _Size(Node *head){
        Node *cur = head;
        size_t ret = 0;
        while(cur){
            if(cur->type ==VALUE){           //当前为值节点
                ++ret;                      //数据个数+1
            }else if(cur->type ==SUB){
                ret += _Size(cur->sublink);  //递归求取子表数据个数
            }else{
                //头节点
            }
            cur = cur->next;
        }
        return ret;
    }
    //递归求广义表深度
    size_t _Depth(Node *head){
        Node *cur = head;
        size_t MaxDepth = 1;                        //当前深度为1
        while(cur){
            if(cur->type == SUB){                    //遇到子表
                size_t Depth = _Depth(cur->sublink);//递归求子表深度
                if(MaxDepth<Depth+1){                //如果子表深入大于当前值
                    MaxDepth = Depth+1;             //更新最大深入
                }
            }
            cur = cur->next;
        }
        return MaxDepth;                            //返回最大深度
    }
private:
    Node * _head;
};

void GeneralListTest(){
    const char * const str1 = "(a)";
    GeneralList g1(str1);
    g1.Print();
    cout<<"Size = "<<g1.Size()<<endl;
    cout<<"Depth = "<<g1.Depth()<<endl;

    const char * const str2 = "(a,b)";
    GeneralList g2(str2);
    g2.Print();
    cout<<"Size = "<<g2.Size()<<endl;
    cout<<"Depth = "<<g2.Depth()<<endl;

    const char * const str3 = "(a,b,(c,d))";
    GeneralList g3(str3);
    g3.Print();
    cout<<"Size = "<<g3.Size()<<endl;
    cout<<"Depth = "<<g3.Depth()<<endl;

    const char * const str4 = "((e,(f),h))";
    GeneralList g4(str4);
    g4.Print();
    cout<<"Size = "<<g4.Size()<<endl;
    cout<<"Depth = "<<g4.Depth()<<endl;

    const char * const str5 = "(((1,2)),((3,4)))";
    GeneralList g5(str5);
    g5.Print();
    cout<<"Size = "<<g5.Size()<<endl;
    cout<<"Depth = "<<g5.Depth()<<endl;

    cout<<"////////拷贝构造//////"<<endl<<endl;
    //(a)
    GeneralList g6(g1);
    g6.Print();
    cout<<"Size = "<<g6.Size()<<endl;
    cout<<"Depth = "<<g6.Depth()<<endl;
    //(a,b)
    GeneralList g7(g2);
    g7.Print();
    cout<<"Size = "<<g7.Size()<<endl;
    cout<<"Depth = "<<g7.Depth()<<endl;

    //(a,b,(c,d))
    GeneralList g8(g3);
    g8.Print();
    cout<<"Size = "<<g8.Size()<<endl;
    cout<<"Depth = "<<g8.Depth()<<endl;

    GeneralList g9(g4);
    g9.Print();
    cout<<"Size = "<<g9.Size()<<endl;
    cout<<"Depth = "<<g9.Depth()<<endl;

    GeneralList g10(g5);
    g10.Print();
    cout<<"Size = "<<g10.Size()<<endl;
    cout<<"Depth = "<<g10.Depth()<<endl;
}
int main(){
    GeneralListTest();
    return 0;
}