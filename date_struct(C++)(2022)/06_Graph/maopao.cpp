//
// Created by 86176 on 2022/6/6 0006.
//

#include <iostream>


using namespace std;
const int MAX = 100;

// 交换两个数
void Swap(int &x, int &y) {
    int temp;

    temp = x;
    x = y;
    y = temp;
}
void print(int a[],int length){
    for (int i = 0; i < length; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}
// 双向冒泡排序
void twoBubbleSort(int a[], int length) {
    int left, right, shift, i; // shift为记录左右两端已排序的元素位置

    left = 0;
    right = length - 1;
    shift = 1;
    while(left < right) { // 往右排序
        for(i = left; i < right; i++) {
            if(a[i] > a[i+1]) {
                Swap(a[i], a[i+1]);
                shift = i;
            }
        }
        print(a,length);
        right = shift;
        for(i = right-1; i >= left; i--) {
            if(a[i] > a[i+1]) {
                Swap(a[i], a[i+1]);
                shift = i + 1;
            }
        }
        print(a,length);
        left = shift;
    }

}

int main() {
    int a[MAX], n=0;
    int num;
    while (cin >> num){
        a[n++] = num;
        char ch = getchar();
        if (ch == '\n')
            break;
    }
    // 调用双向冒泡排序函数
    twoBubbleSort(a, n);
    return 0;
}