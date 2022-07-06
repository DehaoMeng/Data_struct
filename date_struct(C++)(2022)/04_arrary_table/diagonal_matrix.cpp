/*
 * 判断对角矩阵的c++实现。
 */
#include <iostream>
using namespace std;
typedef int Elemtype;
const Elemtype OK = 1;
const Elemtype Error = 0;
const int M = 3;
const int N = 3;

Elemtype diagonal(Elemtype **a, int m, int n) // m n 分别为行和列数
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (abs(i-j)>1 && (*(((int *)a+n*i)+j)) != 0)
                return Error;
        }
    }
    return OK;
}

int main()
{
    Elemtype a[M][N] = {{1,2,0},{1,1,1},{0,1,0}};
    if (diagonal((Elemtype **)a,M,N))
    {
        cout << "该矩阵为对角矩阵" <<endl;
    }
    else
    {
        cout << "该矩阵不为对角矩阵" <<endl;
    }
    return OK;
}