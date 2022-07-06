/*
 *                              有不知名错误 希望有大佬能帮忙更改
 *                              C++低能儿
 *
 *
 * */



/*
 * 三元组表类型说明
 */
#include <iostream>
#include <iomanip>
using namespace std;

const int MaxSize = 100;
typedef int ElemType;
typedef struct
{
  int i; /*行标*/
  int j; /*列标*/
  ElemType e; /*非零元素值*/
}tupletype;
typedef struct
{
    int rownum; /*行数*/
    int colnum; /*列数*/
    int nznum; /*非零元素个数*/
    tupletype data[MaxSize]; /*非零三元组表*/
}table;
/*
 * 存储结构的基本操作实现
 */
const int OK = 1;
const int Error = 0;
const int M1 = 3;
const int N1 = 4;
int creatable(table *M, ElemType A[][N1])
{
    /*
     * 按行序扫描二维矩阵
     */
    int i,j;
    M->rownum = M1;
    M->colnum = N1;
    M->nznum = 0;
    for (i = 0; i < M1; i++) {
        for (j = 0; j < N1; j++) {
            if(A[i][j] != 0)
            {
                M->data[M->nznum].i = i;
                M->data[M->nznum].j = j;
                M->data[M->nznum].e = A[i][j];
                M->nznum++;
            }
        }
    }
    if(i == M1) return OK;
    else return Error;
}
int getvalue(table *M, ElemType *x, int row, int col)
{
    /*
     * 取值操作
     */
    int k=0;
    if(row >= M->rownum || col >= M->colnum) return Error;
    while (k < M->nznum && row > M->data[k].i) k++;
    while (k < M->nznum && col > M->data[k].j) k++;
    if(M->data[k].i == row && M->data[k].j == col)
    {
        (*x) = M->data[k].e;
        return OK;
    }
    else return Error;
}
int putvalue(table *M, ElemType x, int row, int col)
{
    /*
     * 赋值操作
     */
    int i,k=0;
    if(row > M->rownum || col > M->colnum) return Error;
    while (k < M->nznum && row > M->data[k].i) k++;
    while (k < M->nznum && col > M->data[k].j) k++;
    if (M->data[k].i == row && M->data[k].j == col)
        M->data[k].e = x;
    else
    {
        for (i = M->nznum - 1; i >= k; i--)
            M->data[i+1] = M->data[i];
        M->data[k].i = row;
        M->data[k].j = col;
        M->data[k].e = x;
        M->nznum++;
    }
    return OK;
}
int printlist(table *M)
{
    /*
     * 输出操作
     */
    int i,j,k,e;
    for (i = 0; i < M->rownum; i++) {
        for(j = 0; j < M->colnum; j++)
        {
            e = 0;
            for (k = 0; k < M->nznum; k++) {
                if (i == M->data[k].i && j == M->data[k].j)
                {
                    e = M->data[k].e;
                    break;
                }
                cout << setw(4) << e;
            }
            cout <<endl;
        }
    }
    return OK;
}
int trans1(table *M, table *T)
{
    /*
     * 转置稀疏矩阵
     * 算法时间O(colnum * nznum) 即矩阵的列数和非零元个数的乘积
     */
    int col,b,q=0;
    T->rownum = M->colnum;
    T->colnum = M->rownum;
    T->nznum = M->nznum;
    if(T->nznum != 0)
    {
        for (col = 0; col < M->colnum; col++) {
            for (b = 0; b < M->nznum; b++) {
                if (M->data[b].j == col)
                {
                    T->data[b].j = M->data[b].i;
                    T->data[b].i = M->data[b].j;
                    T->data[b].e = M->data[b].e;
                    q++;
                }
            }
        }
    }
    return OK;
}
int trans2(table *M, table *T)
{
    /*
     * 快速转置算法
     */
    int i,q,col,num[N1],cpot[N1];
    T->rownum = M->colnum;
    T->colnum = M->rownum;
    T->nznum = M->nznum;
    for (i = 0; i < M->colnum; i++) num[i] = 0;
    for (i = 0; i < M->nznum; i++) num[M->data[i].j]++;  /*求M中每列非零元素个数*/
    cpot[0] = 0;  /*第1列第一个非零元素在T中的位置*/
    for (i = 1; i < M->colnum; i++) cpot[i] = cpot[i-1]+num[i-1]; /*其他列第一个非零元素在T中的位置*/
    for (i=0; i<M->nznum; i++)                                    /* 对M中每个元素，取其列标 得到该元素在T中存放位置*/
    {
        col = M->data[i].j;
        q = cpot[col];
        T->data[q].i = M->data[i].j;
        T->data[q].j = M->data[i].i;
        T->data[q].e = M->data[i].e;
        cpot[col]++;
    }
    return OK;
}
int main() {
    int a[M1][N1] = {{ 1,0,0,0 },{ 2,0,0,5 },{ 0,4,5,0 }};
    int b[M1][N1] = {{ 0,2,3, 0 },{ 0,3,0 , 0},{ 3,0,5 , 0}};
    table S,T;
    creatable(&S,a);
    creatable(&T,b);
    printlist(&T);
    return OK;
}