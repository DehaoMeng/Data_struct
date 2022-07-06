/*
 * This is about Graph
 * Get the Graph's connected componentsNum !!
 * */


#include<stdio.h>
#define MAXSIZE 30
int connected_componentsNum = 0;
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

// 广度优先遍历
int BFSFindEdge(Graph *p){
	connected_componentsNum++;
	int i,end_vertex,start_vertex;
	int queue[MAXSIZE],front,rear;
	int visited[p->vertexNum];
	rear = 0;
	front = 0;	
	queue[rear]= 0;
	rear = (rear + 1) % MAXSIZE;
	visited[0] = 1;
	while(rear != front){
		int j = queue[front];
		front = (front + 1) % MAXSIZE;
		int f;
		for(f=0;f<p->vertexNum;f++){
			if(p->edge[j][f] == 1 && visited[f] != 1){
				visited[f] = 1;
				queue[rear] = f;
				rear = (rear + 1) % MAXSIZE;
			}
		}
	}
	for(i=0;i<p->vertexNum;i++){
		if(visited[i] != 1){	
			connected_componentsNum++;
			rear = 0;
        		front = 0;
	        	queue[rear]= i;
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
        		                }
                		}
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
	BFSFindEdge(&p);
	printf("%d\n",connected_componentsNum);
	return 0;
}
