#pragma once
#include<iostream>
#include<string>
using namespace std;
class Computer
{
private:
    double length;
    double breadth;
    string name;

public:
    Computer();//无参构造函数
    Computer(double len, double bre,string nm);//有参构造函数
    double area();//返回面积值
    Computer(const Computer& C);//拷贝构造函数
    double getlength();//获取length值
    double getbreadth();//获取breadth值
    string getname();//获取name值
    void setlength(double len);//设置length值
    void setbreadth(double bre);//设置breadth值
    void setname(string nm);//设置name值
    ~Computer()//析构函数
    {          }
};
