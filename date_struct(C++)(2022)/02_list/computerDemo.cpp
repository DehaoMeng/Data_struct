#include "computer.cpp"


using namespace std;
int main()
{
    Computer A(2, 6,"honhr");//调用有参构造函数
    cout << "A电脑的名称是：" << A.getname() << endl;//打印A电脑的名称
    Computer B(A);//调用拷贝构造函数
    cout << "B电脑屏幕的显示面积是：" << B.area() << endl;//打印B电脑的area
    Computer C;//调用无参构造函数
    C.setbreadth(3);//设置C电脑的breadth
    C.setlength(5);//设置C电脑的length
    cout << "C电脑的屏幕显示面积是：" << C.area() << endl;//打印C电脑的area
    system("pause");
    return 0;
}


