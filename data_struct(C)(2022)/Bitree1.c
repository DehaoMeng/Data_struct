#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 256
typedef struct BitNode{
    char val;
    struct BitNode * Lchild;
    struct BitNode * Rchild;
}*BitTree , TreeNode;
int num = 0;
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
// 获取结点高度
int  getHigh(BitTree root){
	int H1,H2;
	if(root == NULL) return 0;
	else{
		H1 = getHigh(root->Lchild);
		H2 = getHigh(root->Rchild);
	}
	return (H1>H2?H1:H2)+1;
}
// 交换度为2的结点
void changeTwoChild(BitTree root){
	if(root == NULL) return;
	if(root->Lchild && root->Rchild) {
		BitTree s = root->Lchild;
		root->Lchild = root->Rchild;
		root->Rchild = s;
	}
	changeTwoChild(root->Lchild);
	changeTwoChild(root->Rchild);
}
// 计算结点左右字数高度相同的结点。
void getNum(BitTree root){
	if (root == NULL) return;
	int H1,H2;
	H1 = getHigh(root->Lchild);
	H2 = getHigh(root->Rchild);
	//printf("%d,%d\n",H1,H2);
	if(H1 == H2) num++;
	getNum(root->Lchild);
	getNum(root->Rchild);
}
// 中序遍历
int InOrder(BitTree root){
	if(root == NULL) return 1;
	else{
		InOrder(root->Lchild);
		printf("%c",root->val);
		InOrder(root->Rchild);
	}
	return 0;
}

int main(){
    BitTree root = NULL ;
    root =creatBitTree(root);
    changeTwoChild(root);
    if (InOrder(root)) printf("NULL");
    printf("\n");
    getNum(root);
    printf("%d",num);
    printf("\n");
}

