#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define FALSE 0
#define TRUE 1
#define MAX_VERTEX_NUM 20    //最大顶点个数 
#define MAX_DISTANCE 99      //定义一个最大距离抽象为表示无穷大
#define MAX_LINE_NUM 5       //定义线路数
#define O MAX_VERTEX_NUM+1
typedef char ElemType;        //图顶点数据类型 
typedef struct  Station_Info
{
	char Station_Name[20];
	int Station_Num;
}Station_Info;
typedef struct      TableNode                 //表结点结构
{
	int VER_j_Num;                           //邻接点域，存放与vi相邻接的顶点vj的序号j
	char Station_Name[20];                    //抽象站点的名字
	struct TableNode* next;                   //指针域，将邻接表的所有表结点链在一起
}TableNode;
//图的数据类型定义
typedef struct    HeadNode                            //头结点结构
{
	char Station_Name[20];
	int Station_Num;
	struct TableNode* head;                           //vi的邻接表的头指针
}HeadNode;
typedef struct  MGraph
{
	struct HeadNode Line[MAX_LINE_NUM];             //线路数组
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
Line_Info Line[MAX_LINE_NUM] =             //线路信息
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
};                                                                                   //弧权值二维数组
int Line_Num[MAX_LINE_NUM][MAX_VERTEX_NUM] =
{
	{0,1,2,3,4,5,6,7,8,O,O,O,O,O,O,O,O,O,O,O},           //0
	{16,17,4,15,14,10,9,O,O,O,O,O,O,O,O,O,O,O,O,O},      //1
	{9,10,11,12,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},        //2
	{11,13,6,18,19,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},       //3
	{10,14,5,18,19,O,O,O,O,O,O,O,O,O,O,O,O,O,O,O},       //4
};
Station_Info Station[MAX_VERTEX_NUM] =                                                   //站点信息数组
{
	{"光谷广场",0},
	{"广埠屯",1},
	{"街道口",2},
	{"洪山广场",3},
	{"中南路",4},
	{"江汉路",5},
	{"循礼门",6},
	{"汉口火车站",7},
	{"常青花园",8},
	{"新汉阳站",9},
	{"王家湾",10},
	{"宗关",11},
	{"王家墩",12},
	{"崇仁路",13},
	{"钟家村",14},
	{"武昌火车站",15},
	{"武汉火车站",16},
	{"仁和路",17},
	{"大智路",18},
	{"汉口北大道",19}
};
int Save_Infomation(void);
int Print_Line_Info(MGraph* G);
MGraph* CreatMGraph(MGraph* G);
void Dijkstra_Time(int start, int end);
int LocateVex(MGraph* G, int n);
/**************************************************************************************************
函数名称：Save_Infomation();
函数功能：根据点集和点关系集创建一个图;
函数参数：点集基址，点关系矩阵基址，定点数n;
函数返回：图的基址;
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
函数名称：Print_Line_Info(MGraph *G)；
函数功能：屏幕打印线路信息；
函数参数：点集基址；
函数返回：若成功则返回OK；
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
		printf("%d号线：", Line[i].Line_Num);
		printf("\t票价：%1.1f元\n\n", Line[i].Line_Price);
		printf("首班车时间：%d：%d", Line[i].Start_Time_hour, Line[i].Start_Time_minute);
		printf("\t末班车时间：%d：%d\n\n", Line[i].End_Time_hour, Line[i].End_Time_minute);
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
函数名称：CreatMGraph(MGraph* G,int *VR,int n)；
函数功能：根据点集和点关系集创建一个图；
函数参数：点集基址，点关系矩阵基址，定点数n；
函数返回：图的基址；
***************************************************************************************************/
MGraph* CreatMGraph(MGraph* G)
{
	int i, j, n, m;
	TableNode* p, * rear;
	n = MAX_LINE_NUM;
	m = MAX_VERTEX_NUM;
	//建立图模型时，是按照线路建立，存储结构为邻接列表；每一条链表表示一条线路；
	for (i = 0; i < n; i++)
	{
		rear = G->Line[i].head;
		for (j = 0; j < m; j++)
		{
			if (Line_Num[i][j] <= m)
			{
				p = (TableNode*)malloc(sizeof(TableNode));  //创建一个新的结点
				p->VER_j_Num = Line_Num[i][j];
				strcpy(p->Station_Name, Station[Line_Num[i][j]].Station_Name);
				p->next = NULL;
				rear->next = p;                          //插入链尾
				rear = p;
			}
		}
	}
	return G;
}
/****************************************************************************************************************************************
函数名称：Dijkstra_Time(int start,int end)；
函数功能：根据起点编号和终点编号在图中计算最短距离；
函数参数：起点编号，终点编号；
函数返回：最短距离值；
函数说明：Dijkstra算法说明如下：
1)算法思想:设G=(V,E)是一个带权有向图，把图中顶点集合 V 分成两组，第一组为已求出最短路径的顶点集合
（用 S 表示，初始时 S 中只有一个源点，以后每求得一条最短路径,就将加入到集合 S 中，直到全部顶点都加入到 S 中，算法就结束了），
第二组为其余未确定最短路径的顶点集合（用 U 表示）,按最短路径长度的递增次序依次把第二组的顶点加入 S 中。在加入的过程中，
总保持从源点 start 到 S 中各顶点的最短路径长度不大于从源点 start 到U中任何顶点的最短路径长度。此外，每个顶点对应一个距离，
S中的顶点的距离就是从 start 到此顶点的最短路径长度，U 中的顶点的距离，是从 start 到此顶点只包括 S 中的顶点为中间顶点的当前最短路径长度。
2)算法步骤：
a.初始时，S 只包含源点，即 S＝{start}，start 的距离为0。U 包含除v外的其他顶点，即:U ={其余顶点}，若 start 与 U 中顶点 u 有边，
则< u ,start >正常有权值，若 u 不是 start 的出边邻接点，则< u ,start >权值为∞。
b.从U中选取一个距离 start 最小的顶点 k，把 k 加入 S 中（该选定的距离就是 start 到 k 的最短路径长度）。
c.以 k 为新考虑的中间点，修改 U 中各顶点的距离；若从源点 start 到顶点 u 的距离（经过顶点 k）比原来距离（不经过顶点 k）短，
则修改顶点 u 的距离值，修改后的距离值的顶点 k 的距离加上边上的权。
d.重复步骤 b 和 c 直到所有顶点都包含在 S 中。
****************************************************************************************************************************************/
void Dijkstra_Time(int start, int end)
{
	int S_Flag[MAX_VERTEX_NUM];           //判断点是否进入S集合的数组
	int Distance[MAX_VERTEX_NUM];          //距离数组
	int Prior_Ver[MAX_VERTEX_NUM];         //前驱点编号数组
	int Out1[MAX_VERTEX_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };              //输出线路时的数组
	int Out2[MAX_VERTEX_NUM] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };              //输出线路时的数组
	int i, j, k, f, Min_Distance = MAX_DISTANCE, m, change;
	int* flag;                                                                //动态分配一个数组，记录一条弧是否已经扫描
	for (i = 0; i < MAX_VERTEX_NUM; i++)
	{
		S_Flag[i] = 0;                      //刚开始都没有进入S集合
		Distance[i] = VR[start][i];          //距离数组中储存的是从起点到改点的距离
		if (Distance[i] == MAX_DISTANCE)
			Prior_Ver[i] = -1;
		else
			Prior_Ver[i] = start;
	}
	Distance[start] = 0;                       //起点到自身没有距离
	S_Flag[start] = 1;                         //起点已经入S集合
	for (i = 1; i < MAX_VERTEX_NUM; i++)
	{
		k = start;
		Min_Distance = MAX_DISTANCE;            //每一次进入循环均要初始化抽象无穷远为最短距离
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
	while (i != start)                      //将前驱顶点编号数组中的数据转移至out1数组；
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
	for (i = 0; i < m; i++)                          //利用out1数组，将前驱编号用倒置顺序方式翻译至out2数组；
		Out2[i] = Station[Out1[i] - 1].Station_Num;
	for (i = m - 1; i >= 0; i--)
		Out2[i + 1] = Out2[i];                    //添加起点编号进数组
	Out2[0] = Station[end].Station_Num;
	flag = (int*)malloc((sizeof(int)) * m);         //动态开辟标记数组
	for (i = 0; i < m; i++)                          //初始化为0
		flag[i] = 0;
	printf("\n================================================================================\n");
	printf("最短距离为：\n\n%d千米\n", Distance[end]);
	printf("\n最短距离的近线路为：\n\n");
	for (j = m - 1; j >= 0; j--)
		printf("%d%s->", Station[Out1[j] - 1].Station_Num + 1, Station[Out1[j] - 1].Station_Name);
	printf("%d%s", Station[end].Station_Num + 1, Station[end].Station_Name);
	printf("\n\n");
	printf("具体换乘建议如下：\n\n");
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
							printf("乘%d号线", j + 1);                    //第一条选择方案
							flag[f] = 1;                              //该弧已经被扫描
						}
						else
							printf("或者乘%d号线", j + 1);                 //同一条弧有多种选择时，则打印“或”

					}
		printf(")-->");
	}
	printf("%s\n", Station[end].Station_Name);
	printf("\n================================================================================\n");
}
/**************************************************************************************************
函数名称：LocateVex(MGraph *G,int i);
函数功能：返回图中某顶点i位置信息
函数参数：图基址,顶点编号
函数返回：如果成功则返回OK；
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
			printf("\n\t“%s”是“%d号线”的起点，下一站是“%s”。\n", p->Station_Name, j + 1, q->Station_Name);
			end_1 = q;
			end_2 = q;
			while (end_1)
			{
				end_2 = end_1;
				end_1 = end_1->next;
			}
			printf("\t“%d号线”的终点是“%s”。\n", j + 1, end_2->Station_Name);
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
						printf("\n\t“%s”在“%d号线”上，上一站是“%s”，", q->Station_Name, j + 1, p->Station_Name);
						r = q->next;
						if (r)
						{
							printf("下一站是“%s”。\n", r->Station_Name);
							start = G->Line[j].head->next;
							printf("\t“%d号线”的起点是 “%s”，", j + 1, start->Station_Name);
							end_1 = r;
							end_2 = r;
							while (end_1)
							{
								end_2 = end_1;
								end_1 = end_1->next;
							}
							printf("终点是“%s”。\n", end_2->Station_Name);
						}
						else
						{
							printf("并且为终点。\n");
							start = G->Line[j].head->next;
							printf("\t“%d号线”的起点是 “%s”。\n", j + 1, start->Station_Name);
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
函数名称：main(void)；
函数功能：进入公交吸纳查询系统；
函数参数：无；
函数返回：无；
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
		printf("\n\t\t\t   欢迎使用公交路线查询系统\n");
		printf("\n\t\t\t       1： 显示线路信息\n");
		printf("\n\t\t\t       2： 查询站点位置\n");
		printf("\n\t\t\t       3： 最优路线查询\n");
		printf("\n\t\t\t       4： 保存系统数据\n");
		printf("\n================================================================================\n\n\n\t\t");
		printf("\t\t请输入您的选择：");
		scanf("%d", &select);
		switch (select)
		{
		case 2:
			system("cls");
			printf("\n================================================================================\n");
			printf("\t\t\t各站点对应编号如下：\n");
			for (i = 0; i < MAX_VERTEX_NUM; i++)
			{
				if (i % 2 == 0)
					printf("\n");
				printf("\t%d  %s \t\t", Station[i].Station_Num + 1, Station[i].Station_Name);
			}
			printf("\n");
			printf("\n================================================================================\n");
			printf("\n\t\t请输入你要查询位置的站点编号：\n\n\t\tn=");
			scanf("%d", &n);
			system("cls");
			LocateVex(&G, n - 1);
			break;
		case 1:
			system("cls");
			printf("\n\n\t\t\t    线路信息如下所示：\n");
			Print_Line_Info(&G);
			printf("\n");
			break;
		case 3:
			system("cls");
			printf("\n================================================================================\n");
			printf("\t\t\t各站点对应编号如下：\n");
			for (i = 0; i < MAX_VERTEX_NUM; i++)
			{
				if (i % 2 == 0)
					printf("\n");
				printf("\t%d  %s \t\t", Station[i].Station_Num + 1, Station[i].Station_Name);
			}
			printf("\n");
			printf("\n================================================================================\n");
			printf("\n\t\t请输入起点编号：\n\t\tStart_Num=");
			scanf("%d", &start);
			printf("\n\t\t请输入终点编号；\n\t\tEnd_Num=");
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
				printf("\n\n\t\t信息存盘成功！\n");
			printf("\n");
			printf("\n================================================================================\n");
			break;
		default:
			printf("\n");
			printf("\n\t\t输入选择出错！\n");
		}
		printf("\n\t\t是否继续使用系统？选择 y 或者 n:\n\t\t");
		scanf("%1s", &c);
		system("cls");
	}
}


