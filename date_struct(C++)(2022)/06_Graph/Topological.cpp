#include <iostream>
#include <stack>
#include <vector>
#include <list>
using namespace std;
vector<int> memony; // 保存员工的工资
vector<list<int>> Adj; //邻接表
vector<int> inDegree; //保存每个节点的入度
stack<int> stk; // 保存当前入度为0的节点编号

void CreatGraph(){                      // 创建图
    int n, m, a, b;
    cin >> n >> m;                      // 输入员工数和代表数
    Adj.assign(n, list<int>());     // 初始化邻接表
    inDegree.assign(n, 0);          // 初始化每个节点的入度
    memony.assign(n,100);           // 初始化每位员工的基础工资
    while (m--){                        // 按照代表数配置邻接表
        cin >> a >> b;                  // 输入代表的想法
        Adj[b-1].push_back(a-1);     // 配置邻接表
        inDegree[a-1]++;                // 弧尾入读++
    }
    for (int i = 0; i < n;i++)          // 查找入度为0的结点加入到栈
        if (inDegree[i] == 0) stk.push(i);
}
void tpSort() {                         // 拓扑排序
    vector<int> vec;                    // 存储遍历过的节点的集合
    int v;                              // 当前遍历节点
    while (!stk.empty()) {              //当栈为空时代表入度为0的节点已经全部遍历
        v = stk.top();                  // 从栈中获取栈顶元素
        stk.pop();                      // 从栈中弹出栈顶元素
        for (auto it = Adj[v].begin(); it != Adj[v].end(); it++) { //遍历与节点v相连的节点
            if (memony[v] >= memony[*it] )// 如果当前遍历节点比他的栈弧头节点工资高或者等于，则提高弧头节点员工的工资
                memony[*it] = memony[v] + 1;
            inDegree[*it]--;             // 减少与v相连的弧头节点的入度
            if (inDegree[*it] == 0) stk.push(*it); // 把入读为0的节点压入栈中
        }
        vec.push_back(v);                // 把已经遍历过的所有节点的弧尾压入容器中生成拓扑图
    }
    if (vec.size() != inDegree.size()) { // 如果生成的拓扑图的节点数与总结点数不相同，则代表生成圈，代表生成失败
        cout << "POOR!\n";
        return;
    }
    int allMoney=0;                      // 所有人总工资
    for (auto item :memony)          // 求所有人的总工资
    {
        allMoney += item;
    }
    cout << allMoney << endl;
}
int main(){
    CreatGraph();                       // 创建图
    tpSort();                           // 生成拓扑图
    return 0;
}