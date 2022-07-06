/**
 * ͼ���ڽӾ���c++ʵ��
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
    DataType m_vertex[MAXSIZE]; // ���㼯��
    int m_nAdjMatrix[MAXSIZE][MAXSIZE]; // �ڽӾ���
    int m_nVertexNum=0; // ������Ŀ
    int m_nGraphType; // ͼ������ 0������ͼ��1������ͼ
public:
    AdjGraph(int nGraphType); // ����ͼ
    int GetVertexNum(); // ��ȡ������Ŀ
    int GetFirstEdge(int nV); // ��ȡ��ָ������nV������ĵ�һ����
    /*��ȡ��ָ���ߣ�nV1,nV2����<nV1,nV2>����ͬ������nV1����һ����*/
    int GetNextEdge(int nV1,int nV2);
    bool AddOneVertex(DataType vertex); //���һ������
    bool AddOneEdge(int nV1,int nV2,int nWeight); // ���һ����
    bool AddOneEdge(int nV1,int nV2); // ���һ����
    bool GetVertexValue(int nV,DataType &vertex); // ��ȡһ�������д洢������
    bool IsEdge(int nV1,int nV2); // �ж�һ�����Ƿ����
    bool SetEdgeWeight(int nV1,int nV2,int nWeight); // ����һ���ߵ�Ȩ
    bool GetEdgeWeight(int nV1,int nV2,int &nWeight); // ��ȡһ���ߵ�Ȩ
    /*�Եݹ鷽ʽ���±�nV�Ķ��㿪ʼ��ͼ��������ȱ���*/
    bool DFSTraverse(int nV);
    /*��DFSTraverse�����Եݹ鷽ʽ���ͼ��������ȱ���*/
    void DFS(int nV,int bVisited[]);
//    bool DFSTraverse(int nV); // �Էǵݹ鷽ʽ��ͼ��������ȱ���
    bool BFSTraverse(char Vertex1,char Vertex2); // ���±�ΪnV�Ķ��㿪ʼ��ͼ��������ȱ���
    int GetNum() {return m_nVertexNum;}
    int Print(); // ����ڽӾ���
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
    // Ȩ��Ϊ����ֵ��������ߴ���
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
    // �������������ڣ������������ԭ��û�б�
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
    // �������������ڣ������������ԭ��û�б�
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
/** ������ȱ����������ĵ������� **/
//template <class DataType>
//bool AdjGraph<DataType>::BFSTraverse(int nV)
//{
//    queue<int> queue;
//    int nVisitVertex, nVertex, nBegVertex = nV;
//    int bVisited[MAXSIZE]; // ��¼һ�������Ƿ��Ѿ�����
//    DataType vertex;
//    if(nV < 0 || nV >=m_nVertexNum)
//        return false;
//    memset(bVisited,0, sizeof(bVisited)); // �����������Ϊδ����״̬
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
//        // �������û�з��ʵĽ�㣬������Ӹö��㿪ʼ����������ȱ���
//        int n;
//        for (n = nBegVertex + 1; n < m_nVertexNum + nV; n++) {
//            if (!bVisited[n % m_nVertexNum])
//            {
//                nBegVertex = n % m_nVertexNum;
//                break;
//            }
//        }
//        if (n == m_nVertexNum + nV) break; // ���ж��㶼�ѷ��ʣ��˳�ѭ��
//    }
//    return true;
//}

template <class DataType>
bool AdjGraph<DataType>::BFSTraverse(char Vertex1,char Vertex2)
{
    queue<int> queue;
    int nVisitVertex, nVertex, nBegVertex = 0;
    int bVisited[MAXSIZE]; // ��¼һ�������Ƿ��Ѿ�����
    DataType vertex;
    memset(bVisited,0, sizeof(bVisited)); // �����������Ϊδ����״̬
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


/** ������ȱ�������������������� **/
template <class DataType>
bool AdjGraph<DataType>::DFSTraverse(int nV)
{
    int nBegVertex;
    int bVisited[MAXSIZE];
    // ���±�ΪnV�Ķ��㲻���ڣ������ʧ��
    if(nV < 0 || nV >= m_nVertexNum)
        return false;
    // ���ø�����Ϊδ����״̬
    memset(bVisited,0,sizeof(bVisited));
    // ����ͼ�е�ÿһ�����㣬��Ϊδ����״̬����Ӹö��㿪ʼ
    // ����DFS�����԰����ö������ͨ��ͼ����������ȱ���
    for (nBegVertex = nV; nBegVertex < m_nVertexNum + nV; nBegVertex++)
    {
        if(!bVisited[nBegVertex % m_nVertexNum])
            DFS(nBegVertex,bVisited);
    }
    return true;
}
/** ��DFSTraverse�����Եݹ鷽ʽ���ͼ��������ȱ��� */
template <class DataType>
void AdjGraph<DataType>::DFS(int nV, int bVisited[])
{
    DataType vertex;
    int nVertex;
    // �ȷ��ʵ�ǰ���㣬������״̬����Ϊ�ѷ���
    GetVertexValue(nV,vertex);
    cout << vertex << " ";
    bVisited[nV] = 1;
    // �����ȡ�뵱ǰ�������ڽӵĶ��㣬����ȡ���Ķ���δ����
    // �����DFS�����԰����ö������ͨ��ͼ����������ȱ���
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
//    cout << "Depth-first traversal results��";
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
//    cout << "Depth-first traversal results��";
//    graph2.DFSTraverse(0);
//    cout << endl;
    return 0;
}