#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 256
typedef struct BitNode{
    char val;
    struct BitNode * Lchild;
    struct BitNode * Rchild;
}*BitTree , TreeNode;


BitTree creatBitTree(BitTree root);
 void Preorder_traversal(BitTree root);
 void Level_traversal(BitTree root);
 void visit(BitTree root);
int main(){
    BitTree root = NULL ;
    root =creatBitTree(root);
    Level_traversal(root);
    printf("\n");
}
BitTree creatBitTree(BitTree root){
    char data ;
    scanf("%c",&data);
    if(data == '#'){
        root = NULL;
    }
    else{
        root = (BitTree)malloc(sizeof(TreeNode));
        root->val = data;
        if(!root){ 
            exit(1);
        }
        root->Lchild =creatBitTree(root->Lchild);
        root->Rchild =creatBitTree(root->Rchild);
    }
    return root;
}

void Level_traversal(BitTree root){
    if (root == NULL) {
	    printf("NULL");
	    return;
    }
    BitTree queue[MAXSIZE];
    int rear =0,front =0;
    BitTree p = root ;
    if(p!=NULL){
        //根结点入队(是整个结点入队)
        queue[rear] = p;
        rear=(rear+1)%MAXSIZE ;
        while(rear != front){
            //每次进来首尾指针不同的时候p指向队列中第一个元素，然后p出队,front指针+1
            p =queue[front];
            visit(queue[front]);
            front =(front+1)%MAXSIZE;
            if(p->Lchild!=NULL){
                //入队左子结点
                queue[rear]=p->Lchild;
                rear =(rear+1)%MAXSIZE;
            }
            if(p->Rchild!=NULL){
                //入队右子结点
    		queue[rear]=p->Rchild;
                rear =(rear+1)%MAXSIZE;
                
            }
        }
    }
}
void visit(BitTree root){
    printf("%c",root->val);
}

