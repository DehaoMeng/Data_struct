/*
 *  C++�����ʵ��
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
    //���캯��
    GeneralList(const char *s){
        _head = _CreateList(s);
    }
    //��������
    GeneralList(const GeneralList &g){
        _head = _Copy(g._head);
    }
    //��ֵ���������
    GeneralList &operator=(const GeneralList &g){
        if(_head!=g._head){     //�����Լ����Լ���ֵ
            GeneralList temp(g);
            swap(_head,temp._head);
        }
        return *this;
    }
    //��������
    ~GeneralList(){
        if(_head!=NULL){
            _Destory(_head);
            _head = NULL;
        }
    }
public:
    //��ӡ�����
    void Print(){
        _Print(_head);
        cout<<endl;
    }
    //��������ݸ���
    size_t Size(){
        return _Size(_head);
    }
    //��������
    size_t Depth(){
        return _Depth(_head);
    }
protected:
    //���������
    Node * _Copy(Node* head){
        Node *NewHead = new Node(HEAD);
        Node *Tail = NewHead;
        Node *cur = head;
        while(cur){
            if(cur->type == VALUE){                          //���ݽڵ�
                Tail->next = new Node(VALUE,cur->value);  //�����½ڵ�,�����β�ڵ�
                Tail = Tail->next;                           //β�ڵ����
                cur = cur->next;                         //�������ڵ����
            }else if(cur->type == SUB){                      //�ӱ�ڵ�
                Node *NewSub = new Node(SUB);               //�������ӱ�ڵ�
                Tail->next = NewSub;                     //�����β�ڵ�
                Tail = Tail->next;                           //β�ڵ����
                NewSub->sublink = _Copy(cur->sublink);        //�ݹ鿽���ӽڵ�
                cur = cur->next;                         //�������ڵ����
            }else if(cur->type == HEAD){                 //ͷ�ڵ�
                cur = cur->next;                         //�������ڵ����
            }else{
                assert(false);          //����!
            }
        }
        return NewHead;
    }
    //����
    void _Swap(Node* &l,Node *&r){
        Node *tmp = l;
        l = r;
        r = tmp;
    }
    //����
    void _Destory(Node *head){
        Node *cur = head;
        while(cur){
            if((cur->type == VALUE)
               ||(cur->type == HEAD)){      //��ǰ�ڵ�Ϊͷ�ڵ�����ݽڵ�
                Node *del = cur;            //���浱ǰ�ڵ�
                cur = cur->next;         //��ǰ�ڵ����
                delete del;                 //ɾ���ڵ�
            }else if(cur->type == SUB){      //��ǰ�ڵ�Ϊ�ӱ�
                Node * del = cur;           //���浱ǰ�ڵ�
                cur = cur->next;         //��ǰ�ڵ����
                _Destory(del->sublink);      //�ݹ������ӱ��������
                delete del;                 //�����ӱ�
            }else{
                assert(false);              //�������г���!
            }

        }
    }
    //�ж��Ƿ�Ϊ����
    bool _IsValue(const char s){
        if((s>='0'&&s<='9')
           ||(s>='a'&&s<='z')
           ||(s>='A'&&s<='Z')){
            return true;
        }
        return false;
    }
    //�ݹ鴴�������
    Node *_CreateList(const char * &s){
        assert(*s=='(');                        //�����ַ���s��һ���ַ���(
        ++s;                                    //����(�������ݲ���
        Node *head = new Node(HEAD);            //����ͷ�ڵ�
        Node *Tail = head;                      //��Ϊβ�ڵ�,������������
        while(*s){
            if(_IsValue(*s)){                       //������
                Tail->next = new Node(VALUE,*s); //�������ݽڵ�
                Tail = Tail->next;                   //β�ڵ����
                ++s;
            }else if(*s == '('){                //�ӱ���
                Node *NewNode = new Node(SUB);  //�����ӱ�ڵ�
                Tail->next = NewNode;            //����β��
                Tail = Tail->next;               //β������
                NewNode->sublink = _CreateList(s);   //�ݹ鴴���ӱ����ݽڵ�
            }else if(*s ==')'){                     //���ݽ���
                ++s;
                return head;                        //����ͷ�ڵ�
            }else{
                ++s;                                //������������
            }
        }
        return head;
    }
    //�ݹ��ӡ�����
    void _Print(Node *head){
        Node * cur = head;
        while(cur){
            if(cur->type == HEAD){           //ͷ�ڵ�
                cout<<"(";
            }else if(cur->type == VALUE){    //ֵ�ڵ�
                cout<<cur->value;
                if(cur->next!=NULL){     //�������һ��Ԫ��
                    cout<<",";                //�Զ��ŷָ�
                }
            }else if(cur->type == SUB){      //�ӱ���
                _Print(cur->sublink);        //�ݹ��ӡ�ӱ�
                if(cur->next!=NULL){     //�������һ������
                    cout<<",";                //�Զ��ŷָ�
                }
            }else{
                assert(false);
            }
            cur = cur->next;
        }
        cout<<")";
    }
    //�ݹ��ȡ��������ݸ���
    size_t _Size(Node *head){
        Node *cur = head;
        size_t ret = 0;
        while(cur){
            if(cur->type ==VALUE){           //��ǰΪֵ�ڵ�
                ++ret;                      //���ݸ���+1
            }else if(cur->type ==SUB){
                ret += _Size(cur->sublink);  //�ݹ���ȡ�ӱ����ݸ���
            }else{
                //ͷ�ڵ�
            }
            cur = cur->next;
        }
        return ret;
    }
    //�ݹ����������
    size_t _Depth(Node *head){
        Node *cur = head;
        size_t MaxDepth = 1;                        //��ǰ���Ϊ1
        while(cur){
            if(cur->type == SUB){                    //�����ӱ�
                size_t Depth = _Depth(cur->sublink);//�ݹ����ӱ����
                if(MaxDepth<Depth+1){                //����ӱ�������ڵ�ǰֵ
                    MaxDepth = Depth+1;             //�����������
                }
            }
            cur = cur->next;
        }
        return MaxDepth;                            //����������
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

    cout<<"////////��������//////"<<endl<<endl;
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