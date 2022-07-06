

#ifndef LINKLIST_LIANSHI_ONLY_CPP_DATA_H
#define LINKLIST_LIANSHI_ONLY_CPP_DATA_H
#include <iostream>
using namespace std;
class Data {
private:
    int year;
    int month;
    int day;
public:
    Data(){};// 无参构造函数
    ~Data(){}; // 析构函数
    void SetData(int y,int m,int d); // 设置日期
    int GetYear();
    int GetMonth();
    int GetDay();
};


#endif //LINKLIST_LIANSHI_ONLY_CPP_DATA_H
