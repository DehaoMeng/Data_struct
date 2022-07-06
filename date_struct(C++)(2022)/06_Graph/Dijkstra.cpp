//
// Created by 86176 on 2022/5/7 0007.
// Dijkstra算法
//

#include<iostream>
#include <string>
#define DataType char
using namespace std;
const int MAXSIZE = 30;
const int MAXCOST = 100;
const int ERROR = -1;

class Graph {
private:
    DataType vertex[MAXSIZE];
    int AdjMatrix[MAXSIZE][MAXSIZE];
    int vertexNum;
public:
    Graph();

    bool Dijkstra(DataType start);

    DataType GetVertex(int n);

    int GetVertexNum(DataType c);

    int Print();
};


Graph::Graph() {
    vertexNum = 0;
    string vertex1;
    cin >> vertex1;
    for (unsigned i = 0; i < vertex1.length(); ++i) {
        vertex[i] = vertex1[i];
    }
    vertexNum = vertex1.length();
    for (int i = 0; i < vertexNum; ++i) {
        for (int j = 0; j < vertexNum; ++j) {
            AdjMatrix[i][j] = MAXCOST;
        }
    }
    char m,n;
    int weights;
    cin >> m >> n >> weights;
    while (true) {
        AdjMatrix[GetVertexNum(m)][GetVertexNum(n)] = weights;
        cin >> m;
        if (m == '#')
            return;
        cin >> n >> weights;
    }
}

int Graph::GetVertexNum(char c) {
    for (int i = 0; i < vertexNum; ++i) {
        if (vertex[i] == c) {
            return i;
        }
    }
    return -1;
}

char Graph::GetVertex(int n) {
    return vertex[n];
}

bool Graph::Dijkstra(DataType start) {
    int S[vertexNum];  // 记录已求出最短路径的顶点。
    int U[vertexNum];  // 表示从某一顶点到其他顶点的最短路径。
    /* 初始化算法信息 */
    int k = GetVertexNum(start);
    for (int i = 0; i < vertexNum; ++i) {
        S[i] = 0;
        U[i] = AdjMatrix[k][i];
    }
    for (int m = 0; m < vertexNum - 1; ++m) {
        S[k] = 1;
        for (int i = 0; i < vertexNum; ++i) {
            if (S[i] != 1) {
                if (U[i] == MAXCOST && AdjMatrix[k][i] != MAXCOST) {
                    U[i] = U[k] + AdjMatrix[k][i];
                } else if (U[i] != MAXCOST && AdjMatrix[k][i] + U[k] < U[i]) {
                    U[i] =U[k] + AdjMatrix[k][i];
                }
            }
        }
        U[k] = -1;
        for (int i = 0; i < vertexNum; ++i) {
            if (U[k] == -1 && U[i] != -1){
                k = i;
            }
            if (U[i] != -1 && U[i] < U[k]) {
                k = i;
            }
        }
        cout << vertex[GetVertexNum(start)] << vertex[k] << " " << U[k] << endl;
    }
    return true;
}

int Graph::Print() {
    for (int i = 0; i < vertexNum; ++i) {
        for (int j = 0; j < vertexNum; ++j) {
            cout << AdjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}

int main() {
    Graph p;
    DataType c;
    cin >> c;
    p.Dijkstra(c);
    return 0;
}