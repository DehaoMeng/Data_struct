/*
 * 对称矩阵的存储,上三角打印输出,从上往下输出；下三角打印输出，横向输出。
 */
#include <iostream>

#define OK 1
#define Error 0
using namespace std;

void Print(int *a,int n){
    int s = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j <= i)
            {
                cout << a[s++] << " ";
            } else {
                cout << a[n * (n + 1) / 2] << " ";
            }
        }
        cout <<endl;
    }
}

int main(){
    int n;
    cin >> n;
    int i=0;
    int *a;
    a = new int[n * (n + 1) / 2 + 1];
    while (i <= n * (n + 1) / 2) {
        cin >> a[i];
        i++;
    }
    Print(a,n);
    return OK;
}

