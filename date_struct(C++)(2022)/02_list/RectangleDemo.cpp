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
    cout<<"Length:"<<r.GetLength();//获取长度
    cout<<",Width:"<<r.GetWidth()<<endl;//获取宽度
    cout<<"Area:"<<r.Area()<<endl;//求面积
}

int main()
{
    Rectangle r;
    r.SetData(10,10);//修改长和宽
    PrintRectangle(r);
    r.SetLength(20);//修改长度
    PrintRectangle(r);
    r.SetWidth(20);//修改宽度
    PrintRectangle(r);
    return 0;
}
