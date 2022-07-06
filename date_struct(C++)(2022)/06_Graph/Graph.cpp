/**
 * 图的邻接矩阵c++实现
 * */
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int ERROR = -1;
const int MAXSIZE = 30;
template<class DataType>
class AdjGraph
{
private:
    DataType m_vertex[MAXSIZE]; // 顶点集合
    int m_nAdjMatrix[MAXSIZE][MAXSIZE]; // 邻接矩阵
    int m_nVertexNum=0; // 顶点数目
    int m_nGraphType; // 图的类型 0：无向图；1：有向图
public:
    AdjGraph(int nGraphType); // 创建图
    int GetVertexNum(); // 获取顶点数目
    int GetFirstEdge(int nV); // 获取与指定顶点nV相关联的第一条边
    /*获取与指定边（nV1,nV2）或<nV1,nV2>有相同关联顶nV1的下一条边*/
    int GetNextEdge(int nV1,int nV2);
    bool AddOneVertex(DataType vertex); //添加一个顶点
    bool AddOneEdge(int nV1,int nV2,int nWeight); // 添加一条边
    bool AddOneEdge(int nV1,int nV2); // 添加一条边
    bool GetVertexValue(int nV,DataType &vertex); // 获取一个顶点中存储的数据
    bool IsEdge(int nV1,int nV2); // 判断一条边是否存在
    bool SetEdgeWeight(int nV1,int nV2,int nWeight); // 设置一条边的权
    bool GetEdgeWeight(int nV1,int nV2,int &nWeight); // 获取一条边的权
    /*以递归方式从下标nV的顶点开始对图作深度优先遍历*/
    bool DFSTraverse(int nV);
    /*由DFSTraverse调用以递归方式完成图的深度优先遍历*/
    void DFS(int nV,int bVisited[]);
//    bool DFSTraverse(int nV); // 以非递归方式对图作深度优先遍历
    bool BFSTraverse(char Vertex1,char Vertex2); // 从下标为nV的顶点开始对图作广度优先遍历
    int GetNum() {return m_nVertexNum;}
    int Print(); // 输出邻接矩阵
};
template <class DataType>
int AdjGraph<DataType>::Print() {
    int n = GetVertexNum();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << m_nAdjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
template <class DataType>
AdjGraph<DataType>::AdjGraph(int nGraphType)
{
    int nI,nJ;
    m_nGraphType = nGraphType;
    for (nI = 0; nI < MAXSIZE; nI++) {
        for (nJ = 0; nJ < MAXSIZE; nJ++) {
            m_nAdjMatrix[nI][nJ] = 0;
        }
    }
}

template <class DataType>
int AdjGraph<DataType>::GetVertexNum()
{
    return m_nVertexNum;
}

template <class DataType>
bool AdjGraph<DataType>::IsEdge(int nV1, int nV2)
{
    // 权重为有限值，则表明边存在
    return m_nAdjMatrix[nV1][nV2] != 0;
}

template<class DataType>
int AdjGraph<DataType>::GetFirstEdge(int nV)
{
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

template <class DataType>
int AdjGraph<DataType>::GetNextEdge(int nV1, int nV2)
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

template <class DataType>
bool AdjGraph<DataType>::AddOneVertex(DataType vertex)
{
    if(m_nVertexNum >= MAXSIZE)
        return false;
    m_vertex[m_nVertexNum] = vertex;
    m_nVertexNum++;
    return true;
}

template <class DataType>
bool AdjGraph<DataType>::GetVertexValue(int nV, DataType &vertex)
{
    if(nV < 0 || nV >= m_nVertexNum)
        return false;
    vertex = m_vertex[nV];
    return true;
}

template <class DataType>
bool AdjGraph<DataType>::AddOneEdge(int nV1, int nV2, int nWeight)
{
    // 两个顶点必须存在，且两个顶点间原先没有边
    if(nV1 < 0 || nV1 >= m_nVertexNum || nV2 < 0 || nV2 >= m_nVertexNum || IsEdge(nV1,nV2))
        return false;
    m_nAdjMatrix[nV1][nV2] = nWeight;
    if(m_nGraphType == 0)
        m_nAdjMatrix[nV2][nV1] = nWeight;
    return true;
}
template <class DataType>
bool AdjGraph<DataType>::AddOneEdge(int nV1, int nV2)
{
    // 两个顶点必须存在，且两个顶点间原先没有边
    if(nV1 < 0 || nV1 >= m_nVertexNum || nV2 < 0 || nV2 >= m_nVertexNum || IsEdge(nV1,nV2))
        return false;
    m_nAdjMatrix[nV1][nV2] = 1;
    if(m_nGraphType == 0)
        m_nAdjMatrix[nV2][nV1] = 1;
    return true;
}

template <class DataType>
bool AdjGraph<DataType>::SetEdgeWeight(int nV1, int nV2, int nWeight)
{
    if(!IsEdge(nV1,nV2))
        return false;
    m_nAdjMatrix[nV1][nV2] = nWeight;
    return true;
}

template <class DataType>
bool AdjGraph<DataType>::GetEdgeWeight(int nV1, int nV2, int &nWeight)
{
    if(!IsEdge(nV1,nV2))
        return false;
    nWeight = m_nAdjMatrix[nV1][nV2];
    return true;
}
/** 广度优先遍历类似树的的逐层遍历 **/
//template <class DataType>
//bool AdjGraph<DataType>::BFSTraverse(int nV)
//{
//    queue<int> queue;
//    int nVisitVertex, nVertex, nBegVertex = nV;
//    int bVisited[MAXSIZE]; // 记录一个顶点是否已经访问
//    DataType vertex;
//    if(nV < 0 || nV >=m_nVertexNum)
//        return false;
//    memset(bVisited,0, sizeof(bVisited)); // 各顶点均设置为未访问状态
//    while (true)
//    {
//        queue.push(nBegVertex);
//        bVisited[nBegVertex] = 1;
//        while (!queue.empty())
//        {
//            nVisitVertex = queue.front();
//            queue.pop();
//            GetVertexValue(nVisitVertex,vertex);
//            cout << vertex << " ";
//            nVertex = GetFirstEdge(nVisitVertex);
//            while (nVertex != ERROR)
//            {
//                if(!bVisited[nVertex])
//                {
//                    queue.push(nVertex);
//                    bVisited[nVertex] = 1;
//                }
//                nVertex = GetNextEdge(nVisitVertex,nVertex);
//            }
//        }
//        // 如果还有没有访问的结点，若有则从该顶点开始再做广度优先遍历
//        int n;
//        for (n = nBegVertex + 1; n < m_nVertexNum + nV; n++) {
//            if (!bVisited[n % m_nVertexNum])
//            {
//                nBegVertex = n % m_nVertexNum;
//                break;
//            }
//        }
//        if (n == m_nVertexNum + nV) break; // 所有顶点都已访问，退出循环
//    }
//    return true;
//}

template <class DataType>
bool AdjGraph<DataType>::BFSTraverse(char Vertex1,char Vertex2)
{
    queue<int> queue;
    int nVisitVertex, nVertex, nBegVertex = 0;
    int bVisited[MAXSIZE]; // 记录一个顶点是否已经访问
    DataType vertex;
    memset(bVisited,0, sizeof(bVisited)); // 各顶点均设置为未访问状态
    while (m_vertex[nBegVertex] != Vertex1)
        nBegVertex++;
    queue.push(nBegVertex);
    bVisited[nBegVertex] = 1;
    while (!queue.empty())
    {
        nVisitVertex = queue.front();
        queue.pop();
        GetVertexValue(nVisitVertex,vertex);
        if (vertex == Vertex2) return 1;
        nVertex = GetFirstEdge(nVisitVertex);
        while (nVertex != ERROR)
        {
            if(!bVisited[nVertex])
            {
                queue.push(nVertex);
                bVisited[nVertex] = 1;
            }
            nVertex = GetNextEdge(nVisitVertex,nVertex);
        }
    }
    return 0;
}


/** 深度优先遍历类似于树的先序遍历 **/
template <class DataType>
bool AdjGraph<DataType>::DFSTraverse(int nV)
{
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
        if(!bVisited[nBegVertex % m_nVertexNum])
            DFS(nBegVertex,bVisited);
    }
    return true;
}
/** 由DFSTraverse调用以递归方式完成图的深度优先遍历 */
template <class DataType>
void AdjGraph<DataType>::DFS(int nV, int bVisited[])
{
    DataType vertex;
    int nVertex;
    // 先访问当前顶点，并将其状态设置为已访问
    GetVertexValue(nV,vertex);
    cout << vertex << " ";
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


int main() {
//    AdjGraph<char> graph1(1),graph2(0);
    AdjGraph<char> graph(1);
    char c, s;
    cin >> c;
    while (c != '!') {
        graph.AddOneVertex(c);
        cin >> c;
    }
    int i, j;
    cin >> i >> j;
    while (i != -1 && j != -1) {
        graph.AddOneEdge(i, j);
        cin >> i >> j;
    }
    cin >> c >> s;
    graph.Print();
    if (graph.BFSTraverse(c, s)) {
        cout << "T" <<endl;
    }
    else{
        cout << "F" << endl;
    }
//    for(c = 'A'; c <= 'E'; c++)
//        graph1.AddOneVertex(c);
//    graph1.AddOneEdge(0,1,2);
//    graph1.AddOneEdge(0,2,2);
//    graph1.AddOneEdge(1,4,3);
//    graph1.AddOneEdge(2,0,5);
//    graph1.AddOneEdge(2,3,6);
//    graph1.AddOneEdge(3,0,3);
//    cout << "directed graph";
//    cout << " Breadth prioritizes traversal of results:";
//    graph1.BFSTraverse(0);
//    cout << endl;
//    cout << "Depth-first traversal results：";
//    graph1.DFSTraverse(0);
//    cout << endl;
//
//    for(c = 'A'; c <= 'E'; c++)
//        graph2.AddOneVertex(c);
//    graph2.AddOneEdge(0,1,2);
//    graph2.AddOneEdge(0,2,5);
//    graph2.AddOneEdge(0,3,3);
//    graph2.AddOneEdge(1,4,3);
//    graph2.AddOneEdge(2,3,6);
//    cout << "directed graph";
//    cout << " Breadth prioritizes traversal of results:";
//    graph2.BFSTraverse(0);
//    cout << endl;
//    cout << "Depth-first traversal results：";
//    graph2.DFSTraverse(0);
//    cout << endl;
    return 0;
}