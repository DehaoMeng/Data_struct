//
// Created by 86176 on 2022/5/7 0007.
// prim算法
//

#include<iostream>

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

    bool Prim(DataType start);

    DataType GetVertex(int n);

    int GetVertexNum(DataType c);

    int Print();
};


Graph::Graph() {
    vertexNum = 0;
    DataType vertex1;
    cin >> vertex1;
    while (vertex1 != '!') {
        vertex[vertexNum] = vertex1;
        vertexNum++;
        cin >> vertex1;
    }
    for (int i = 0; i < vertexNum; ++i) {
        for (int j = 0; j < vertexNum; ++j) {
            AdjMatrix[i][j] = MAXCOST;
        }
    }
    int m, n, weights;
    cin >> m >> n >> weights;
    while (true) {
        AdjMatrix[m][n] = AdjMatrix[n][m] = weights;
        cin >> m;
        if (m == -1)
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
    return MAXSIZE;
}

char Graph::GetVertex(int n) {
    return vertex[n];
}

bool Graph::Prim(DataType start) {
    int sumcoast=0;
    int lowcost[vertexNum];
    int closest[vertexNum];
    int i, j, k, min;
    int startNum = GetVertexNum(start);
    for (i = 0; i < vertexNum; ++i) {
        lowcost[i] = AdjMatrix[startNum][i];
        closest[i] = startNum;
    }
    lowcost[startNum] = MAXCOST;
    closest[startNum] = -1;
    for (i = 0; i < vertexNum-1; ++i) {
        min = MAXCOST;
        k = i;
        for (j = 0; j < vertexNum; ++j) {
            if (lowcost[j] != 0 && lowcost[j] < min && closest[j] != -1) {
                min = lowcost[j];
                k = j;
            }
        }
//            cout << k << " " << closest[k] <<endl;
        cout << vertex[closest[k]] << vertex[k] << " " << min <<endl;
        sumcoast += min;
        closest[k] = -1;
        lowcost[k] = MAXCOST;
        for (j = 0; j < vertexNum; ++j) {
            if (closest[j] != -1 && AdjMatrix[k][j] < lowcost[j]) {
                lowcost[j] = AdjMatrix[k][j];
                closest[j] = k;
            }
        }
    }
    cout << sumcoast;
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
//    p.Print();
    cin >> c;
    p.Prim(c);
    return 0;
}