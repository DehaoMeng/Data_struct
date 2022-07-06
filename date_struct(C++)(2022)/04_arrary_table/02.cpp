/*
 * 编写一个算法，将一个n阶矩阵A的元素从左上角开始，按照蛇形方式按行优先存储到一维数组中B中，并且以矩阵的格式输出矩阵A和B
 */
#include <iostream>

#define OK 1
#define Error 0
using namespace std;

void Print_line(int *a,int n){
    for (int i = 0; i < n*n; i++) {
        if (i != 0 && i % n == 0){
            cout << endl << a[i] << " ";
        } else{
            cout << a[i] << " ";
        }
    }
    cout << endl << endl;
}

void Print_cow(int *a,int n)
{
    int i,j=0;
    for (i = 0; i < n; i++) {
        if (j <= n) {
            for (; j < n * n; ) {
                cout << a[j] << " ";
                j += n;
            }
            j = j-n+1;
        }
        else if(j >= n*(n-1)) {
            for (; j > 0; ) {
                cout << a[j] << " ";
                j -= n;
            }
            j += n + 1;
        }
        cout << endl;
    }
}

int main(){
    int n;
    cin >> n;
    int i=0;
    int *a;
    a = new int[n * n];
    while (i < n * n) {
        cin >> a[i];
        i++;
    }
    Print_line(a,n);
    Print_cow(a,n);
    return OK;
}

