#include "computer.cpp"


using namespace std;
int main()
{
    Computer A(2, 6,"honhr");//�����вι��캯��
    cout << "A���Ե������ǣ�" << A.getname() << endl;//��ӡA���Ե�����
    Computer B(A);//���ÿ������캯��
    cout << "B������Ļ����ʾ����ǣ�" << B.area() << endl;//��ӡB���Ե�area
    Computer C;//�����޲ι��캯��
    C.setbreadth(3);//����C���Ե�breadth
    C.setlength(5);//����C���Ե�length
    cout << "C���Ե���Ļ��ʾ����ǣ�" << C.area() << endl;//��ӡC���Ե�area
    system("pause");
    return 0;
}


