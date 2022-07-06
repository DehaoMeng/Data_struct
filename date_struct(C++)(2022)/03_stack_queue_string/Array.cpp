//
// Created by 86176 on 2022/3/31 0031.
//

#include "Array.h"
#include <iostream>
#include <cassert>
using namespace std;
Array::Array() {
    a = new int[10]();
}
Array::Array(int b[], int length) {
    a = new int[length];
    a = b;
    len = length;
}

Array::Array(const Array &arr) {
    this->a = arr.a;
    this->len = arr.len;
}

void Array::sort() {
    int startScan, minIndex, minValue;
    for (startScan = 0; startScan < len-1; startScan++)
    {
        minIndex = startScan;
        minValue = a[startScan];
        for(int index = startScan + 1; index < len; index++)
        {
            if (a[index] < minValue)
            {
                minValue = a[index];
                minIndex = index;
            }
        }
        a[minIndex] = a[startScan];
        a[startScan] = minValue;
    }
}
Array::~Array() {}

void Array::print() {
    for (int i = 0; i < len; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int &Array::operator[](int index) {
    if(index<0||index>len)
    {
        cout<<"Index is out of range. Program terminates.";
        assert(false);
    }
    return a[index];

}

Array &Array::operator=(const Array &r) {
    for (int i = 0; i < r.len; i++) {
        if (a[i] != r.a[i])
        {
            a[i] = r.a[i];
        }
    }
    len = r.len;
    return *this;

}