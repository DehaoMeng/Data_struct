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
    Computer();//�޲ι��캯��
    Computer(double len, double bre, string nm);//�вι��캯��
    void area()//�������ֵ
    {
        cout << "���Եĳߴ���" << length * breadth << endl;
    }
    Computer(const Computer& C);//�������캯��
    double getlength();//��ȡlengthֵ
    double getbreadth();//��ȡbreadthֵ
    string getname();//��ȡnameֵ
    void setlength(double len);//����lengthֵ
    void setbreadth(double bre);//����breadthֵ
    void setname(string nm);//����nameֵ
    ~Computer()//��������
    {
        cout << "Computer����" << endl;
    }
};
Computer::Computer()   //�޲ι��캯��
{
    cout << "Computer is created,but it is null" << endl;
}
Computer::Computer(double len, double bre, string nm)//�вι��캯��
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
        cout << "ipad�ĳߴ���" << size << endl;
    }
    IPAD(double sz)
    {
        size = sz;
    }
    ~IPAD()
    {
        cout << "IPAD����" << endl;
    }
};
Computer::Computer(const Computer& C)// �������캯��
{
    length = C.length;
    breadth = C.breadth;
}double Computer::getlength()//����lengthֵ
{
    return length;
}
double Computer::getbreadth()//����breadthֵ
{
    return breadth;
}
string Computer::getname()//����nameֵ
{
    return name;
}
void Computer::setbreadth(double bre)//����bredthֵ
{
    breadth = bre;
}
void Computer::setlength(double len)//����lengthֵ
{
    length = len;
}
void Computer::setname(string nm)//����nameֵ
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
