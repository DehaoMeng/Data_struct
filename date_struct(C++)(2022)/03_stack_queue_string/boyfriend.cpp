/*
 * BF字符串匹配算法
 */
#include <iostream>
#define OK 1
#define Error 0
using namespace std;
int BF(string A, string B, int i){
    int j=0;
    while(i<(int)A.length()&&j<(int)B.length()){//两个字符串均为比较到串尾（只有有一个到串尾就跳出循环）
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
        cout<<"已查询到！"<<endl;
        return i-(int)B.length() ;
    }
    else{
        cout<<"未查询到！"<<endl;
        return Error;
    }
}
int main(){
    cout<<"请输入主串：";
    string a,b;
    cin>>a;
    cout<<"请输入模式串：";
    cin>>b;
    cout<<"请输入查询开始的位置：(第一位为0)";
    int i=0;
    cin>>i;
    if(!BF(a,b,i)){
        cout<<"模式串在主串之中不存在！"<<endl;
        return Error;
    }
    else{
        cout<<"模式串在主串之中存在！"<<endl;
        cout<<"起始位置为："<<BF(a,b,i)+1<<endl;
        return OK;
    }
}
