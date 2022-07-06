//
// Created by 86176 on 2022/3/31 0031.
//
#include <iostream>
#include "Array.cpp"
int main()
{
    Array x;
    int a[10];
    for (int i = 0; i < 10; i++) {
        a[i] = 10 - i;
    }
    Array y(a,10);
    y.print();
    y.sort();
    y.print();
    cout << y[1] <<endl;
    x = y;
    x.print();
    return 0;
}