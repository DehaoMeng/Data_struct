//
// Created by 86176 on 2022/3/31 0031.
//

#ifndef SHUXUN_STACK_CPP_ARRARY_H
#define SHUXUN_STACK_CPP_ARRARY_H


class Array {
private:
    int *a;
    int len;
public:
    Array();
    Array(int b[],int length);
    Array(const Array &arr);
    Array& operator=(const Array& r);
    int& operator[](int index);
    void sort();
    void print();
    ~Array();
};


#endif //SHUXUN_STACK_CPP_ARRARY_H
