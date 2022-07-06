/*
 * KMP�㷨C++ʵ��
 */
#include <iostream>
#define OK 1
#define Error 0
using namespace std;
int* GetNext(string &A)
{
    int* next = new int(A.length());
    next[0] = -1;
    int j=0,k=-1;
    while(j<(int)A.length() - 1)
    {
        if(k == -1 || A[j] == A[k])
        {
            j++;
            k++;
            next[j] = k;
        } else
        {
            k = next[k];
        }
    }
    return next;
}
int Kmp(string &A,string &B)
{
    int i=0;
    int j=0;
    int* next = GetNext(A);
    while(i < (int)A.length() && j < (int)B.length())
    {
        if (j == -1 || A[i] == B[j])
        {
            i++;
            j++;
        }
        else
        {
            j=next[j];
        }
    }
    if (j == (int)B.length())
    {
        return i-j+1;
    }
    return Error;
}


int main()
{
    string A,B;
    cout << "����������";
    cin >> A;
    cout << "������ƥ�䴮";
    cin >> B;
    int p = Kmp(A,B);
    if(p!=Error)
    {
        cout << "ƥ�䵽���ַ���λ��Ϊ" << p << endl;
    }
    else
    {
        cout << "δƥ�䵽" << endl;
    }
    return OK;
}