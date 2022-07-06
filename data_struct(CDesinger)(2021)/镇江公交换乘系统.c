#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define INFINITY      999999999999     /*无穷大*/ 
#define MAX 40
int STATION_NUM;             //站点总数
struct station                   //途径站点信息
{
    char c[20];                  //站点名称
};

typedef struct bus                    //公交车信息
{
    char num[20];                //公交车编号
    int n;                       //站台数目
    struct station name[12];     //站台名称
    char topen[20];              //起始时间
    char tclose[20];             //终止时间
    int money;                   //票价
}BUS;
BUS  bus[MAX];
typedef struct
{
	int name;  	//站点名称 
	int lines[6]; 	//途径路线 
}Vertex;
typedef struct
{
	Vertex vexs[MAX];  	//站点 
	int arc[MAX][MAX]; 	//邻接矩阵 
	int numVertexes, numEdges; 	//顶点数和边数 
}MGraph;
int Distance[100][100];
//声明：
void init();  void save();int host_menu(); int administrator_menu();int visitor_menu(); 
int query_menu();void modbus_menu(); void modstation_menu(); char Test(char a, char b, char c);void add();void view(); void mod(); 
void delete(); void findnum();void administrator(); void menu();void visitor();void floyd();void searchnavi();int show();void show_travel();
/* 构造图 */
void CreateMGraph(MGraph* G)
{
	int i, j;

	//请输入边数和顶点数
	G->numEdges = 52;
	G->numVertexes = 26;

	for (i = 0; i < G->numVertexes; i++)
	{
		G->vexs[i].name = i;
	}

	for (i = 0; i < 26; i++)//初始化每个站点通过路线的数组，设为零 
	{
		for (j = 0; j < 6; j++)
		{
			G->vexs[i].lines[j] = 0;
		}
	}

	G->vexs[1].lines[1] = 1;
	G->vexs[2].lines[1] = 1; G->vexs[2].lines[2] = 2;
	G->vexs[3].lines[1] = 1;
	G->vexs[4].lines[1] = 1;
	G->vexs[5].lines[2] = 2;
	G->vexs[6].lines[1] = 1;
	G->vexs[7].lines[2] = 2;
	G->vexs[8].lines[1] = 1; G->vexs[8].lines[2] = 2;
	G->vexs[9].lines[1] = 1; G->vexs[9].lines[2] = 2; G->vexs[9].lines[3] = 3;
	G->vexs[10].lines[3] = 3;
	G->vexs[11].lines[1] = 1;
	G->vexs[12].lines[3] = 3;
	G->vexs[13].lines[2] = 2; G->vexs[13].lines[5] = 5;
	G->vexs[14].lines[1] = 1;
	G->vexs[15].lines[3] = 3;
	G->vexs[16].lines[5] = 5;
	G->vexs[17].lines[2] = 2;
	G->vexs[18].lines[4] = 4;
	G->vexs[19].lines[3] = 3; G->vexs[19].lines[4] = 4;
	G->vexs[20].lines[5] = 5;
	G->vexs[21].lines[5] = 5;
	G->vexs[22].lines[3] = 3;
	G->vexs[23].lines[4] = 4;
	G->vexs[24].lines[4] = 4;
	G->vexs[25].lines[4] = 4; G->vexs[25].lines[5] = 5;

	int t[MAX][MAX] = { 0 }; //构造无向带权图的邻接矩阵 
	t[1][2] = t[2][1] = 2;
	t[2][3] = t[3][2] = 3;
	t[2][5] = t[5][2] = 7;
	t[3][4] = t[4][3] = 5;
	t[4][6] = t[6][4] = 9;
	t[5][7] = t[7][5] = 7;
	t[6][9] = t[9][6] = 2;
	t[7][8] = t[8][7] = 4;
	t[8][9] = t[9][8] = 6;
	t[8][11] = t[11][8] = 2;
	t[9][10] = t[10][9] = 5;
	t[9][12] = t[12][9] = 7;
	t[11][14] = t[14][11] = 8;
	t[12][15] = t[15][12] = 8;
	t[13][9] = t[9][13] = 2;
	t[13][16] = t[16][13] = 3;
	t[13][17] = t[17][13] = 3;
	t[15][19] = t[19][15] = 6;
	t[16][20] = t[20][16] = 7;
	t[18][19] = t[19][18] = 1;
	t[19][22] = t[22][19] = 4;
	t[19][23] = t[23][19] = 5;
	t[20][21] = t[21][20] = 1;
	t[21][25] = t[25][21] = 3;
	t[23][24] = t[24][23] = 1;
	t[24][25] = t[25][24] = 7;//?

	for (i = 0; i < G->numVertexes; i++)//* 初始化图 
	{
		for (j = 0; j < G->numVertexes; j++)
		{
			if (i == j)
				G->arc[i][j] = 0;
			else
				G->arc[i][j] = G->arc[j][i] = INFINITY;
		}
	}

	for (i = 0; i < G->numVertexes; i++)//* 复制邻接矩阵 
	{
		for (j = 0; j < G->numVertexes; j++)
		{
			if (t[i][j] != 0)
			{
				G->arc[i][j] = t[i][j];
			}
		}
	}
}
//初始化
void init()     //初始化函数       
{
    FILE* fp;                        //文件指针
    int i;
    if ((fp = fopen("bus.txt", "r+")) == NULL)                  //初次尝试打开"bus.txt"文本文件
    {
        printf("\n\t\t文件打开失败\n\n\t\t正在尝试创建新文件...\n");
        fp = fopen("bus.txt", "w");                          //创建"bus.txt"文本文件
        if ((fp = fopen("bus.txt", "r+")) == NULL)              //再次判断是否打开成功
        {
            printf("\t\t文件创建失败!!!\n");
            return;
        }
    }
    fp = fopen("bus.txt", "r+");
    for (i = 0; i < MAX; i++)                                          //将磁盘中的信息输出到内存中
        if (fread(&bus[i], sizeof(struct bus), 1, fp) != 1)
            break;
    fclose(fp);
    printf("\n\t\t初始化完成!!!\n\n");
    return;
}
//将删改后的信息写入文档
void save()         //信息保存函数 
{
    FILE* fp = NULL;
    int i;
    if ((fp = fopen("bus.txt", "w+")) == NULL)            //以读写的方式打开名称为"bus"的文本文件
    {
        printf("文件打开错误!!!\n");
        return;
    }
    fp = fopen("bus.txt", "w+");
    for (i = 0; *bus[i].num != '\0' && i < MAX; i++)                   //将内存中的数据输出到磁盘中
        if (fwrite(&bus[i], sizeof(struct bus), 1, fp) != 1)
            break;
    printf("\n\t保存成功!!!\n");
    fclose(fp);
    return;
}
//主菜单（1级菜单）
int host_menu() 
{
	printf("\n");
    printf("                               主菜单                                 \n");
    printf("**********************************************************************\n");
    printf("                            1.管理员系统                              \n");
    printf("                            2.乘客系统                                \n");
    printf("                            3.退出                                    \n");
    printf("**********************************************************************\n");
    printf("输入选择操作的序号:");
}
//管理员菜单
int administrator_menu()
{
	printf("\n");
    printf("                               管理员菜单                             \n");
    printf("**********************************************************************\n");
	printf("                            1.修改公交线路                            \n");
    printf("                            2.查询路线                                    \n");
    printf("                            3.返回主菜单                              \n");
    printf("**********************************************************************\n");
    printf("输入选择操作的序号:");
}
//游客菜单
int visitor_menu()
{
	printf("\n");
    printf("                               游客菜单                               \n");
    printf("**********************************************************************\n");
    printf("                            1.查询                                    \n");
    printf("                            2.返回主菜单                              \n");
    printf("**********************************************************************\n");
    printf("输入选择操作的序号:");
}
//路线查询菜单
int query_menu()
{
	printf("\n");
    printf("                               查询菜单                               \n");
    printf("**********************************************************************\n");
	printf("                            1.查询所有公交路线                        \n");
    printf("                            2.查询某条公交路线                        \n");
    printf("                            3.换乘查询                                \n");
    printf("                            4.旅游路线规划                            \n");
    printf("                            5.返回上一层菜单                          \n");
    printf("**********************************************************************\n");
    printf("输入选择操作的序号:");
}
//查询
void query(int n) {
	char a;
	while (1)
	{
		//system("cls");
		query_menu();
		a = Test(getchar(), '1', '5');      //菜单检测输入函数 
		switch (a)
		{
		case '1':	system("cls"); view(); break;
		case '2':	system("cls"); findnum(); break;
		case '3':   system("cls"); show(); searchnavi(); break;
		case '4':   system("cls"); show_travel(); searchnavi(); break;
		case '5':   system("cls"); 
			if (n == 1)
				administrator();
			else
				visitor();
			break;
		}
	}
	return 0;
}
//修改公交信息菜单
void modbus_menu()  //修改菜单
{
	printf("\n\t\t                 修改菜单                   ");
	printf("\n\t\t********************************************");
	printf("\n\t\t*            1、修改原有路线                *");
	printf("\n\t\t*            2、新增路线                   *");
	printf("\n\t\t*            3、删除原有路线               *");
	printf("\n\t\t*            4、返回到管理员菜单           *");
	printf("\n\t\t********************************************");
	printf("\n\n\t\t请输入您的选择:");
}
//修改具体路线菜单
void modload_menu() {
	printf("\n\t\t             修改具体路线菜单               ");
	printf("\n\t\t********************************************");
	printf("\n\t\t*            1、修改路线编号               *");
	printf("\n\t\t*            2、修改车辆票价               *");
	printf("\n\t\t*            3、修改行车路线               *");
	printf("\n\t\t*            4、修改行车时间               *");
	printf("\n\t\t*            5、返回上一层菜单             *");
	printf("\n\n\t\t请输入您的选择:");
}
//修改具体路线菜单
void modstation_menu() //路线修改菜单
{
	printf("\n\t\t               路线修改菜单                 ");
	printf("\n\t\t********************************************");
	printf("\n\t\t*            1、 站 点 添 加               *");
	printf("\n\t\t*            2、 站 点 修 改               *");
	printf("\n\t\t*            3、 站 点 删 除               *");
	printf("\n\t\t*            4、 路 线 重 置               *");
	printf("\n\t\t*            5、 返 回 菜 单               *");
	printf("\n\t\t********************************************");
	printf("\n\n\t\t请输入您的选择:");
}
//检测输入是否正确的函数
char Test(char a, char b, char c)
{
	while (a<b || a>c)
	{
		printf("\n\t\t\t输入错误，请重新输入: ");
		fflush(stdin);                           //清除键盘缓冲区
		a = getchar();
	}
	return a;
}	
//添加新的路线
void add()           
{
    FILE* fp = NULL;                        //文件指针
    int i, j;
    char cc[20];
    for (i = 0; i < MAX; i++)
    {
        if (*bus[i].num != '\0')
            continue;
        else
        {
            printf("\n添加第%d辆公交车路线记录:\n", i + 1);
            printf("\n请输入路线编码:\n");    //路线编码
            scanf("%s", cc);
            for (j = 0; j < MAX; j++)                                                           //检验是否重复
                if (strcmp(bus[j].num, cc) == 0)
                {
                    printf("\n与已有路线编码重复，按回车键返回!!!\n");
                    fflush(stdin);                           //清除键盘缓冲区
                    getchar();
                    //system("cls");
                    return;
                }
            strcpy(bus[i].num, cc);
            printf("\n请输入途径站台总数(>=2): ");                                     //站台总数
            scanf("%d", &bus[i].n);
            printf("\n");
            if (bus[i].n < 2 || bus[i].n>12)
            {
                while (bus[i].n < 2 || bus[i].n>12)
                {
                    printf("\n站台总数应满足(2<=n<=25)，请重新输入: ");
                    scanf("%d", &bus[i].n);
                    printf("\n");
                }
            }
            for (j = 0; j < bus[i].n; j++)
            {
                printf("请输入第%d个站台名称 ", j + 1);                    //站台名称
                scanf("%s", bus[i].name[j].c);
            }
            printf("\n自动生成公交路线:(1) %s", bus[i].name[0].c);
            for (j = 1; j < bus[i].n; j++)
            {
                printf(" ----> (%d) %s", j + 1, bus[i].name[j].c);
            }
            printf("\n\n请输入公交车的起始时间: ");       //起始时间
            scanf("%s", bus[i].topen);
            printf("请输入公交车的终止时间: ");           //终止时间
            scanf("%s", bus[i].tclose);
            printf("\n请输入公交车的票价: ");                            //票价
            scanf("%d", &bus[i].money);
            printf("\n第%d辆公交车路线记录创建成功!!!\n", i + 1);
            save();
            printf("\n\t按回车键返回!!!\n");
            fflush(stdin);                           //清除键盘缓冲区
            getchar();
            //system("cls");
            return;
        }
    }
    if (i == MAX)
        printf("\n\n\n\t空间已满，不能录入!!!\n");
    printf("\n\t按回车键返回!!!\n");
    fflush(stdin);                           //清除键盘缓冲区
    getchar();
    //system("cls");
    return;
}
//显示所有公交信息
void view()        
{
    int i, j, min;
	show();
    printf("\n\n                              公交车信息库");
    printf("\n********************************************************************************\n");
    for (i = 0; *bus[i].num != '\0' && i < MAX; i++)
    {
        printf("\t路线编号: %-6s\t单程票价: %d 元\n", bus[i].num, bus[i].money);
        printf("\t起始时间: %-6s\t终止时间: %-6s\t站台总数: %d\n", bus[i].topen, bus[i].tclose, bus[i].n);
        printf("\t公交路线:(1) %s", bus[i].name[0].c);
        for (j = 1; j < bus[i].n; j++)
            printf(" ---->(%d) %s", j + 1, bus[i].name[j].c);
        printf("\n\n");
    }
    printf("\n********************************************************************************\n");
    printf("\n\t\t公交车信息显示完毕!!!\n");
    printf("\n\t\t输入回车键返回主菜单:");
    fflush(stdin);                           //清除键盘缓冲区
    getchar();
    //system("cls");
    return;
}
//修改公交信息函数
void mod()                         
{
	int i, j, m = 0;
	char t, cc[20], mod[20];
	
	printf("请输入要修改信息的公交车路线编号:\n");
	scanf("%s", cc);
	for (i = 0; *bus[i].num != '\0' && i < MAX; i++)     //查找所输入的公交车
	{
		if (strcmp(bus[i].num, cc) == 0)
		{
			m = 1;
			printf("\n\n\t\t已找到!!!\n");
			while (1)
			{
				system("cls");
				printf("\n\n                            正在修改的公交车信息\n");
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
				printf("\t路线编号: %-6s\t单程票价: %d 元\n", bus[i].num, bus[i].money);
				printf("\t起始时间: %-6s\t终止时间: %-6s\t站台总数: %d\n", bus[i].topen, bus[i].tclose, bus[i].n);
				printf("\t公交路线:(1) %s", bus[i].name[0].c);
				for (j = 1; j < bus[i].n; j++)
					printf(" ---->(%d) %s", j + 1, bus[i].name[j].c);
				printf("\n\n");
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
				modload_menu();
				fflush(stdin);                           //清除键盘缓冲区
				t = Test(getchar(), '1', '5');      //菜单检测输入函数 
				//system("cls");
				switch (t)
				{
				case '1':           //修改路线编号
				{
					int k;
					printf("\n请输入新的公交车编号:");
					scanf("%s", mod);
					for (k = 0; *bus[k].num != '\0' && k < MAX; k++)
					{
						if (strcmp(bus[k].num, mod) == 0)
						{
							printf("与已有编号重复,按回车键返回主菜单\n");
							fflush(stdin);                           //清除键盘缓冲区
							getchar();
							//system("cls");
							return;
						}
					}
					strcpy(bus[i].num, mod);
					save();
					break;
				}
				case '2':           //修改车辆信息
				{
					printf("\n请输入新的公交车票价:");
					scanf("%d", &bus[i].money);
					save();
					break;
				}
				case '3':           //修改行车路线
				{
					void modstation_menu(); //路线修改菜单
					int k;
					char z;
					while (1)
					{
						//system("cls");
						modstation_menu();
						fflush(stdin);                           //清除键盘缓冲区
						z = Test(getchar(), '1', '6');      //菜单检测输入函数 
						//system("cls");
						switch (z)
						{
						case '1':     //添加站点
						{
							if (bus[i].n + 1 > 12)             //判断是否满足条件
							{
								printf("\n站台总数达到25个，无法添加新站点\n\n按回车键返回\n");
								fflush(stdin);                           //清除键盘缓冲区
								getchar();
								system("cls");
								return;
							}
							printf("\n请输入需要添加第几个站点：");
							scanf("%d", &k);
							while (bus[i].n + 1 < k)
							{
								printf("目前共%d个站点，无法添加第%d个站点\n请重新输入：", bus[i].n, k);
								scanf("%d", &k);
								printf("\n");
							}
							bus[i].n = bus[i].n + 1;
							for (j = bus[i].n; j > k - 1; j--)
							{
								bus[i].name[j] = bus[i].name[j - 1];
							}
							printf("\n请输入新添加的站点名称：");
							scanf("%s", bus[i].name[k - 1].c);
							save();
							break;
						}
						case '2':     //修改站点
						{
							printf("\n请输入需要修改第几个站点：");
							scanf("%d", &k);
							printf("\n请输入新的站点名称：");
							scanf("%s", bus[i].name[k - 1].c);
							save();
							break;
						}
						case '3':     //删除站点
						{
							printf("\n请输入需要删除第几个站点：");
							scanf("%d", &k);
							for (j = k - 1; j < bus[i].n; j++)
							{
								bus[i].name[j] = bus[i].name[j + 1];
							}
							bus[i].n = bus[i].n - 1;
							save();
							break;
						}
						case '4':     //重置路线
						{
							printf("\n请输入新的途径站台总数(2<=n<=25): ");
							scanf("%d", &bus[i].n);
							printf("\n");
							while (bus[i].n < 2 || bus[i].n>12)             //判断是否满足条件
							{
								printf("\n站台总数应满足(2<=n<=25)，请重新输入: ");
								scanf("%d", &bus[i].n);
								printf("\n");
							}
							for (j = 0; j < bus[i].n; j++)
							{
								printf("请输入新的第%d个站台名称: ", j + 1);
								scanf("%s", bus[i].name[j].c);
							}
							printf("\t公交路线:(1) %s", bus[i].name[0].c);
							for (j = 1; j < bus[i].n; j++)
								printf(" ---->(%d) %s", j + 1, bus[i].name[j].c);
							printf("\n\n");
							save();
							break;
						}
						case '5':     //返回菜单
						{
							printf("\n\t\t按回车键返回菜单\n");
							modbus_menu();
							fflush(stdin);                           //清除键盘缓冲区
							getchar();
							//system("cls");
							return;                            //返回主菜单
						}
						}
					}
				}
				case '4':           //修改行车时间
				{
					printf("\n\n请输入公交车的起始时间(格式为：时:分): ");
					scanf("%s", bus[i].topen);
					printf("请输入公交车的终止时间(格式为：时:分): ");
					scanf("%s", bus[i].tclose);
					save();
					break;
				}
				case '5': 
				{
                    printf("\n\t\t按回车键返回主菜单\n");
					fflush(stdin);                           //清除键盘缓冲区
					getchar();
					//system("cls");
					return;                            //返回主菜单
				}
				}
			}
		}
	}
	if (m == 0)
		printf("\n\n\t\t无此公交车信息!!!\n");
	printf("\n\t\t按回车键返回\n");
	fflush(stdin);                           //清除键盘缓冲区
	getchar();
	system("cls");
	return;
}
//删除公交信息函数
void delete()       //信息删除函数
{
	int i, j, t, m = 0;
	char cc[20];
	printf("\n请输入要删改信息的公交车路线编号:\n");
	scanf("%s", cc);
	for (i = 0; *bus[i].num != '\0' && i < MAX; i++)     //查找所输入的公交车
	{
		if (strcmp(bus[i].num, cc) == 0)
		{
			m = 1;
			printf("\n已找到:\n");
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
			printf("\t路线编号: %-6s\t单程票价: %d 元\\n", bus[i].num, bus[i].money);
			printf("\t起始时间: %-6s\t终止时间: %-6s\t站台总数: %d\n", bus[i].topen, bus[i].tclose, bus[i].n);
			printf("\t公交路线:(1) %s", bus[i].name[0].c);
			for (j = 1; j < bus[i].n; j++)
				printf(" ---->(%d) %s", j + 1, bus[i].name[j].c);
			printf("\n\n");
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
			printf("即将删除该公交车信息!!!\n确定请按1：");
			scanf("%d", &t);
			if (t == 1)
			{
				if (i + 1 == MAX)
					memset(&bus[i], '\0', sizeof(struct bus));      //最后一辆直接进行清空
				else
					for (j = i; *bus[j].num != '\0' && j + 1 < MAX; j++)         //后面的公交车信息补上删去的公交车信息
						bus[j] = bus[j + 1];
				printf("编号为%s的公交车信息删除完毕!\n", cc);
				save();
				break;
			}
		}
	}
	if (m == 0)
		printf("\n\n\t\t无此公交车信息!!!\n");
	printf("\n\n\t输入回车键返回主菜单:");
	fflush(stdin);                           //清除键盘缓冲区
	getchar();
	//system("cls");
	return;
}
//根据公交车号查询
void findnum()           
{
	int i, j, m = 0;
	char cc[20];
	printf("请输入您想要查找的公交路线编号:\n");
	scanf("%s", cc);
	for (i = 0; *bus[i].num != '\0' && i < MAX; i++)
	{
		if (strcmp(bus[i].num, cc) == 0)
		{
			m = 1;
			printf("\n已找到:\n");
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
			printf("\t路线编号: %-6s\t单程票价: %d 元\n", bus[i].num, bus[i].money);
			printf("\t起始时间: %-6s\t终止时间: %-6s\t站台总数: %d\n", bus[i].topen, bus[i].tclose, bus[i].n);
			printf("\t公交路线:(1) %s", bus[i].name[0].c);
			for (j = 1; j < bus[i].n; j++)
				printf(" ---->(%d) %s", j + 1, bus[i].name[j].c);
			printf("\n\n");
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
			break;
		}
	}
	if (m == 0)
		printf("\n\t\t无此公交车信息\n");
	printf("\n\t\t输入回车键返回查询菜单:");
	fflush(stdin);                           //清除键盘缓冲区
	getchar();
	//system("cls");
	return;
}
//路线导航查询函数(?)功能不全 暂定
void modbus() {
	char a;
	while (1)
	{
		//system("cls");
		modbus_menu();
		a = Test(getchar(), '1', '4');      //菜单检测输入函数 
		switch (a)
		{
		case '1':	system("cls"); mod(); break;
		case '2':	system("cls"); add(); break;
		case '3':   system("cls"); delete(); break;
		case '4':   system("cls"); administrator(); break;
		}
	}
	return 0;
}
//游客功能
void visitor() {
	char a;
	while (1)
	{
		system("cls");
		visitor_menu();
		a = Test(getchar(), '1', '2');      //菜单检测输入函数 
		switch (a)
		{
		case '1':	system("cls"); query(2); break;
		case '2':	system("cls"); menu(); break;
		}
	}
	return 0;
}    
//主菜单
void menu() {
	char a;
	int n=0;
	while (1)
	{
		system("cls");
		host_menu();
		a = Test(getchar(), '1', '3');      //菜单检测输入函数 
		switch (a)
		{
		case '1':	system("cls"); 
			while (n != 1) {
				printf("请输入密码：");
				scanf("%d", &n);
				if (n == 1) {
					administrator();
				}
				else {
					printf("密码错误！请重新输入");
					scanf("%d", &n);
				}
			}
			break;
		case '2':	system("cls"); visitor(); break;
		case '3':   exit(1); return 0;
		}
	}
	return 0;
}
//管理员功能
void administrator(){
	char a;
		while (1)
		{
			//system("cls");
			administrator_menu();
			a = Test(getchar(), '1', '3');      //菜单检测输入函数 
			switch (a)
			{
			case '1':	system("cls"); modbus(); break;
			case '2':	system("cls"); query(1); break;
			case '3':   system("cls"); menu(); break;
			}
		}
	return 0;
	}
void searchnavi() //车辆换乘查询函数
{
	int i, j, k, m = 0;
	int t1, t2, n = 0;
	char c1[20], c2[20];
	printf("请输入您目前所在的站点:\n\t\t");
	scanf("%s", c1);
	printf("请输入您想要前往的站点:\n\t\t");
	scanf("%s", c2);
	printf("\n\n您可选择的公交车信息如下\n");
	printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
	for (i = 0; *bus[i].num != '\0' && i < MAX; i++)
	{
		for (j = 0; j < bus[i].n; j++)
			for (k = j + 1; k < bus[i].n; k++)
				if (strcmp(bus[i].name[j].c, c1) == 0 && strcmp(bus[i].name[k].c, c2) == 0)
				{
					m = 1;
					printf("\n");
					printf("\t路线编号: %-6s\t单程票价: %d 元\n", bus[i].num, bus[i].money);
					printf("\t起始时间: %-6s\t终止时间: %-6s\t站台总数: %d\n", bus[i].topen, bus[i].tclose, bus[i].n);
					printf("\t公交路线:(1) %s",bus[i].name[0].c);
					for (j = 1; j < bus[i].n; j++)
						printf(" ---->(%d) %s", j + 1, bus[i].name[j].c);
					printf("\n\n");
				}
	}
	printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n");
	printf("\t\t\t\t显示完毕\n");
	if (m == 0)
	{
		printf("\n\n\t\t\t\t抱歉,无途经此路线的公交车\n");
		for (i = 0; i < MAX; i++)
		{
			for (j = 0; j < bus[i].n; j++)
				if (strcmp(bus[i].name[j].c, c1) == 0)
					t1 = i;
		}
		for (i = 0; i < MAX; i++)
		{
			for (j = 0; j < bus[i].n; j++)
				if (strcmp(bus[i].name[j].c, c2) == 0)
					t2 = i;
		}
		for (i = 0; i <bus[t1].n; i++)
		{
			for (j = 0; j < bus[t2].n; j++)
			{
				if (strcmp(bus[t1].name[i].c,bus[t2].name[j].c) == 0)
				{
					n = 1;
				}
			}
		}
		if (n == 1)
		{
			printf("你可以选择换乘，具体路线信息如下：\n");
			printf("\n");
			printf("\t路线编号: %-6s\t单程票价: %d \n", bus[t1].num, bus[t1].money);
			printf("\t起始时间: %-6s\t终止时间: %-6s\t站台总数: %d\n", bus[t1].topen, bus[t1].tclose, bus[t1].n);
			printf("\t公交路线:(1) %s", bus[t1].name[0].c);
			for (j = 1; j < bus[t1].n; j++)
				printf(" -->(%d) %s", j + 1, bus[t1].name[j].c);
			printf("\n\n");
			printf("\n");
			printf("\t路线编号: %-6s\t单程票价: %d 元\n", bus[t2].num, bus[t2].money);
			printf("\t起始时间: %-6s\t终止时间: %-6s\t站台总数: %d\n", bus[t2].topen, bus[t2].tclose, bus[t2].n);
			printf("\t公交路线:(1) %s", bus[t2].name[0].c);
			for (j = 1; j < bus[t2].n; j++)
				printf(" -->(%d) %s", j + 1, bus[t2].name[j].c);
			printf("\n\n");
		}
		else
			printf("不可达！\n");
	}
	printf("\n\t\t\t\t输入回车键返回查询菜单:");
	fflush(stdin);              //清除键盘缓冲区
	getchar();
	return;
}
int dist[MAX][MAX], path[MAX][MAX];//dist 数组用来记录最短路径的权值,path 数组用 来记录路径 
int show() {
	printf("                        各个公交车站编号   \n");
	printf("*********************************************************************************************\n");
	printf("\t1.镇江南站\t2.焦山公园\t3.金山公园\t4.江苏大学中门\t5.渡口\n");
	printf("\t6.西津渡\t7.镇江新区\t8.东方村\t9.南山\t10.镇江中学\n");
	printf("\t11.党校\t12.江苏大学西门\t13.京谷大厦\t14.乔家门\t15.瑞丹花园\n");
	printf("\t16.彩虹城\t17.东昌\t18.印江桥\t19.松盛园\t20.北固山\n");
	printf("\t21.汽车客运站\t22.以泉村\t23.宝塔山公园\t24.我家山水\t25.丁卯开发区\n");
	printf("*********************************************************************************************\n");
}
void show_travel() {
	printf("                        旅游攻略查询    \n");
	printf("*********************************************************************************************\n");
	printf("\t1.北固山(编号20）\t2.焦山公园（编号2）\t3.金山公园（编号3）\t4.南山（编号9）\n");
	printf("*********************************************************************************************\n");
}
void floyd(MGraph *G)
{
	int i, j, v;
	for (i = 0; i < G->numVertexes; i++)
		for (j = 0; j < G->numVertexes; j++)
		{
			if (i == j) dist[i][j] = 0;
			dist[i][j] = G->arc[i][j];
			path[i][j] = -1;
		}
	for (v = 0; v < G->numVertexes; v++)
		for (i = 0; i < G->numVertexes; i++)
			for (j = 0; j < G->numVertexes; j++)
			{
				if (dist[i][v] + dist[v][j] < dist[i][j])
				{
					dist[i][j] = dist[i][v] + dist[v][j];
					path[i][j] = v;
				}
			}
}
int main() {
	char a;
	int n;
	scanf("%d", &n);
	STATION_NUM = n;
	init();
	menu();
	return 0;
}