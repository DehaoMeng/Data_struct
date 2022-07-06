/*
  拓扑排序的应用
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 20//最大顶点个数
#define VertexType int//顶点数据的类型
typedef enum{false,true} bool;
typedef struct ArcNode{
	int adjvex;//邻接点在数组中的位置下标
	struct ArcNode * nextarc;//指向下一个邻接点的指针
}ArcNode;
typedef struct VNode{
	VertexType data;//顶点的数据域
	int money;
     	ArcNode * firstarc;//指向邻接点的指针
}VNode,AdjList[MAX_VERTEX_NUM];//存储各链表头结点的数组
typedef struct {
	AdjList vertices;//图中顶点及各邻接点数组
	int vexnum,arcnum;//记录图中顶点数和边或弧数
}ALGraph;
//找到顶点对应在邻接表数组中的位置下标
int LocateVex(ALGraph G,VertexType u){
	for (int i=0; i<G.vexnum; i++) {
		if (G.vertices[i].data==u) {
			return i;
		}
	}
	return -1;
}
//创建 AOV 网，构建邻接表
void CreateAOV(ALGraph **G){
	*G=(ALGraph*)malloc(sizeof(ALGraph));
	scanf("%d %d",&((*G)->vexnum),&((*G)->arcnum));	
	for (int i=0; i<(*G)->vexnum; i++) {
		(*G)->vertices[i].data=i;
		(*G)->vertices[i].firstarc=NULL;
		(*G)->vertices[i].money=100;
	}
	VertexType initial,end;
	for (int i=0; i<(*G)->arcnum; i++) { 
		scanf("%d %d",&end,&initial);
		ArcNode *p=(ArcNode*)malloc(sizeof(ArcNode));
	 	p->adjvex=LocateVex(*(*G), end-1);
	 	p->nextarc=NULL;
	 	int locate=LocateVex(*(*G), initial-1);
	 	p->nextarc=(*G)->vertices[locate].firstarc;
	    	(*G)->vertices[locate].firstarc=p;
     	}
}
//结构体定义栈结构
typedef struct stack{
	VertexType data; 
    	struct stack * next;
}stack;
//初始化栈结构
void initStack(stack* *S){
	(*S)=(stack*)malloc(sizeof(stack));
	(*S)->next=NULL;
}
//判断链表是否为空
bool StackEmpty(stack S){
      	if (S.next==NULL) { 
		return true;
      	}
	return false;
}
//进栈，以头插法将新结点插入到链表中
void push(stack *S,VertexType u){
    	stack *p=(stack*)malloc(sizeof(stack));
    	p->data=u;
    	p->next=NULL;
    	p->next=S->next;
    	S->next=p;
}
//弹栈函数，删除链表首元结点的同时，释放该空间，并将该结点中的数据域通过地址传值给变量 i; 
void pop(stack *S,VertexType *i){ 
     	stack *p=S->next; 
     	*i=p->data;
     	S->next=S->next->next;
     	free(p);
}
//统计各顶点的入度
void FindInDegree(ALGraph G,int indegree[]){
//初始化数组，默认初始值全部为 0
	for (int i=0; i<G.vexnum; i++) {
		indegree[i]=0;
	}
//遍历邻接表，根据各链表中结点的数据域存储的各顶点位置下标，在 indegree 数组相应位置+1
	for (int i=0; i<G.vexnum; i++) {
	    	ArcNode *p=G.vertices[i].firstarc; 
	    	while (p) {
		    	indegree[p->adjvex]++;
		    	p=p->nextarc;
	    	}
	}
}
void TopologicalSort(ALGraph G){
     	int indegree[G.vexnum];//创建记录各顶点入度的数组
     	FindInDegree(G,indegree);//统计各顶点的入度
//建立栈结构，程序中使用的是链表
	stack *S;
     	initStack(&S);
//查找度为 0 的顶点，作为起始点
	for (int i=0; i<G.vexnum; i++) {    
		if (!indegree[i]) {
		   	push(S, i);
	     	}
      	}
     	int count=0;
//当栈为空，说明排序完成
	while (!StackEmpty(*S)) {
	     	int index;
//弹栈，并记录栈中保存的顶点所在邻接表数组中的位置
		pop(S,&index);
	     	// printf("%d",G.vertices[index].data);
	     	++count;
//依次查找跟该顶点相链接的顶点，如果初始入度为 1，当删除前一个顶点后，该顶点入度为 0
		for (ArcNode *p=G.vertices[index].firstarc; p; p=p->nextarc) {
			VertexType k=p->adjvex;
			if(G.vertices[k].money <= G.vertices[index].money) G.vertices[k].money = G.vertices[index].money + 1;
		   	if (!(--indegree[k])) {
 //顶点入度为 0，入栈
				push(S, k);
		    	}
	      	}
       	}
//如果 count 值小于顶点数量，表明该有向图有环
	if (count<G.vexnum) {
		printf("POOR!"); return;
     	}else{
		int allmoney=0;
		for(int i=0;i<G.vexnum;i++){
			allmoney+=G.vertices[i].money;
		}
		printf("%d\n",allmoney);
	}
}
int main(){
	ALGraph *G;
	CreateAOV(&G);//创建 AOV网
	TopologicalSort(*G);//进行拓扑排序
   	return 0;
}

