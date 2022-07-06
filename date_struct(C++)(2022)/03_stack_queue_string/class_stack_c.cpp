/*
 * C++ 自带了栈类实现
 */
#include <iostream>
#include <stack>
#define OK 1
#define Error 0
using namespace std;

int main(){
	//定义一个整形的栈
	stack <int> mStack;
	cout<<"the size of mStack is:"<<mStack.size()<<endl;
	//向栈中加入元素
	mStack.push(1);
	mStack.push(2);
	mStack.push(3);
	mStack.push(4);
	cout<<"after push , the size of mStack is:"<<mStack.size()<<endl;
    if(mStack.empty()) return Error;
	//弹出栈中的内容
	while(!mStack.empty()) {    //栈的遍历
        cout << "the data will be pop is:" << mStack.top() << endl;
        mStack.pop();
        cout << "after pop ,the len of stack is:" << mStack.size() << endl;
    }
	return OK;
}
