#include <iostream>
#include <iomanip>
using namespace std;
const double Pi = 3.1415926;
class Sphere{
private:
    float radius;
public:
    float GetRadius(){return radius;}
    void SetRadiu(float r=1.0){radius = r;}
    float GetArea() {return 4 * Pi * radius * radius;}
    float GetVolume(){return 4 / 3 * Pi * radius * radius;}
};

int main()

{
    Sphere s;
    cout<<fixed<<setprecision(2);
    s.SetRadiu();//缺省设置球半径为1
    cout<<"Radius:"<<s.GetRadius()//获取半径
        <<",Superficial area:"<<s.GetArea()//求表面积
        <<",Volume:"<<s.GetVolume()<<endl;//求体积
    double r;
    cin>>r;
    s.SetRadiu(r);
    cout<<"Radius:"<<s.GetRadius()<<",Superficial area:"<<s.GetArea()
        <<",Volume:"<<s.GetVolume()<<endl;
}
