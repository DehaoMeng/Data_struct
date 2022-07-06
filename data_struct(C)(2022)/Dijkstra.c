/*
 * 	This is about Graph and Dijkstra!!
 *	This is a question about geting minimum spanning tree throwing Dijkstra!!! 
 *
 * */

#include<stdio.h>
#include<string.h>
#define MAXSIZE 30
#define MAXCOST 100
typedef struct Graph{
	char vertex[MAXSIZE]; 
	int edge[MAXSIZE][MAXSIZE];
	int vertexNum;
}Graph;

int InitGraph(Graph *p){
	p->vertexNum = 0;
	return 1;
}

int AddVertex(Graph *p,char s){
	p->vertex[p->vertexNum] = s;
	p->vertexNum++;
	return 1;
}

int InitEdge(Graph *p){
	int i,j;
	for(i=0;i<p->vertexNum;i++){
		for(j=0;j<p->vertexNum;j++){
			p->edge[i][j] = MAXCOST;
		}
	}
	return 1;
}

int AddEdge(Graph *p,int i,int j,int weight){
	p->edge[i][j] = weight;
	return 1;
}

int GetVertexNum(Graph *p,char n){
	int i;
	for(i=0;i<p->vertexNum;i++){
		if(p->vertex[i] == n) return i;
	}
	return -1;
}
// This is the Dijkstra describe!!!
int Dijkstra(Graph *p,char start){
	int S[p->vertexNum];
	int U[p->vertexNum];
	int k = GetVertexNum(p,start);
	int i,m;
    	for (i = 0; i < p->vertexNum; i++) {
        	S[i] = 0;
        	U[i] = p->edge[k][i];
    	}	
    	for (m = 0; m < p->vertexNum - 1; m++) {
        	S[k] = 1;
        	for (i = 0; i < p->vertexNum; i++) {
            		if (S[i] != 1) {
                		if (U[i] == MAXCOST && p->edge[k][i] != MAXCOST) {
                    			U[i] = U[k] + p->edge[k][i];
                		} else if (U[i] != MAXCOST && p->edge[k][i] + U[k] < U[i]) {
                    			U[i] =U[k] + p->edge[k][i];
                		}
            		}
        	}
        	U[k] = -1;
        	for (i = 0; i < p->vertexNum; i++) {
            		if (U[k] == -1 && U[i] != -1){
                		k = i;
            		}
            		if (U[i] != -1 && U[i] < U[k]) {
                		k = i;
            		}
        	}
        	printf("%c%c %d\n",p->vertex[GetVertexNum(p,start)],p->vertex[k],U[k]);
    	}
    	return 1;
}
int Print(Graph p){
	int i,j;
	for(i=0;i<p.vertexNum;i++){
		for(j=0;j<p.vertexNum;j++){
			printf("%d ",p.edge[i][j]);
		}
		printf("\n");
	}
	return 0;
}
int main(){
	char s[MAXSIZE];
	Graph p;
	InitGraph(&p);
	scanf("%s",s);
	int i;
	for(i=0;i<strlen(s);i++){
		AddVertex(&p,s[i]);
	}
	InitEdge(&p);
	char m,n;
	int weight;
	while(1){
		getchar();
		scanf("%c",&m);
		if(m == '#') break;
		scanf("%c %d",&n,&weight);
		AddEdge(&p,GetVertexNum(&p,m),GetVertexNum(&p,n),weight);
	}
	getchar();
	scanf("%c",&m);
	Dijkstra(&p,m);
	return 0;
}
