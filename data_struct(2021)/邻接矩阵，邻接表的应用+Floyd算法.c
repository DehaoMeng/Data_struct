#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 100
#define MAX_WEIGHT 1000
typedef int Elemtype;
Elemtype flag[MAX];
Elemtype visited[MAX];
Elemtype path[MAX][MAX];
//邻接矩阵定义
typedef struct
{
	int vexnum, arcnum;
	char vex[MAX];         //存顶点信息
	int arc[MAX][MAX];       //存边的信息
}AdjMatrix;
//邻接表定义
typedef struct node
{
	int num;
	struct node* next;
}slink;                     //创建边类型
typedef struct
{
	struct
	{
		Elemtype vertex;         //节点信息
		slink* first;            //节点指针
	}ve[MAX];                    //顶点结构信息
	int vex, edge, tag;          //存放顶点数、边数、图的类型
}adjlist;
//广度优先遍历
void bfs(adjlist* G, int v)
{
	int queue[MAX], front, rear, i;
	slink* p;
	front = rear = 0;
	queue[rear++] = v;
	while (front != rear)
	{
		v = queue[front++];
		printf("%c", G->ve[v].vertex);
		visited[v] = 1;
		p = G->ve[v].first;
		while (p != NULL)
		{
			for (i = 0; i < rear; i++)
				if (p->num == queue[i])break;
			if (i >= rear)
				queue[rear++] = p->num;
			p = p->next;
		}
	}
}
void BFSgraph(adjlist* G) {
	int i = 0;
	for (i = 0; i < G->vex; i++)
		if (!visited[i])
			bfs(G, i);
}
//建立邻接矩阵
void Creadjm(AdjMatrix* G) {
	int i, j, k,weigh;
	printf("Input vexnum,arcnum:");
	scanf("%d%d", &G->vexnum, &G->arcnum);  //输入顶点数、边数
	for (k = 0; k < G->vexnum; k++)
	{
		G->vex[k] = 'A' + k;
	}
	for (i = 0; i < G->vexnum; i++) {
		for (j = 0; j < G->vexnum; j++) {
			G->arc[i][j] = 0;             //初始化邻接矩阵
		}
	}
	printf("Input %d edges:\n", G->arcnum);
	for (k = 0; k < G->arcnum; k++) {
		scanf("%d%d%d", &i, &j,&weigh);
		G->arc[i][j] = weigh;
	}
}
//列出邻接矩阵
void listMatrix(AdjMatrix* G) {     // 输出邻接表
	int i, j;
	for (i = 0; i < G->vexnum; i++) {
		printf("%6c---", G->vex[i]);   
		for (j = 0; j < G->vexnum; j++) {
			printf("%4d", G->arc[i][j]);	
		}
		printf("\n");
	}
}
//把邻接矩阵转换为邻接表
void MatToList(AdjMatrix* A, adjlist* B)
{
	int i, j, k;
	slink* s;
	B->vex = A->vexnum;
	B->edge = A->arcnum;
	for (k = 0; k < A->vexnum; k++)
	{
		B->ve[k].vertex = A->vex[k];
		B->ve[k].first = NULL;
	}
	for (i = 0; i < A->vexnum; i++)
		for (j = A->vexnum - 1; j >= 0; j--)
			if (A->arc[i][j] != 0)
			{
				s = (slink*)malloc(sizeof(slink));
				s->num = j;
				if (B->ve[i].first == NULL)
				{
					B->ve[i].first = s;
					s->next = NULL;
				}
				else
				{
					s->next = B->ve[i].first;
					B->ve[i].first = s;
				}
			}

}
//深度优先遍历
void DFS_begin(AdjMatrix* G,int k) {
	int i;
	flag[k] = 1;
	printf("%c", G->vex[k]);
	for (i = 0; i < G->vexnum; i++) {
		if (!flag[i]&&G->arc[k][i]!=0 ) {
			DFS_begin(G, i);
		}
	}
}
void DFS_END(AdjMatrix* G) {
	for (int i = 0; i < G->vexnum; i++) {
		flag[i] = 0;
	}
	for (int i = 0; i < G->vexnum; i++) {
		if (!flag[i])
			DFS_begin(G, i);
	}
}
//列出邻接表
void listList(adjlist* G)
{
	int i;
	slink* p;
	for (i = 0; i < G->vex; i++)
	{
		printf("%d:%c-->", i, G->ve[i].vertex);
		p = G->ve[i].first;
		while (p)
		{
			printf("%4d", p->num);
			p = p->next;
		}
		printf("\n");
	}
}
void Floyd(AdjMatrix* G)
{
	int i, j, v;
	int n = G->vexnum;
	int dist[MAX][MAX];
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (G->arc[i][j] == 0)
				dist[i][j] = MAX_WEIGHT;
			else
				dist[i][j] = G->arc[i][j];
			path[i][j] = -1;
		}
		dist[i][i] = 0;
	}
	for (v = 0; v < n; v++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (dist[i][j] > dist[i][v] + dist[v][j])
				{
					dist[i][j] = dist[i][v] + dist[v][j];
					path[i][j] = v;
				}
}
void list_floyd(int u, int v) {
	int mid;
	if (path[u][v] == -1)
		printf("-->%c", 'A'+v);
	else
	{
		mid = path[u][v];
		list_floyd(u, mid, path);
		list_floyd(mid, v, path);
	}
}
int main() {
	int i, j;
	AdjMatrix* G;
	adjlist* P;
	G = (AdjMatrix*)malloc(sizeof(AdjMatrix));
	P = (adjlist*)malloc(sizeof(adjlist));
    Creadjm(G);
	printf("邻接矩阵的深度优先遍历为：");
	DFS_END(G);       
	printf("\n");
	printf("输出邻接矩阵：\n");
	listMatrix(G);      
	MatToList(G, P);      //邻接矩阵转邻接表
	printf("输出邻接表：\n");
	listList(P);     
	printf("邻接表的广度优先遍历为：");
	BFSgraph(P);
	printf("\n");
	Floyd(G);             //最短路径Floyd算法
	scanf("%d%d", &i, &j);
	printf("最短路径为：");
	printf("%c", 'A' + i);
	list_floyd(i, j);
	system("pause");
	return 0;
}