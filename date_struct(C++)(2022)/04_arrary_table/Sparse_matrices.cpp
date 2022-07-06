/*
 * C++类模板实现稀疏矩阵的实现
 * */
#include <iostream>
using namespace std;
const int OK = 1;
const int Error = 0;
const int MaxSize = 1000;	//定义常量MaxSize，表示矩阵中非零数据元素个数的最大值
typedef int ElemType;


class SMatrix
{
public:
    typedef struct Trituple {
        int i;	//非零数据元素的行号
        int j;	//非零数据元素的列号
        ElemType e;	//非零数据元素的数据值
    }Tupletype;
    SMatrix();    //构造函数，初始化一个空三元组表
    SMatrix(int **d, int m, int n);    //重载：构造函数，根据原始矩阵创建稀疏矩阵
    ~SMatrix() {
        delete &mu, &nu, &tu;
        delete[] &data; // 这里的析构由于c艹没有void指针所以会警告
    };    //析构函数，释放内存。（注：delete 删除的是指针）
    int MDisplay();    //遍历矩阵，并输出非零数据元素的值
    SMatrix *MatrixTrans_Fast();    //矩阵转置算法（快速）
    SMatrix *MatrixTrans();    //矩阵转置算法（普通）
    SMatrix *MultiMatrix(SMatrix *MB);    //矩阵相乘算法
private:
    int mu;    //矩阵的行数mu
    int nu;    //矩阵的列数nu
    int tu;    //矩阵中非零数据元素的个数tu
    Tupletype data[MaxSize];    //矩阵的三元组表
};

SMatrix::SMatrix()
{
    /*
        构造函数，初始化
    */
    this->mu = 0;	//原矩阵行数
    this->nu = 0;	//原矩阵列数
    this->tu = 0;	//原矩阵非零元素个数
}

SMatrix::SMatrix(int **d, int m, int n)
{
    /*
        构造函数（重载）：根据原始矩阵创建稀疏矩阵
        注：参数 int **d 的入参（二维数组）需要强制转换 （int **）
        如：int array[2][3];  (int **) array
        ***注：此创建的一维稀疏矩阵以行优先顺序存储
    */
    //1.参数矩阵为空，调默认构造函数
    if (d == NULL || m <= 0 || n <= 0) {
        SMatrix();
        return;
    }
    //2.初始化
    this->mu = m;	//原矩阵行数
    this->nu = n;	//原矩阵列数
    this->tu = 0;	//原矩阵非零元素个数
    int e = 0;	//非零元素临时变量
    //3.遍历原矩阵，查找非零元素，并存放入三元组表中
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            e = *((int*)d + n * i + j);	//待研究一下！！（注：指针的指针 在数组中无法通过 d[i][j] 寻址，可参看编译原理）
            if (e == 0)
                continue;
            this->data[tu].i = i;
            this->data[tu].j = j;
            this->data[tu].e = e;
            this->tu++;
        }
    }
}

int SMatrix::MDisplay()
{
    /*
        打印稀疏矩阵
    */
    int t = 0;
    if (this->tu == 0) return Error;
    for (int i = 0; i < this->mu; i++)
    {
        for (int j = 0; j < this->nu; j++)
        {
            //非零元素
            if (t < this->tu && this->data[t].i == i && this->data[t].j == j)
            {
                cout << this->data[t++].e << " ";
            }
                //零元素
            else
                cout << 0 << " ";
        }
        cout << endl;
    }
    return OK;
}

SMatrix *SMatrix::MatrixTrans()
{
    /*
        矩阵转置算法（普通版）
        算法实现：按原矩阵列遍历一维稀疏矩阵
        注：此类中的一维稀疏矩阵以行优先顺序存储，故转置变为以列优先顺序，需改变次序
        复杂度：O(nu*tu)	（若非零数据元个数与原矩阵同一数量级，则复杂度：O(nu*nu*mu) ）
    */
    //0.初始化 转置矩阵 MT 对象
    SMatrix *MT = new SMatrix();
    MT->mu = this->nu;
    MT->nu = this->mu;
    MT->tu = this->tu;
    //1.遍历矩阵每一列
    int p = 0;	//计数 MT矩阵 非零元素个数
    for (int j = 0; j < this->nu; j++)
    {
        //2.遍历一维稀疏矩阵，寻找同列的非零元素
        for (int q = 0; q < this->tu; q++)
        {
            if (this->data[q].j == j)
            {
                //转置赋值
                MT->data[p].i = this->data[q].j;
                MT->data[p].j = this->data[q].i;
                MT->data[p].e = this->data[q].e;
                p++;
            }
        }
    }
    return MT;
}

SMatrix *SMatrix::MatrixTrans_Fast()
{
    /*
    矩零阵转置算法（快速版）
    算法导引：普通算法中，在每次遍历一列中的非数据元时，同时也遍历到了非当前列的数据元，
            由于不知道此非当前列的数据元应置于转置后的什么位置，导致每次跳过，最终导致复杂度升高。
    算法实现：
        描述：先确定每列首个非零元位置，后每列后续元素根据当前列首个元素位置填放
        1.遍历稀疏矩阵列的非零元个数
        2.遍历每列，构建一维数组 col_position[]， 存放每列非零元位置
            初始化为每列首个非零元位置，后续元素位置逐步加一
            初始化公式：col_position[j] = col_num[j-1] + col_position[j-1], j 为列数
        3.遍历稀疏矩阵，根据 col_position[]，求得转置稀疏矩阵
    注：此类中的一维稀疏矩阵以行优先顺序存储，故转置变为以列优先顺序，需改变次序
    复杂度：O(tn+nu)
    注：转置稀疏矩阵的另一种表述：
            将原矩阵以列优先顺序存储，后以行优先顺序读取，便是转置后的稀疏矩阵
    */
    //0.初始化 转置矩阵 MT 对象
    SMatrix *MT = new SMatrix();
    MT->mu = this->nu;
    MT->nu = this->mu;
    MT->tu = this->tu;
    //1.统计每列非零数据元个数
    int *col_num = new int[this->nu]{ 0 };	//每列非零元个数数组，初始化每个元素为 0
    for (int i = 0; i < this->tu; i++)
    {
        col_num[data[i].j]++;
    }
    //2.初始化 col_position[] 为每列首个非零元素对应转置稀疏矩阵的下标位置
    int *col_position = new int[this->nu]{ 0 }; //每列数据元位置数组，初始化每个元素为 0
    for (int i = 1; i < this->nu; i++)
    {
        col_position[i] = col_position[i-1] + col_num[i-1];
    }
    //3.实现转置
    int p = 0;	//转置矩阵下标
    for (int i = 0; i < this->tu; i++)
    {
        //获取稀疏矩阵元素对应的转置稀疏矩阵下标，并将当前列元素位置下标加一（为后一个非零元素准备）
        p = col_position[this->data[i].j]++;
        //转置元素赋值
        MT->data[p].i = this->data[i].j;
        MT->data[p].j = this->data[i].i;
        MT->data[p].e = this->data[i].e;
    }
    return MT;
}

SMatrix *SMatrix::MultiMatrix(SMatrix *MB)
{
    /*
        矩阵相乘算法（快速版）：利用矩阵快速转置算法理念
        算法导引：由于稀疏矩阵是以行优先顺序存储的，所以在矩阵乘法中（左矩阵每一行与右矩阵每一列相乘），
            左矩阵 A 的每一行非零元在其稀疏矩阵中是按行优先顺序 连续存储的；
            右矩阵 B 的每一列非零元在其稀疏矩阵中是按行优先顺序 不连续存储的。
            在一般算发实现上，主要一下几个基本步骤：
                1.矩阵 A 每行的非零元（ A_ij ）都需 与 矩阵 B 对应的 m 行（m == j）的每个非零元 （B_mn） 相乘;
                2.矩阵 A 每行的所有非零元 在与 矩阵 B 每列相乘、再相加后，得到一个每行的累加器；
                3.这个累加器是具有 一 行 Bn 列 的一维数组。
            这样，在实现步骤 1 时，对矩阵 B 的按列遍历，每次都需遍历其整个稀疏矩阵，复杂度很高：O(A.tu * B.tu)；
            所以采用对 矩阵 B 非零元的按行标记，来简化步骤 1 的实现。
        算法实现：
            1.统计 B 矩阵的每行非零元个数：按行遍历，结果存放于数组 row_num[]
            2.标记 B 矩阵每行首个非零元在其稀疏矩阵中的下标位置，存放于 row_position[] 中
            3.实现 A 矩阵每个非零元（因为按行优先存储，故只需按序访问其稀疏矩阵） 与 B 矩阵中对应行的所有非零元（已做标记，节省了全局遍历的时间）相乘
            4.将步骤 3 的结果存放于 累加器 row_result[] 中 （按矩阵 A 的行）
            5.每遍历完 A 矩阵一行非零元，便将 累加器 row_result[] 中非零结果 放于返回对象的稀疏矩阵中，并初始化 累加器 为0
        复杂度：O( B.tu + B.mu + A.tu * B.tu / B.mu + A.mu * B.nu )
            其中： B.tu / B.mu 意为：取 B 矩阵 每行平均非零元 个数
    */
    //合法化校验
    if (this->nu != MB->mu)
    {
        cout << "两个矩阵不能相乘！" << endl;
        return NULL;
    }
    if (this->tu == 0 || MB->tu == 0)
    {
        cout << "结果为零阵！" << endl;
        return NULL;
    }

    //0.初始化结果矩阵
    SMatrix *MResult = new SMatrix();
    MResult->mu = this->mu;
    MResult->nu = MB->nu;
    MResult->tu = 0;

    //1.统计 B 矩阵每行非零元个数
    int *row_num = new int[MB->mu]{ 0 };	//每行非零元个数数组，初始化为 0
    for (int i = 0; i < MB->tu; i++)
    {
        row_num[MB->data[i].i]++;
    }
    //2.标记 B 矩阵每行非零元在其稀疏矩阵中的下标位置，初始化为每行首个非零元位置
    int *row_position = new int[MB->mu]{ 0 };	//每行首个非零元在其稀疏矩阵中的下标位置数组
    for (int i = 1; i < MB->mu; i++)
    {
        row_position[i] = row_position[i-1] + row_num[i-1];
    }
    //3.实现矩阵相乘
    //遍历 A 矩阵的一维稀疏矩阵
    int EA = 0, EB = 0;	//初始化 A、B 矩阵元素 E 为 0
    int IA = 0, IB = 0, JA = 0, JB = 0;	//初始化 A、B 矩阵元素行列为 0
    int NB = 0;	//初始化 B 矩阵某一行的非零元素个数
    int PB = 0;	//初始化 B 矩阵稀疏矩阵下标位置为 0
    int *row_result = new int[MB->nu]{ 0 };	//临时存放 A 矩阵每一行 与 B 矩阵每一列 元素乘积 累加结果
    for (int p = 0; p < this->tu; p++)
    {
        //获取 A 矩阵元素 （ia,ja,ea）
        IA = this->data[p].i;
        JA = this->data[p].j;
        EA = this->data[p].e;
        IB = JA;
        //定位 B 矩阵 IB 行的非零数据元下标位置（对应稀疏矩阵中的）
        PB = row_position[IB];
        //获取 B 矩阵 IB 行的非零元素个数
        NB = row_num[IB];
        //遍历 B 矩阵 IB 行上的非零数据元，实现相乘
        for (int n = 0; n < NB; n++)
        {
            IB = MB->data[PB + n].i;
            JB = MB->data[PB + n].j;
            EB = MB->data[PB + n].e;
            row_result[JB] += EA * EB;
        }
        /*
            A 矩阵一行遍历完的判断条件：（2个情况）
                1.最后一个非零元时：(p == this->tu - 1)
                2.非最后一个非零元时：取下一个非零元的行，判断是否与当前非零元同一行 (this->data[p + 1].i != IA)
            则将一行的非零累加结果赋值到结果矩阵（稀疏矩阵）中，并初始化累加器 为0
        */
        if (p == this->tu - 1 || this->data[p + 1].i != IA )	//不用担心越界！
        {
            //读取并初始化 累加器 row_result[]
            for (int j = 0; j < MB->nu; j++)
            {
                //将累加器不为 0 的结果，放入一维稀疏矩阵中
                if (row_result[j] != 0)
                {
                    MResult->data[MResult->tu].i = IA;
                    MResult->data[MResult->tu].j = j;
                    MResult->data[MResult->tu].e = row_result[j];
                    MResult->tu++;
                }
                //初始化 累加器 row_result[] 为 0
                row_result[j] = 0;
            }
        }
    }

    return MResult;
}


int main()
{
    int a1[3][4] = { { 1,0,0,0 },{ 2,0,0,5 },{ 0,4,5,0 } };
    int a2[4][3] = { { 0,2,3 },{ 0,3,0 },{ 3,0,5 },{ 1,1,1 } };
    SMatrix *sm1 = new SMatrix((int **)a1, 3, 4);
    SMatrix *sm2 = new SMatrix((int **)a2, 4, 3);
    cout << "矩阵1：" << endl;
    sm1->MDisplay();
    cout << "矩阵2：" << endl;
    sm2->MDisplay();
    cout << "矩阵1 转置结果：" << endl;
    SMatrix *sm1_t = sm1->MatrixTrans_Fast();
    sm1_t->MDisplay();
    cout << "矩阵相乘结果：" << endl;
    SMatrix *multiResult = sm1->MultiMatrix(sm2);
    multiResult->MDisplay();
    return OK;
}