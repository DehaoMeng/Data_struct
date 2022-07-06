//
// Created by 86176 on 2022/4/16 0016.
//

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
    Computer(double len, double bre, string nm);//有参构造函数
    void area()//返回面积值
    {
        cout << "电脑的尺寸是" << length * breadth << endl;
    }
    Computer(const Computer& C);//拷贝构造函数
    double getlength();//获取length值
    double getbreadth();//获取breadth值
    string getname();//获取name值
    void setlength(double len);//设置length值
    void setbreadth(double bre);//设置breadth值
    void setname(string nm);//设置name值
    ~Computer()//析构函数
    {
        cout << "Computer析构" << endl;
    }
};
Computer::Computer()   //无参构造函数
{
    cout << "Computer is created,but it is null" << endl;
}
Computer::Computer(double len, double bre, string nm)//有参构造函数
{
    length = len;
    breadth = bre;
    name = nm;
}
class IPAD :public Computer
{
private:
    double size;
public:
    void area()
    {
        cout << "ipad的尺寸是" << size << endl;
    }
    IPAD(double sz)
    {
        size = sz;
    }
    ~IPAD()
    {
        cout << "IPAD析构" << endl;
    }
};
Computer::Computer(const Computer& C)// 拷贝构造函数
{
    length = C.length;
    breadth = C.breadth;
}double Computer::getlength()//返回length值
{
    return length;
}
double Computer::getbreadth()//返回breadth值
{
    return breadth;
}
string Computer::getname()//返回name值
{
    return name;
}
void Computer::setbreadth(double bre)//设置bredth值
{
    breadth = bre;
}
void Computer::setlength(double len)//设置length值
{
    length = len;
}
void Computer::setname(string nm)//设置name值
{
    name = nm;
}
int main()
{
    Computer D(3, 4, "honor");
    IPAD U(9);
    U.area();
    Computer* C;
    C = &U;
    C->area();
//    system("pause");
    return 0;
}
