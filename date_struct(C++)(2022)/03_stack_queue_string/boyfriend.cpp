/*
 * BF�ַ���ƥ���㷨
 */
#include <iostream>
#define OK 1
#define Error 0
using namespace std;
int BF(string A, string B, int i){
    int j=0;
    while(i<(int)A.length()&&j<(int)B.length()){//�����ַ�����Ϊ�Ƚϵ���β��ֻ����һ������β������ѭ����
        if(A[i]==B[j]) {
            i++;
            j++;
        }
        else{
            i=i-j+1;
            j=0;
        }
    }
    if(j>=(int)B.length()){
        cout<<"�Ѳ�ѯ����"<<endl;
        return i-(int)B.length() ;
    }
    else{
        cout<<"δ��ѯ����"<<endl;
        return Error;
    }
}
int main(){
    cout<<"������������";
    string a,b;
    cin>>a;
    cout<<"������ģʽ����";
    cin>>b;
    cout<<"�������ѯ��ʼ��λ�ã�(��һλΪ0)";
    int i=0;
    cin>>i;
    if(!BF(a,b,i)){
        cout<<"ģʽ��������֮�в����ڣ�"<<endl;
        return Error;
    }
    else{
        cout<<"ģʽ��������֮�д��ڣ�"<<endl;
        cout<<"��ʼλ��Ϊ��"<<BF(a,b,i)+1<<endl;
        return OK;
    }
}
