/*
 * �ж϶ԽǾ����c++ʵ�֡�
 */
#include <iostream>
using namespace std;
typedef int Elemtype;
const Elemtype OK = 1;
const Elemtype Error = 0;
const int M = 3;
const int N = 3;

Elemtype diagonal(Elemtype **a, int m, int n) // m n �ֱ�Ϊ�к�����
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
        cout << "�þ���Ϊ�ԽǾ���" <<endl;
    }
    else
    {
        cout << "�þ���Ϊ�ԽǾ���" <<endl;
    }
    return OK;
}