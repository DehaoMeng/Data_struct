#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>    //map���ݽṹ�洢HT�����
#include <queue>  //�����Ľڵ��������
#include <string> //�ַ��������������
#include <iterator> //���������mapչʾ
#include <bitset>

using namespace std;
const int OK = 1;
const int ERROR = 0;
class HTNode{
public:
    char ch; //�ַ�
    int weight;//Ȩ��
    HTNode *left;//����
    HTNode *right;//�Һ���
    HTNode(int weight) : weight(weight) {}
    //���رȽ����㷨���������򣬹������ȶ���
    bool operator<(const HTNode &htnode) const{
        return weight > htnode.weight;
    }
    //�������캯��
    HTNode(char ch, int weight, HTNode *left, HTNode *right) : ch(ch), weight(weight), left(left), right(right) {}
    HTNode(char ch, int weight) : ch(ch), weight(weight) {}
};
/*
 * ͨ�����ȶ��й����շ�����
 */
void CreateHuffmanTree(priority_queue<HTNode> &queue);
/*
 * ͨ���ַ���ͳ���ַ���Ƶ��
 */
priority_queue<HTNode> count(string s);
/*
 * չʾÿ���ַ���Ӧ��Ȩ��
 */
void show(priority_queue<HTNode> q);
/*
 * ͨ��·����ȡ�ļ�
 */
static map<char,string> huffmanCode; //��̬��ȫ�ֱ���map���ϣ�keyΪ�ַ���stringΪ��Ӧ���룬������Ϊ�����
/*
 * ��ȡ������˴���Ͼ�̬��Map���ϴ������
 */
void getCodes(HTNode *root,string code,string &prefix);
/*
 * ��ӡ�����
 */
void printCode(map<char,string> codes);
/*
 * ͨ���������ļ���ȡ��������������->��������
 */
string BecomeCode(map<char,string> codetTable,string data);
/*
 * ���룺ͨ�������ͱ���������
 */
void deCode(map<char,string> codetTable,string CodeData);

/*
 * ������������
 */
void CreateHuffmanTree(priority_queue<HTNode> &queue){
    while (queue.size()>1){
        HTNode *left = new HTNode(queue.top()); queue.pop();
        HTNode *right = new HTNode(queue.top()); queue.pop();
        HTNode parent('R',left->weight + right->weight,left,right);
        queue.push(parent);
    }
}

priority_queue<HTNode> count(string s){
    int a[128] = {0};
    priority_queue<HTNode> queue;
    for (int i = 0; i < s.length();i++) {
        if (s[i] >= 0 && s[i] <= 127) { a[s[i]]++; }
    }
    for (int i = 0; i < 128;i++) {
        if (a[i]!=0){
            HTNode *htNode = new HTNode((char)i,a[i]);
            queue.push(*htNode);
        }
    }
    return queue;
}
void show(priority_queue<HTNode> q){
    while(!q.empty()){
        HTNode node = q.top(); q.pop();
        cout<<node.ch<<": "<<node.weight<<endl;
    }
}

void getCodes(HTNode *root,string code,string &prefix){
    string s=prefix;
    s.append(code);
    if(root){
        if (root->ch==82){
            getCodes(root->left,"0",s);
            getCodes(root->right,"1",s);
        }else{
            huffmanCode[root->ch] = s;
        }
    }
}
void printCode(map<char,string> codes){
    map<char,string>::const_iterator it = codes.begin();
    while(it != codes.end()){
        cout<<"����: "<<it->first<<"���룺"<<it->second<<endl;
        ++it;
    }
}
/*
 * ���ɺշ�����������
 */
string BecomeCode(map<char,string> codetTable,string data){
    string res="";
    for (int i = 0; i < data.length(); ++i) {
        res.append(codetTable[data[i]]);
    }
    return res;
}
void deCode(map<char,string> codetTable,string CodeData){
    map<char,string>::const_iterator it;
    string sub="";
    for (int i = 0; i < CodeData.length(); ++i) {
        for (int j = 0; j < 10; ++j) {
            sub = CodeData.substr(i,j);
            it = codetTable.begin();
            while(it != codetTable.end()){
                if(sub == it->second){
                    char s = it->first;
                    cout<<s;
                    i = j + i ;
                    j = 0;
                    break;
                }
                ++it;
            }
        }

    }
}

int main(){
    string s = "1212311215464asdasdasasd";
    priority_queue<HTNode>  queue = count(s);//��ȡ���ʵ�Ƶ�ʣ�ͨ������������ȶ���
    show(queue);//�������
    CreateHuffmanTree(queue);//�����շ�����
    string bulid="";
    HTNode root = queue.top();//��ȡ�����ڵ�
    getCodes(&root,"",bulid);//��ʼ���ɱ����
    printCode(huffmanCode);//չʾ�����
    string res = BecomeCode(huffmanCode,s);//���ɱ�������
    cout << "����:";
    deCode(huffmanCode,res);//���������ݽ���
    return OK;
}
