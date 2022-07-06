#include <iostream>

using namespace std;
class Rectangle{
private:
    float length,width;
public:
    Rectangle(){};
    ~Rectangle(){}
    void SetData(float a,float b){length = a;width = b;}
    void SetLength(float a){length = a;}
    void SetWidth(float b){width = b;}
    float GetLength() {return length;}
    float GetWidth(){return width;}
    float Area(){return width * length;}
};


void PrintRectangle(Rectangle& r)
{
    cout<<"Length:"<<r.GetLength();//��ȡ����
    cout<<",Width:"<<r.GetWidth()<<endl;//��ȡ���
    cout<<"Area:"<<r.Area()<<endl;//�����
}

int main()
{
    Rectangle r;
    r.SetData(10,10);//�޸ĳ��Ϳ�
    PrintRectangle(r);
    r.SetLength(20);//�޸ĳ���
    PrintRectangle(r);
    r.SetWidth(20);//�޸Ŀ��
    PrintRectangle(r);
    return 0;
}
