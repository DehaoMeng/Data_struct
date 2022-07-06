//
// Created by 86176 on 2022/5/6 0006.
//
#include <iostream>
#include <cstring>

using namespace std;
const int ERROR = -1;
const int MAXSIZE=30;
class Graph{
private:
    char m_vertex[MAXSIZE]{};
    int m_nAdjMatrix[MAXSIZE][MAXSIZE]; // 邻接矩阵
    int m_nVertexNum; // 顶点数目
    int connected_componentsNum; // 连通分量个数
    bool DFSTraverse(int nV);
public:
    Graph();
    Graph(char *vertex);
    Graph(char *vertex,int **m_nAdjMatrix);
    int Print();
    int FindPath();// 查询联通分量
    void DFS(int nV, int bVisited[]);
    int GetFirstEdge(int nV);
    int GetNextEdge(int nV1, int nV2);
    bool IsEdge(int nV1, int nV2);
    bool GetVertexValue(int nV,char &vertex);
    bool judge_Array(int bVisited[]);
};
bool Graph::GetVertexValue(int nV, char &vertex)
{
    if(nV < 0 || nV >= m_nVertexNum)
        return false;
    vertex = m_vertex[nV];
    return true;
}
bool Graph::IsEdge(int nV1, int nV2)
{
    // 权重为有限值，则表明边存在
    return m_nAdjMatrix[nV1][nV2] != 0;
}

int Graph::GetNextEdge(int nV1, int nV2)
{
    int nJ;
    if(!IsEdge(nV1,nV2))
        return ERROR;
    for (nJ = nV2 + 1; nJ < m_nVertexNum; nJ++) {
        if(IsEdge(nV1,nJ))
            return nJ;
    }
    return ERROR;
}

int Graph::GetFirstEdge(int nV){
    int nJ;
    if(nV < 0|| nV >= m_nVertexNum)
        return ERROR;
    for (nJ = 0; nJ < m_nVertexNum; nJ++) {
        if(IsEdge(nV,nJ))
            break;
    }
    if(nJ == m_nVertexNum)
        return ERROR;
    return nJ;
}
int Graph::FindPath() {
    DFSTraverse(0);
    return connected_componentsNum;
}

void Graph::DFS(int nV, int bVisited[]){
    char vertex;
    int nVertex;
    // 先访问当前顶点，并将其状态设置为已访问
    GetVertexValue(nV,vertex);
//    cout << vertex << " ";
    bVisited[nV] = 1;
    // 逐个获取与当前顶点相邻接的顶点，若获取到的顶点未访问
    // 则调用DFS函数对包含该顶点的连通子图进行深度优先遍历
    nVertex = GetFirstEdge(nV);
    while (nVertex != ERROR)
    {
        if(!bVisited[nVertex])
            DFS(nVertex,bVisited);
        nVertex = GetNextEdge(nV,nVertex);
    }
}
bool Graph::DFSTraverse(int nV){
    int nBegVertex;
    int bVisited[MAXSIZE];
    // 若下标为nV的顶点不存在，则遍历失败
    if(nV < 0 || nV >= m_nVertexNum)
        return false;
    // 设置各顶点为未访问状态
    memset(bVisited,0,sizeof(bVisited));
    // 对于图中的每一个顶点，若为未访问状态，则从该顶点开始
    // 调用DFS函数对包含该顶点的连通子图进行深度优先遍历
    for (nBegVertex = nV; nBegVertex < m_nVertexNum + nV; nBegVertex++)
    {
        if(!bVisited[nBegVertex % m_nVertexNum]){
            connected_componentsNum++;
            DFS(nBegVertex,bVisited);
        }
    }
    return true;
}

bool Graph::judge_Array(int bVisited[]){
    for (int i = 0; i < m_nVertexNum; ++i) {
        if (bVisited[i] != 1)
            return false;
    }
    return true;
}

Graph::Graph(){
    connected_componentsNum = 0;
    m_nAdjMatrix[MAXSIZE][MAXSIZE] = {0};
    m_nVertexNum = 0;
    char c;
    cin >> c;
    while (c != '!'){
        m_vertex[m_nVertexNum] = c;
        m_nVertexNum ++;
        cin >> c;
    }
//    cout << "输入边信息" << endl;
    int m,n;
    cin >> m >> n;
    while (m != -1 && n != -1){
        m_nAdjMatrix[m][n] = 1;
        cin >> m >> n;
    }
}

int Graph::Print() {
    for (int i = 0; i < m_nVertexNum; ++i) {
        for (int j = 0; j < m_nVertexNum; ++j) {
            cout << m_nAdjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

int main(){
    Graph p;
//    p.Print();
    cout << p.FindPath();
    return 0;
}