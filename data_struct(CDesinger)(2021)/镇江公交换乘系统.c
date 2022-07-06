#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define INFINITY      999999999999     /*�����*/ 
#define MAX 40
int STATION_NUM;             //վ������
struct station                   //;��վ����Ϣ
{
    char c[20];                  //վ������
};

typedef struct bus                    //��������Ϣ
{
    char num[20];                //���������
    int n;                       //վ̨��Ŀ
    struct station name[12];     //վ̨����
    char topen[20];              //��ʼʱ��
    char tclose[20];             //��ֹʱ��
    int money;                   //Ʊ��
}BUS;
BUS  bus[MAX];
typedef struct
{
	int name;  	//վ������ 
	int lines[6]; 	//;��·�� 
}Vertex;
typedef struct
{
	Vertex vexs[MAX];  	//վ�� 
	int arc[MAX][MAX]; 	//�ڽӾ��� 
	int numVertexes, numEdges; 	//�������ͱ��� 
}MGraph;
int Distance[100][100];
//������
void init();  void save();int host_menu(); int administrator_menu();int visitor_menu(); 
int query_menu();void modbus_menu(); void modstation_menu(); char Test(char a, char b, char c);void add();void view(); void mod(); 
void delete(); void findnum();void administrator(); void menu();void visitor();void floyd();void searchnavi();int show();void show_travel();
/* ����ͼ */
void CreateMGraph(MGraph* G)
{
	int i, j;

	//����������Ͷ�����
	G->numEdges = 52;
	G->numVertexes = 26;

	for (i = 0; i < G->numVertexes; i++)
	{
		G->vexs[i].name = i;
	}

	for (i = 0; i < 26; i++)//��ʼ��ÿ��վ��ͨ��·�ߵ����飬��Ϊ�� 
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

	int t[MAX][MAX] = { 0 }; //���������Ȩͼ���ڽӾ��� 
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

	for (i = 0; i < G->numVertexes; i++)//* ��ʼ��ͼ 
	{
		for (j = 0; j < G->numVertexes; j++)
		{
			if (i == j)
				G->arc[i][j] = 0;
			else
				G->arc[i][j] = G->arc[j][i] = INFINITY;
		}
	}

	for (i = 0; i < G->numVertexes; i++)//* �����ڽӾ��� 
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
//��ʼ��
void init()     //��ʼ������       
{
    FILE* fp;                        //�ļ�ָ��
    int i;
    if ((fp = fopen("bus.txt", "r+")) == NULL)                  //���γ��Դ�"bus.txt"�ı��ļ�
    {
        printf("\n\t\t�ļ���ʧ��\n\n\t\t���ڳ��Դ������ļ�...\n");
        fp = fopen("bus.txt", "w");                          //����"bus.txt"�ı��ļ�
        if ((fp = fopen("bus.txt", "r+")) == NULL)              //�ٴ��ж��Ƿ�򿪳ɹ�
        {
            printf("\t\t�ļ�����ʧ��!!!\n");
            return;
        }
    }
    fp = fopen("bus.txt", "r+");
    for (i = 0; i < MAX; i++)                                          //�������е���Ϣ������ڴ���
        if (fread(&bus[i], sizeof(struct bus), 1, fp) != 1)
            break;
    fclose(fp);
    printf("\n\t\t��ʼ�����!!!\n\n");
    return;
}
//��ɾ�ĺ����Ϣд���ĵ�
void save()         //��Ϣ���溯�� 
{
    FILE* fp = NULL;
    int i;
    if ((fp = fopen("bus.txt", "w+")) == NULL)            //�Զ�д�ķ�ʽ������Ϊ"bus"���ı��ļ�
    {
        printf("�ļ��򿪴���!!!\n");
        return;
    }
    fp = fopen("bus.txt", "w+");
    for (i = 0; *bus[i].num != '\0' && i < MAX; i++)                   //���ڴ��е����������������
        if (fwrite(&bus[i], sizeof(struct bus), 1, fp) != 1)
            break;
    printf("\n\t����ɹ�!!!\n");
    fclose(fp);
    return;
}
//���˵���1���˵���
int host_menu() 
{
	printf("\n");
    printf("                               ���˵�                                 \n");
    printf("**********************************************************************\n");
    printf("                            1.����Աϵͳ                              \n");
    printf("                            2.�˿�ϵͳ                                \n");
    printf("                            3.�˳�                                    \n");
    printf("**********************************************************************\n");
    printf("����ѡ����������:");
}
//����Ա�˵�
int administrator_menu()
{
	printf("\n");
    printf("                               ����Ա�˵�                             \n");
    printf("**********************************************************************\n");
	printf("                            1.�޸Ĺ�����·                            \n");
    printf("                            2.��ѯ·��                                    \n");
    printf("                            3.�������˵�                              \n");
    printf("**********************************************************************\n");
    printf("����ѡ����������:");
}
//�οͲ˵�
int visitor_menu()
{
	printf("\n");
    printf("                               �οͲ˵�                               \n");
    printf("**********************************************************************\n");
    printf("                            1.��ѯ                                    \n");
    printf("                            2.�������˵�                              \n");
    printf("**********************************************************************\n");
    printf("����ѡ����������:");
}
//·�߲�ѯ�˵�
int query_menu()
{
	printf("\n");
    printf("                               ��ѯ�˵�                               \n");
    printf("**********************************************************************\n");
	printf("                            1.��ѯ���й���·��                        \n");
    printf("                            2.��ѯĳ������·��                        \n");
    printf("                            3.���˲�ѯ                                \n");
    printf("                            4.����·�߹滮                            \n");
    printf("                            5.������һ��˵�                          \n");
    printf("**********************************************************************\n");
    printf("����ѡ����������:");
}
//��ѯ
void query(int n) {
	char a;
	while (1)
	{
		//system("cls");
		query_menu();
		a = Test(getchar(), '1', '5');      //�˵�������뺯�� 
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
//�޸Ĺ�����Ϣ�˵�
void modbus_menu()  //�޸Ĳ˵�
{
	printf("\n\t\t                 �޸Ĳ˵�                   ");
	printf("\n\t\t********************************************");
	printf("\n\t\t*            1���޸�ԭ��·��                *");
	printf("\n\t\t*            2������·��                   *");
	printf("\n\t\t*            3��ɾ��ԭ��·��               *");
	printf("\n\t\t*            4�����ص�����Ա�˵�           *");
	printf("\n\t\t********************************************");
	printf("\n\n\t\t����������ѡ��:");
}
//�޸ľ���·�߲˵�
void modload_menu() {
	printf("\n\t\t             �޸ľ���·�߲˵�               ");
	printf("\n\t\t********************************************");
	printf("\n\t\t*            1���޸�·�߱��               *");
	printf("\n\t\t*            2���޸ĳ���Ʊ��               *");
	printf("\n\t\t*            3���޸��г�·��               *");
	printf("\n\t\t*            4���޸��г�ʱ��               *");
	printf("\n\t\t*            5��������һ��˵�             *");
	printf("\n\n\t\t����������ѡ��:");
}
//�޸ľ���·�߲˵�
void modstation_menu() //·���޸Ĳ˵�
{
	printf("\n\t\t               ·���޸Ĳ˵�                 ");
	printf("\n\t\t********************************************");
	printf("\n\t\t*            1�� վ �� �� ��               *");
	printf("\n\t\t*            2�� վ �� �� ��               *");
	printf("\n\t\t*            3�� վ �� ɾ ��               *");
	printf("\n\t\t*            4�� · �� �� ��               *");
	printf("\n\t\t*            5�� �� �� �� ��               *");
	printf("\n\t\t********************************************");
	printf("\n\n\t\t����������ѡ��:");
}
//��������Ƿ���ȷ�ĺ���
char Test(char a, char b, char c)
{
	while (a<b || a>c)
	{
		printf("\n\t\t\t�����������������: ");
		fflush(stdin);                           //������̻�����
		a = getchar();
	}
	return a;
}	
//����µ�·��
void add()           
{
    FILE* fp = NULL;                        //�ļ�ָ��
    int i, j;
    char cc[20];
    for (i = 0; i < MAX; i++)
    {
        if (*bus[i].num != '\0')
            continue;
        else
        {
            printf("\n��ӵ�%d��������·�߼�¼:\n", i + 1);
            printf("\n������·�߱���:\n");    //·�߱���
            scanf("%s", cc);
            for (j = 0; j < MAX; j++)                                                           //�����Ƿ��ظ�
                if (strcmp(bus[j].num, cc) == 0)
                {
                    printf("\n������·�߱����ظ������س�������!!!\n");
                    fflush(stdin);                           //������̻�����
                    getchar();
                    //system("cls");
                    return;
                }
            strcpy(bus[i].num, cc);
            printf("\n������;��վ̨����(>=2): ");                                     //վ̨����
            scanf("%d", &bus[i].n);
            printf("\n");
            if (bus[i].n < 2 || bus[i].n>12)
            {
                while (bus[i].n < 2 || bus[i].n>12)
                {
                    printf("\nվ̨����Ӧ����(2<=n<=25)������������: ");
                    scanf("%d", &bus[i].n);
                    printf("\n");
                }
            }
            for (j = 0; j < bus[i].n; j++)
            {
                printf("�������%d��վ̨���� ", j + 1);                    //վ̨����
                scanf("%s", bus[i].name[j].c);
            }
            printf("\n�Զ����ɹ���·��:(1) %s", bus[i].name[0].c);
            for (j = 1; j < bus[i].n; j++)
            {
                printf(" ----> (%d) %s", j + 1, bus[i].name[j].c);
            }
            printf("\n\n�����빫��������ʼʱ��: ");       //��ʼʱ��
            scanf("%s", bus[i].topen);
            printf("�����빫��������ֹʱ��: ");           //��ֹʱ��
            scanf("%s", bus[i].tclose);
            printf("\n�����빫������Ʊ��: ");                            //Ʊ��
            scanf("%d", &bus[i].money);
            printf("\n��%d��������·�߼�¼�����ɹ�!!!\n", i + 1);
            save();
            printf("\n\t���س�������!!!\n");
            fflush(stdin);                           //������̻�����
            getchar();
            //system("cls");
            return;
        }
    }
    if (i == MAX)
        printf("\n\n\n\t�ռ�����������¼��!!!\n");
    printf("\n\t���س�������!!!\n");
    fflush(stdin);                           //������̻�����
    getchar();
    //system("cls");
    return;
}
//��ʾ���й�����Ϣ
void view()        
{
    int i, j, min;
	show();
    printf("\n\n                              ��������Ϣ��");
    printf("\n********************************************************************************\n");
    for (i = 0; *bus[i].num != '\0' && i < MAX; i++)
    {
        printf("\t·�߱��: %-6s\t����Ʊ��: %d Ԫ\n", bus[i].num, bus[i].money);
        printf("\t��ʼʱ��: %-6s\t��ֹʱ��: %-6s\tվ̨����: %d\n", bus[i].topen, bus[i].tclose, bus[i].n);
        printf("\t����·��:(1) %s", bus[i].name[0].c);
        for (j = 1; j < bus[i].n; j++)
            printf(" ---->(%d) %s", j + 1, bus[i].name[j].c);
        printf("\n\n");
    }
    printf("\n********************************************************************************\n");
    printf("\n\t\t��������Ϣ��ʾ���!!!\n");
    printf("\n\t\t����س����������˵�:");
    fflush(stdin);                           //������̻�����
    getchar();
    //system("cls");
    return;
}
//�޸Ĺ�����Ϣ����
void mod()                         
{
	int i, j, m = 0;
	char t, cc[20], mod[20];
	
	printf("������Ҫ�޸���Ϣ�Ĺ�����·�߱��:\n");
	scanf("%s", cc);
	for (i = 0; *bus[i].num != '\0' && i < MAX; i++)     //����������Ĺ�����
	{
		if (strcmp(bus[i].num, cc) == 0)
		{
			m = 1;
			printf("\n\n\t\t���ҵ�!!!\n");
			while (1)
			{
				system("cls");
				printf("\n\n                            �����޸ĵĹ�������Ϣ\n");
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
				printf("\t·�߱��: %-6s\t����Ʊ��: %d Ԫ\n", bus[i].num, bus[i].money);
				printf("\t��ʼʱ��: %-6s\t��ֹʱ��: %-6s\tվ̨����: %d\n", bus[i].topen, bus[i].tclose, bus[i].n);
				printf("\t����·��:(1) %s", bus[i].name[0].c);
				for (j = 1; j < bus[i].n; j++)
					printf(" ---->(%d) %s", j + 1, bus[i].name[j].c);
				printf("\n\n");
				printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
				modload_menu();
				fflush(stdin);                           //������̻�����
				t = Test(getchar(), '1', '5');      //�˵�������뺯�� 
				//system("cls");
				switch (t)
				{
				case '1':           //�޸�·�߱��
				{
					int k;
					printf("\n�������µĹ��������:");
					scanf("%s", mod);
					for (k = 0; *bus[k].num != '\0' && k < MAX; k++)
					{
						if (strcmp(bus[k].num, mod) == 0)
						{
							printf("�����б���ظ�,���س����������˵�\n");
							fflush(stdin);                           //������̻�����
							getchar();
							//system("cls");
							return;
						}
					}
					strcpy(bus[i].num, mod);
					save();
					break;
				}
				case '2':           //�޸ĳ�����Ϣ
				{
					printf("\n�������µĹ�����Ʊ��:");
					scanf("%d", &bus[i].money);
					save();
					break;
				}
				case '3':           //�޸��г�·��
				{
					void modstation_menu(); //·���޸Ĳ˵�
					int k;
					char z;
					while (1)
					{
						//system("cls");
						modstation_menu();
						fflush(stdin);                           //������̻�����
						z = Test(getchar(), '1', '6');      //�˵�������뺯�� 
						//system("cls");
						switch (z)
						{
						case '1':     //���վ��
						{
							if (bus[i].n + 1 > 12)             //�ж��Ƿ���������
							{
								printf("\nվ̨�����ﵽ25�����޷������վ��\n\n���س�������\n");
								fflush(stdin);                           //������̻�����
								getchar();
								system("cls");
								return;
							}
							printf("\n��������Ҫ��ӵڼ���վ�㣺");
							scanf("%d", &k);
							while (bus[i].n + 1 < k)
							{
								printf("Ŀǰ��%d��վ�㣬�޷���ӵ�%d��վ��\n���������룺", bus[i].n, k);
								scanf("%d", &k);
								printf("\n");
							}
							bus[i].n = bus[i].n + 1;
							for (j = bus[i].n; j > k - 1; j--)
							{
								bus[i].name[j] = bus[i].name[j - 1];
							}
							printf("\n����������ӵ�վ�����ƣ�");
							scanf("%s", bus[i].name[k - 1].c);
							save();
							break;
						}
						case '2':     //�޸�վ��
						{
							printf("\n��������Ҫ�޸ĵڼ���վ�㣺");
							scanf("%d", &k);
							printf("\n�������µ�վ�����ƣ�");
							scanf("%s", bus[i].name[k - 1].c);
							save();
							break;
						}
						case '3':     //ɾ��վ��
						{
							printf("\n��������Ҫɾ���ڼ���վ�㣺");
							scanf("%d", &k);
							for (j = k - 1; j < bus[i].n; j++)
							{
								bus[i].name[j] = bus[i].name[j + 1];
							}
							bus[i].n = bus[i].n - 1;
							save();
							break;
						}
						case '4':     //����·��
						{
							printf("\n�������µ�;��վ̨����(2<=n<=25): ");
							scanf("%d", &bus[i].n);
							printf("\n");
							while (bus[i].n < 2 || bus[i].n>12)             //�ж��Ƿ���������
							{
								printf("\nվ̨����Ӧ����(2<=n<=25)������������: ");
								scanf("%d", &bus[i].n);
								printf("\n");
							}
							for (j = 0; j < bus[i].n; j++)
							{
								printf("�������µĵ�%d��վ̨����: ", j + 1);
								scanf("%s", bus[i].name[j].c);
							}
							printf("\t����·��:(1) %s", bus[i].name[0].c);
							for (j = 1; j < bus[i].n; j++)
								printf(" ---->(%d) %s", j + 1, bus[i].name[j].c);
							printf("\n\n");
							save();
							break;
						}
						case '5':     //���ز˵�
						{
							printf("\n\t\t���س������ز˵�\n");
							modbus_menu();
							fflush(stdin);                           //������̻�����
							getchar();
							//system("cls");
							return;                            //�������˵�
						}
						}
					}
				}
				case '4':           //�޸��г�ʱ��
				{
					printf("\n\n�����빫��������ʼʱ��(��ʽΪ��ʱ:��): ");
					scanf("%s", bus[i].topen);
					printf("�����빫��������ֹʱ��(��ʽΪ��ʱ:��): ");
					scanf("%s", bus[i].tclose);
					save();
					break;
				}
				case '5': 
				{
                    printf("\n\t\t���س����������˵�\n");
					fflush(stdin);                           //������̻�����
					getchar();
					//system("cls");
					return;                            //�������˵�
				}
				}
			}
		}
	}
	if (m == 0)
		printf("\n\n\t\t�޴˹�������Ϣ!!!\n");
	printf("\n\t\t���س�������\n");
	fflush(stdin);                           //������̻�����
	getchar();
	system("cls");
	return;
}
//ɾ��������Ϣ����
void delete()       //��Ϣɾ������
{
	int i, j, t, m = 0;
	char cc[20];
	printf("\n������Ҫɾ����Ϣ�Ĺ�����·�߱��:\n");
	scanf("%s", cc);
	for (i = 0; *bus[i].num != '\0' && i < MAX; i++)     //����������Ĺ�����
	{
		if (strcmp(bus[i].num, cc) == 0)
		{
			m = 1;
			printf("\n���ҵ�:\n");
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
			printf("\t·�߱��: %-6s\t����Ʊ��: %d Ԫ\\n", bus[i].num, bus[i].money);
			printf("\t��ʼʱ��: %-6s\t��ֹʱ��: %-6s\tվ̨����: %d\n", bus[i].topen, bus[i].tclose, bus[i].n);
			printf("\t����·��:(1) %s", bus[i].name[0].c);
			for (j = 1; j < bus[i].n; j++)
				printf(" ---->(%d) %s", j + 1, bus[i].name[j].c);
			printf("\n\n");
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
			printf("����ɾ���ù�������Ϣ!!!\nȷ���밴1��");
			scanf("%d", &t);
			if (t == 1)
			{
				if (i + 1 == MAX)
					memset(&bus[i], '\0', sizeof(struct bus));      //���һ��ֱ�ӽ������
				else
					for (j = i; *bus[j].num != '\0' && j + 1 < MAX; j++)         //����Ĺ�������Ϣ����ɾȥ�Ĺ�������Ϣ
						bus[j] = bus[j + 1];
				printf("���Ϊ%s�Ĺ�������Ϣɾ�����!\n", cc);
				save();
				break;
			}
		}
	}
	if (m == 0)
		printf("\n\n\t\t�޴˹�������Ϣ!!!\n");
	printf("\n\n\t����س����������˵�:");
	fflush(stdin);                           //������̻�����
	getchar();
	//system("cls");
	return;
}
//���ݹ������Ų�ѯ
void findnum()           
{
	int i, j, m = 0;
	char cc[20];
	printf("����������Ҫ���ҵĹ���·�߱��:\n");
	scanf("%s", cc);
	for (i = 0; *bus[i].num != '\0' && i < MAX; i++)
	{
		if (strcmp(bus[i].num, cc) == 0)
		{
			m = 1;
			printf("\n���ҵ�:\n");
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n");
			printf("\t·�߱��: %-6s\t����Ʊ��: %d Ԫ\n", bus[i].num, bus[i].money);
			printf("\t��ʼʱ��: %-6s\t��ֹʱ��: %-6s\tվ̨����: %d\n", bus[i].topen, bus[i].tclose, bus[i].n);
			printf("\t����·��:(1) %s", bus[i].name[0].c);
			for (j = 1; j < bus[i].n; j++)
				printf(" ---->(%d) %s", j + 1, bus[i].name[j].c);
			printf("\n\n");
			printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  - - - - - - \n\n");
			break;
		}
	}
	if (m == 0)
		printf("\n\t\t�޴˹�������Ϣ\n");
	printf("\n\t\t����س������ز�ѯ�˵�:");
	fflush(stdin);                           //������̻�����
	getchar();
	//system("cls");
	return;
}
//·�ߵ�����ѯ����(?)���ܲ�ȫ �ݶ�
void modbus() {
	char a;
	while (1)
	{
		//system("cls");
		modbus_menu();
		a = Test(getchar(), '1', '4');      //�˵�������뺯�� 
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
//�ο͹���
void visitor() {
	char a;
	while (1)
	{
		system("cls");
		visitor_menu();
		a = Test(getchar(), '1', '2');      //�˵�������뺯�� 
		switch (a)
		{
		case '1':	system("cls"); query(2); break;
		case '2':	system("cls"); menu(); break;
		}
	}
	return 0;
}    
//���˵�
void menu() {
	char a;
	int n=0;
	while (1)
	{
		system("cls");
		host_menu();
		a = Test(getchar(), '1', '3');      //�˵�������뺯�� 
		switch (a)
		{
		case '1':	system("cls"); 
			while (n != 1) {
				printf("���������룺");
				scanf("%d", &n);
				if (n == 1) {
					administrator();
				}
				else {
					printf("�����������������");
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
//����Ա����
void administrator(){
	char a;
		while (1)
		{
			//system("cls");
			administrator_menu();
			a = Test(getchar(), '1', '3');      //�˵�������뺯�� 
			switch (a)
			{
			case '1':	system("cls"); modbus(); break;
			case '2':	system("cls"); query(1); break;
			case '3':   system("cls"); menu(); break;
			}
		}
	return 0;
	}
void searchnavi() //�������˲�ѯ����
{
	int i, j, k, m = 0;
	int t1, t2, n = 0;
	char c1[20], c2[20];
	printf("��������Ŀǰ���ڵ�վ��:\n\t\t");
	scanf("%s", c1);
	printf("����������Ҫǰ����վ��:\n\t\t");
	scanf("%s", c2);
	printf("\n\n����ѡ��Ĺ�������Ϣ����\n");
	printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
	for (i = 0; *bus[i].num != '\0' && i < MAX; i++)
	{
		for (j = 0; j < bus[i].n; j++)
			for (k = j + 1; k < bus[i].n; k++)
				if (strcmp(bus[i].name[j].c, c1) == 0 && strcmp(bus[i].name[k].c, c2) == 0)
				{
					m = 1;
					printf("\n");
					printf("\t·�߱��: %-6s\t����Ʊ��: %d Ԫ\n", bus[i].num, bus[i].money);
					printf("\t��ʼʱ��: %-6s\t��ֹʱ��: %-6s\tվ̨����: %d\n", bus[i].topen, bus[i].tclose, bus[i].n);
					printf("\t����·��:(1) %s",bus[i].name[0].c);
					for (j = 1; j < bus[i].n; j++)
						printf(" ---->(%d) %s", j + 1, bus[i].name[j].c);
					printf("\n\n");
				}
	}
	printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n");
	printf("\t\t\t\t��ʾ���\n");
	if (m == 0)
	{
		printf("\n\n\t\t\t\t��Ǹ,��;����·�ߵĹ�����\n");
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
			printf("�����ѡ�񻻳ˣ�����·����Ϣ���£�\n");
			printf("\n");
			printf("\t·�߱��: %-6s\t����Ʊ��: %d \n", bus[t1].num, bus[t1].money);
			printf("\t��ʼʱ��: %-6s\t��ֹʱ��: %-6s\tվ̨����: %d\n", bus[t1].topen, bus[t1].tclose, bus[t1].n);
			printf("\t����·��:(1) %s", bus[t1].name[0].c);
			for (j = 1; j < bus[t1].n; j++)
				printf(" -->(%d) %s", j + 1, bus[t1].name[j].c);
			printf("\n\n");
			printf("\n");
			printf("\t·�߱��: %-6s\t����Ʊ��: %d Ԫ\n", bus[t2].num, bus[t2].money);
			printf("\t��ʼʱ��: %-6s\t��ֹʱ��: %-6s\tվ̨����: %d\n", bus[t2].topen, bus[t2].tclose, bus[t2].n);
			printf("\t����·��:(1) %s", bus[t2].name[0].c);
			for (j = 1; j < bus[t2].n; j++)
				printf(" -->(%d) %s", j + 1, bus[t2].name[j].c);
			printf("\n\n");
		}
		else
			printf("���ɴ\n");
	}
	printf("\n\t\t\t\t����س������ز�ѯ�˵�:");
	fflush(stdin);              //������̻�����
	getchar();
	return;
}
int dist[MAX][MAX], path[MAX][MAX];//dist ����������¼���·����Ȩֵ,path ������ ����¼·�� 
int show() {
	printf("                        ����������վ���   \n");
	printf("*********************************************************************************************\n");
	printf("\t1.����վ\t2.��ɽ��԰\t3.��ɽ��԰\t4.���մ�ѧ����\t5.�ɿ�\n");
	printf("\t6.�����\t7.������\t8.������\t9.��ɽ\t10.����ѧ\n");
	printf("\t11.��У\t12.���մ�ѧ����\t13.���ȴ���\t14.�Ǽ���\t15.�𵤻�԰\n");
	printf("\t16.�ʺ��\t17.����\t18.ӡ����\t19.��ʢ԰\t20.����ɽ\n");
	printf("\t21.��������վ\t22.��Ȫ��\t23.����ɽ��԰\t24.�Ҽ�ɽˮ\t25.��î������\n");
	printf("*********************************************************************************************\n");
}
void show_travel() {
	printf("                        ���ι��Բ�ѯ    \n");
	printf("*********************************************************************************************\n");
	printf("\t1.����ɽ(���20��\t2.��ɽ��԰�����2��\t3.��ɽ��԰�����3��\t4.��ɽ�����9��\n");
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