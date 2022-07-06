#include<stdio.h>
#define MAXSIZE 30

typedef struct Graph{
	char vertex[MAXSIZE]; // 存放结点数据
	int edge[MAXSIZE][MAXSIZE]; // 邻接矩阵
	int vertexNum;
}Graph;

// 初始化图
int InitGraph(Graph *p){
	p->vertexNum = 0;
	return 1;
}

// 添加结点
int AddVertex(Graph *p,char s){
	p->vertex[p->vertexNum] = s;
	p->vertexNum++;
	return 1;
}

// 初始化边
int InitEdge(Graph *p){
	int i,j;
	for(i=0;i<p->vertexNum;i++){
		for(j=0;j<p->vertexNum;j++){
			p->edge[i][j] = 0;
		}
	}
	return 1;
}

// 添加边
int AddEdge(Graph *p,int i,int j){
	p->edge[i][j] = 1;
	return 1;
}

// 输出邻接矩阵
int PrintEdge(Graph *p){
	int i,j;
	for(i=0;i<p->vertexNum;i++){
		for(j=0;j<p->vertexNum;j++){
			printf("%d ",p->edge[i][j]);
		}
		printf("\n");
	}
	return 1;
}

// 广度优先查询边
int BFSFindEdge(Graph *p,char s,char n){
	int i,end_vertex,start_vertex;
	for(i=0;i<p->vertexNum;i++){
		if(p->vertex[i] == s){
			start_vertex = i;
		}
		if(p->vertex[i] == n){
			end_vertex = i;
		}
	}
	int queue[MAXSIZE],front,rear;
	int visited[p->vertexNum];
	rear = 0;
	front = 0;	
	queue[rear]= start_vertex;
	rear = (rear + 1) % MAXSIZE;
	while(rear != front){
		int j = queue[front];
		front = (front + 1) % MAXSIZE;
		int f;
		for(f=0;f<p->vertexNum;f++){
			if(p->edge[j][f] == 1 && visited[f] != 1){
				visited[f] = 1;
				queue[rear] = f;
				rear = (rear + 1) % MAXSIZE;
				if( f == end_vertex) return 1;
			}
		}
	}
	return 0;
}

int main(){
	char s;
	Graph p;
	InitGraph(&p);
	scanf("%c",&s);
	while(s != '!'){
		AddVertex(&p,s);
		scanf("%c",&s);
	}
	InitEdge(&p);
	int i,j;
	scanf("%d %d",&i,&j);
	while(i != -1 && j != -1){
		AddEdge(&p,i,j);
		scanf("%d %d",&i,&j);
	}
	
	char n;
	getchar();
	scanf("%c%c",&s,&n);
	PrintEdge(&p);
	if(BFSFindEdge(&p,s,n)) printf("T\n");
	else printf("F\n");
	return 0;
}
