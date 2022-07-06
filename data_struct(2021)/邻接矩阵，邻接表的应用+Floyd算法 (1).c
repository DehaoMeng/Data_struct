#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
#define MAX_VERTEX_NUM 20    //��󶥵���� 
#define MAX_DISTANCE 99      //����һ�����������Ϊ��ʾ�����
#define MAX_LINE_NUM 5       //������·��
#define O MAX_VERTEX_NUM+1
typedef char ElemType;        //ͼ������������ 
typedef struct  Station_Info
{
	char Station_Name[20];
	int Station_Num;
}Station_Info;
typedef struct      TableNode                 //����ṹ
{
	int VER_j_Num;                           //�ڽӵ��򣬴����vi���ڽӵĶ���vj�����j
	char Station_Name[20];                    //����վ�������
	struct TableNode* next;                   //ָ���򣬽��ڽӱ�����б�������һ��
}TableNode;
//ͼ���������Ͷ���
typedef struct    HeadNode                            //ͷ���ṹ
{
	char Station_Name[20];
	int Station_Num;
	struct TableNode* head;                           //vi���ڽӱ��ͷָ��
}HeadNode;
typedef struct  MGraph
{
	struct HeadNode Line[MAX_LINE_NUM];             //��·����
}MGraph;
typedef struct Line_Info
{
	int Line_Num;
	float Line_Price;
	int Start_Time_hour;
	int Start_Time_minute;
	int End_Time_hour;
	int End_Time_minute;
}Line_Info;
Line_Info Line[MAX_LINE_NUM] =             //��·��Ϣ
{
	{1,2,6,30,22,30},
	{2,1.5,7,0,23,0},
	{3,2.5,6,30,22,30},
	{4,2,7,0,23,0},
	{5,1.5,6,30,22,30}
};
int VR[MAX_VERTEX_NUM][MAX_VERTEX_NUM] =
{//    0    1   2   3   4   5   6   7   8   9   10  11  12  13  14   15  16  17  18  19 
	{  0,  1, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},//0
	{  1,  0,  1, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},//1
	{ 99,  1,  0,  1, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},//2
	{ 99, 99,  1,  0,  1, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},//3
	{ 99, 99, 99,  1,  0,  2, 99, 99, 99, 99, 99, 99, 99, 99, 99,  4, 99,  2, 99, 99},//4
	{ 99, 99, 99, 99,  2,  0,  1, 99, 99, 99, 99, 99, 99, 99,  4, 99, 99, 99,  2, 99},//5
	{ 99, 99, 99, 99, 99,  1,  0,  2, 99, 99, 99, 99, 99,  2, 99, 99, 99, 99,  2, 99},//6
	{ 99, 99, 99, 99, 99, 99,  2,  0,  2, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},//7
	{ 99, 99, 99, 99, 99, 99, 99,  2,  0, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99},//8
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99,  0,  1, 99, 99, 99, 99, 99, 99, 99, 99, 99},//9
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99,  1,  0,  4, 99, 99,  2, 99, 99, 99, 99, 99},//10
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,  4,  0,  1,  2, 99, 99, 99, 99, 99, 99},//11
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,  1,  0, 99, 99, 99, 99, 99, 99, 99},//12
	{ 99, 99, 99, 99, 99, 99,  2, 99, 99, 99, 99,  2, 99,  0, 99, 99, 99, 99, 99, 99},//13
	{ 99, 99, 99, 99, 99,  4, 99, 99, 99, 99,  2, 99, 99, 99,  0,  3, 99, 99, 99, 99},//14
	{ 99, 99, 99, 99,  4, 99, 99, 99, 99, 99, 99, 99, 99, 99,  3,  0, 99, 99, 99, 99},//15
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,  0,  1, 99, 99},//16
	{ 99, 99, 99, 99,  2, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,  1,  0, 99, 99},//17
	{ 99, 99, 99, 99, 99,  2,  2, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,  0,  4},//18
	{ 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99,  4,  0},//19
};                                                                                   //��Ȩֵ��ά����
int Line_Num[MAX_LINE_NUM][MAX_VERTEX_NUM] =
{
	{0,1,2,3,4,5,6,7,8,O,O,O,O,O,O,O,O,O,O,O},           //0
	{16,17,4,15,14,10,9,O,O,O,O,O,O,O,O,O,O,O,O,O},      //1
	{9,10,11,12,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},        //2
	{11,13,6,18,19,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},       //3
	{10,14,5,18,19,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},       //4
};
Station_Info Station[MAX_VERTEX_NUM] =                                                   //վ����Ϣ����
{
	{"��ȹ㳡",0},
	{"�㲺��",1},
	{"�ֵ���",2},
	{"��ɽ�㳡",3},
	{"����·",4},
	{"����·",5},
	{"ѭ����",6},
	{"���ڻ�վ",7},
	{"���໨԰",8},
	{"�º���վ",9},
	{"������",10},
	{"�ڹ�",11},
	{"���Ҷ�",12},
	{"����·",13},
	{"�ӼҴ�",14},
	{"�����վ",15},
	{"�人��վ",16},
	{"�ʺ�·",17},
	{"����·",18},
	{"���ڱ����",19}
};
int Save_Infomation(void);
int Print_Line_Info(MGraph* G);
MGraph* CreatMGraph(MGraph* G);
void Dijkstra_Time(int start, int end);
int LocateVex(MGraph* G, int n);
/**************************************************************************************************
�������ƣ�Save_Infomation();
�������ܣ����ݵ㼯�͵��ϵ������һ��ͼ;
�����������㼯��ַ�����ϵ�����ַ��������n;
�������أ�ͼ�Ļ�ַ;
***************************************************************************************************/
int Save_Infomation(void)
{
	FILE* p1, * p2, * p3, * p4;
	int i, j;
	int* p_VR, * p_Line_Node;
	Station_Info* p_Station;
	Line_Info* p_Line_Info;
	if ((p1 = fopen("f:\\VR.txt", "wb")) == NULL)
		exit(-1);
	if ((p2 = fopen("f:\\Line_Node.txt", "wb")) == NULL)
		exit(-1);
	if ((p3 = fopen("f:\\Station.txt", "wb")) == NULL)
		exit(-1);
	if ((p4 = fopen("f:\\Line_Info.txt", "wb")) == NULL)
		exit(-1);
	for (i = 0; i < MAX_VERTEX_NUM; i++)
		for (j = 0; j < MAX_VERTEX_NUM; j++)
		{
			p_VR = &VR[i][j];
			fwrite(p_VR, sizeof(int), 1, p1);
		}
	for (i = 0; i < MAX_LINE_NUM; i++)
		for (j = 0; j < MAX_VERTEX_NUM; j++)
		{
			p_Line_Node = &Line_Num[i][j];
			fwrite(p_Line_Node, sizeof(int), 1, p2);
		}
	for (i = 0; i < MAX_VERTEX_NUM; i++)
	{
		p_Station = &Station[i];
		fwrite(p_Station, sizeof(Station_Info), 1, p3);
	}
	for (i = 0; i < MAX_LINE_NUM; i++)
	{
		p_Line_Info = &Line[i];
		fwrite(p_Line_Info, sizeof(Line_Info), 1, p4);
	}
	fclose(p1);
	fclose(p2);
	fclose(p3);
	fclose(p4);
	return OK;
}
/**************************************************************************************************
�������ƣ�Print_Line_Info(MGraph *G)��
�������ܣ���Ļ��ӡ��·��Ϣ��
�����������㼯��ַ��
�������أ����ɹ��򷵻�OK��
***************************************************************************************************/
int Print_Line_Info(MGraph* G)
{
	int i, n;
	TableNode* p;
	n = MAX_LINE_NUM;
	printf("\n");
	for (i = 0; i < n; i++)
	{
		printf("\n================================================================================");
		printf("%d���ߣ�", Line[i].Line_Num);
		printf("\tƱ�ۣ�%1.1fԪ\n\n", Line[i].Line_Price);
		printf("�װ೵ʱ�䣺%d��%d", Line[i].Start_Time_hour, Line[i].Start_Time_minute);
		printf("\tĩ�೵ʱ�䣺%d��%d\n\n", Line[i].End_Time_hour, Line[i].End_Time_minute);
		p = G->Line[i].head->next;
		while (p)
		{
			if (p->next)
				printf("%s->", p->Station_Name);
			else
				printf("%s", p->Station_Name);
			p = p->next;
		}
		printf("\n================================================================================\n");
		printf("\n");
	}
	return OK;
}
/**************************************************************************************************
�������ƣ�CreatMGraph(MGraph* G,int *VR,int n)��
�������ܣ����ݵ㼯�͵��ϵ������һ��ͼ��
�����������㼯��ַ�����ϵ�����ַ��������n��
�������أ�ͼ�Ļ�ַ��
***************************************************************************************************/
MGraph* CreatMGraph(MGraph* G)
{
	int i, j, n, m;
	TableNode* p, * rear;
	n = MAX_LINE_NUM;
	m = MAX_VERTEX_NUM;
	//����ͼģ��ʱ���ǰ�����·�������洢�ṹΪ�ڽ��б�ÿһ�������ʾһ����·��
	for (i = 0; i < n; i++)
	{
		rear = G->Line[i].head;
		for (j = 0; j < m; j++)
		{
			if (Line_Num[i][j] <= m)
			{
				p = (TableNode*)malloc(sizeof(TableNode));  //����һ���µĽ��
				p->VER_j_Num = Line_Num[i][j];
				strcpy(p->Station_Name, Station[Line_Num[i][j]].Station_Name);
				p->next = NULL;
				rear->next = p;                          //������β
				rear = p;
			}
		}
	}
	return G;
}
/****************************************************************************************************************************************
�������ƣ�Dijkstra_Time(int start,int end)��
�������ܣ���������ź��յ�����ͼ�м�����̾��룻
��������������ţ��յ��ţ�
�������أ���̾���ֵ��
����˵����Dijkstra�㷨˵�����£�
1)�㷨˼��:��G=(V,E)��һ����Ȩ����ͼ����ͼ�ж��㼯�� V �ֳ����飬��һ��Ϊ��������·���Ķ��㼯��
���� S ��ʾ����ʼʱ S ��ֻ��һ��Դ�㣬�Ժ�ÿ���һ�����·��,�ͽ����뵽���� S �У�ֱ��ȫ�����㶼���뵽 S �У��㷨�ͽ����ˣ���
�ڶ���Ϊ����δȷ�����·���Ķ��㼯�ϣ��� U ��ʾ��,�����·�����ȵĵ����������ΰѵڶ���Ķ������ S �С��ڼ���Ĺ����У�
�ܱ��ִ�Դ�� start �� S �и���������·�����Ȳ����ڴ�Դ�� start ��U���κζ�������·�����ȡ����⣬ÿ�������Ӧһ�����룬
S�еĶ���ľ�����Ǵ� start ���˶�������·�����ȣ�U �еĶ���ľ��룬�Ǵ� start ���˶���ֻ���� S �еĶ���Ϊ�м䶥��ĵ�ǰ���·�����ȡ�
2)�㷨���裺
a.��ʼʱ��S ֻ����Դ�㣬�� S��{start}��start �ľ���Ϊ0��U ������v����������㣬��:U ={���ඥ��}���� start �� U �ж��� u �бߣ�
��< u ,start >������Ȩֵ���� u ���� start �ĳ����ڽӵ㣬��< u ,start >ȨֵΪ�ޡ�
b.��U��ѡȡһ������ start ��С�Ķ��� k���� k ���� S �У���ѡ���ľ������ start �� k �����·�����ȣ���
c.�� k Ϊ�¿��ǵ��м�㣬�޸� U �и�����ľ��룻����Դ�� start ������ u �ľ��루�������� k����ԭ�����루���������� k���̣�
���޸Ķ��� u �ľ���ֵ���޸ĺ�ľ���ֵ�Ķ��� k �ľ�����ϱ��ϵ�Ȩ��
d.�ظ����� b �� c ֱ�����ж��㶼������ S �С�
****************************************************************************************************************************************/
void Dijkstra_Time(int start, int end)
{
	int S_Flag[MAX_VERTEX_NUM];           //�жϵ��Ƿ����S���ϵ�����
	int Distance[MAX_VERTEX_NUM];          //��������
	int Prior_Ver[MAX_VERTEX_NUM];         //ǰ����������
	int Out1[MAX_VERTEX_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };              //�����·ʱ������
	int Out2[MAX_VERTEX_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };              //�����·ʱ������
	int i, j, k, f, Min_Distance = MAX_DISTANCE, m, change;
	int* flag;                                                                //��̬����һ�����飬��¼һ�����Ƿ��Ѿ�ɨ��
	for (i = 0; i < MAX_VERTEX_NUM; i++)
	{
		S_Flag[i] = 0;                      //�տ�ʼ��û�н���S����
		Distance[i] = VR[start][i];          //���������д�����Ǵ���㵽�ĵ�ľ���
		if (Distance[i] == MAX_DISTANCE)
			Prior_Ver[i] = -1;
		else
			Prior_Ver[i] = start;
	}
	Distance[start] = 0;                       //��㵽����û�о���
	S_Flag[start] = 1;                         //����Ѿ���S����
	for (i = 1; i < MAX_VERTEX_NUM; i++)
	{
		k = start;
		Min_Distance = MAX_DISTANCE;            //ÿһ�ν���ѭ����Ҫ��ʼ����������ԶΪ��̾���
		for (j = 0; j < MAX_VERTEX_NUM; j++)
		{
			if ((!S_Flag[j]) && (Distance[j] < Min_Distance))
			{
				k = j;
				Min_Distance = Distance[j];
			}
		}
		S_Flag[k] = 1;
		for (j = 0; j < MAX_VERTEX_NUM; j++)
		{
			if ((!S_Flag[j]) && (VR[k][j] < MAX_DISTANCE))
			{
				if (Distance[k] + VR[k][j] < Distance[j])
				{
					Distance[j] = Distance[k] + VR[k][j];
					Prior_Ver[j] = k;
				}
			}
		}
	}
	i = end;
	j = 0;
	while (i != start)                      //��ǰ�������������е�����ת����out1���飻
	{
		Out1[j] = Prior_Ver[i] + 1;
		j++;
		i = Prior_Ver[i];
	}
	for (j = 0, m = 0; j < MAX_VERTEX_NUM; j++)
	{
		if (Out1[j])
			m++;
		else
			break;
	}
	for (i = 0; i < m; i++)                          //����out1���飬��ǰ������õ���˳��ʽ������out2���飻
		Out2[i] = Station[Out1[i] - 1].Station_Num;
	for (i = m - 1; i >= 0; i--)
		Out2[i + 1] = Out2[i];                    //�������Ž�����
	Out2[0] = Station[end].Station_Num;
	flag = (int*)malloc((sizeof(int)) * m);         //��̬���ٱ������
	for (i = 0; i < m; i++)                          //��ʼ��Ϊ0
		flag[i] = 0;
	printf("\n================================================================================\n");
	printf("��̾���Ϊ��\n\n%dǧ��\n", Distance[end]);
	printf("\n��̾���Ľ���·Ϊ��\n\n");
	for (j = m - 1; j >= 0; j--)
		printf("%d%s->", Station[Out1[j] - 1].Station_Num + 1, Station[Out1[j] - 1].Station_Name);
	printf("%d%s", Station[end].Station_Num + 1, Station[end].Station_Name);
	printf("\n\n");
	printf("���廻�˽������£�\n\n");
	change = 0;
	for (i = m, f = 0, change = m - 1; change > 0, i > 0; change--, i--, f++)
	{
		printf("%s", Station[Out1[change] - 1].Station_Name);
		printf("(");
		for (j = 0; j < MAX_LINE_NUM; j++)
			for (k = 0; k < MAX_VERTEX_NUM; k++)
				if (Out2[i] == Line_Num[j][k])
					if (Out2[i - 1] == Line_Num[j][k - 1] || Out2[i - 1] == Line_Num[j][k + 1])
					{

						if (!flag[f])
						{
							printf("��%d����", j + 1);                    //��һ��ѡ�񷽰�
							flag[f] = 1;                              //�û��Ѿ���ɨ��
						}
						else
							printf("���߳�%d����", j + 1);                 //ͬһ�����ж���ѡ��ʱ�����ӡ����

					}
		printf(")-->");
	}
	printf("%s\n", Station[end].Station_Name);
	printf("\n================================================================================\n");
}
/**************************************************************************************************
�������ƣ�LocateVex(MGraph *G,int i);
�������ܣ�����ͼ��ĳ����iλ����Ϣ
����������ͼ��ַ,������
�������أ�����ɹ��򷵻�OK��
***************************************************************************************************/
int LocateVex(MGraph* G, int n)
{
	TableNode* p = NULL, * q = NULL, * r = NULL, * start = NULL, * end_1 = NULL, * end_2 = NULL;
	int j = 0;
	printf("\n================================================================================\n");
	for (j = 0; j < MAX_LINE_NUM; j++)
	{
		p = G->Line[j].head->next;
		if (p->VER_j_Num == n)
		{
			q = p->next;
			printf("\n\t��%s���ǡ�%d���ߡ�����㣬��һվ�ǡ�%s����\n", p->Station_Name, j + 1, q->Station_Name);
			end_1 = q;
			end_2 = q;
			while (end_1)
			{
				end_2 = end_1;
				end_1 = end_1->next;
			}
			printf("\t��%d���ߡ����յ��ǡ�%s����\n", j + 1, end_2->Station_Name);
		}
		else
		{
			while (p)
			{
				q = p->next;
				if (q)
				{
					if (q->VER_j_Num == n)
					{
						printf("\n\t��%s���ڡ�%d���ߡ��ϣ���һվ�ǡ�%s����", q->Station_Name, j + 1, p->Station_Name);
						r = q->next;
						if (r)
						{
							printf("��һվ�ǡ�%s����\n", r->Station_Name);
							start = G->Line[j].head->next;
							printf("\t��%d���ߡ�������� ��%s����", j + 1, start->Station_Name);
							end_1 = r;
							end_2 = r;
							while (end_1)
							{
								end_2 = end_1;
								end_1 = end_1->next;
							}
							printf("�յ��ǡ�%s����\n", end_2->Station_Name);
						}
						else
						{
							printf("����Ϊ�յ㡣\n");
							start = G->Line[j].head->next;
							printf("\t��%d���ߡ�������� ��%s����\n", j + 1, start->Station_Name);
						}


					}
				}
				p = p->next;
			}
		}
	}
	printf("\n================================================================================\n");
	return OK;
}
/******************************************************************************************************
�������ƣ�main(void)��
�������ܣ����빫�����ɲ�ѯϵͳ��
�����������ޣ�
�������أ��ޣ�
*******************************************************************************************************/
void main()
{
	MGraph G;
	int select = 0, n = 0, i = 0, end = 0, start = 0;
	char c = 'y';
	for (i = 0; i < MAX_LINE_NUM; i++)
	{
		G.Line[i].head = (TableNode*)malloc(sizeof(TableNode));
		G.Line[i].head->next = NULL;
	}
	CreatMGraph(&G);
	while (c == 'y' || c == 'Y')
	{
		printf("\n================================================================================");
		printf("\n\t\t\t   ��ӭʹ�ù���·�߲�ѯϵͳ\n");
		printf("\n\t\t\t       1�� ��ʾ��·��Ϣ\n");
		printf("\n\t\t\t       2�� ��ѯվ��λ��\n");
		printf("\n\t\t\t       3�� ����·�߲�ѯ\n");
		printf("\n\t\t\t       4�� ����ϵͳ����\n");
		printf("\n================================================================================\n\n\n\t\t");
		printf("\t\t����������ѡ��");
		scanf("%d", &select);
		switch (select)
		{
		case 2:
			system("cls");
			printf("\n================================================================================\n");
			printf("\t\t\t��վ���Ӧ������£�\n");
			for (i = 0; i < MAX_VERTEX_NUM; i++)
			{
				if (i % 2 == 0)
					printf("\n");
				printf("\t%d  %s \t\t", Station[i].Station_Num + 1, Station[i].Station_Name);
			}
			printf("\n");
			printf("\n================================================================================\n");
			printf("\n\t\t��������Ҫ��ѯλ�õ�վ���ţ�\n\n\t\tn=");
			scanf("%d", &n);
			system("cls");
			LocateVex(&G, n - 1);
			break;
		case 1:
			system("cls");
			printf("\n\n\t\t\t    ��·��Ϣ������ʾ��\n");
			Print_Line_Info(&G);
			printf("\n");
			break;
		case 3:
			system("cls");
			printf("\n================================================================================\n");
			printf("\t\t\t��վ���Ӧ������£�\n");
			for (i = 0; i < MAX_VERTEX_NUM; i++)
			{
				if (i % 2 == 0)
					printf("\n");
				printf("\t%d  %s \t\t", Station[i].Station_Num + 1, Station[i].Station_Name);
			}
			printf("\n");
			printf("\n================================================================================\n");
			printf("\n\t\t����������ţ�\n\t\tStart_Num=");
			scanf("%d", &start);
			printf("\n\t\t�������յ��ţ�\n\t\tEnd_Num=");
			scanf("%d", &end);
			system("cls");
			Dijkstra_Time(start - 1, end - 1);
			printf("\n");
			break;
		case 4:
			system("cls");
			printf("\n================================================================================");
			i = Save_Infomation();
			if (i)
				printf("\n\n\t\t��Ϣ���̳ɹ���\n");
			printf("\n");
			printf("\n================================================================================\n");
			break;
		default:
			printf("\n");
			printf("\n\t\t����ѡ�����\n");
		}
		printf("\n\t\t�Ƿ����ʹ��ϵͳ��ѡ�� y ���� n:\n\t\t");
		scanf("%1s", &c);
		system("cls");
	}
}


