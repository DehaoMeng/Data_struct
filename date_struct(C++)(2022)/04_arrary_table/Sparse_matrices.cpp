/*
 * C++��ģ��ʵ��ϡ������ʵ��
 * */
#include <iostream>
using namespace std;
const int OK = 1;
const int Error = 0;
const int MaxSize = 1000;	//���峣��MaxSize����ʾ�����з�������Ԫ�ظ��������ֵ
typedef int ElemType;


class SMatrix
{
public:
    typedef struct Trituple {
        int i;	//��������Ԫ�ص��к�
        int j;	//��������Ԫ�ص��к�
        ElemType e;	//��������Ԫ�ص�����ֵ
    }Tupletype;
    SMatrix();    //���캯������ʼ��һ������Ԫ���
    SMatrix(int **d, int m, int n);    //���أ����캯��������ԭʼ���󴴽�ϡ�����
    ~SMatrix() {
        delete &mu, &nu, &tu;
        delete[] &data; // �������������cܳû��voidָ�����Իᾯ��
    };    //�����������ͷ��ڴ档��ע��delete ɾ������ָ�룩
    int MDisplay();    //�������󣬲������������Ԫ�ص�ֵ
    SMatrix *MatrixTrans_Fast();    //����ת���㷨�����٣�
    SMatrix *MatrixTrans();    //����ת���㷨����ͨ��
    SMatrix *MultiMatrix(SMatrix *MB);    //��������㷨
private:
    int mu;    //���������mu
    int nu;    //���������nu
    int tu;    //�����з�������Ԫ�صĸ���tu
    Tupletype data[MaxSize];    //�������Ԫ���
};

SMatrix::SMatrix()
{
    /*
        ���캯������ʼ��
    */
    this->mu = 0;	//ԭ��������
    this->nu = 0;	//ԭ��������
    this->tu = 0;	//ԭ�������Ԫ�ظ���
}

SMatrix::SMatrix(int **d, int m, int n)
{
    /*
        ���캯�������أ�������ԭʼ���󴴽�ϡ�����
        ע������ int **d ����Σ���ά���飩��Ҫǿ��ת�� ��int **��
        �磺int array[2][3];  (int **) array
        ***ע���˴�����һάϡ�������������˳��洢
    */
    //1.��������Ϊ�գ���Ĭ�Ϲ��캯��
    if (d == NULL || m <= 0 || n <= 0) {
        SMatrix();
        return;
    }
    //2.��ʼ��
    this->mu = m;	//ԭ��������
    this->nu = n;	//ԭ��������
    this->tu = 0;	//ԭ�������Ԫ�ظ���
    int e = 0;	//����Ԫ����ʱ����
    //3.����ԭ���󣬲��ҷ���Ԫ�أ����������Ԫ�����
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            e = *((int*)d + n * i + j);	//���о�һ�£�����ע��ָ���ָ�� ���������޷�ͨ�� d[i][j] Ѱַ���ɲο�����ԭ��
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
        ��ӡϡ�����
    */
    int t = 0;
    if (this->tu == 0) return Error;
    for (int i = 0; i < this->mu; i++)
    {
        for (int j = 0; j < this->nu; j++)
        {
            //����Ԫ��
            if (t < this->tu && this->data[t].i == i && this->data[t].j == j)
            {
                cout << this->data[t++].e << " ";
            }
                //��Ԫ��
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
        ����ת���㷨����ͨ�棩
        �㷨ʵ�֣���ԭ�����б���һάϡ�����
        ע�������е�һάϡ�������������˳��洢����ת�ñ�Ϊ��������˳����ı����
        ���Ӷȣ�O(nu*tu)	������������Ԫ������ԭ����ͬһ�����������Ӷȣ�O(nu*nu*mu) ��
    */
    //0.��ʼ�� ת�þ��� MT ����
    SMatrix *MT = new SMatrix();
    MT->mu = this->nu;
    MT->nu = this->mu;
    MT->tu = this->tu;
    //1.��������ÿһ��
    int p = 0;	//���� MT���� ����Ԫ�ظ���
    for (int j = 0; j < this->nu; j++)
    {
        //2.����һάϡ�����Ѱ��ͬ�еķ���Ԫ��
        for (int q = 0; q < this->tu; q++)
        {
            if (this->data[q].j == j)
            {
                //ת�ø�ֵ
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
    ������ת���㷨�����ٰ棩
    �㷨��������ͨ�㷨�У���ÿ�α���һ���еķ�����Ԫʱ��ͬʱҲ�������˷ǵ�ǰ�е�����Ԫ��
            ���ڲ�֪���˷ǵ�ǰ�е�����ԪӦ����ת�ú��ʲôλ�ã�����ÿ�����������յ��¸��Ӷ����ߡ�
    �㷨ʵ�֣�
        ��������ȷ��ÿ���׸�����Ԫλ�ã���ÿ�к���Ԫ�ظ��ݵ�ǰ���׸�Ԫ��λ�����
        1.����ϡ������еķ���Ԫ����
        2.����ÿ�У�����һά���� col_position[]�� ���ÿ�з���Ԫλ��
            ��ʼ��Ϊÿ���׸�����Ԫλ�ã�����Ԫ��λ���𲽼�һ
            ��ʼ����ʽ��col_position[j] = col_num[j-1] + col_position[j-1], j Ϊ����
        3.����ϡ����󣬸��� col_position[]�����ת��ϡ�����
    ע�������е�һάϡ�������������˳��洢����ת�ñ�Ϊ��������˳����ı����
    ���Ӷȣ�O(tn+nu)
    ע��ת��ϡ��������һ�ֱ�����
            ��ԭ������������˳��洢������������˳���ȡ������ת�ú��ϡ�����
    */
    //0.��ʼ�� ת�þ��� MT ����
    SMatrix *MT = new SMatrix();
    MT->mu = this->nu;
    MT->nu = this->mu;
    MT->tu = this->tu;
    //1.ͳ��ÿ�з�������Ԫ����
    int *col_num = new int[this->nu]{ 0 };	//ÿ�з���Ԫ�������飬��ʼ��ÿ��Ԫ��Ϊ 0
    for (int i = 0; i < this->tu; i++)
    {
        col_num[data[i].j]++;
    }
    //2.��ʼ�� col_position[] Ϊÿ���׸�����Ԫ�ض�Ӧת��ϡ�������±�λ��
    int *col_position = new int[this->nu]{ 0 }; //ÿ������Ԫλ�����飬��ʼ��ÿ��Ԫ��Ϊ 0
    for (int i = 1; i < this->nu; i++)
    {
        col_position[i] = col_position[i-1] + col_num[i-1];
    }
    //3.ʵ��ת��
    int p = 0;	//ת�þ����±�
    for (int i = 0; i < this->tu; i++)
    {
        //��ȡϡ�����Ԫ�ض�Ӧ��ת��ϡ������±꣬������ǰ��Ԫ��λ���±��һ��Ϊ��һ������Ԫ��׼����
        p = col_position[this->data[i].j]++;
        //ת��Ԫ�ظ�ֵ
        MT->data[p].i = this->data[i].j;
        MT->data[p].j = this->data[i].i;
        MT->data[p].e = this->data[i].e;
    }
    return MT;
}

SMatrix *SMatrix::MultiMatrix(SMatrix *MB)
{
    /*
        ��������㷨�����ٰ棩�����þ������ת���㷨����
        �㷨����������ϡ���������������˳��洢�ģ������ھ���˷��У������ÿһ�����Ҿ���ÿһ����ˣ���
            ����� A ��ÿһ�з���Ԫ����ϡ��������ǰ�������˳�� �����洢�ģ�
            �Ҿ��� B ��ÿһ�з���Ԫ����ϡ��������ǰ�������˳�� �������洢�ġ�
            ��һ���㷢ʵ���ϣ���Ҫһ�¼����������裺
                1.���� A ÿ�еķ���Ԫ�� A_ij ������ �� ���� B ��Ӧ�� m �У�m == j����ÿ������Ԫ ��B_mn�� ���;
                2.���� A ÿ�е����з���Ԫ ���� ���� B ÿ����ˡ�����Ӻ󣬵õ�һ��ÿ�е��ۼ�����
                3.����ۼ����Ǿ��� һ �� Bn �� ��һά���顣
            ��������ʵ�ֲ��� 1 ʱ���Ծ��� B �İ��б�����ÿ�ζ������������ϡ����󣬸��ӶȺܸߣ�O(A.tu * B.tu)��
            ���Բ��ö� ���� B ����Ԫ�İ��б�ǣ����򻯲��� 1 ��ʵ�֡�
        �㷨ʵ�֣�
            1.ͳ�� B �����ÿ�з���Ԫ���������б����������������� row_num[]
            2.��� B ����ÿ���׸�����Ԫ����ϡ������е��±�λ�ã������ row_position[] ��
            3.ʵ�� A ����ÿ������Ԫ����Ϊ�������ȴ洢����ֻ�谴�������ϡ����� �� B �����ж�Ӧ�е����з���Ԫ��������ǣ���ʡ��ȫ�ֱ�����ʱ�䣩���
            4.������ 3 �Ľ������� �ۼ��� row_result[] �� �������� A ���У�
            5.ÿ������ A ����һ�з���Ԫ���㽫 �ۼ��� row_result[] �з����� ���ڷ��ض����ϡ������У�����ʼ�� �ۼ��� Ϊ0
        ���Ӷȣ�O( B.tu + B.mu + A.tu * B.tu / B.mu + A.mu * B.nu )
            ���У� B.tu / B.mu ��Ϊ��ȡ B ���� ÿ��ƽ������Ԫ ����
    */
    //�Ϸ���У��
    if (this->nu != MB->mu)
    {
        cout << "������������ˣ�" << endl;
        return NULL;
    }
    if (this->tu == 0 || MB->tu == 0)
    {
        cout << "���Ϊ����" << endl;
        return NULL;
    }

    //0.��ʼ���������
    SMatrix *MResult = new SMatrix();
    MResult->mu = this->mu;
    MResult->nu = MB->nu;
    MResult->tu = 0;

    //1.ͳ�� B ����ÿ�з���Ԫ����
    int *row_num = new int[MB->mu]{ 0 };	//ÿ�з���Ԫ�������飬��ʼ��Ϊ 0
    for (int i = 0; i < MB->tu; i++)
    {
        row_num[MB->data[i].i]++;
    }
    //2.��� B ����ÿ�з���Ԫ����ϡ������е��±�λ�ã���ʼ��Ϊÿ���׸�����Ԫλ��
    int *row_position = new int[MB->mu]{ 0 };	//ÿ���׸�����Ԫ����ϡ������е��±�λ������
    for (int i = 1; i < MB->mu; i++)
    {
        row_position[i] = row_position[i-1] + row_num[i-1];
    }
    //3.ʵ�־������
    //���� A �����һάϡ�����
    int EA = 0, EB = 0;	//��ʼ�� A��B ����Ԫ�� E Ϊ 0
    int IA = 0, IB = 0, JA = 0, JB = 0;	//��ʼ�� A��B ����Ԫ������Ϊ 0
    int NB = 0;	//��ʼ�� B ����ĳһ�еķ���Ԫ�ظ���
    int PB = 0;	//��ʼ�� B ����ϡ������±�λ��Ϊ 0
    int *row_result = new int[MB->nu]{ 0 };	//��ʱ��� A ����ÿһ�� �� B ����ÿһ�� Ԫ�س˻� �ۼӽ��
    for (int p = 0; p < this->tu; p++)
    {
        //��ȡ A ����Ԫ�� ��ia,ja,ea��
        IA = this->data[p].i;
        JA = this->data[p].j;
        EA = this->data[p].e;
        IB = JA;
        //��λ B ���� IB �еķ�������Ԫ�±�λ�ã���Ӧϡ������еģ�
        PB = row_position[IB];
        //��ȡ B ���� IB �еķ���Ԫ�ظ���
        NB = row_num[IB];
        //���� B ���� IB ���ϵķ�������Ԫ��ʵ�����
        for (int n = 0; n < NB; n++)
        {
            IB = MB->data[PB + n].i;
            JB = MB->data[PB + n].j;
            EB = MB->data[PB + n].e;
            row_result[JB] += EA * EB;
        }
        /*
            A ����һ�б�������ж���������2�������
                1.���һ������Ԫʱ��(p == this->tu - 1)
                2.�����һ������Ԫʱ��ȡ��һ������Ԫ���У��ж��Ƿ��뵱ǰ����Ԫͬһ�� (this->data[p + 1].i != IA)
            ��һ�еķ����ۼӽ����ֵ���������ϡ������У�����ʼ���ۼ��� Ϊ0
        */
        if (p == this->tu - 1 || this->data[p + 1].i != IA )	//���õ���Խ�磡
        {
            //��ȡ����ʼ�� �ۼ��� row_result[]
            for (int j = 0; j < MB->nu; j++)
            {
                //���ۼ�����Ϊ 0 �Ľ��������һάϡ�������
                if (row_result[j] != 0)
                {
                    MResult->data[MResult->tu].i = IA;
                    MResult->data[MResult->tu].j = j;
                    MResult->data[MResult->tu].e = row_result[j];
                    MResult->tu++;
                }
                //��ʼ�� �ۼ��� row_result[] Ϊ 0
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
    cout << "����1��" << endl;
    sm1->MDisplay();
    cout << "����2��" << endl;
    sm2->MDisplay();
    cout << "����1 ת�ý����" << endl;
    SMatrix *sm1_t = sm1->MatrixTrans_Fast();
    sm1_t->MDisplay();
    cout << "������˽����" << endl;
    SMatrix *multiResult = sm1->MultiMatrix(sm2);
    multiResult->MDisplay();
    return OK;
}