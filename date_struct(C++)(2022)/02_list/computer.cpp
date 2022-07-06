#include"computer.h"
#include<iostream>
#include<string>
Computer::Computer()   //调用无参构造函数
{
    cout << "Computer is created,but it is null" << endl;
}
Computer::Computer(double len, double bre, string nm)//有参构造函数
{
    length = len;
    breadth = bre;
    name = nm;
}

double Computer::area()   //返回面积值
{
    return length * breadth;

}

Computer::Computer(const Computer& C)// 拷贝构造函数
{
    length = C.length;
    breadth = C.breadth;
}

double Computer::getlength()//返回length值
{
    return length;
}

double Computer::getbreadth()//返回breadth值
{
    return breadth;
}

void Computer::setbreadth(double bre)//设置bredth值
{
    breadth = bre;
}

void Computer::setlength(double len)//设置length值
{
    length=len;
}

string Computer::getname()//返回name值
{
    return name;
}

void Computer::setname(string nm)//设置name值
{
    name = nm;
}