/*
 * 	This is about Graph and Prime!!
 *	This is a question about geting minimum spanning tree throwing Prime!!! 
 *
 * */

#include<stdio.h>
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
			p->edge[i][j] = p->edge[j][i] = MAXCOST;
		}
	}
	return 1;
}

int AddEdge(Graph *p,int i,int j,int weight){
	p->edge[i][j] = p->edge[j][i] = weight;
	return 1;
}

int GetVertexNum(Graph *p,char n){
	int i;
	for(i=0;i<p->vertexNum;i++){
		if(p->vertex[i] == n) return i;
	}
	return -1;
}

int Prime(Graph *p,char start){
	int sumcoast=0;
	int lowcost[p->vertexNum];
       	int closest[p->vertexNum];
	int i, j, k, min;
    	int startNum = GetVertexNum(p,start);
	for (i = 0; i < p->vertexNum;i++) {
		lowcost[i] = p->edge[startNum][i];
		closest[i] = startNum;
	}
    	lowcost[startNum] = MAXCOST;
	closest[startNum] = -1;
	for (i = 0; i < p->vertexNum-1;i++) {
		min = MAXCOST;
        	k = i;
        	for (j = 0; j < p->vertexNum;j++) {
            		if (lowcost[j] != 0 && lowcost[j] < min && closest[j] != -1) {
                		min = lowcost[j];
                		k = j;
            		}
        	}
        	printf("%c%c %d\n",p->vertex[closest[k]],p->vertex[k], min);
        	sumcoast += min;
        	closest[k] = -1;
        	lowcost[k] = MAXCOST;
        	for (j = 0; j < p->vertexNum;j++) {
            		if (closest[j] != -1 && p->edge[k][j] < lowcost[j]) {
                		lowcost[j] = p->edge[k][j];
		                closest[j] = k;
            		}
	        }
    	}
    printf("%d\n",sumcoast);
    return 1;
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
	int i,j,weight;
	while(1){
		scanf("%d",&i);
		if(i == -1) break;
		scanf("%d %d",&j,&weight);
		AddEdge(&p,i,j,weight);
	}
	getchar();
	scanf("%c",&s);
	Prime(&p,s);
	return 0;
}
