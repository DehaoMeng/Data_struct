#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>    //map数据结构存储HT编码表
#include <queue>  //构建的节点的优先性
#include <string> //字符串方便输入输出
#include <iterator> //迭代器输出map展示
#include <bitset>

using namespace std;
const int OK = 1;
const int ERROR = 0;
class HTNode{
public:
    char ch; //字符
    int weight;//权重
    HTNode *left;//左孩子
    HTNode *right;//右孩子
    HTNode(int weight) : weight(weight) {}
    //重载比较运算法，便于排序，构造优先队列
    bool operator<(const HTNode &htnode) const{
        return weight > htnode.weight;
    }
    //两个构造函数
    HTNode(char ch, int weight, HTNode *left, HTNode *right) : ch(ch), weight(weight), left(left), right(right) {}
    HTNode(char ch, int weight) : ch(ch), weight(weight) {}
};
/*
 * 通过优先队列构建赫夫曼树
 */
void CreateHuffmanTree(priority_queue<HTNode> &queue);
/*
 * 通过字符串统计字符的频率
 */
priority_queue<HTNode> count(string s);
/*
 * 展示每个字符对应的权重
 */
void show(priority_queue<HTNode> q);
/*
 * 通过路径读取文件
 */
static map<char,string> huffmanCode; //静态的全局变量map集合：key为字符，string为对应编码，用来作为编码表
/*
 * 获取编码表，此处配合静态的Map集合存入编码
 */
void getCodes(HTNode *root,string code,string &prefix);
/*
 * 打印编码表
 */
void printCode(map<char,string> codes);
/*
 * 通过编码表和文件读取出的数据来生成->编码数据
 */
string BecomeCode(map<char,string> codetTable,string data);
/*
 * 解码：通过编码表和编码后的数据
 */
void deCode(map<char,string> codetTable,string CodeData);

/*
 * 创建哈夫曼树
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
        cout<<"符号: "<<it->first<<"编码："<<it->second<<endl;
        ++it;
    }
}
/*
 * 生成赫夫曼编码数据
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
    priority_queue<HTNode>  queue = count(s);//获取单词的频率，通过升序进入优先队列
    show(queue);//输出队列
    CreateHuffmanTree(queue);//创建赫夫曼树
    string bulid="";
    HTNode root = queue.top();//获取树根节点
    getCodes(&root,"",bulid);//开始生成编码表
    printCode(huffmanCode);//展示编码表
    string res = BecomeCode(huffmanCode,s);//生成编码数据
    cout << "解码:";
    deCode(huffmanCode,res);//将编码数据解码
    return OK;
}
